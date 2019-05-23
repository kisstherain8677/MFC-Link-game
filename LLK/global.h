#pragma once//为了防止文件被重复包含

typedef struct  tagVertex
{
	int row;
	int col;
	int info;
}Vertex;

#define BLANK -1
#define MAX_VERTEX_NUM 96
#define MAX_ROW 8
#define MAX_COL 12
#define MAX_PIC_NUM 16
#define REPEAT_NUM 6
#define MAP_TOP 50
#define MAP_LEFT 50
#define PIC_WIDTH 70
#define PIC_HEIGHT 70
#define PLAY_TIMER_ID 1
#define GAME_LOSE -2
#define GAME_SUCCESS 0
#define GAME_PLAY 2

