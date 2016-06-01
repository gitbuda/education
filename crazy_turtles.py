#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Solution for the crazy turtle game board.
./crazy_turtles.py 436313711407564402360467264555227520
'''

import sys

CARD_SIDES_NO = 4
BOARD_SIZE = 9
BOARD_SIZE_Y = 3
SIDES = list('LTRB')


def rotate(l, n):
    '''
    Rotate list l clockwise for n.
    Args:
        l: list
        n: rotation size
    Returns:
        rotated list
    '''
    return l[-n:] + l[:-n]


def chunks(l, n):
    '''
    Yield successive n-sized chunks from l.
    '''
    for i in xrange(0, len(l), n):
        yield l[i:i+n]


def remove_from_list(l, index):
    '''
    Removes element at the index from the list.
    '''
    return l[:index] + l[index + 1:]


def card_rotation(card, angle):
    '''
    Args:
        card: list of elements in LTRB order
        angle: rotation angle, 0 -> 0   clockwise
                               1 -> 90  clockwise
                               2 -> 180 clockwise
                               3 -> 270 clockwise
    Returns:
        dict: { 'L': X, 'T': Y, 'R': Z, 'B': W }
    '''
    rotated = rotate(card, angle)
    rotated_card = {}
    for index, side in enumerate(SIDES):
        rotated_card[side] = int(rotated[index])
    return rotated_card


class CTCard:
    '''
    Contains all rotations for a card in the dictionary.
    '''
    def __init__(self, card):
        self.rotations = {}
        for angle in range(CARD_SIDES_NO):
            self.rotations[angle] = card_rotation(card, angle)


def neighbor_card_top(cards, build):
    '''
    Returns:
        top card if exists else None
    '''
    index = len(build)
    if index < BOARD_SIZE_Y:
        return None
    card_index = index - BOARD_SIZE_Y
    neighbor_index, angle = build[card_index]
    return cards[neighbor_index].rotations[angle]


def neighbor_card_left(cards, build):
    '''
    Returns:
        left card if exists else None
    '''
    index = len(build)
    if index % BOARD_SIZE_Y == 0:
        return None
    card_index = index - 1
    neighbor_index, angle = build[card_index]
    return cards[neighbor_index].rotations[angle]


def dfs(cards, build, rest):
    '''
    Find the solutions with the DFS algorithm.
    '''
    if len(build) == 0:
        # at the start any card could be a solution part
        for index, card in enumerate(rest):
            for angle in range(CARD_SIDES_NO):
                dfs(cards, [(card, angle)], remove_from_list(rest, index))
    elif len(build) == BOARD_SIZE:
        # if DFS reaches leaf of the DFS tree solution is found
        print 'SOLUTION: %s' % str(map(lambda x: (x[0] + 1, x[1]), build))
    else:
        # call recursive DFS only if top and left card matches
        for index, card in enumerate(rest):
            for angle in range(CARD_SIDES_NO):
                chosen = cards[card].rotations[angle]
                neighbor_top = neighbor_card_top(cards, build)
                neighbor_left = neighbor_card_left(cards, build)
                doDFS = True
                if neighbor_top is not None \
                   and abs(neighbor_top['B'] - chosen['T']) != 4:
                    doDFS = False
                if neighbor_left is not None \
                   and abs(neighbor_left['R'] - chosen['L']) != 4:
                        doDFS = False
                if doDFS:
                    dfs(cards, build + [(card, angle)],
                        remove_from_list(rest, index))


if __name__ == '__main__':
    '''
    Call DFS to solve the problem.
    '''
    cards_definition = list(sys.argv[1])
    cards = [CTCard(card) for card in chunks(cards_definition, CARD_SIDES_NO)]
    dfs(cards, [], range(BOARD_SIZE))
