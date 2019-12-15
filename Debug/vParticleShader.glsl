#version 430
in vec3 vPosition;

uniform mat4 ModelView;		// 模视矩阵
uniform mat4 Projection;	// 投影矩阵

void main()
{
    gl_Position = ModelView * vec4(vPosition,1.0);
}