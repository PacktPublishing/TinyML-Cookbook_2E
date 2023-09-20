import serial
import soundfile as sf
import numpy as np

def serial_readline(obj):
  data = obj.readline()
  return data.decode("utf-8")

baudrate  = 115200
port      = '/dev/ttyACM0'

ser = serial.Serial()
ser.port     = port
ser.baudrate = baudrate
ser.open()
ser.reset_input_buffer()

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

  print("Captured audio: [Sample-rate|Num-samples]", ad_sr, ad_len)
  sf.write("test.wav", ad_buf, ad_sr, subtype='PCM_16')

