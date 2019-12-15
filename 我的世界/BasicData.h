#ifndef _BASIC_DATA_H_
#define _BASIC_DATA_H_

#include <windows.h>
#include <fstream>
#include <tchar.h>
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <io.h>
#include <stdlib.h>

#include "Angel.h"
using namespace std;

#define MAX_CHAR  128

#define ClientW 800
#define ClientH 500

typedef vec4 color4;
typedef vec3 point3;
typedef vec2 point2;

enum { UP, DOWN, LEFT, RIGHT, FRONT,BACK,NUM_KEY };

//声音
#define		MENU_BGM		1
#define		LOAD_BGM		2
#define		GAME_BGM		3
#define		FALL_SOUND		4
#define		HIT_SOUND		5
#define		LAY_SOUND		6
#define		CLICK_SOUND		7

//对象
#define		BACKGROUND		100
#define     BUTTON			101
#define		SKY				102
#define		TERRAIN			103

//按钮
#define		NEW_GAME		0
#define		LOAD_GAME		1
#define		EXIT_GAME		2

//方块
#define		GRASS_BLOCK			1
#define		SAND_BLOCK			2
#define		CLAY_BLOCK			3
#define		STONE_BLOCK			4
#define		STONEBRICK_BLOCK	5
#define		BRICK_BLOCK			6
#define		PLANKS_BLOCK		7
#define		GLASS_BLOCK			8
#define		BEDROCK_BLOCK		9

#define		TREE_LOG			11
#define     TREE_LEAVES			12

struct GS_OUTPUT
{
	vec3 FacePos[3];
	float depth;
	UINT id;
	UINT idParent;

	UINT xPos;
	UINT yPos;
	UINT zPos;
};
struct isPos
{
	int x;
	int y;
	int z;
};
typedef struct lightingStruct
{
	color4 ambient;		//环境光
	color4 diffuse;		//漫反射光
	color4 specular;	//镜面反射光

}lightingStruct;
typedef struct materialStruct
{
	color4 ambient;			//环境反射系数
	color4 diffuse;			//漫反射系数
	color4 specular;		//镜面反射系数
	color4 emission;		//发射光
	GLfloat shininess;		//高光系数
}materialStruct;
#endif