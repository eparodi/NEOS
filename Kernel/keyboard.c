#include "include/keyboard.h"
#include "include/naiveConsole.h"
#include "include/vsa_driver.h"


static char* KEYS_VALUES[] = {"", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", 			// 0 - 10
									"0", "'", "¿", "BACKSPACE", "    ", "q", "w", "e", "r", "t",// 11 - 20
								  	"y", "u", "i", "o", "p", "´", "+", "\n", "", "a",				// 21 - 30
									"s", "d", "f", "g", "h", "j", "k", "l", "", "{", 			// 31 - 40
								  	"|", "LSHIFT", "}", "z", "x", "c", "v", "b", "n", "m",  	// 41 - 50
								  	",", ".", "-", "", "*", "ALT", " ", "", "", ""		}	;	// 51 - 60


static char* SHIFT_KEYS_VALUES[] = {"", "ESC", "!", "\"", "#", "$", "%", "&", "/", "(", ")", 	// 0 - 10
									"=", "?", "¡", "BACKSPACE", "    ", "Q", "W", "E", "R", "T",// 11 - 20
								  	"Y", "U", "I", "O", "P", "¨", "*", "\n", "", "A",				// 21 - 30
									"S", "D", "F", "G", "H", "J", "K", "L", "", "[", 			// 31 - 40
								  	"°", "LSHIFT", "]", "Z", "X", "C", "V", "B", "N", "M",  		// 41 - 50
								  	";", ":", "_", "", "*", "ALT", " ", "", "", ""}	;		// 51 - 60


static int addBuff = -1; /** flag that indicates to add or not a key**/
static int endOfLine = -1;/** flag that indicates if an end of line was found**/
static unsigned int counter = 0;/** written keys counter.It decrease in deletion**/
static int shiftRightPressed = -1;
static int shiftLeftPressed = -1;
static int bloqMayusPressed = -1;
static int altPressed = -1;
static int mapSize = 60;
static char buffer[BUFFER_SIZE]={0};
static unsigned int read_index = 0;
static unsigned int write_index = 0;

void
update_screen(unsigned char keyCode){
	addBuff = -1;
	// Key Pressed
	if (keyCode >= 0 && keyCode < mapSize) {
		switch(keyCode){
			case 28: endOfLine=1;
								counter = 0;
                  addBuff=1;
									delete();/** deletes the cursor**/
                  nextLine();
                  break;
			case 14: if(counter > 0){
									delete();
									delete();/** deletes the cursor**/
									counter--;
									if(counter != 0){
										update_cursor();
									}
									if(write_index != 0){
										write_index--;
									}
								}
				 				break;
			case 42:
						shiftLeftPressed*=-1;
						break;
			case 54:
						shiftRightPressed*=-1;
						break;
			case 56:
						altPressed *= -1;
						break;
			case 58:
						bloqMayusPressed*=-1;
				 		break;
			default:
						if(counter!=0){
							delete();/**deletes current cursor**/
						}
						addBuff = 1;
						if(shiftRightPressed == 1 || shiftLeftPressed == 1 ){
								if(bloqMayusPressed == -1  ||  numberBoard(keyCode)){
										print_char(SHIFT_KEYS_VALUES[keyCode][0],0xffffff);
								}else{
										print_char(KEYS_VALUES[keyCode][0],0xffffff);
								}
						}else if(bloqMayusPressed == 1 && !numberBoard(keyCode)){
								print_char(SHIFT_KEYS_VALUES[keyCode][0],0xffffff);
						}else{
								print_char(KEYS_VALUES[keyCode][0],0xffffff);
							}
							update_cursor();
							break;
		}
	}

	// Key Released
 else {
		if (keyCode == 170){
			shiftLeftPressed *= -1;
		}if(keyCode == 182) {
			shiftRightPressed *= -1;
		}

	}

}

void update_cursor(){
	if ( get_buffer_position() > 0){
		int x = ((get_buffer_position()) % get_buffer_max_per_line()) * 10;
		int y = ((get_buffer_position()) / get_buffer_max_per_line()) * 16;
		draw_filled_rectangle(x,y,x+10,y+16,0xffffff);
		update_buffer_position();
	}
}

void add_to_buffer(){
	char key_code = _read_keyboard();
	update_screen(key_code);
	if(addBuff == 1){
		if(key_code != 28){
		counter++;
	}
		if(shiftRightPressed == 1 || shiftLeftPressed == 1 ){
			if(bloqMayusPressed == -1  ||  numberBoard(key_code)){
				buffer[(write_index++) % (BUFFER_SIZE-1)]= SHIFT_KEYS_VALUES[(int)key_code][0];
			}else{
				buffer[(write_index++) % (BUFFER_SIZE-1)]= KEYS_VALUES[(int)key_code][0];
			}
		}else if(bloqMayusPressed == 1 && !numberBoard(key_code)){
				buffer[(write_index++) % (BUFFER_SIZE-1)]= SHIFT_KEYS_VALUES[(int)key_code][0];
		}else{
			buffer[(write_index++) % (BUFFER_SIZE-1)]= KEYS_VALUES[(int)key_code][0];
		}
	}
}

int numberBoard(unsigned char keyCode){

	if(keyCode >= 2 && keyCode<=13){
		return 1;
	}
	return 0;
}

int read_from_buffer(int numOfChars,char * str){
	if(read_index == write_index || write_index-read_index < numOfChars || endOfLine != 1){
		return 0;
	}
	int i = 0;
	int j = numOfChars;
	while(numOfChars > 0 && endOfLine != -1){
		if(buffer[read_index % (BUFFER_SIZE-1)] == '\n'){
			endOfLine = -1;
		}
		 str[i++] = buffer[(read_index++) %(BUFFER_SIZE-1)];
		numOfChars--;
	}
	return j;

}

// Rewrites the line written before.
void
restart_line(){
	int i;
	print_string("$> ",0xffffff);
	if (read_index == write_index){
		return;
	}
	for (i = read_index; i % (BUFFER_SIZE-1) < write_index + 1; i++ ){
		print_char(buffer[i % (BUFFER_SIZE-1)],0xffffff);
	}
	//update_cursor();
}

void
erase_cursor(){
	if (read_index == write_index){
		return;
	}else{
		delete();
	}
}
