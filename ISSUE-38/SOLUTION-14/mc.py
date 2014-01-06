'''
Usage:
------
    mc.py [<image>]
    red circle shows center of mass

Keys:
-----
    ESC   - exit

'''

import cv2
import numpy as np

def draw(image, cont):
    M = cv2.moments(cont)
    print M

    cv2.drawContours(drawing,[cont],-1,(0, 255, 0),1)
    cx = int(M['m10']/M['m00'])
    cy = int(M['m01']/M['m00'])
    print cx, cy
    cv2.circle(drawing, (cx, cy), 2, (0, 0, 255))


if __name__ == '__main__':
    import sys
    try: image_src = sys.argv[1]
    except: image_src = '100x100.png'

    img = cv2.imread(image_src)
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    thresh = 10
    edge = cv2.Canny(gray, thresh,thresh*2, apertureSize=5)
    drawing = np.zeros(img.shape,np.uint8) # Image to draw the contours
    contours,hierarchy = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    ##for cnt in contours:
    ##    draw(drawing, cnt)

    draw(drawing, contours[0])


    while True:
        cv2.imshow('img', img)
        cv2.imshow('edges', edges)
        cv2.imshow('cnt', drawing)

        if 0xFF & cv2.waitKey(5) == 27:
            break

    cv2.destroyAllWindows()
