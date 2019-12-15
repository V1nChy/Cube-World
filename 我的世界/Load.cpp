#include "Load.h"
#include "GameFrame.h"

BOOL LoadGameScene::mIsLoading = FALSE;
int LoadGameScene::mRecordNum = 0;
int LoadGameScene::mUsedRecord = 0;
void LoadGameScene::Init()
{
	//LoadFile("Res\\saves\\record.txt");
	mRecordNum = 4;
	mUsedRecord = 1;
	
	LoadButton(new cButton1(point3(0, 0.6, 0), "Res\\textures\\buttons\\´æµµ1in.png", "Res\\textures\\buttons\\´æµµ1out.png"), BUTTON, 1, "Game³¡¾°");
	LoadButton(new cButton1(point3(0, 0.3, 0), "Res\\textures\\buttons\\´æµµ2in.png", "Res\\textures\\buttons\\´æµµ2out.png"), BUTTON, 2, "Game³¡¾°");
	LoadButton(new cButton1(point3(0, 0.0, 0), "Res\\textures\\buttons\\´æµµ3in.png", "Res\\textures\\buttons\\´æµµ3out.png"), BUTTON, 3, "Game³¡¾°");
	LoadButton(new cButton1(point3(0, -0.3, 0), "Res\\textures\\buttons\\´æµµ4in.png", "Res\\textures\\buttons\\´æµµ4out.png"), BUTTON, 4, "Game³¡¾°");

	LoadObject(new cPlane("Res\\textures\\background.png"), -1, 0);
}
void LoadGameScene::Enter()
{

	mIsLoading = TRUE;
	
	GameFrame::GetObject()->GetGI()->ResetCamera();
	GameFrame::GetObject()->GetGI()->mMatView = mat4() * Translate(0.0, 0.0, -2.0);

	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->mActive = FALSE;
		i->second->mClick = FALSE;
	}
}

void LoadGameScene::LoadFile(const char* pathName)
{
	ifstream in;
	in.open(pathName);
	char str[100];
	if (in.is_open())
	{
		while (!in.eof())
		{
			in.getline(str,100);
			switch (str[0])
			{
			case 'n': {
				sscanf_s(str + 2, "%d", &mRecordNum);
			}break;
			}
		}

	}
	in.close();
}
void LoadGameScene::Updata()
{
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		if (i->second->mActive && i->second->mClick)
		{
			if (i->second->ID == 1)
			{
				mUsedRecord = 1;
				GameFrame::GetObject()->SetScene("Game³¡¾°");
			}
			else if (i->second->ID == 2)
			{
				mUsedRecord = 2;
				GameFrame::GetObject()->SetScene("Game³¡¾°");
			}
			else if (i->second->ID == 3)
			{
				mUsedRecord = 3;
				GameFrame::GetObject()->SetScene("Game³¡¾°");
			}
			else if (i->second->ID == 4)
			{
				mUsedRecord = 4;
				GameFrame::GetObject()->SetScene("Game³¡¾°");
			}
		}
	}
}
void LoadGameScene::RenderForSelect(mat4 vp)
{
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->RenderForSelect(vp);
	}
}
void LoadGameScene::Quit()
{
}
void LoadGameScene::End()
{
	delete mBg;
}