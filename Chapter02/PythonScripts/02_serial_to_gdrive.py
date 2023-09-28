import serial
import time
from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive
from argparse import ArgumentParser

def serial_readline(obj):
  data = obj.readline()
  return data.decode("utf-8")

def create_file(filename, content):
  text_file = open(filename, "w")
  text_file.write(content)
  text_file.close()

def gdrive_upload(obj, filename, gdrive_id):
  gfile = drive.CreateFile({'parents': [{'id': gdrive_id}]})
  gfile.SetContentFile(filename)
  gfile.Upload()

parser = ArgumentParser()
parser.add_argument("--baudrate", dest="baudrate", help="Baudrate", type=int, required=True)
parser.add_argument("--port", dest="port", help="Port", type=str, required=True)
parser.add_argument("--logging_time_s", dest="logging_time_s", help="The amount of time (in seconds) required to record the serial transmission", type=int, required=True)
args = parser.parse_args()

port       = args.port     # e.g. /dev/ttyACM0
baudrate   = args.baudrate # e.g. 9600
max_time_s = args.logging_time_s

ser = serial.Serial()
ser.port     = port
ser.baudrate = baudrate

ser.open()
ser.flushInput()

text = ""

start_s   = time.time()
elapsed_s = 0
while(elapsed < max_time_s):
  text   += serial_readline(ser)
  end_s   = time.time()
  elapsed = end_s - start_s

filename = "test.log"

# Create file
create_file(filename, text)

# Upload to Google Drive
gauth = GoogleAuth()
gauth.LocalWebserverAuth()
drive = GoogleDrive(gauth)

# Replace with your Google ID
gdrive_id = ""

gdrive_upload(drive, filename, gdrive_id)