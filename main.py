import serial
import time
from pynput.keyboard import Key, Controller
from win32gui import GetWindowText, GetForegroundWindow

keyboard = Controller()


ser = serial.Serial('COM6', 9600)
while True:
    currentWindow = GetWindowText(GetForegroundWindow())
    time.sleep(0.1)
    input = ser.read().decode()
    if currentWindow[:7] == 'csTimer':

        try:
            print(int(input))
            keyboard.press(str(input))
            keyboard.release(str(input))
        except:
            print('done')
            keyboard.press(Key.enter)
            keyboard.release(Key.enter)


