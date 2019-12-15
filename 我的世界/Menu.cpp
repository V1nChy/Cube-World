#include "Menu.h"
#include "Load.h"
#include "GameFrame.h"

void MenuScene::Init()
{
	LoadButton(new cButton1(point3(0, -0.4, 0),"Res\\textures\\buttons\\新的世界in.png", "Res\\textures\\buttons\\新的世界out.png"), BUTTON,NEW_GAME,"Game场景");
	LoadButton(new cButton1(point3(0, -0.7, 0), "Res\\textures\\buttons\\读取存档in.png", "Res\\textures\\buttons\\读取存档out.png"), BUTTON,LOAD_GAME, "Load场景");
	LoadButton(new cButton1(point3(0, -1.0, 0), "Res\\textures\\buttons\\退出游戏in.png", "Res\\textures\\buttons\\退出游戏out.png"), BUTTON,EXIT_GAME, "");

	LoadObject(new cPlane("Res\\textures\\cover.png"),-1, BACKGROUND);
}
void MenuScene::Enter()
{
	GameFrame::GetObject()->GetGI()->mButtonSelect = TRUE;
	GameFrame::GetObject()->GetGI()->ResetCamera();
	mat4 mat;
	mat*= Translate(0.0,0.0,-2.0);
	GameFrame::GetObject()->GetGI()->mMatView = mat;

	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->mActive = FALSE;
		i->second->mClick = FALSE;
	}
	mSoundPlay.play(MENU_BGM);
}
void MenuScene::Updata()
{
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		if (i->second->mActive && i->second->mClick)
		{
			if (i->second->ID == NEW_GAME)
			{
				LoadGameScene::mIsLoading = FALSE;
				/*if(LoadGameScene::mRecordNum<1)
					LoadGameScene::mRecordNum += 1;
				LoadGameScene::mUsedRecord = LoadGameScene::mRecordNum;
				char temp[100];
				_stprintf(temp, "n	%d", LoadGameScene::mRecordNum);
				ofstream out;
				out.open("Res\\saves\\record.txt");

				out << "#我的世界 archive Game record" << endl;
				out << temp << endl;

				out.close();*/
				GameFrame::GetObject()->SetScene(i->second->mTargetSceneName);
			}
			else if (i->second->ID == LOAD_GAME)
			{
				GameFrame::GetObject()->SetScene(i->second->mTargetSceneName);
			}
			else if (i->second->ID == EXIT_GAME)
			{
				exit(0);
			}
		}
	}
}
void MenuScene::RenderForSelect(mat4 vp)
{
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->RenderForSelect(vp);
	}
}
void MenuScene::Quit()
{

}
void MenuScene::End()
{
	delete mBg;
}