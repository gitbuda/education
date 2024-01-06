#!/bin/bash -e
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$script_dir"
if [ ! -d "nvbandwidth" ]; then
  git clone https://github.com/NVIDIA/nvbandwidth
fi
cd nvbandwidth
./debian_install.sh
