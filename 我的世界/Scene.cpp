#include"Scene.h"

CSoundManage Scene::mSoundPlay;
Scene::Scene():
mDirButton(0),
mDirObject(0)
{
	mMap = NULL;
}
Scene::~Scene()
{
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->End();
		delete i->second;
	}
	mButtonMap.clear();
	map<int, cObject*>::iterator j;
	for (j = m_ObjectMap.begin(); j != m_ObjectMap.end(); j++)
	{
		j->second->End();
		delete j->second;
	}
	m_ObjectMap.clear();
}

BOOL Scene::LoadButton(cButton* pButton, const int parentID,const int ID, const string TargetID)
{
	if (mButtonMap[ID])
		return FALSE;
	pButton->mTargetSceneName = TargetID;
	pButton->Init();
	pButton->idParent = parentID;
	pButton->ID = ID;
	mButtonMap[ID] = pButton;
}
BOOL Scene::ReleaseButton(const int ID)
{
	map<int, cButton*>::iterator i = mButtonMap.find(ID);
	if (i == mButtonMap.end())
		return FALSE;
	i->second->End();
	mButtonMap.erase(i);
	delete i->second;
}
BOOL Scene::SetButton(const int ID)
{
	if (ID<0)
		mDirButton = 0;
	else
	{
		map<int, cButton*>::iterator i = mButtonMap.find(ID);
		if (i == mButtonMap.end())
			return FALSE;
		mDirButton = i->second;
	}
	return TRUE;
}

BOOL Scene::LoadObject(cObject* pUI, const int parentID, const int ID)
{
	if (m_ObjectMap[ID])
		return FALSE;
	pUI->Init();
	pUI->idParent = parentID;
	pUI->ID = ID;
	m_ObjectMap[ID] = pUI;
}
BOOL Scene::ReleaseObject(const int ID)
{
	map<int, cObject*>::iterator i = m_ObjectMap.find(ID);
	if (i == m_ObjectMap.end())
		return FALSE;
	i->second->End();
	m_ObjectMap.erase(i);
	delete i->second;
}
BOOL Scene::SetObject(const int ID)
{

	map<int, cObject*>::iterator i = m_ObjectMap.find(ID);
	if (i == m_ObjectMap.end())
		return FALSE;
	mDirObject = i->second;
	return TRUE;
}
cObject* Scene::GetObjectID(const int ID)
{
	map<int, cObject*>::iterator i = m_ObjectMap.find(ID);
	if (i == m_ObjectMap.end())
		return NULL;
	return i->second;
}

void Scene::Init(){}
void Scene::Enter(){}
void Scene::Render()
{
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->Enter();
		i->second->Render();
	}

	map<int, cObject*>::iterator j;
	for (j = m_ObjectMap.begin(); j != m_ObjectMap.end(); j++)
	{
		j->second->Enter();
		j->second->Render();
	}
}
void Scene::RenderForSelect(mat4 vp)
{
}
void Scene::Updata(){}
void Scene::Quit(){}
void Scene::End(){}