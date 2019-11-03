#!/usr/bin/python3

from itertools import combinations
from random import shuffle


def similar_groups(g1, g2):
    for member in g1:
        if member in g2:
            return True
    return False


def group_naive_scheduling(candidates, group_size):
    all_groups = list(set(combinations(candidates, group_size)))
    previous_group = None
    while len(all_groups) > 2 * len(candidates) / group_size:
        shuffle(all_groups)
        selected_group = all_groups[-1]
        if previous_group is None or not similar_groups(previous_group,
                                                        selected_group):
            previous_group = selected_group
            print(','.join(list(map(lambda x: str(x), selected_group))))
            all_groups.pop()


if __name__ == '__main__':
    candidates = range(1, 10)
    group_size = 3
    group_naive_scheduling(candidates, group_size)
