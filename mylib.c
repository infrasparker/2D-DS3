#include "mylib.h"

// unsigned short *videoBuffer = (unsigned short *) 0x60000000;

void setPixel(int row, int col, u16 color) {
	videoBuffer[row * SCREENW + col] = color;
}

void drawChar(int row, int col, unsigned char ch, unsigned short color) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			if (data[i * 6 + j + ch * 48]) {
				setPixel(i + row, j + col, color);
			}
		}
	}
}

void drawString(int row, int col, char* ch, u16 color) {
	int charOffset = 0;
	while(*ch) {
		drawChar(row, col + charOffset, *ch, color);
		ch++;
		charOffset += 6;
	}
}

// draw image on screen
void drawImage(int x, int y, int width, int height, const unsigned short *image) {
	for (unsigned short i = 0; i < height; i++) {
		DMA[3].src = (vu32*) (image + (width * i));
		DMA[3].dst = (vu32*) (videoBuffer + SCREENW * (y + i) + x);
		DMA[3].cnt = width | DMA_ON;
	}
}

// draw rectangle of color on screen
void drawRect(int x, int y, int width, int height, vu16 color) {
	for (int i = 0; i < height; i++) {
		DMA[3].src = (vu16*) &color;
		DMA[3].dst = (vu32*) (videoBuffer + (y + i) * SCREENW + x);
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

// draw fill screen with color
void fillScreen(vu16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 240 * 160 | DMA_ON | DMA_SOURCE_FIXED;
}

// DMA wait
void waitForVBlank() {
	while(SCANLINECOUNTER > SCREENH);
	while(SCANLINECOUNTER < SCREENH);
}

// change p.image and adjust
void change_pimage(int neww, int newh, int focalx, int focaly, const unsigned short * image) {
	p.x += p.fx - focalx;
	p.y += p.fy - focaly;
	p.fx = focalx;
	p.fy = focaly;
	p.w = neww;
	p.h = newh;
	p.image = image;
}

// jchange f.image and adjust
void change_fimage(int neww, int newh, int focalx, int focaly, const unsigned short * image) {
	f.x += f.fx - focalx;
	f.y += f.fy - focaly;
	f.fx = focalx;
	f.fy = focaly;
	f.w = neww;
	f.h = newh;
	f.image = image;
}