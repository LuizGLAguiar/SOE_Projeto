import cv2
import matplotlib.pyplot as plt 
import cvlib as cv
from cvlib.object_detection import draw_bbox

cap = cv2.VideoCapture(1)
ret, frame = cap.read()
cap.release()
box, label, c_score = cv.detect_common_objects(frame, model='yolov3-tiny')
output = draw_bbox(frame,box,label,c_score)
plt.imshow(output)
plt.show()

#image = cv2.imread('image2.jpg', -1) 

#box, label, c_score = cv.detect_common_objects(image, model='yolov3-tiny')
#output = draw_bbox(image,box,label,c_score)
#plt.imshow(output)
#plt.show()
#print('number of people: ', label.count('person'))