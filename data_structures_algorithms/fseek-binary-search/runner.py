#!/usr/bin/env python
# -*- coding: utf-8 -*-

from statistics import median
from math import log2
import subprocess


def runs(cmd):
    data = {}
    for size in [2**i for i in range(5, 19)]:
        it_times = []
        for it in range(10):
            process = subprocess.run(
                [cmd, '%s' % size], check=True, stdout=subprocess.PIPE)
            output = process.stdout
            times = output.decode('utf-8').strip()
            it_times.append(times)
        data[size] = it_times
    return data


rbs_data = runs('./build/rbs')
fbs_data = runs('./build/fbs')

print("RBS")
for size, data in rbs_data.items():
    print(log2(size), median(
        map(lambda x: int(x.split(',')[0]) + int(x.split(',')[1]), data)))

print("FBS")
for size, data in fbs_data.items():
    print(log2(size), median(map(lambda x: int(x), data)))
