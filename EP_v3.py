from pynput import keyboard
from pynput.keyboard import Key, Controller
import msvcrt

keyboard = Controller()

while True:
	try:
		if(keyboard.is_pressed('q')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('w')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('e')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('a')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('s')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('d')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('z')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('c')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('l')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('1')): #keypad numbers
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('2')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('3')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('4')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('5')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		elif (keyboard.is_pressed('6')):
			keyboard.press(Key.enter)
			keyboard.release(Key.enter)
		else:
			pass
	except: #if any other key is pressed the script ends (do not FUCK UP!)
		break

