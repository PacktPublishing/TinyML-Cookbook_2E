import cv2
import numpy as np
import serial

port = '/dev/ttyACM0'
baudrate = 115200

# Initialize serial port
ser = serial.Serial()
ser.port     = port
ser.baudrate = baudrate

# Initialize camera with OpenCV
cam = cv2.VideoCapture(0)

cam.set(cv2.CAP_PROP_BUFFERSIZE, 1)

ser.open()
ser.reset_input_buffer()

def serial_readline(obj):
  data = obj.readline() # read a '\n' terminated line
  return data.decode("utf-8").strip()

while True:
  data_str = serial_readline(ser)

  if str(data_str) == "<cam-read>":
    print("Read request received")
    ret, img_bgr = cam.read()

    h0 = img_bgr.shape[0]
    w0 = img_bgr.shape[1]
    h1 = min(h0, w0)
    w1 = h1

    img_cropped = img_bgr[0:w1, 0:h1]
    img_resized = cv2.resize(img_cropped, (76, 76), interpolation=cv2.INTER_LINEAR)

    img_gray = cv2.cvtColor(img_resized, cv2.COLOR_BGR2GRAY)

    data = bytearray(img_gray.astype(np.uint8))
    ser.write(data)

    cv2.imshow("Captured image", img_resized)

    if cv2.waitKey(1) == ord('q'):
      break

cv2.destroyAllWindows()
cam.release()
