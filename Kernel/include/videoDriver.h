#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H



/* print msg ('\0' given string) with given code color */
void print(const char* msg, char colourCode);

/* print any string whith given color */
void printWithLength(const char* msg, int length, char colourCode);

/* prints a number */
void printNum(int num, int colorCode);

/* prints a new line */
void printNewLine();



void backspace();
void supr();
void moveCursorUp();
void moveCursorDown();
void moveCursorRight();
void moveCursorLeft();
void clearScreen();
#endif
