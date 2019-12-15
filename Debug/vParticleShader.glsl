#version 430
in vec3 vPosition;

uniform mat4 ModelView;		// ģ�Ӿ���
uniform mat4 Projection;	// ͶӰ����

void main()
{
    gl_Position = ModelView * vec4(vPosition,1.0);
}