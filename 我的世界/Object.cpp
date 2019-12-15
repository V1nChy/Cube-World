#include "Object.h"
#include "Load.h"
#include "GameFrame.h"

int mExtent;
float* mAltitude;
float RandRange;

//yzx
int gTree[5][5][5] = {
	{
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,TREE_LOG,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 }
	},
	{
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,TREE_LOG,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 }
	},
	{
		{ 0,0,0,0,0 },
		{ 0,0,TREE_LEAVES,TREE_LEAVES,0 },
		{ 0,TREE_LEAVES,TREE_LOG,TREE_LEAVES,0 },
		{ 0,0,TREE_LEAVES,0,0 },
		{ 0,0,0,0,0 }
	},
	{
		{ 0,0,TREE_LEAVES,TREE_LEAVES,0 },
		{ TREE_LEAVES,TREE_LEAVES,0,TREE_LEAVES,TREE_LEAVES },
		{ TREE_LEAVES,TREE_LEAVES,TREE_LEAVES,TREE_LEAVES,TREE_LEAVES },
		{ 0,TREE_LEAVES,TREE_LEAVES,TREE_LEAVES,0 },
		{ 0,TREE_LEAVES,TREE_LEAVES,0,0 }
	},
	{
		{ 0,0,TREE_LEAVES,0,0 },
		{ 0,TREE_LEAVES,TREE_LEAVES,TREE_LEAVES,0 },
		{ 0,TREE_LEAVES,TREE_LEAVES,TREE_LEAVES,0 },
		{ 0,TREE_LEAVES,TREE_LEAVES,TREE_LEAVES,0 },
		{ 0,0,TREE_LEAVES,0,0 }
	}
};

materialStruct GrassMaterial = {
	color4(255,255,255,255) / 255.0,
	color4(255,255,255,255) / 255.0,
	color4(80,80,80,255) / 255.0,
	color4(0.0,0.0,0.0,0.0) / 255.0,
	5
};
materialStruct SandMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.2,0.2,0.2,1.0),
	color4(0.0,0.0,0.0,0.0),
	10
};
materialStruct BedrockBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.3,0.3,0.3,1.0),
	color4(0.0,0.0,0.0,0.0),
	50
};
materialStruct StoneBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.3,0.3,0.3,1.0),
	color4(0.0,0.0,0.0,0.0),
	8
};
materialStruct StoneBrickBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.3,0.3,0.3,1.0),
	color4(0.0,0.0,0.0,0.0),
	9
};
materialStruct BrickBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.3,0.3,0.3,1.0),
	color4(0.0,0.0,0.0,0.0),
	9
};
materialStruct PlanksBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.3,0.3,0.3,1.0),
	color4(0.0,0.0,0.0,0.0),
	10
};
materialStruct GlassBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.0,0.0,0.0,0.0),
	80
};
materialStruct ClayBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.0,0.0,0.0,0.0),
	70
};
materialStruct TreeBlockMaterial = {
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(1.0,1.0,1.0,1.0),
	color4(0.0,0.0,0.0,0.0),
	70
};

int cBlockMap::mNowBlock=0;
cBlockMap::cBlockMap()
{
	mMapWidth = 40;
	mMapHeight = 20;
	mMapDepth = 40;
	mModelTranslate *= Translate(-mMapWidth / 2.0, 0.0, -mMapDepth / 2.0);

	mGrassBlock = new cBlock(GRASS_BLOCK, "LightTexture", "Block2",&GrassMaterial, "Res\\textures\\blocks\\grass.png", "Res\\textures\\blocks\\grass_NORM.png");
	mSandBlock = new cBlock(SAND_BLOCK, "LightTexture", "Block", &SandMaterial, "Res\\textures\\blocks\\sand.png", "Res\\textures\\blocks\\sand_NORM.png");
	mStoneBlock = new cBlock(STONE_BLOCK, "LightTexture", "Block", &StoneBlockMaterial,"Res\\textures\\blocks\\stone.png", "Res\\textures\\blocks\\stone_NORM.png");
	mStoneBrickBlock = new cBlock(STONEBRICK_BLOCK, "LightTexture", "Block",&StoneBrickBlockMaterial, "Res\\textures\\blocks\\stonebrick.png", "Res\\textures\\blocks\\stonebrick_NORM.png");
	mBrickBlock = new cBlock(BRICK_BLOCK, "LightTexture", "Block",&BrickBlockMaterial, "Res\\textures\\blocks\\brick.png", "Res\\textures\\blocks\\brick_NORM.png");
	mPlanksBlock = new cBlock(PLANKS_BLOCK, "LightTexture", "Block",&PlanksBlockMaterial, "Res\\textures\\blocks\\plank.png", "Res\\textures\\blocks\\plank_NORM.png");
	mGlassBlock = new cBlock(GLASS_BLOCK, "LightTexture", "Block", &GlassBlockMaterial,"Res\\textures\\blocks\\glass.png");
	mClayBlock = new cBlock(CLAY_BLOCK, "LightTexture", "Block", &ClayBlockMaterial, "Res\\textures\\blocks\\clay.png");
	mBedrockBlock= new cBlock(BEDROCK_BLOCK, "LightTexture", "Block", &BedrockBlockMaterial, "Res\\textures\\blocks\\bedrock.png","Res\\textures\\blocks\\bedrock_NORM.png");

	mTreeLogBlock = new cBlock(TREE_LOG, "LightTexture", "Block2", &TreeBlockMaterial, "Res\\textures\\blocks\\treelog.png", "Res\\textures\\blocks\\treelog_NORM.png");
	mTreeLeavesBlock = new cBlock(TREE_LEAVES, "LightTexture", "Block", &TreeBlockMaterial, "Res\\textures\\blocks\\treeleaves.png");
}
cBlockMap::~cBlockMap()
{
	delete mGrassBlock;
	delete mSandBlock;
	delete mClayBlock;
	delete mStoneBlock;
	delete mStoneBrickBlock;
	delete mBrickBlock;
	delete mPlanksBlock;
	delete mGlassBlock;
}
void cBlockMap::Render()
{
	for (int z = 0; z < mMapDepth; z++)
	{
		for (int x = 0; x < mMapWidth; x++)
		{
			for (int y = 0; y < mMapHeight; y++)
			{
				switch (mBlockMap[z][y][x])
				{
				case GRASS_BLOCK: {
					mGrassBlock->Enter();
					mGrassBlock->bOnlyTex = FALSE;
					mGrassBlock->bNormalOn = TRUE;
					mGrassBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mGrassBlock->Render();
				}break;
				case SAND_BLOCK: {
					mSandBlock->Enter();
					mSandBlock->bOnlyTex = FALSE;
					mSandBlock->bNormalOn = TRUE;
					mSandBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mSandBlock->Render();
				}break;
				case CLAY_BLOCK: {
					mClayBlock->Enter();
					mClayBlock->bOnlyTex = FALSE;
					mClayBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mClayBlock->Render();
				}break;
				case STONE_BLOCK: {
					mStoneBlock->Enter();
					mStoneBlock->bOnlyTex = FALSE;
					mStoneBlock->bNormalOn = TRUE;
					mStoneBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mStoneBlock->Render();
				}break;
				case STONEBRICK_BLOCK: {
					mStoneBrickBlock->Enter();
					mStoneBrickBlock->bOnlyTex = FALSE;
					mStoneBrickBlock->bNormalOn = TRUE;
					mStoneBrickBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mStoneBrickBlock->Render();
				}break;
				case BRICK_BLOCK: {
					mBrickBlock->Enter();
					mBrickBlock->bOnlyTex = FALSE;
					mBrickBlock->bNormalOn = TRUE;
					mBrickBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mBrickBlock->Render();
				}break;
				case PLANKS_BLOCK: {
					mPlanksBlock->Enter();
					mPlanksBlock->bOnlyTex = FALSE;
					mPlanksBlock->bNormalOn = TRUE;
					mPlanksBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mPlanksBlock->Render();
				}break;
				case GLASS_BLOCK: {
					mvGlass.push_back(isPos{ x,y,z });
				}break;
				case BEDROCK_BLOCK: {
					mBedrockBlock->Enter();
					mBedrockBlock->bOnlyTex = FALSE;
					mBedrockBlock->bNormalOn = TRUE;
					mBedrockBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mBedrockBlock->Render();
				}break;
				case TREE_LOG: {
					mTreeLogBlock->Enter();
					mTreeLogBlock->bOnlyTex = FALSE;
					mTreeLogBlock->bNormalOn = TRUE;
					mTreeLogBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mTreeLogBlock->Render();
				}break;
				case TREE_LEAVES: {
					mTreeLeavesBlock->Enter();
					mTreeLeavesBlock->bOnlyTex = FALSE;

					mTreeLeavesBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mTreeLeavesBlock->Render();
				}break;
				}
			}
		}
	}
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	for (int i = 0; i < mvGlass.size(); i++)
	{
		mGlassBlock->Enter();
		//mGlassBlock->bOnlyTex = FALSE;
		mGlassBlock->SetModelMat(mModelTranslate*Translate(mvGlass[i].x, mvGlass[i].y, mvGlass[i].z));
		mGlassBlock->Render();
	}
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	mvGlass.clear();
}
void cBlockMap::RenderForSelect(mat4 vp)
{
	for (int z = 0; z < mMapDepth; z++)
	{
		for (int x = 0; x < mMapWidth; x++)
		{
			for (int y = 0; y < mMapHeight; y++)
			{
				switch (mBlockMap[z][y][x])
				{
				case GRASS_BLOCK: {
					//1282
					mGrassBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mGrassBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mGrassBlock->RenderForSelect(vp);

				}break;
				case SAND_BLOCK: {
					mSandBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mSandBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mSandBlock->RenderForSelect(vp);
					
				}break;
				case CLAY_BLOCK: {
					mClayBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mClayBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mClayBlock->RenderForSelect(vp);
					
				}break;
				case STONE_BLOCK: {
					mStoneBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mStoneBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mStoneBlock->RenderForSelect(vp);
					
				}break;
				case STONEBRICK_BLOCK: {
					mStoneBrickBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mStoneBrickBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mStoneBrickBlock->RenderForSelect(vp);
					
				}break;
				case BRICK_BLOCK: {
					mBrickBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mBrickBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mBrickBlock->RenderForSelect(vp);
				}break;
				case PLANKS_BLOCK: {
					mPlanksBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mPlanksBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mPlanksBlock->RenderForSelect(vp);
					
				}break;
				case GLASS_BLOCK: {
					mGlassBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mGlassBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mGlassBlock->RenderForSelect(vp);
				}break;
				case BEDROCK_BLOCK: {
					mBedrockBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mBedrockBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mBedrockBlock->RenderForSelect(vp);
				}break;
				case TREE_LOG: {
					mTreeLogBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mTreeLogBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mTreeLogBlock->RenderForSelect(vp);
					
				}break;
				case TREE_LEAVES: {
					mTreeLeavesBlock->Enter();
					glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matModel, 1, GL_TRUE, Translate(x, y, z));
					glUniform3ui(GameFrame::GetObject()->GetGI()->H_xyzPos, x, y, z);
					mTreeLeavesBlock->SetModelMat(mModelTranslate*Translate(x, y, z));
					mTreeLeavesBlock->RenderForSelect(vp);
					
				}break;
				}
			}
		}
	}
}
void cBlockMap::Update(int px, int py, int pz, point3* fPos, point3 &cPos, int value)
{
	if (value < 0)//删除方块
	{
		mBlockMap[pz][py][px] = 0;
	}
	else//增加方块
	{
		//获取在哪个方向增加
		int dirt;
		if (fPos[0][0] == fPos[1][0] && fPos[0][0] == fPos[2][0])
		{
			if (fPos[0][0] < px)
				dirt = LEFT;
			else
				dirt = RIGHT;
		}
		else if (fPos[0][1] == fPos[1][1] && fPos[0][1] == fPos[2][1])
		{
			if (fPos[0][1] < py)
				dirt = DOWN;
			else
				dirt = UP;
		}
		else if (fPos[0][2] == fPos[1][2] && fPos[0][2] == fPos[2][2])
		{
			if (fPos[0][2] < pz)
				dirt = BACK;
			else
				dirt = FRONT;
		}
		//上下左右前后增加方块的情况
		switch (dirt)
		{
		case 0:
		{
			py += 1;
		}break;
		case 1:
		{
			py -= 1;
		}break;
		case 2:
		{
			px -= 1;
		}break;
		case 3:
		{
			px += 1;
		}break;
		case 4:
		{
			pz += 1;
		}break;
		case 5:
		{
			pz -= 1;
		}break;
		}
		int cx = cPos.x + mMapWidth / 2.0 + 0.5;
		int cy = cPos.y;
		int cz = cPos.z + mMapDepth / 2.0 + 0.5;
		if (cx != px || cz != pz)
			mBlockMap[pz][py][px] = mNowBlock;
	}
}

BOOL cBlockMap::Collision(float x, float y, float z)
{
	int width = x + mMapWidth / 2.0 + 0.5;
	int height = y;
	int depth = z + mMapDepth / 2.0 + 0.5;

	return mBlockMap[depth][height][width]>0 ? 1 : 0;
}

void cBlockMap::BuildMap()
{
	//地势形成相关
	int nDivide = 4;
	mExtent = pow(2, nDivide) + 1;	//行数33
	int mTotVertexNum = mExtent*mExtent;
	mAltitude = new float[mTotVertexNum];
	RandRange = 5.0;			//决定地形高度

								//初始化高度数组及4个初始点
	//memset(mAltitude, -1, mTotVertexNum);
	mAltitude[0] = 1;
	mAltitude[mExtent - 1] = 1;
	mAltitude[mExtent*(mExtent - 1)] = 1;
	mAltitude[mTotVertexNum - 1] = 1;

	divide(0, mExtent - 1, 0);

	memset(mBlockMap, -1, sizeof(mBlockMap));
	int offsetX = (mMapWidth - mExtent) / 2;
	int offsetZ = (mMapDepth - mExtent) / 2+5;
	for (int z = 0; z < mExtent && (z + offsetZ)<mMapDepth; z++)
	{
		for (int x = 0; x < mExtent && (x + offsetX)<mMapWidth; x++)
		{
			for (int y = 0; y < mAltitude[z*mExtent + x] && y<mMapHeight; y++)
			{
				if(y == ((int)mAltitude[z*mExtent + x]))
					mBlockMap[z + offsetZ][y][x + offsetX] = GRASS_BLOCK;
				else
					mBlockMap[z + offsetZ][y][x + offsetX] = STONE_BLOCK;
			}
		}
	}

	//圆形地基
	int centerX = 20;
	int centerZ = 20;
	int radius = 16;
	float dis;
	for (int z = 0; z < mMapDepth; z++)
	{
		for (int x = 0; x < mMapWidth; x++)
		{
			dis = (x - centerX)*(x - centerX) + (z - centerZ)*(z - centerZ);
			if (sqrtf(dis) < radius)
			{
				int temp;
				temp = rand() % 10;
				if (sqrtf(dis) > 11)
				{
					if (temp < 8)
						mBlockMap[z][0][x] = SAND_BLOCK;
					else
						mBlockMap[z][0][x] = GRASS_BLOCK;
				}
				else
				{
					if (temp < 8)
						mBlockMap[z][0][x] = GRASS_BLOCK;
					else
						mBlockMap[z][0][x] = SAND_BLOCK;
				}
			}
		}
	}

	//树木位置定位
	int treeNum = 15;
	int locateX;
	int LocateY=0;
	int LocateZ;
	dis = 0;

	while (treeNum > 0)
	{
		do
		{
			locateX = rand() % mMapWidth;
			LocateZ = rand() % mMapWidth;
			dis = (locateX - centerX)*(locateX - centerX) + (LocateZ - centerZ)*(LocateZ - centerZ);
			if (sqrt(dis) <= 13)
			{
				while (mBlockMap[LocateZ][LocateY][locateX] > 0)
				{
					LocateY++;
				}
				if (LocateY > 4)
					LocateY = 100000;
			}
		} while (sqrt(dis) > 13);

		locateX -= 2;
		LocateZ -= 2;
		for (int y = 0; y < 5; y++)
		{
			for (int z = 0; z < 5; z++)
			{
				for (int x = 0; x < 5; x++)
				{
					if(mBlockMap[LocateZ + z][LocateY + y][locateX + x]<=0)
						mBlockMap[LocateZ + z][LocateY + y][locateX + x] = gTree[y][z][x];
				}
			}
		}
		LocateY = 0;
		treeNum--;
	}
	delete mAltitude;
}
void cBlockMap::divide(int begin, int offset, int n)
{
	if (offset < 2)
		return;
	int a = begin;
	int b = a + offset*mExtent;
	int c = b + offset;
	int d = a + offset;

	int s = pow(2, n);

	while (mAltitude[(a + d) / 2] <= 0)
		mAltitude[(a + d) / 2] = (mAltitude[a] + mAltitude[d]) / 2 + (-RandRange / s + rand() % 10 * (RandRange / s * 2.0 / 10.0));

	while (mAltitude[(b + c) / 2] <= 0)
		mAltitude[(b + c) / 2] = (mAltitude[b] + mAltitude[c]) / 2 + (-RandRange / s + rand() % 10 * (RandRange / s * 2.0 / 10.0));

	while (mAltitude[(a + b) / 2] <= 0)
		mAltitude[(a + b) / 2] = (mAltitude[a] + mAltitude[b]) / 2 + (-RandRange / s + rand() % 10 * (RandRange / s * 2.0 / 10.0));

	while (mAltitude[(d + c) / 2] <= 0)
		mAltitude[(d + c) / 2] = (mAltitude[d] + mAltitude[c]) / 2 + (-RandRange / s + rand() % 10 * (RandRange / s * 2.0 / 10.0));

	while (mAltitude[(a + c) / 2] <= 0)
		mAltitude[(a + c) / 2] = (mAltitude[(a + d) / 2] + mAltitude[(b + c) / 2]
			+ mAltitude[(a + b) / 2] + mAltitude[(d + c) / 2]) / 4 + (-RandRange / s + rand() % 10 * (RandRange / s * 2.0 / 10.0));

	divide(a, offset / 2, n + 1);
	divide((a + d) / 2, offset / 2, n + 1);
	divide((a + b) / 2, offset / 2, n + 1);
	divide((a + c) / 2, offset / 2, n + 1);
}
int cBlockMap::SearchHigh(float x, float z)
{
	int width = x + mMapWidth / 2.0 + 0.5;
	int depth = z + mMapDepth / 2.0 + 0.5;
	int height = 0;
	while (mBlockMap[depth][height][width] > 0)
	{
		height++;
	}
	return height-1;
}
void cBlockMap::LoadMap()
{
	memset(mBlockMap, -1, sizeof(mBlockMap));
	char temp[100];
	isPos pos;
	int value;
	_stprintf(temp, "Res\\saves\\%d.txt", LoadGameScene::mUsedRecord);
	ifstream in;
	in.open(temp);
	char str[100];
	if (in.is_open())
	{
		while (!in.eof())
		{
			in.getline(str, 100);
			switch (str[0])
			{
			case 'n': {
			
			}break;
			case 'v': {
				sscanf_s(str + 2, "%d %d %d %d", &pos.x, &pos.y, &pos.z, &value);
				mBlockMap[pos.z][pos.y][pos.x] = value;
			}break;
			case 'c': {
				float pc[3];
				sscanf_s(str + 2, "( %f, %f, %f", &pc[0], &pc[1], &pc[2]);
				//printf("%f %f %f\n", pc[0], pc[1], pc[2]);
				GameFrame::GetObject()->GetGI()->mMatCameraReverse = mat4()*Translate(pc[0], pc[1], pc[2]);
				GameFrame::GetObject()->GetGI()->mMatCamera = mat4()*Translate(-pc[0], -pc[1], -pc[2]);
			}break;
			}
			//printf("%d %d %d %d\n", pos.x, pos.y, pos.z, value);
		}

	}
	in.close();
}
void cBlockMap::SaveMap()
{
	char temp[100];
	_stprintf(temp, "Res\\saves\\%d.txt", LoadGameScene::mUsedRecord);
	ofstream out;
	out.open(temp);
	int num = 0;
	for (int z = 0; z < mMapDepth; z++)
	{
		for (int x = 0; x < mMapWidth; x++)
		{
			for (int y = 0; y < mMapHeight; y++)
			{
				if (mBlockMap[z][y][x] > 0)
				{
					_stprintf(temp, "v	%d %d %d %d", x, y, z, mBlockMap[z][y][x]);
					out << temp << endl;
					num++;
				}
			}
		}
	}
	out << "n	"<<num << endl;
	out << "c	"<<GameFrame::GetObject()->GetGI()->mCameraPos << endl;
	out.close();
}

cObject::cObject() :
	mPrimi(NULL),
	mUseShader(NULL),
	mMaterial(NULL),
	bOnlyTex(TRUE),
	bNormalOn(FALSE)
{}
cObject::~cObject()
{
	delete mPrimi;
	delete mUseShader;
	delete mMaterial;
}
void cObject::Init() {

}
void cObject::Enter() 
{
	int error = glGetError();
	if (mUseShader)
		mUseShader->Enter();
	error = glGetError();
	if(mPrimi)
		mPrimi->Enter(mUseShader->vPosition, mUseShader->vNormal, mUseShader->vTexCoord, mUseShader->vTangent);
	if (mMaterial)
		SetMaterial();
	error = glGetError();
	if (mTex != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTex);
	}
	if (bNormalOn)
	{
		glUniform1i(mUseShader->TexNormalOn, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mNormalTex);
	}
	else
	{
		glUniform1i(mUseShader->TexNormalOn, 0);
	}
	if(bOnlyTex)
		glUniform1i(mUseShader->bOnlyTexture, 1);
	else
	{
		glUniform1i(mUseShader->bOnlyTexture, 0);
		vec4 lightPos(-1.0, 5.0, -5.0, 0.0);
		glUniform4fv(mUseShader->LightPosition, 1, GameFrame::GetObject()->GetGI()->mMatView*lightPos);
		//glUniform4fv(mUseShader->LightPosition + 1, 1, GameFrame::GetObject()->GetGI()->mMatView*vec4(0.0, 0.0, 0.0, 1.0));
	}
}
void cObject::Render() {
	mPrimi->Render();
}
void cObject::RenderForSelect(mat4 vp)
{
	glUniform2ui(GameFrame::GetObject()->GetGI()->H_id, ID, idParent);
	glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matMVP, 1, GL_TRUE, vp*mModelTranslate);
	mPrimi->Render();
}
void cObject::End() {}
void cObject::Update(point3 pos, int offset)
{}
void cObject::SetModelMat(mat4 mat)
{
	mModelTranslate = mat;
}
void cObject::SetMaterial()
{
	glUniform4fv(mUseShader->MaterialAmbientProduct, 1, mMaterial->ambient);
	glUniform4fv(mUseShader->MaterialDiffuseProduct, 1, mMaterial->diffuse);
	glUniform4fv(mUseShader->MaterialSpecularProduct, 1, mMaterial->specular);
	glUniform1f(mUseShader->Shininess, mMaterial->shininess);
	glUniform4fv(mUseShader->Emission, 1, mMaterial->emission);
}

cButton::cButton():cObject()
{
	mActive = FALSE;
	mClick = FALSE;
}
void cButton::SetActive()
{}
void cButton::SetUnActive()
{}

cButton1::cButton1(point3 pos, const char* in, const char* out) : cButton()
{
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer("LightTexture");
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer("Face");
	mModelTranslate *= Translate(pos.x, pos.y, pos.z)*Scale(1.0, 0.1, 0.1);

	glGenTextures(1, &mOutTex);
	glBindTexture(GL_TEXTURE_2D, mOutTex);
	LoadTexture(out);

	glGenTextures(1, &mInTex);
	glBindTexture(GL_TEXTURE_2D, mInTex);
	LoadTexture(in);
}
void cButton1::Render()
{
	if (mActive)
		glBindTexture(GL_TEXTURE_2D, mInTex);
	else
		glBindTexture(GL_TEXTURE_2D, mOutTex);

	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate);
	glUniform1i(mUseShader->bOnlyTexture, 1);
	mPrimi->Render();
}

cGoodsButton::cGoodsButton(point3 pos, const char* pathTex) : cButton()
{
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer("LightTexture");
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer("Face");
	mModelTranslate *= Translate(pos.x, pos.y, pos.z)*Scale(0.1,0.1,0.1);
	mUnactiveMat = mModelTranslate;
	mActiveMat = mModelTranslate*Scale(1.15, 1.15, 1.15);

	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture(pathTex);

}
void cGoodsButton::SetActive()
{
	mModelTranslate = mActiveMat;
}
void cGoodsButton::SetUnActive()
{
	mModelTranslate = mUnactiveMat;
}
void cGoodsButton::Render()
{
	//glBindTexture(GL_TEXTURE_2D, mTex);
	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, mModelTranslate);
	//glUniform1i(mUseShader->bOnlyTexture, 1);
	mPrimi->Render();
}


cBlock::cBlock(int id, char* shader, char* primi, char* pathTex):cObject()
{
	ID = id;
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer(shader);
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer(primi);

	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture(pathTex);
}
cBlock::cBlock(int id,char* shader,char* primi, materialStruct* material,char* pathTex) :cObject()
{
	ID = id;
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer(shader);
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer(primi);
	mMaterial = material;

	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture(pathTex);
}
cBlock::cBlock(int id, char* shader, char* primi, materialStruct* material, char* pathTex, char* pathNorTex)
{
	ID = id;
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer(shader);
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer(primi);
	mMaterial = material;

	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture(pathTex);

	glGenTextures(1, &mNormalTex);
	glBindTexture(GL_TEXTURE_2D, mNormalTex);
	LoadTexture(pathNorTex);
}
void cBlock::Render()
{
	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate);
	//glUniform1i(mUseShader->bOnlyTexture, 1);

	mPrimi->Render();
}
void cBlock::RenderForSelect(mat4 vp)
{
	glUniform2ui(GameFrame::GetObject()->GetGI()->H_id, ID, TERRAIN);
	glUniformMatrix4fv(GameFrame::GetObject()->GetGI()->H_matMVP, 1, GL_TRUE, vp*mModelTranslate);
	mPrimi->Render();
}

cPlane::cPlane(const char* pathName) :cObject()
{
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer("LightTexture");
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer("Face");
	mModelTranslate *= Scale(2.0, 1.2, 1.0);

	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture(pathName);
}
void cPlane::Render()
{
	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate);
	//glUniform1i(mUseShader->bOnlyTexture, 1);

	mPrimi->Render();
}