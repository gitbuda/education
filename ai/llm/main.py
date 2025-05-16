# 1. tokenizer        DONE
# 2. model            DONE
# 3. run example      DONE
# 4. generate dataset DONE
# 5. prep inputs      NEXT
#     a) template
#     b) validation
# 6. multi GPU        https://gemini.google.com/app/b9c2f2b81d58fe1c

import os
import re
from datasets import load_dataset, config
import torch
from torch.nn.parallel import DistributedDataParallel as DDP
from transformers import AutoModelForCausalLM, AutoTokenizer
import datetime

#### DATASET
# Login using e.g. `huggingface-cli login` to access this dataset.
print("datasets are cached under: ", config.HF_DATASETS_CACHE)
text2cypher_2025v1 = "neo4j/text2cypher-2025v1"
ds = load_dataset(text2cypher_2025v1)
print(ds)
print(ds['train'][0]["schema"])
print(ds['train'][0]["question"])
print(ds['train'][0]["cypher"])

model_path = "/tmp/DeepSeek-R1-Distill-Qwen-1.5B"
model_path = "/tmp/Qwen3-0.6B" # just to test on a smaller scale


def inference():
    #### MODEL
    model = AutoModelForCausalLM.from_pretrained(model_path)
    tokenizer = AutoTokenizer.from_pretrained(model_path)
    print(tokenizer)
    #### DEVICE
    # Check if MPS (Metal Performance Shaders, Apple's GPUs) is available and use it if so.
    if torch.backends.mps.is_available():
        device = "mps"
    else:
        device = "cuda" if torch.cuda.is_available() else "cpu"
    model.to(device)

    eos = tokenizer.eos_token
    eot = "<|EOT|>"
    input_text = f"""Generate me a Cypher graph query for the question:
    {ds['train'][0]["question"]}
    Given the schema:
    {ds['train'][0]["schema"]}
    {eot}"""
    print(input_text)
    input_ids = tokenizer.encode(input_text, return_tensors="pt").to(device)
    with torch.no_grad():
        output = model.generate(input_ids, max_length=4096)
        generated_text = tokenizer.decode(output[0])
        print(generated_text)
        pattern = r"```cypher\n(.*?)```"
        matches = re.findall(pattern, generated_text, re.DOTALL)
        for i, match in enumerate(matches):
            print(f"Cypher block {i+1}:\n{match}")


def init_process(rank, world_size):
    os.environ["MASTER_ADDR"] = "127.0.0.1"
    os.environ["MASTER_PORT"] = "29500"
    torch.distributed.init_process_group(
        backend="nccl",
        rank=rank,
        world_size=world_size,
        timeout=datetime.timedelta(seconds=5400),
    )
    torch.cuda.set_device(rank)


def dist_check():
    if torch.distributed.is_initialized():
        print("Distributed initialized!")
        print(f"Backend: {torch.distributed.get_backend()}")
        print(f"Rank: {torch.distributed.get_rank()} / World Size: {torch.distributed.get_world_size()}")
    else:
        print("Distributed not initialized.")


def dist_cleanup():
    torch.distributed.destroy_process_group()


def train(rank, world_size):
    init_process(rank, world_size)
    dist_check()
    try:
        model = AutoModelForCausalLM.from_pretrained(model_path).to(rank)
        ddp_model = DDP(model, device_ids=[rank])
        optimizer = torch.optim.AdamW(ddp_model.parameters(), lr=1e-4)
    finally:
        dist_cleanup()


def init_distributed():
    world_size = torch.cuda.device_count()
    torch.multiprocessing.spawn(train, args=(world_size,), nprocs=world_size, join=True)
    if torch.distributed.is_initialized():
        print("Distributed initialized!")
        print(f"Backend: {torch.distributed.get_backend()}")
        print(f"Rank: {torch.distributed.get_rank()} / World Size: {torch.distributed.get_world_size()}")
    else:
        print("Distributed not initialized.")


if __name__ == "__main__":
    init_distributed()
