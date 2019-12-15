#version 430
layout(location = 0) in vec3 vPosition;		 
uniform mat4 matModel,matProjView;	
uniform mat4 matMVP;	
out vec3 posWorld;
out vec3 posModel;
void main()
{
	posWorld = vec4(matModel* vec4(vPosition, 1.0)).xyz;
	posModel = vPosition;
	gl_Position = matMVP*vec4(vPosition, 1.0);
}