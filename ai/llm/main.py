# 1. tokenizer        DONE
# 2. model            DONE
# 3. run example      DONE
# 4. generate dataset NEXT
# 5. single GPU
# 6. multi-GPU

import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

# model_path = "/tmp/Qwen2-0.5B-Instruct"
model_path = "/tmp/DeepSeek-R1-Distill-Qwen-1.5B"
model = AutoModelForCausalLM.from_pretrained(model_path)
tokenizer = AutoTokenizer.from_pretrained(model_path)

# Check if MPS (Metal Performance Shaders, Apple's GPUs) is available and use it if so.
if torch.backends.mps.is_available():
    print("MPS available")
    device = "mps"
else:
    print("CPU training")
    device = "cpu"
model.to(device)

# Example inference.
input_text = "Your input text here"
input_ids = tokenizer.encode(input_text, return_tensors="pt").to(device)

# Generate text
with torch.no_grad():
    output = model.generate(input_ids, max_length=50)
    generated_text = tokenizer.decode(output[0])
    print(generated_text)
