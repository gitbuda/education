#!/bin/bash

sudo apt install python3-pip python3-virtualenv

# TODO: set and activate the virtualenv

# Install stable version of PyTorch libraries using pip
pip install torch torchvision torchao
# # Or nightly install for latest features
# pip install --pre torch torchvision torchao --index-url https://download.pytorch.org/whl/nightly/cu126 # full options are cpu/cu118/cu121/cu124/cu126/xpu
pip install torchtune

# Download DeepSeek-V3 https://huggingface.co/deepseek-ai/DeepSeek-V3-Base#61-inference-with-deepseek-infer-demo-example-only
# rm -rf DeepSeek-V3
if [ ! -d DeepSeek-V3 ]; then
  git clone https://github.com/deepseek-ai/DeepSeek-V3.git
fi

# tune download org/model --output-dir /tmp/model
if [ ! -d DeepSeek-R1-Distill-Qwen-1.5B ]; then
  tune download deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B --output-dir /tmp/DeepSeek-R1-Distill-Qwen-1.5B
fi

# tune cp config local_path

## Resources
# pure  -> https://github.com/aws-samples/amazon-sagemaker-llm-fine-tuning-remote-decorator/blob/main/deepseek/deepseek-r1-distilled-qwen-1.5b-qlora-remote-decorator_qa.ipynb
#       -> https://techcommunity.microsoft.com/blog/machinelearningblog/fine-tuning-deepseek-r1-distill-llama-8b-with-pytorch-fsdp-qlora-on-azure-machin/4377965
#
# tune  -> https://github.com/pytorch/torchtune
# AMD   -> https://rocm.blogs.amd.com/artificial-intelligence/torchtune/README.html
#       -> https://github.com/nktice/AMD-AI/blob/main/dev.md
#
#       -> https://github.com/modelscope/ms-swift
# issue -> https://github.com/pytorch/torchtune/issues/2287
#       -> https://huggingface.co/deepseek-ai/deepseek-vl-1.3b-chat/discussions/1
