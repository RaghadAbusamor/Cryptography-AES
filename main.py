import base64
import numpy as np
from matplotlib import image
import matplotlib.pyplot as plt
import os
import cv2
os.environ["OPENCV_IO_MAX_IMAGE_PIXELS"] = pow(2,100).__str__()
def decimalToBinary(n):
    return bin(n).replace("0b", "")
# load image as pixel array
image = image.imread('lena15.jpg')
plt.imshow(image)
plt.show()
# summarize shape of the pixel array
print("image type is",image.dtype)
print("image size is",image.shape)
# data(watermark)after converting to binary
imageArray = np.array(plt.imread('lena15.jpg'), dtype=np.uint8)
# this is data you want to hide it in the img.
data="11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"

#convert RGb matrix to binary matrix
s=""
for x in range(512):
     for y in range(512):
         for z in range(3):
             f=imageArray[x,y,z]
             n=decimalToBinary(f)
             o=len(n)
             while o < 8:
                n='0'+n
                o=o+1


             s=s+n

print("step1:the image convert to binary")
arr1=[]

for b in range(len(s)):
    arr1.append(s[b])

#store the image bits to file  :
f= open("imageBits.txt", "w")
f.writelines(["%s" % item  for item in arr1])
f.close()
#read the cipher text from cpp code :
memory = np.zeros(shape=[512, 512, 3], dtype=np.uint8)
file = open('cipher.txt', 'rb')
cipher = file.read()
strCipher = base64.b64decode(cipher)
file.close()
#convert it to array
enc = np.frombuffer(strCipher, dtype=np.uint8)
cv2.imwrite("encImage.bmp", enc)
finalImage = cv2.imread('encImage.bmp')
height, width, channels = finalImage.shape
res = cv2.resize(finalImage, dsize=(512, 512), interpolation=cv2.INTER_CUBIC)

# Write to a file to show conversion worked
cv2.imwrite("finalImage.png", res)
plt.imshow(res)
plt.show()
print("the encryption process Done ")