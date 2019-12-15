#ifndef _SHADER_DATA_H_
#define _SHADER_DATA_H_

#include "Angel.h"
#include "BasicData.h"

class cShaderData
{
public:

	GLuint program;

	GLuint vPosition;
	GLuint vTexCoord;
	GLuint vNormal;
	GLuint vTangent;

	GLuint LightAmbientProduct, LightDiffuseProduct, LightSpecularProduct;
	GLuint MaterialAmbientProduct, MaterialDiffuseProduct, MaterialSpecularProduct;
	GLuint Shininess, Emission;

	GLuint ModelView;
	GLuint Projection;

	GLuint cTex, nTex, cubeTex;

	GLuint LightPosition;
	GLuint LightOn;
	GLuint Time;

	GLuint TexNormalOn;
	GLuint bOnlyTexture;
	GLuint bFogOn;

	virtual void Init();
	virtual void Enter();
	virtual void SetLightMaterial(const int lightNum, const lightingStruct light[]);
};
class cSkyShader :public cShaderData
{
public:
	cSkyShader();
};
class cLightTextureShader :public cShaderData
{
public:
	cLightTextureShader();
};
class cWaterShader :public cShaderData
{
public:
	cWaterShader();
};
class cParticleShader :public cShaderData
{
public:
	cParticleShader();
};

#endif
