#include "driver/gpu/frameBuffer.h"
#include "driver/gpu/colors.h"
#include "driver/gpu/drawing.h"
#include <string.h>

static int textColor = COLOR_16_Red;

static int gpu_width = 1024;
static int gpu_height = 768;

static int cursorX = 0;
static int cursorY = 1;

static const int fontw = 8;
static const int fonth = 16;

static int rows = -1;
static int cols = -1;

int gputerm_init(void)
{
	FrameBuferDescription* fbd = InitialiseFrameBuffer(gpu_width,gpu_height,16);
	SetGraphicsAddress(fbd);
	
	cols = gpu_width / fontw;
	rows = gpu_height / fonth + 1;
	
	SetForeColour(textColor);
	DrawLine(0,0,1024,768);
	
	SetForeColour(textColor);
	DrawLine(0,768,1024,0);
	
	return fbd != NULL;
}

void gputerm_writeln(char* string)
{
	int strl = strlen(string);
	DrawString(string, strl, cursorX * fontw, cursorY * fonth);
	cursorX = 0;
	cursorY++;
}

