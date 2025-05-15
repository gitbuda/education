#!/bin/bash

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
