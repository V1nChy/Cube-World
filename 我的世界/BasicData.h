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

//����
#define		MENU_BGM		1
#define		LOAD_BGM		2
#define		GAME_BGM		3
#define		FALL_SOUND		4
#define		HIT_SOUND		5
#define		LAY_SOUND		6
#define		CLICK_SOUND		7

//����
#define		BACKGROUND		100
#define     BUTTON			101
#define		SKY				102
#define		TERRAIN			103

//��ť
#define		NEW_GAME		0
#define		LOAD_GAME		1
#define		EXIT_GAME		2

//����
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
	color4 ambient;		//������
	color4 diffuse;		//�������
	color4 specular;	//���淴���

}lightingStruct;
typedef struct materialStruct
{
	color4 ambient;			//��������ϵ��
	color4 diffuse;			//������ϵ��
	color4 specular;		//���淴��ϵ��
	color4 emission;		//�����
	GLfloat shininess;		//�߹�ϵ��
}materialStruct;
#endif