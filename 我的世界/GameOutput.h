#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include "BasicData.h"
#include "Object.h"

class GameOutput
{
	map<string, cShaderData*> mShaderMap;
	map<string, cPrimitive*> mPrimiMap;
public:
	GameOutput();
	~GameOutput();

	 void Init();

	 static cShaderData* m_pShaderID;
	 BOOL LoadShader();
	 BOOL SetShader(const string nameID);
	 cShaderData* GetShaderPointer(const string nameID);

	 cPrimitive* m_pPrimiID;
	 BOOL LoadPrimi();
	 BOOL SetPrimi(const string nameID);
	 cPrimitive* GetPrimiPointer(const string nameID);
};

int LoadTexture(const char *szPathName);
#endif