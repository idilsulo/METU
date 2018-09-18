import cv2
import numpy as np

filename = "images.dat"

with open(filename) as fn:
	images = fn.readlines() 

images = [x.strip() for x in images]

print(images)

#for item in images:
#	img = cv2.imread(item)
#	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#	
#	sift = cv2.xfeatures2d.SIFT_create()
#	kp, des = sift.detectAndCompute(gray,None)

#	descriptors.append(des)

print(descriptors)
#print(len(des))




