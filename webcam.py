from urllib.request import urlopen
import cv2
import numpy as np
from ssl import SSLContext,PROTOCOL_TLSv1

#url='http://192.168.43.139:8080/shot.jpg'
url='http://192.168.43.139:8080/shot.jpg'

x = urlopen("http://127.0.0.1:8000/suny")
print(x.read())

# while True:
# 	gcontext = SSLContext(PROTOCOL_TLSv1)
# 	info = urlopen(url, context=gcontext)
# 	imgNp=np.array(bytearray(info.read()),dtype=np.uint8)
# 	img=cv2.imdecode(imgNp,-1)

# 	# all the opencv processing is done here
# 	cv2.imshow('test',img)
# 	if ord('q')==cv2.waitKey(10):
# 		exit(0)