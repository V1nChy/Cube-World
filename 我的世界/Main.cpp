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
												// ����͸��ͶӰ������
	mat4 matProj = Perspective(60.0f, pGF->mAspect, 0.001f, 50.0f);
	pGF->GetGI()->SetProjection(matProj);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(ClientW, ClientH);
	glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) - ClientW) / 2, (GetSystemMetrics(SM_CYSCREEN) - ClientH) / 2);
	// ����2����������freeglut�⣬����ȷ�� 
	// �����ǻ���OpenGL 3.1�汾��
	glutInitContextVersion( 3, 1 ); // ����ʹ��OpenGL 3.1
	// ������ǰ���ݣ�����ʹ���κ����õĺ���
	// �������ʹ�������ú�����ע�͵�����
	//glutInitContextFlags(GLUT_FORWARD_COMPATIBLE); 

	glutCreateWindow("2014030403073 - ���");

	// �Կ���������ʽ�����������glew��淶������ʱ���ϴ���
	// �����glGenVertexArrays������Access Violation����ϴ���
	glewExperimental = GL_TRUE; 

	GLenum err = glewInit(); // ��ʼ��glew�⣬������glutCreateWindow֮�����
	if(err != GLEW_OK)  // ��ʼ�����ɹ���
	{
		std::cout << "glewInit ʧ��, �˳�����." << std::endl;
		exit(EXIT_FAILURE); // �˳�����
	}

	glClearColor(0.0f, 0.0f, 0.50f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	// ���������޳�
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
	printf("�ƶ���ʽ��	W	S	A	D	SPACE\n\n");
	printf("�ӽ�ת����ʽ��	��������Ҽ��϶�\n\n");
	printf("�½����ٷ��飺	���������٣��м��½�\n\n");
	printf("����ѡ�񰴼����������ּ�1 2 3 4 5 6 7 8 9\n\n");

	printf("���⹦�ܰ�����\n");
	printf("	F1:����\\�ر�����ϵͳ(��)\n");
	printf("	r:��λ\n\n");

	printf("������ʾ��\n");
	printf("	������Ϸ��Ĭ��ʹ�ô浵1��ע��ѡ��ǰ��ʹ�õĴ浵\n\n");

	printf("	�浵��Ϊ����ʾ����ˮ������QAQ\n");


	glutMainLoop();

	return 0;
}