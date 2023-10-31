from pynput.keyboard import Key, Controller
import msvcrt

keyboard = Controller()

key = " "

while 1:
	key = msvcrt.getch()
	if(key != " "):
		keyboard.press(Key.enter)
		key = " "
		keyboard.release(Key.enter)
		
	

