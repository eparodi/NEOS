#include "include/types.h"
#include "include/font.h"

#define FONT_WIDTH     10
#define FONT_HEIGHT    16
//http://wiki.osdev.org/VESA_Video_Modes

#pragma pack(push)
#pragma pack(1)
typedef struct{
  uint16_t attributes;
  uint8_t winA,winB;
  uint16_t granularity;
  uint16_t winsize;
  uint16_t segmentA, segmentB;
  //VBE_FAR(realFctPtr);
  uint32_t farptr;
  uint16_t pitch; // bytes per scanline
 
  uint16_t Xres, Yres;
  uint8_t Wchar, Ychar, planes, bpp, banks;
  uint8_t memory_model, bank_size, image_pages;
  uint8_t reserved0;
 
  uint8_t red_mask, red_position;
  uint8_t green_mask, green_position;
  uint8_t blue_mask, blue_position;
  uint8_t rsv_mask, rsv_position;
  uint8_t directcolor_attributes;
 
  uint32_t physbase;  // your LFB (Linear Framebuffer) address ;)
  uint32_t reserved1;
  uint16_t reserved2;
} ModeInfoBlock;
#pragma pack(pop)

//http://wiki.osdev.org/Drawing_In_Protected_Mode

/* The beginning of the table */
static ModeInfoBlock * screen_info =  (ModeInfoBlock *) 0x5C00;
static byte * screen;
static int pitch;
static int pixel_width;
static int xres, yres;
static int buffer_position = 0;
static int buffer_max;

void
start_video_mode(){
	screen = (byte *) screen_info->physbase;
	pitch = screen_info->pitch;
	pixel_width = screen_info->bpp / 8;
	xres = screen_info->Xres;
	yres = screen_info->Yres;
  buffer_max = xres/FONT_WIDTH;
}

void
draw_pixel(int x, int y, int color){
	unsigned pos = x * pixel_width + y * pitch;
    screen[pos] = color & 255;              // BLUE
    screen[pos + 1] = (color >> 8) & 255;   // GREEN
    screen[pos + 2] = (color >> 16) & 255;  // RED
}

/* hacer más eficiente */

void
draw_char(unsigned char c, int x, int y, int color){
	int cx,cy;
	int mask[8]={1,2,4,8,16,32,64,128};
	unsigned char * glyph=font[c-32];
 
	for(cy=0;cy<13;cy++){
		for(cx=0;cx<8;cx++){
			if(glyph[cy]&mask[cx]){
				draw_pixel(x+8-cx,y+13-cy, color);
			}
		}
	}
}

void
draw_string( char * str , int x , int y , int color){
	int i = 0;
	while(str[i] != '\0'){
		draw_char(str[i++],x+(10*i),y,color);
	}
}

void
draw_filled_rectangle(int x1, int y1, int x2, int y2, int color){
  int i,j;
  byte blue = color & 255;
  byte green = (color >> 8 ) & 255;
  byte red = (color >> 16) & 255;
  int pos1 = x1 * pixel_width + y1 * pitch;
  byte * draw = &screen[pos1];
  for ( i = 0; i <= y2-y1 ; i++){
    for ( j= 0 ; j <= x2-x1 ; j++){
      draw[pixel_width * j] = blue;
      draw[pixel_width*j+1] = green;
      draw[pixel_width*j+2] = red;
    }
    draw += pitch;
  }
}

void
clear_screen(){
  int i, j;
  byte * draw = screen;
  buffer_position = 0;
  for ( i = 0 ; i <= xres; i++ ){
    for( j = 0 ; j <= yres; j++ ){
      draw[pixel_width * j] = 0;
      draw[pixel_width * j + 1 ] = 0;
      draw[pixel_width * j + 2 ] = 0;
    }
    draw += pitch;
  }
}

void
print_char(unsigned char c, int color ){
  draw_char(c, (buffer_position % buffer_max)*FONT_WIDTH, (buffer_position / buffer_max)*FONT_HEIGHT , color);
  buffer_position++;
}

void
print_string(const char * str, int color ){
  int i = 0;
  while(str[i] != '\0'){
    print_char(str[i],color);
    i++;
  }
}

void
print_string_by_length(const char * str, int length , int color){
  int i = 0;
  while( i < length){
    print_char(str[i],color);
    i++;
  }
}

void
delete(){
  if ( buffer_position > 0){
    int x = ((buffer_position-1) % buffer_max) * FONT_WIDTH;
    int y = ((buffer_position-1) / buffer_max) * FONT_HEIGHT;
    draw_filled_rectangle(x,y,x+FONT_WIDTH,y+FONT_HEIGHT,0x000000);
    buffer_position--;
  }
}