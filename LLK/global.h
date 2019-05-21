#pragma once//为了防止文件被重复包含

typedef struct  tagVertex
{
	int row;
	int col;
	int info;
}Vertex;

#define BLANK -1
#define MAX_VERTEX_NUM 160
#define MAX_ROW 10
#define MAX_COL 16
#define MAX_PIC_NUM 16
#define REPEAT_NUM 10
#define MAP_TOP 50
#define MAP_LEFT 20
#define PIC_WIDTH 40
#define PIC_HEIGHT 40
