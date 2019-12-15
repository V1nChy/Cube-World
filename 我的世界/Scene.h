#ifndef _SCENE_H_
#define _SCENE_H_

#include "Basicdata.h"
#include "Object.h"
#include "Res\\sound\\SoundManage.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	static CSoundManage mSoundPlay;
	cBlockMap* mMap;

	map<int, cButton*> mButtonMap;
	cButton* mDirButton;
	BOOL LoadButton(cButton* pButton, const int parentID, const int ID,const string TargetID);
	BOOL ReleaseButton(const int ID);
	BOOL SetButton(const int ID);

	map<int, cObject*> m_ObjectMap;
	cObject* mDirObject;
	BOOL LoadObject(cObject* pUI, const int parentID, const int ID);
	BOOL ReleaseObject(const int ID);
	BOOL SetObject(const int ID);
	cObject* GetObjectID(const int ID);

	virtual void Init();
	virtual void Enter();
	virtual void Render();
	virtual void RenderForSelect(mat4 vp);
	virtual void Updata();
	virtual void Quit();
	virtual void End();
};

#endif