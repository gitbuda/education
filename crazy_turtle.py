#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Solution for the crazy turtle game board.
'''

import sys

CARD_SIDES_NO = 4
BOARD_SIZE = 9
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
        rotated_card[side] = rotated[index]
    return rotated_card


class CTCard:
    '''
    Contains all rotations for a card in the dictionary.
    '''
    def __init__(self, card):
        self.rotations = {}
        for angle in range(CARD_SIDES_NO):
            self.rotations[angle] = card_rotation(card, angle)


def dfs(build, rest):
    if len(build) == 0:
        for index, card in enumerate(rest):
            for angle in range(CARD_SIDES_NO):
                dfs([(card, angle)], remove_from_list(rest, index))
    elif len(build) == BOARD_SIZE:
        print build
    else:
        print build, rest

if __name__ == '__main__':
    '''
    Call DFS to solve the problem.
    '''
    cards_definition = list(sys.argv[1])
    cards = [CTCard(card) for card in chunks(cards_definition, CARD_SIDES_NO)]
    dfs([], range(BOARD_SIZE))
