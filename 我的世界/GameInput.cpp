#include"GameInput.h"
#include"Gameframe.h"
#include"Game.h"
GameInput::GameInput()
{
}
GameInput::~GameInput()
{}
void GameInput::Init()
{
	ESC = FALSE;

	//移动相关

	KeyDown[0] = FALSE;
	KeyDown[1] = FALSE;
	KeyDown[2] = FALSE;
	KeyDown[3] = FALSE;

	yRot = 0.0;
	jumpDis = 0.0;
	fallDis = 0.0;
	yHigh = 0.0;
	rOffsetY = 0.0;
	rOffsetX = 0.0;
	rRotateY = 0.0;
	rRotateX = 0.0;
	MoveSpeed = 1.5;

	bFall = FALSE;
	bJump = FALSE;
	gravity = 9.8;
	initSpeed = 5.0;
	ySpeed = 0.0;
	MounseRightDown = FALSE;

	InitFramBufferForSelect();
}
void GameInput::InitFramBufferForSelect()
{
	mPerNum = 1000;
	mButtonSelect = TRUE;

	nearPlane = 0.1f;
	farPlane = 3.0f;
	pickingprogram = InitShader("vpicking.glsl", 0, "gpicking.glsl");
	glUseProgram(pickingprogram);
	H_MousePosition = glGetUniformLocation(pickingprogram, "ptMouse");
	//H_matModel = glGetUniformLocation(pickingprogram, "matModel");
	//H_matProjView=glGetUniformLocation(pickingprogram,"matProjView");
	H_matModel = glGetUniformLocation(pickingprogram, "matModel");
	H_matMVP = glGetUniformLocation(pickingprogram, "matMVP");
	H_id = glGetUniformLocation(pickingprogram, "idIn");
	H_xyzPos = glGetUniformLocation(pickingprogram, "xyzPos");
	H_near = glGetUniformLocation(pickingprogram, "near");
	H_far = glGetUniformLocation(pickingprogram, "far");
	//申请一个未用的VAO ID，存于变量feedbackobj中
	glGenTransformFeedbacks(1, &feedbackobj);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedbackobj);
	glGenBuffers(1, &feedbackbuffer);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, feedbackbuffer);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, mPerNum * sizeof(GS_OUTPUT), NULL, GL_DYNAMIC_COPY);
	//来设置缓冲区与binding point的绑定 void glBindBufferBase(GLenum target, GLuint bindingPoint, GLuint bufferName);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, feedbackbuffer);
	static const GLchar * vars[] =
	{
		"FacePos", "depth", "id","mPos"
	};
	//这个函数指定了这个Shader中将可用于Transform FeedBack的输出变量
	glTransformFeedbackVaryings(pickingprogram, 4,
		vars, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(pickingprogram);
	glVertexAttribPointer(H_Position, 3, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(H_Position);
	glGenQueries(1, &queryobj);		//遮挡查询对象ID

}
void GameInput::Update()
{
	cBlockMap* temp = GameFrame::GetObject()->GetNowScene()->mMap;
	if (bFall)
	{
		fallDis += ySpeed * GameFrame::GetObject()->mDeltaTime;
		ySpeed -= gravity * GameFrame::GetObject()->mDeltaTime;
		if (ySpeed < -8)
			ySpeed = -8;
	}
	if (bJump)
	{
		jumpDis += ySpeed * GameFrame::GetObject()->mDeltaTime;
		ySpeed -= gravity * GameFrame::GetObject()->mDeltaTime;
		if (jumpDis < 0)
		{
			jumpDis = 0;
			bJump = false;

			if (!bFall && !temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] - 1, mMatCameraReverse[2][3]))
			{
				bFall = TRUE;
			}
			else
			{
				Scene::mSoundPlay.play(FALL_SOUND);
			}
		}
	}
	if (ESC)
	{
		ESC = FALSE;
		GameFrame::GetObject()->SetScene("Menu场景");
	}
}
void GameInput::Enter()
{
}

void GameInput::SpecialKeyFun(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		GameScene::bParOn = GameScene::bParOn == 0 ? 1 : 0;
		if(GameScene::bParOn)
			glUniform1i(GameFrame::GetObject()->GetGO()->GetShaderPointer("LightTexture")->bFogOn, 1);
		else
			glUniform1i(GameFrame::GetObject()->GetGO()->GetShaderPointer("LightTexture")->bFogOn, 0);
	}
}
void GameInput::KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0': {
		cBlockMap::mNowBlock = 1;
	}break;
	case '1': {
		cBlockMap::mNowBlock = 1;
	}break;
	case '2': {
		cBlockMap::mNowBlock = 2;
	}break;
	case '3': {
		cBlockMap::mNowBlock = 3;
	}break;
	case '4': {
		cBlockMap::mNowBlock = 4;
	}break;
	case '5': {
		cBlockMap::mNowBlock = 5;
	}break;
	case '6': {
		cBlockMap::mNowBlock = 6;
	}break;
	case '7': {
		cBlockMap::mNowBlock = 7;
	}break;
	case '8': {
		cBlockMap::mNowBlock = 8;
	}break;
	case '9': {
		cBlockMap::mNowBlock = 9;
	}break;
	case 'R':case 'r': {
		ResetCamera();
		int high = GameFrame::GetObject()->GetNowScene()->mMap->SearchHigh(0, 0);
		GameFrame::GetObject()->GetGI()->mMatCameraReverse = mat4()*Translate(0.0, 1.8 + high, 0.0);
		GameFrame::GetObject()->GetGI()->mMatCamera = mat4()*Translate(0.0, -1.8 - high, 0.0);
	}break;
	case 'z': {
		cBlockMap::mNowBlock = TREE_LOG;
	}break;
	case 'x': {
		cBlockMap::mNowBlock = TREE_LEAVES;
	}break;
	case 27:
	{
		ESC = TRUE;
	}break;
	}
	if (!bFall && !bJump && key == ' ')
	{
		bJump = true;
		ySpeed = initSpeed;
	}
	if (key == 'w' || key == 'W')
		KeyDown[UP] = GL_TRUE;
	if (key == 's' || key == 'S')
		KeyDown[DOWN] = GL_TRUE;
	if (key == 'a' || key == 'A')
		KeyDown[LEFT] = GL_TRUE;
	if (key == 'd' || key == 'D')
		KeyDown[RIGHT] = GL_TRUE;
	if (key == 'l' || key == 'L')
	{
		bWire = !bWire;
		if (bWire)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void GameInput::KeyboardUpFunc(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
		KeyDown[UP] = GL_FALSE;
	if (key == 's' || key == 'S')
		KeyDown[DOWN] = GL_FALSE;
	if (key == 'a' || key == 'A')
		KeyDown[LEFT] = GL_FALSE;
	if (key == 'd' || key == 'D')
		KeyDown[RIGHT] = GL_FALSE;
}
void GameInput::MouseFunc(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Scene* temp = GameFrame::GetObject()->GetNowScene();
		GS_OUTPUT* selectData = SelectObject(x, y);
		if (mButtonSelect)
		{
			map<int, cButton*>::iterator i;
			for (i = temp->mButtonMap.begin(); i != temp->mButtonMap.end(); i++)
			{
				i->second->mClick = FALSE;
			}
			if (selectData && selectData->idParent == BUTTON)
			{
				temp->mButtonMap[selectData->id]->mClick = TRUE;
			}
			Scene::mSoundPlay.play(CLICK_SOUND);
		}
		else
		{
			if (selectData && selectData->idParent == TERRAIN)
			{
				Scene::mSoundPlay.play(HIT_SOUND);
				temp->mMap->Update(selectData->xPos, selectData->yPos,selectData->zPos, selectData->FacePos,mCameraPos,-1);
			}
		}
	}
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN && !mButtonSelect)
	{
		Scene* temp = GameFrame::GetObject()->GetNowScene();
		GS_OUTPUT* selectData = SelectObject(x, y);
		
		if (selectData && selectData->idParent == TERRAIN)
		{
			Scene::mSoundPlay.play(LAY_SOUND);
			temp->mMap->Update(selectData->xPos, selectData->yPos, selectData->zPos, selectData->FacePos, mCameraPos, 1);
		}
	}
	if (MounseRightDown == FALSE && btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mouse.x = x;
		mouse.y = y;
		MounseRightDown = TRUE;
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		rRotateY -= rOffsetY;
		rRotateX -= rOffsetX;
		rRotateY = rRotateY - (rRotateY > 360 ? 1 : 0) * 360;
		rRotateY = rRotateY + (rRotateY < 0 ? 1 : 0) * 360;

		rRotateX = rRotateX > 80 ? 80 : rRotateX;
		rRotateX = rRotateX < -80 ? -80 : rRotateX;

		rOffsetY = 0;
		rOffsetX = 0;
		MounseRightDown = FALSE;
	}
}
void GameInput::PassiveMotionFunc(int x, int y)
{
	if (mButtonSelect)
	{
		Scene* temp = GameFrame::GetObject()->GetNowScene();
		GS_OUTPUT* selectData = SelectObject(x, y);
		map<int, cButton*>::iterator i;
		for (i = temp->mButtonMap.begin(); i != temp->mButtonMap.end(); i++)
		{
			i->second->mActive = FALSE;
		}
		if (selectData && selectData->idParent == BUTTON)
		{
			temp->mButtonMap[selectData->id]->mActive = TRUE;
		}
	}
}
void GameInput::MotionFunc(int x, int y)
{
	if (MounseRightDown)
	{
		rOffsetY = (mouse.x - x) / 5.0;
		rOffsetX = (y - mouse.y) / 5.0;

		rOffsetX = (rRotateX - rOffsetX) > 80 ? (rRotateX - 80) : rOffsetX;
		rOffsetX = (rRotateX - rOffsetX) < -80 ? (80 + rRotateX) : rOffsetX;
	}
}


GS_OUTPUT* GameInput::SelectObject(int x, int y)
{
	int front;
	GS_OUTPUT *data;

	glUseProgram(pickingprogram);
	GLint viewport[4];			// 用于存储视口属性
	glGetIntegerv(GL_VIEWPORT, viewport);	// 获取视口属性
													// 计算规范化设备坐标系下鼠标位置
	GLfloat ptX = ((x - viewport[0]) / (GLfloat)viewport[2] - 0.5) * 2;
	GLfloat ptY = ((viewport[3] - 1 - y - viewport[1]) / (GLfloat)viewport[3] - 0.5) * 2;

	glUniform2f(H_MousePosition, ptX, ptY);
	glUniform1f(H_near, nearPlane);
	glUniform1f(H_far, farPlane);
	/*整个Tranform Feedback过程：在绑定了一个作为tranform feedback buffer的VBO后，
	在glBeginTransformFeedback/glEndTransformFeedback之间的
	DrawCall将会把结果按GL_PONTS的组织形式输出到该Buffer中*/

	glEnable(GL_RASTERIZER_DISCARD);		//开启关闭栅格化阶段
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedbackobj);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, queryobj);

	glBeginTransformFeedback(GL_POINTS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	mat4 matVP = mMatProjection*mMatView;
	int error = glGetError();
	GameFrame::GetObject()->GetNowScene()->RenderForSelect(matVP);
	error = glGetError();
	if (bWire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEndTransformFeedback();

	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);

	GLuint count;
	glGetQueryObjectuiv(queryobj, GL_QUERY_RESULT, &count);

	front = -1;
	float mindepth = 1.1;

	data = (GS_OUTPUT *)glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);
 	while (count--)
	{
		if (data)
		{
			if (data->depth < mindepth)
			{
				mindepth = data->depth;
				front = count;
			}
			data++;
		}
	}
	if (front != -1)
	{
		//返回到选择的深度最小的对象
		data -= (front + 1);
	}
	glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
	
	glDisable(GL_RASTERIZER_DISCARD);

	GameFrame::GetObject()->GetGO()->SetShader("LightTexture");

	error = glGetError();
	if (front != -1)
		return data;
	else
		return NULL;
}

void GameInput::SetProjection(mat4 &projection)
{
	mMatProjection = projection;
	glUniformMatrix4fv(GameOutput::m_pShaderID->Projection, 1, GL_TRUE, mMatProjection);
}
void GameInput::ResetCamera()
{
	mat4 temp;
	mMatCamera = temp;
	mMatCameraReverse = temp;
	mMatEyeAngle = temp;
}
void GameInput::UpdateCamera()
{
	vec3 vTemp;
	mat4 rmat = mMatCameraReverse;
	mat4 mat = mMatCamera;

	cBlockMap* temp = GameFrame::GetObject()->GetNowScene()->mMap;
	if (bFall && temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] + fallDis - 1, mMatCameraReverse[2][3]))
	{
		int h= temp->SearchHigh(mMatCameraReverse[0][3], mMatCameraReverse[2][3]);

		mMatCameraReverse *= Translate(0.0, -(1.0-(int)fallDis), 0.0);
		mMatCamera = Translate(0.0, (1.0 - (int)fallDis), 0.0)*mMatCamera;

		if (h == ((int)mMatCameraReverse[1][3]))
		{
			mMatCameraReverse *= Translate(0.0, 1, 0.0);
			mMatCamera = Translate(0.0,-1, 0.0)*mMatCamera;
		}

		bFall = FALSE;
		fallDis = 0;
		Scene::mSoundPlay.play(FALL_SOUND);
	}

	if (KeyDown[UP])
	{
		vTemp = vec3(-MoveSpeed* GameFrame::GetObject()->mDeltaTime, 0.0, MoveSpeed* GameFrame::GetObject()->mDeltaTime);
		vTemp.x *= sin(M_PI / 180.0* (rRotateY - rOffsetY));
		vTemp.z *= cos(M_PI / 180.0 * (rRotateY - rOffsetY));

		rmat = mMatCameraReverse;
		mat = mMatCamera;

		mMatCameraReverse *= Translate(-vTemp.x, 0.0, -vTemp.z);
		mMatCamera = Translate(vTemp.x, 0.0, vTemp.z)*mMatCamera;

		if (temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3], mMatCameraReverse[2][3]))
		{
 			if (bJump && jumpDis>1.0 && !temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] + jumpDis, mMatCameraReverse[2][3]))
			{
				jumpDis = 0;
				mMatCameraReverse *= Translate(0.0, 1.0, 0.0);
				mMatCamera = Translate(0.0, -1.0, 0.0)*mMatCamera;
			}
			else
			{
				mMatCameraReverse = rmat;
				mMatCamera = mat;
			}
		}
	}
	if (KeyDown[DOWN])
	{
		vTemp = vec3(MoveSpeed* GameFrame::GetObject()->mDeltaTime, 0.0, -MoveSpeed* GameFrame::GetObject()->mDeltaTime);
		vTemp.x *= sin(M_PI / 180.0* (rRotateY - rOffsetY));
		vTemp.z *= cos(M_PI / 180.0 * (rRotateY - rOffsetY));

		rmat = mMatCameraReverse;
		mat = mMatCamera;

		mMatCameraReverse *= Translate(-vTemp.x, 0.0, -vTemp.z);
		mMatCamera = Translate(vTemp.x, 0.0, vTemp.z)*mMatCamera;

		if (temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3], mMatCameraReverse[2][3]))
		{
			if (bJump && jumpDis>1.0 && !temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] + jumpDis, mMatCameraReverse[2][3]))
			{
				jumpDis = 0;
				mMatCameraReverse *= Translate(0.0, 1.0, 0.0);
				mMatCamera = Translate(0.0, -1.0, 0.0)*mMatCamera;
			}
			else
			{
				mMatCameraReverse = rmat;
				mMatCamera = mat;
			}
		}
	}
	if (KeyDown[LEFT])
	{
		vTemp = vec3(MoveSpeed* GameFrame::GetObject()->mDeltaTime, 0.0, MoveSpeed* GameFrame::GetObject()->mDeltaTime);
		vTemp.x *= cos(M_PI / 180.0* (rRotateY - rOffsetY));
		vTemp.z *= sin(M_PI / 180.0 * (rRotateY - rOffsetY));

		rmat = mMatCameraReverse;
		mat = mMatCamera;

		mMatCameraReverse *= Translate(-vTemp.x, 0.0, -vTemp.z);
		mMatCamera = Translate(vTemp.x, 0.0, vTemp.z)*mMatCamera;

		if (temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3], mMatCameraReverse[2][3]))
		{
			if (bJump && jumpDis>1.0 && !temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] + jumpDis, mMatCameraReverse[2][3]))
			{
				jumpDis = 0;
				mMatCameraReverse *= Translate(0.0, 1.0, 0.0);
				mMatCamera = Translate(0.0, -1.0, 0.0)*mMatCamera;
			}
			else
			{
				mMatCameraReverse = rmat;
				mMatCamera = mat;
			}
		}
	}
	if (KeyDown[RIGHT])
	{
		vTemp = vec3(-MoveSpeed* GameFrame::GetObject()->mDeltaTime, 0.0, -MoveSpeed* GameFrame::GetObject()->mDeltaTime);
		vTemp.x *= cos(M_PI / 180.0* (rRotateY - rOffsetY));
		vTemp.z *= sin(M_PI / 180.0 * (rRotateY - rOffsetY));

		rmat = mMatCameraReverse;
		mat = mMatCamera;

		mMatCameraReverse *= Translate(-vTemp.x, 0.0, -vTemp.z);
		mMatCamera = Translate(vTemp.x, 0.0, vTemp.z)*mMatCamera;

		if (temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3], mMatCameraReverse[2][3]))
		{
 			if (bJump && jumpDis>1.0 && !temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] + jumpDis, mMatCameraReverse[2][3]))
			{
				jumpDis = 0;
				mMatCameraReverse *= Translate(0.0, 1.0, 0.0);
				mMatCamera = Translate(0.0, -1.0, 0.0)*mMatCamera;
			}
			else
			{
				mMatCameraReverse = rmat;
				mMatCamera = mat;
			}
		}
	}
	if (!bJump && !bFall && !temp->Collision(mMatCameraReverse[0][3], mMatCameraReverse[1][3] - 1, mMatCameraReverse[2][3]))
	{
		bFall = TRUE;
		ySpeed = 0;
	}


	mCameraPos.x = mMatCameraReverse[0][3];
	mCameraPos.y = mMatCameraReverse[1][3] + jumpDis + fallDis;
	mCameraPos.z = mMatCameraReverse[2][3];

	float eyeAngleY = sin(M_PI / 180 * (rRotateX - rOffsetX));
	float eyeAngleZ = cos(M_PI / 180 * (rRotateX - rOffsetX));

	float eyeAngleX = eyeAngleZ*sin(M_PI / 180 * (rRotateY - rOffsetY));
	eyeAngleZ = eyeAngleZ*cos(M_PI / 180 * (rRotateY - rOffsetY));
	mMatEyeAngle = mat4();
	mMatEyeAngle*= LookAt(vec4(0.0, 0.0, 0.0, 1.0), vec4(eyeAngleX, eyeAngleY, -eyeAngleZ, 1.0), vec4(0.0, 1.0, 0.0, 0.0));

	mMatView = mMatEyeAngle*Translate(0.0, -jumpDis-fallDis, 0.0)* mMatCamera;
}