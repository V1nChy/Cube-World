#include "GameFrame.h"

GameFrame* pGF;

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pGF->Render();

	glutSwapBuffers();
}

void TimerFunc(int value)
{
	pGF->Updata();

	glutPostRedisplay();
	glutTimerFunc(16, TimerFunc, value);
}
void MyMouse(int btn, int state, int x, int y)
{
	pGF->GetGI()->MouseFunc(btn,state,x,y);
	glutPostRedisplay();
}
void MyMotion(int x, int y)
{
	pGF->GetGI()->MotionFunc(x,y);
}
void MyPassMotion(int x,int y)
{
	pGF->GetGI()->PassiveMotionFunc(x,y);
}
void MyKeyDown(unsigned char key, int x, int y)
{
	pGF->GetGI()->KeyboardFunc(key,x,y);
	glutPostRedisplay();
}
void MyKeyUp(unsigned char key, int x, int y)
{
	pGF->GetGI()->KeyboardUpFunc(key,x,y);
	glutPostRedisplay();
}
void MySpecialKey(int key,int x,int y)
{
	pGF->GetGI()->SpecialKeyFun(key,x,y);
}
void ChangeSize(int w, int h)
{
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	if (pGF->mAspect == 0)
	{
		pGF->mAspect = (GLfloat)w / (GLfloat)h;
	}

	int newW, newH;
	
	if (h*pGF->mAspect <= w)
	{
		newW = h*pGF->mAspect;
		newH = h;
		glViewport(w / 2 - newW / 2, 0, newW, newH);
	}
	else
	{
		newH = w / pGF->mAspect;
		newW = w;
		glViewport(0, h / 2 - newH / 2, newW, newH);
	}
												// 设置透视投影视域体
	mat4 matProj = Perspective(60.0f, pGF->mAspect, 0.001f, 50.0f);
	pGF->GetGI()->SetProjection(matProj);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(ClientW, ClientH);
	glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) - ClientW) / 2, (GetSystemMetrics(SM_CYSCREEN) - ClientH) / 2);
	// 以下2个函数来自freeglut库，用于确认 
	// 代码是基于OpenGL 3.1版本的
	glutInitContextVersion( 3, 1 ); // 表明使用OpenGL 3.1
	// 保持向前兼容，即不使用任何弃用的函数
	// 如程序中使用了弃用函数则注释掉本行
	//glutInitContextFlags(GLUT_FORWARD_COMPATIBLE); 

	glutCreateWindow("2014030403073 - 杨长华");

	// 显卡驱动非正式发布版或者与glew库规范不兼容时加上此行
	// 如果在glGenVertexArrays处发生Access Violation则加上此行
	glewExperimental = GL_TRUE; 

	GLenum err = glewInit(); // 初始化glew库，必须在glutCreateWindow之后调用
	if(err != GLEW_OK)  // 初始化不成功？
	{
		std::cout << "glewInit 失败, 退出程序." << std::endl;
		exit(EXIT_FAILURE); // 退出程序
	}

	glClearColor(0.0f, 0.0f, 0.50f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	// 开启背面剔除
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutSpecialFunc(MySpecialKey);
	glutKeyboardFunc(MyKeyDown);
	glutKeyboardUpFunc(MyKeyUp);
	glutMouseFunc(MyMouse);
	glutMotionFunc(MyMotion);
	glutPassiveMotionFunc(MyPassMotion);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(100, TimerFunc, 0);

	pGF = GameFrame::GetObject();
	pGF->Init();


	printf("\n\n");
	printf("移动方式：	W	S	A	D	SPACE\n\n");
	printf("视角转动方式：	按着鼠标右键拖动\n\n");
	printf("新建销毁方块：	鼠标左键销毁，中键新建\n\n");
	printf("方块选择按键按键：数字键1 2 3 4 5 6 7 8 9\n\n");

	printf("特殊功能按键：\n");
	printf("	F1:开启\\关闭粒子系统(雾化)\n");
	printf("	r:复位\n\n");

	printf("友情提示：\n");
	printf("	进入游戏后默认使用存档1，注意选择当前想使用的存档\n\n");

	printf("	存档二为建筑示例，水景别墅QAQ\n");


	glutMainLoop();

	return 0;
}