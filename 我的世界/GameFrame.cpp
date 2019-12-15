#include"GameFrame.h"
#include"Menu.h"
#include"Game.h"
#include"Load.h"

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
					   // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// �����ַ��ĸ���
	// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	// ����һ���ֽ���һ���ַ�
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

GameFrame *GameFrame::m_pGameFrame = 0;
GameFrame::GameFrame():
m_pGameOutput(0),
m_pGameInput(0),
m_pScene(0),
mDeltaTime(0),
mAspect(0)
{
	m_pGameFrame = this;

	m_pGameOutput = new GameOutput();
	m_pGameInput = new GameInput();

	mRunTime = 0;
	mFrameTime = 16;
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mStartCount);
}
GameFrame::~GameFrame()
{
	map<string, Scene*>::iterator i;
	for (i = m_Scene.begin(); i != m_Scene.end(); i++)
	{
		i->second->End();
		delete i->second;
	}
	m_Scene.clear();
	delete m_pGameOutput;
	delete m_pGameInput;
}
void GameFrame::Init()
{
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(1.0f, 1.0f, 0.0f);

	LoadSound();

	m_pGameInput->Init();
	m_pGameOutput->Init();

	LoadScene(new MenuScene(), "Menu����");
	LoadScene(new LoadGameScene(), "Load����");
	LoadScene(new GameScene(), "Game����");
	SetScene("Menu����");
}
void GameFrame::LoadSound()
{
	Scene::mSoundPlay.ReadFile(MENU_BGM,"Res\\sound\\sound\\hal3.ogg");
	Scene::mSoundPlay.ReadFile(GAME_BGM, "Res\\sound\\sound\\calm1.ogg");

	Scene::mSoundPlay.ReadFile(FALL_SOUND, "Res\\sound\\music\\fall.ogg", DOSOUND);
	Scene::mSoundPlay.ReadFile(HIT_SOUND, "Res\\sound\\music\\hit.ogg", DOSOUND);
	Scene::mSoundPlay.ReadFile(LAY_SOUND, "Res\\sound\\music\\lay.ogg", DOSOUND);
	Scene::mSoundPlay.ReadFile(CLICK_SOUND, "Res\\sound\\music\\click.wav", DOSOUND);
}
void GameFrame::Render()
{
	static LARGE_INTEGER lastCounter = mStartCount;

	int error = glGetError();
	if (m_pScene)
	{
		m_pScene->Render();

		glRasterPos2f(-1.0f, 0.8f);
		static TCHAR temp[100];
		_stprintf(temp, "Time:%3d", (int)mRunTime);
		drawString(temp);
		glRasterPos2f(-1.0f, 0.6f);
		_stprintf(temp, "FPS :%3d", (int)mFPS);
		drawString(temp);
		glRasterPos2f(0.5f, 0.8f);
		_stprintf(temp, "ʹ�ô浵:%2d", LoadGameScene::mUsedRecord);
		drawCNString(temp);
		
	}
	error = glGetError();
	LARGE_INTEGER currentCounter;
	QueryPerformanceCounter(&currentCounter);

	// ��֮֡���ʱ����
	mDeltaTime = (float)(currentCounter.LowPart - lastCounter.LowPart) / mFrequency.LowPart;
	mRunTime += mDeltaTime;
	mFPS = 1.0f / mDeltaTime;	// ���㵱ǰ��֡��
	
	int iDt = mDeltaTime * 1000;
	mFrameTime = mFrameTime > iDt ? mFrameTime - iDt : 1;
	lastCounter = currentCounter;	// �ѵ�ǰ�ļ����������ھ�̬������
}
void GameFrame::Updata()
{
	if (m_pScene)
	{
		m_pScene->Updata();
	}
	m_pGameInput->Update();
}
void GameFrame::End()
{
	if (m_pGameFrame)
	{
		delete m_pGameFrame;
		m_pGameFrame = 0;
	}
}
GameFrame* GameFrame::GetObject()
{
	if (!m_pGameFrame)
		m_pGameFrame = new GameFrame;
	return m_pGameFrame;
}
GameOutput* GameFrame::GetGO()
{
	return m_pGameOutput;
}
GameInput* GameFrame::GetGI()
{
	return m_pGameInput;
}

BOOL GameFrame::LoadScene(Scene* pScene, const string ID)
{
	if (!m_Scene[ID])
	{
		pScene->Init();
		m_Scene[ID] = pScene;
	}
	else
		return FALSE;
	return TRUE;
}
BOOL GameFrame::ReleaseScene(const string ID)
{
	map<string, Scene*>::iterator i = m_Scene.find(ID);
	if (i == m_Scene.end())
		return FALSE;
	i->second->End();
	delete i->second;
	m_Scene.erase(i);
	return TRUE;
}
BOOL GameFrame::SetScene(const string ID)
{
	map<string, Scene*>::iterator i = m_Scene.find(ID);
	if (i == m_Scene.end())
		return FALSE;
	if (m_pScene)
		m_pScene->Quit();
	m_pScene = i->second;
	m_pScene->Enter();
	return TRUE;
}
Scene* GameFrame::GetScene(const string ID)
{
	map<string, Scene*>::iterator i = m_Scene.find(ID);
	return i != m_Scene.end() ? i->second : 0;
}
Scene* GameFrame::GetNowScene()
{
	return m_pScene;
}
