#ifndef _GAME_INPUT_
#define _GAME_INPUT_

#include"BasicData.h"

class GameInput
{
public:
	BOOL ESC;
	BOOL MounseRightDown;
	BOOL bJump,bFall;
	BOOL KeyDown[NUM_KEY];
	BOOL bWire = false;
	//投影，照相机矩阵
	point3 mCameraPos;
	mat4 mMatProjection;
	mat4 mMatCamera;
	mat4 mMatCameraReverse;
	mat4 mMatEyeAngle;
	mat4 mMatView;

	//移动更新相关
	point3 mouse;
	GLfloat yRot;
	GLfloat jumpDis, fallDis,yHigh;
	float rOffsetY, rOffsetX;
	float rRotateY,rRotateX;
	float MoveSpeed;
	float gravity;
	float initSpeed;
	float ySpeed;

	//拾取操作相关
	BOOL mButtonSelect;

	float nearPlane;
	float farPlane;
	int mPerNum;

	GLuint H_xyzPos,H_id, H_matMVP, H_MousePosition, H_Position = 0, H_DrawType, H_near, H_far, H_matModel;
	GLuint pickingprogram;
	GLuint feedbackobj, feedbackbufferobj, queryobj, feedbackbuffer;
	GLuint vaoPickingTriangles, vboPickingTriangles;

	GS_OUTPUT* SelectObject(int x, int y);

	GameInput();
	~GameInput();

	void Init();
	void InitFramBufferForSelect();
	void Update();
	void Enter();
	void Run(float t);

	void SpecialKeyFun(int key, int x, int y);
	void KeyboardFunc(unsigned char key, int x, int y);
	void KeyboardUpFunc(unsigned char key, int x, int y);
	void MouseFunc(int btn, int state, int x, int y);
	void MotionFunc(int x, int y);
	void PassiveMotionFunc(int x, int y);
	void SetProjection(mat4 &projection);
	void ResetCamera();
	void UpdateCamera();
};

#endif