#include "include/keyboard.h"
#include "include/videoDriver.h"





static char* KEYS_VALUES[] = {"", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", 			// 0 - 10
									"0", "'", "¿", "BACKSPACE", "    ", "q", "w", "e", "r", "t",// 11 - 20
								  	"y", "u", "i", "o", "p", "´", "+", "", "", "a",				// 21 - 30
									"s", "d", "f", "g", "h", "j", "k", "l", "", "{", 			// 31 - 40
								  	"|", "LSHIFT", "}", "z", "x", "c", "v", "b", "n", "m",  	// 41 - 50
								  	",", ".", "-", "", "*", "ALT", " ", "", "", "",				// 51 - 60
								  	"", "", "", "", "", "", "", "", "", "", 					// 61 - 70
								  	"7", "UARR", "9", "-", "LARR", "5", "RARR", "+", "1", "2",  // 71 - 80
								  	"3", "0", ".", "", "", "", "", "", "", ""}; 				// 81 - 90

static char* SHIFT_KEYS_VALUES[] = {"", "ESC", "!", "\"", "#", "$", "%", "&", "/", "(", ")", 	// 0 - 10
									"=", "?", "¡", "BACKSPACE", "    ", "Q", "W", "E", "R", "T",// 11 - 20
								  	"Y", "U", "I", "O", "P", "¨", "*", "", "", "A",				// 21 - 30
									"S", "D", "F", "G", "H", "J", "K", "L", "", "[", 			// 31 - 40
								  	"°", "LSHIFT", "]", "Z", "X", "C", "V", "B", "N", "M",  		// 41 - 50
								  	";", ":", "_", "", "*", "ALT", " ", "", "", "",				// 51 - 60
								  	"", "", "", "", "", "", "", "", "", "", 					// 61 - 70
								  	"7", "8", "9", "-", "4", "5", "6", "+", "1", "2", 			// 71 - 80
								  	"3", "0", ".", "", "", "", "", "", "", ""}; 				// 81 - 90

void
update_screen(char keyCode){
	// Key Pressed
	if (keyCode >= 0 && keyCode < mapSize) {
		switch(keyCode){
			case 28: printNewLine();
				 break;
			case 14: backspace();
				 break;
			case 42:
			case 54:
			case 58: shiftPressed*=-1;
				 break;
			case 29: ctrlPressed *= -1;
				  break;
			case 72: moveCursorUp();
				break;
			case 80: moveCursorDown();
				break;
			case 75: moveCursorLeft();
				break;
			case 77: moveCursorRight();
				break;
			case 83: supr();
				break;
			default:
				if (shiftPressed == 1) {
					print(SHIFT_KEYS_VALUES[keyCode], 0x07);
				} else {
					print(KEYS_VALUES[keyCode], 0x07);
				}
				break;
		}
	}

	// Key Released
 else {
		if (keyCode == 170 || keyCode == 182) {			// L/R Shift
			shiftPressed *= -1;
		}
		if (keyCode == 157) {							// Ctrl
			ctrlPressed *= -1;
		}
	}

}

void add_to_buffer(){
	char key_code = _read_keyboard();
	buffer[(write_index++) % (BUFFER_SIZE-1)]= key_code;
	update_screen(key_code);
}

char read_from_buffer(){
		if(read_index > write_index){
			//todo excepcion o algo;
		}if(read_index == write_index){
			//esperando teclas
		}
		char key = buffer[(read_index++) %(BUFFER_SIZE-1)];
			return key;
}
