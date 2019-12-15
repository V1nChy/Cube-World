#include "ShaderData.h"
#include "GameFrame.h"

lightingStruct whiteLight = {
	color4(0.5,0.5,0.5,1.0),
	color4(0.8,0.8,0.8,1.0),
	color4(1.0,1.0,1.0,1.0)
};
lightingStruct redLight = {
	color4(0.2,0.0,0.0,1.0),
	color4(1.0,0.0,0.0,1.0),
	color4(1.0,0.0,0.0,1.0)
};
lightingStruct yellowLight = {
	color4(0.0,0.0,0.0,1.0),
	color4(1.0,1.0,0.0,1.0),
	color4(1.0,1.0,0.0,1.0)
};
lightingStruct Lights[] = { whiteLight,redLight,yellowLight };

void cShaderData::Init()
{
}
void cShaderData::Enter()
{
	int error = glGetError();
	glUseProgram(program);
	error = glGetError();
	error = 0;
	glUniformMatrix4fv(Projection, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatProjection);
	error = glGetError();
}
void cShaderData::SetLightMaterial(const int lightNum, const lightingStruct light[])
{
	for (int i = 0; i < lightNum; i++)
	{
		glUniform4fv(LightAmbientProduct + i, 1, light[i].ambient);
		glUniform4fv(LightDiffuseProduct + i, 1, light[i].diffuse);
		glUniform4fv(LightSpecularProduct + i, 1, light[i].specular);
	}
}

cSkyShader::cSkyShader()
{
	program = InitShader("vSky.glsl", "fSky.glsl", 0);

	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition");
	vTexCoord = glGetAttribLocation(program, "vTexCoord");

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");

	cTex = glGetUniformLocation(program, "tex");
	glUniform1i(cTex, 0);
}
cLightTextureShader::cLightTextureShader()
{
	program = InitShader("vLightTexture.glsl", "fLightTexture.glsl",0);

	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition");
	vNormal = glGetAttribLocation(program, "vNormal");
	vTexCoord = glGetAttribLocation(program, "vTexCoord");
	vTangent = glGetAttribLocation(program, "vTangent");

	LightAmbientProduct = glGetUniformLocation(program, "LightAmbientProduct");
	LightDiffuseProduct = glGetUniformLocation(program, "LightDiffuseProduct");
	LightSpecularProduct = glGetUniformLocation(program, "LightSpecularProduct");
	MaterialAmbientProduct = glGetUniformLocation(program, "MaterialAmbientProduct");
	MaterialDiffuseProduct = glGetUniformLocation(program, "MaterialDiffuseProduct");
	MaterialSpecularProduct = glGetUniformLocation(program, "MaterialSpecularProduct");
	Shininess = glGetUniformLocation(program, "Shininess");
	Emission = glGetUniformLocation(program, "Emission");

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");

	bFogOn = glGetUniformLocation(program, "FogOn");
	bOnlyTexture = glGetUniformLocation(program, "bOnlyTexture");
	LightOn = glGetUniformLocation(program, "LightOn");
	TexNormalOn = glGetUniformLocation(program, "TexNormalOn");

	LightPosition = glGetUniformLocation(program, "LightPosition");

	glUniform4fv(LightPosition + 2, 1, vec4(0.0, 0.0, 0.0, 1.0));
	glUniform1i(LightOn, 1);
	glUniform1i(LightOn + 1, 0);
	glUniform1i(LightOn + 2, 0);

	glUniform3fv(glGetUniformLocation(program, "SpotDirection"), 1, vec3(0.0, 0.0, -1.0));
	glUniform1f(glGetUniformLocation(program, "SpotCutOff"), 8);
	glUniform1f(glGetUniformLocation(program, "SpotExponent"), 3);

	cTex = glGetUniformLocation(program, "tex");
	nTex = glGetUniformLocation(program, "nTex");
	glUniform1i(cTex, 0);
	glUniform1i(nTex, 1);

	SetLightMaterial(3, Lights);
}
cWaterShader::cWaterShader()
{
	program = InitShader("vWaterShader.glsl", "fWaterShader.glsl", 0);

	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition");
	vNormal = glGetAttribLocation(program, "vNormal");
	vTexCoord = glGetAttribLocation(program, "vTexCoord");

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");
	LightPosition = glGetUniformLocation(program, "LightPosition");
	Time = glGetUniformLocation(program, "time");

	glUniform4fv(LightPosition, 1, vec4(0.0, 2.0, 0.0, 1.0));

	cTex = glGetUniformLocation(program, "tex");
	nTex = glGetUniformLocation(program, "nTex");
	cubeTex = glGetUniformLocation(program, "cubeTex");
	glUniform1i(cTex, 0);
	glUniform1i(nTex, 1);
	glUniform1i(cubeTex, 2);
}
cParticleShader::cParticleShader()
{
	program = InitShader("vParticleShader.glsl", "fParticleShader.glsl", "gParticleShader.glsl");

	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition");

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");

	Time = glGetUniformLocation(program, "time");
	cTex = glGetUniformLocation(program, "tex");
	glUniform1i(cTex, 0);
}