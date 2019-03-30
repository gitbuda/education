#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cv2 as cv

RED_COLOR = (255, 0, 0)
MEDIUM_THICKNESS = 2


def show(label, img, wait=True, show=True):
    '''
    Show the img.
    '''
    if show is True:
        cv.imshow(label, img)
        if wait is True:
            cv.waitKey(0)


original_image = cv.imread('data/Chironomus_plumosus_MHNT.jpg',
                           cv.IMREAD_COLOR)
show("Original image", original_image)

img = original_image.copy()
img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
show("Grayscale image", img)

ret, thresh = cv.threshold(img, 127, 255, 0)
show("Trashold image", img)

cnt, _ = cv.findContours(thresh, cv.RETR_LIST, cv.CHAIN_APPROX_SIMPLE)
for x, y, w, h in [cv.boundingRect(c) for c in cnt]:
    cv.rectangle(original_image, (x, y), (x + w, y + h),
                 RED_COLOR, MEDIUM_THICKNESS)
show('Bounding boxes', original_image)
