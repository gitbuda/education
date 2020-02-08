#!/usr/bin/env python
# -*- coding: utf-8 -*-

from statistics import median
from math import log2
import subprocess

import matplotlib.pyplot as plt
from pyplotcomponents.linear_multiline import LinearMultiline


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

rbs_x = []
rbs_y_load = []
rbs_y_total = []
for size, data in rbs_data.items():
    rbs_x.append('2^%s' % int(log2(size)))
    rbs_y_load.append(median(
        map(lambda x: int(x.split(',')[0]), data)))
    rbs_y_total.append(median(
        map(lambda x: int(x.split(',')[0]) + int(x.split(',')[1]), data)))

fbs_x = []
fbs_y = []
for size, data in fbs_data.items():
    fbs_x.append('2^%s' % int(log2(size)))
    fbs_y.append(median(map(lambda x: int(x), data)))

fig = plt.figure(figsize=(10, 10))
chart = LinearMultiline(
    fig,
    'RAM vs fseek Binary Search',
    'Size',
    'Time (ns)',
    grid=True)
chart.plot(rbs_x, rbs_y_load, '-', label='RAM Load')
chart.plot(rbs_x, rbs_y_total, '-', label='RAM Load + Binary Search')
chart.plot(fbs_x, fbs_y, '-', label='fseek Binary Search')
chart.add_legend()
chart.show_or_save()
