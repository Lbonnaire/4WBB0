from pynput.keyboard import Key, Controller
import time

keyboard = Controller()

time.sleep(5)
while 1:
	time.sleep(0.5)
	keyboard.press(Key.enter)
	keyboard.release(Key.enter)