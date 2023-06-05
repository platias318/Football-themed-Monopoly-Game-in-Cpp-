#pragma once
#include <chrono>
#include <thread>
#include <stdlib.h>
#include<random>

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 700

#define ASSET_PATH ".\\assets\\"

#define WINDOWS_WIDTH 900
#define WINDOWS_HEIGHT 800

#define DICE_ICON_X CANVAS_WIDTH /4.5+18
#define DICE_ICON_Y CANVAS_HEIGHT /3.9 + 18

#define DICE_ICON_WIDTH 50
#define DICE_ICON_HEIGHT 50

#define MAIN_MENU_X CANVAS_WIDTH/2
#define MAIN_MENU_Y CANVAS_HEIGHT/2
#define MAIN_MENU_SIZEX CANVAS_WIDTH/1.10
#define MAIN_MENU_SIZEY CANVAS_HEIGHT/1.3

#define SETCOLOR(c,r,g,b){c[0]=r;c[1]=g;c[2]=b;}

#define PLAYER_SIZE 43

#define RAND0TO1() (rand()/(float)RAND_MAX)

#define  RAND1TO6()(rand() % 6 + 1)

#define  icon_size_x 25
#define  icon_size_y 25

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}
inline void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}