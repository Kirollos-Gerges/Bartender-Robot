from picamera import PiCamera
from time import sleep
import cv2
import pytesseract
import numpy as np
from pytesseract import Output
import re
from datetime import datetime, timedelta
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(21, GPIO.IN)
#sleep(20)
if GPIO.input(21):
    camera.capture('/home/pi/Downloads/vjllr3.jpg')
    camera.stop_preview()
print("The GPU Pin value is: ")
print(GPIO.input(21))

camera = PiCamera()
#camera.start_preview()
#sleep(20)
if GPIO.input(21):
    camera.capture('/home/pi/Downloads/vjllr3.jpg')
    camera.stop_preview()
    
img = cv2.imread('vjllr3.jpg')
resize = cv2.resize(img,(640,480),interpolation= cv2.INTER_LINEAR)
crop = img[115:164, 530:720]
recrop = cv2.resize(crop,(800,400),interpolation= cv2.INTER_LINEAR)

print(img.shape)
print(resize.shape)
print(crop.shape)
print(recrop.shape)

def get_grayscale(image):
    return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

def thresholding(image):
    return cv2.threshold(image, 100, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)[1]

#import cv2norm_img = np.zeros((image.shape[0], image.shape[1]))

def normalize(image):
    norm_img = np.zeros((800,800))
    return cv2.normalize(image, norm_img, 20, 255, cv2.NORM_MINMAX)

def gaussian(image):
    return cv2.GaussianBlur(image, (3, 3), 0)

def canny(image):
    return cv2.Canny(image,50,150)

def dilate(image):
    kernel = np.ones((3,1),np.uint8)
    #kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(3,3))
    return cv2.dilate(image,kernel,iterations = 1)

#crop = normalize(crop)
#recrop = normalize(recrop)

#crop = get_grayscale(crop)
#recrop = get_grayscale(recrop)

#crop = thresholding(crop)
#recrop = thresholding(recrop)

#crop = gaussian(crop)
#recrop = gaussian(recrop)

#crop = dilate(crop)
#recrop = dilate(recrop)

#recrop = cv2.resize(recrop,(800,300),interpolation= cv2.INTER_LINEAR)

#crop = canny(crop)
#recrop = canny(recrop)
#crop = get_grayscale(crop)
#crop = thresholding(crop)
#crop = thresholding(crop)
#recrop = thresholding(recrop)

cv2.imshow('common', recrop)
cv2.imwrite("llrcroppedagain.jpg",crop)

image = crop

txt_string = pytesseract.image_to_string(image)
text_string = txt_string.replace("/","-")
#text_string = "My DOB is 09-14-1999"
leg_string = "Legal DOB is 03/30/2001"
legal_string = leg_string.replace("/","-")

print(text_string)
print(legal_string)

search_str = re.search(r'\d{2}-\d{2}-\d{4}',text_string)
print(search_str)

search_legal = re.search(r'\d{2}-\d{2}-\d{4}',legal_string)
print(search_legal)

birth_date = datetime.strptime(search_str.group(), '%m-%d-%Y').date()
print(birth_date)

legal_date = datetime.strptime(search_legal.group(), '%m-%d-%Y').date()
print(legal_date)

current_date = datetime.now()
print(current_date)

print(birth_date<legal_date)

if(birth_date<legal_date):
    
    print("YOU CAN DRINK")

cv2.imshow('img', image)