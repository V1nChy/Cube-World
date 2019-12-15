#ifndef _GAME_FRAME_H_
#define _GAME_FRAME_H_

#include"BasicData.h"
#include"GameOutput.h"
#include"GameInput.h"
#include"Scene.h"

class GameFrame
{
private:
	static GameFrame* m_pGameFrame;

	GameOutput* m_pGameOutput;
	GameInput* m_pGameInput;
	map<string, Scene*> m_Scene;
	Scene* m_pScene;

	GameFrame();
public:
	~GameFrame();

	// ʱ�䡢֡��
	LARGE_INTEGER mFrequency;
	LARGE_INTEGER mStartCount;
	float mFPS;
	float mDeltaTime;
	int mFrameTime;
	float mRunTime;
	float mAspect;

	//������
	static GameFrame* GetObject();
	void Init();
	void LoadSound();
	void Render();
	void Updata();
	void End();
	//�������
	BOOL LoadScene(Scene* pScene, const string ID);
	BOOL ReleaseScene(const string ID);
	BOOL SetScene(const string ID);
	Scene* GetScene(const string ID);
	Scene* GetNowScene();

	GameOutput* GetGO();
	GameInput* GetGI();
};

#endif