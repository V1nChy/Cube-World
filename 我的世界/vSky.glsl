#version 140
//��յ�������Ч��һ����Ľ�
in vec2 vTexCoord;
in  vec3 vPosition;	

out vec2 texCoord;
out float fogFactor;
uniform mat4 ModelView;		// ģ�Ӿ���
uniform mat4 Projection;	// ͶӰ����
void main()
{
    gl_Position=Projection*ModelView*vec4(vPosition,1.0);
    texCoord=vTexCoord;

	 const float LOG2 = 1.442695;
     float fogDensity = 0.02;              //����������������Ũ�ȣ�Խ����ԽŨ
    //gl_FogFragCoord = length(vViewPosition.xyz-gl_Vertex.xyz);   //�����ӵ��붥��ľ���

    gl_FogFragCoord = abs(gl_Position.z);                                     //������þ���Ч�ʽϸ�

	fogFactor = exp2( -fogDensity * fogDensity * gl_FogFragCoord * gl_FogFragCoord * LOG2 );//2��X�η�
    fogFactor = clamp(fogFactor, 0.0, 1.0);			//��ֹԽ��               
}