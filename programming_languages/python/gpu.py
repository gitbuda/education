import sys

# NOTE: With nccl b6d7438d3145a619f924dbbca6c96db21fab716e on 2023-11-20
#                 -> g++-10 is required
#       export CC=/usr/bin/gcc-10
#       export CXX=/usr/bin/g++-10
#       export CPPFLAGS=-I/usr/include/c++/10
#       export was not good enough -> /usr/bin/gcc&g++ -> gcc&g++-10
#       TODO(gitbuda): Figure out still doesn't work...
#       before pip install cupy
import cupy as cp


if cp.cuda.runtime.getDeviceCount() > 0:
    with cp.cuda.Device(0):
        x = cp.array([1, 2, 3, 4, 5])
        print(x.device)
        print(x.mean())
else:
    print("No GPUs available")
    sys.exit(1)
