import numpy as np
import uuid
import serial
import soundfile as sf
from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

def serial_readline(obj):
	data = obj.readline()
	return data.decode("utf-8").strip()

port = '/dev/ttyACM0'
baudrate = 115600

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
  ad_sr_str  = serial_readline(ser)
  ad_len_str = serial_readline(ser)
  ad_sr  = int(ad_sr_str)
  ad_len = int(ad_len_str)

  ad_buf = np.empty((ad_len), dtype=np.int16)

  print("Reading samples:", ad_sr, ad_len)
  for i in range(0, ad_len):
    sample_str = serial_readline(ser)
    ad_buf[i] = int(sample_str)

  key = input("Save audio? [y] for YES: ")
  if key == 'y':
    str_label = '''Provide the label's name or leave it empty to use [{}]: '''.format(label)
    label_new = input(str_label)
    if label_new != '':
      label = label_new
    unique_id = str(uuid.uuid4())
    filename = label + "_"+ unique_id + ".wav"
    sf.write(filename, ad_buf, ad_sr, subtype='PCM_16')
    print("File", filename, "saved")
    str_gid = '''Provide the Google Drive folder ID or leave it empty to use [{}]: '''.format(gdrive_id)
    gdrive_id_new = input(str_gid)
    if gdrive_id_new != '':
      gdrive_id = gdrive_id_new
    gfile = drive.CreateFile({'parents': [{'id': gdrive_id}]})
    gfile.SetContentFile(filename)
    gfile.Upload()
    print("Audio file uploaded")
  else:
    print("Audio file discarded")