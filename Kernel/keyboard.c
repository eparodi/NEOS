#include "include/keyboard.h"
#include "include/videoDriver.h"
#include "include/naiveConsole.h"
#include "include/vsa_driver.h"


static char* KEYS_VALUES[] = {"", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", 			// 0 - 10
									"0", "'", "¿", "BACKSPACE", "    ", "q", "w", "e", "r", "t",// 11 - 20
								  	"y", "u", "i", "o", "p", "´", "+", "\n", "", "a",				// 21 - 30
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

static int addBuff = -1;
static int endOfLine = -1;
static int counter = 0;
void
update_screen(char keyCode){
	addBuff = -1;
	// Key Pressed
	if (keyCode >= 0 && keyCode < mapSize) {

		switch(keyCode){
			case 28: endOfLine=1;
					counter = 0;
                    addBuff=1;
                    nextLine();
                    break;
			case 14: if(counter != 0){
									delete();
									counter--;
									if(write_index != 0){
										write_index--;
									}
								}
				//backspace();
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

			addBuff = 1;
		//		print_char(keyCode);
				if (shiftPressed == 1) {
					print_char(SHIFT_KEYS_VALUES[keyCode][0], 0xffffff);
					//print(SHIFT_KEYS_VALUES[keyCode], 0x07);
				} else {
					print_char(KEYS_VALUES[keyCode][0], 0xffffff);
					//print(KEYS_VALUES[keyCode], 0x07);
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
	update_screen(key_code);
	if(addBuff == 1){
		if(key_code != 28){
		counter++;
	}
		if(shiftPressed == 1){
			buffer[(write_index++) % (BUFFER_SIZE-1)]= SHIFT_KEYS_VALUES[key_code][0];
		}else{
			buffer[(write_index++) % (BUFFER_SIZE-1)]= KEYS_VALUES[key_code][0];
		}
	}
	if ( write_index == BUFFER_SIZE ){
		write_index = 0;
	}
}

int read_from_buffer(int numOfChars,char * str){
	//TODO: change this to take only one key.
	if(read_index == write_index || write_index-read_index < numOfChars){
		return 0;
	}

	int i = 0;
	int j = numOfChars;
	while(numOfChars > 0){
		 str[i++] = buffer[(read_index++) %(BUFFER_SIZE-1)];
		numOfChars--;
	}
	if ( read_index == BUFFER_SIZE ){
		read_index = 0;
	}
	return j;

}
int read_until_enter(char* str){
   if(endOfLine != 1){
		 return 0;
	 }
	 int i = 0;
	 char c;
	 do{
  	c = buffer[(read_index++) % (BUFFER_SIZE-1)];
  	str[i++] = c;
	}while(c!= '\n');
endOfLine == -1;
	return i;
	}
