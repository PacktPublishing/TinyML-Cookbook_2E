import numpy as np
import uuid
import serial
from PIL import Image
from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

def serial_readline(obj):
  data = obj.readline()
  return data.decode("utf-8").strip()

port = '/dev/ttyACM0'
baudrate = 115200

# Initialize serial port
ser = serial.Serial()
ser.port     = port
ser.baudrate = baudrate

ser.open()
ser.reset_input_buffer()

label = ""
gdrive_id = ""

gauth = GoogleAuth()
gauth.LocalWebserverAuth()

drive = GoogleDrive(gauth)

while True:
  data_str = serial_readline(ser)

  if str(data_str) == "<image>":
    w_str = serial_readline(ser)
    h_str = serial_readline(ser)
    w = int(w_str)
    h = int(h_str)
    c = int(3)
    image = np.empty((h, w, c), dtype=np.uint8)

    print("Reading frame:", w, h)
    for y in range(0, h):
      for x in range(0, w):
        for d in range(0, c):
          data_str = serial_readline(ser)
          image[y][x][d] = int(data_str)

    data_str = serial_readline(ser)
    if str(data_str) == "</image>":
      print("Captured frame")
      image_pil = Image.fromarray(image)
      crop_area = (0, 0, h, h)
      image_cropped = image_pil.crop(crop_area)
      image_cropped.show()
      key = input("Save image? [y] for YES: ")
      if key == 'y':
        str_label = '''Provide the label's name or leave it empty to use [{}]: '''.format(label)
        label_new = input(str_label)
        if label_new != '':
          label = label_new
          unique_id = str(uuid.uuid4())
          filename = label + "_"+ unique_id + ".png"
          image_cropped.save(filename)
          print("File", filename, "saved")
          str_gid = '''Provide the Google Drive folder ID or leave it empty to use [{}]: '''.format(gdrive_id)
          gdrive_id_new = input(str_gid)
          if gdrive_id_new != '':
            gdrive_id = gdrive_id_new
            gfile = drive.CreateFile({'parents': [{'id': gdrive_id}]})
            gfile.SetContentFile(filename)
            gfile.Upload()
            print("Image file uploaded")
          else:
            print("Image discarded")
    else:
      print("Error capture image")
