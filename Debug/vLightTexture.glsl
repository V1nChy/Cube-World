#version 140 
//���գ���ͼ��������ͼ

const int LightNum = 3; // ��Դ����

in vec2 vTexCoord;
in  vec3 vPosition;	// ����λ��(��ģ����ϵ)
in  vec3 vNormal;	// ���㷨��(��ģ����ϵ)
in  vec3 vTangent;	// ������(��ģ����ϵ)

out vec2 texCoord;
out vec3 fN;	// ����(�۲�����ϵ)
out vec3 fE;	// �۲�����(�۲�����ϵ)
out vec3 fL[LightNum];	// ��������(�۲�����ϵ)
out float dist;	// ���㵽�ֵ�Ͳ��Դ����
out vec3 SpotDirect; // �������ռ�����ϵ�¾۹�����䷽��
out float fogFactor;

uniform mat4 ModelView;		// ģ�Ӿ���
uniform mat4 Projection;	// ͶӰ����
uniform vec4 LightPosition[LightNum];	// ��Դλ��(�۲�����ϵ)
uniform vec3 SpotDirection;
uniform bool TexNormalOn=false;

void main()
{
    // ����������ת���۲�����ϵ��(�ڹ۲�����ϵ�������)
    vec3 pos = (ModelView * vec4(vPosition, 1.0)).xyz;
	// �����㷨��ת���۲�����ϵ��(���ģ�ӱ任�����Ǿ����������)
    fN = normalize((ModelView * vec4(vNormal, 0.0)).xyz);
	
	dist = distance(pos, LightPosition[2].xyz);

	if(TexNormalOn)
	{
		vec3 T  = normalize((ModelView * vec4(vTangent, 0.0)).xyz);
		vec3 B  = cross(fN, T);
		for(int i = 0; i < LightNum; i++){
			/* �����������ռ��µĹ�Դ����*/
			if(LightPosition[i].w != 0){ // �������Դ
				fL[i].x = dot(T, LightPosition[i].xyz - pos);
				fL[i].y = dot(B, LightPosition[i].xyz - pos);
				fL[i].z = dot(fN, LightPosition[i].xyz - pos);
			}
			else{
				fL[i].x = dot(T, LightPosition[i].xyz);
				fL[i].y = dot(B, LightPosition[i].xyz);
				fL[i].z = dot(fN, LightPosition[i].xyz);
			}
			fL[i] = normalize(fL[i]);
		}

		/* �������ռ��µĹ۲����� */
		fE.x = dot(T, -pos);
		fE.y = dot(B, -pos);
		fE.z = dot(fN, -pos);
		fE   = normalize(fE);

		/* �������ռ��µľ۹�����䷽������ */
		SpotDirect.x = dot(T, SpotDirection);
		SpotDirect.y = dot(B, SpotDirection);
		SpotDirect.z = dot(fN, SpotDirection);
		SpotDirect = normalize(SpotDirect);
	}
	else
	{
		fE = normalize(-pos);		// �۲��߷�������

		for(int i = 0; i < LightNum; i++)
		{	
			if(LightPosition[i].w != 0) // �������Դ
				fL[i] = normalize(LightPosition[i].xyz - pos);
			else					 	// Զ�����Դ
				fL[i] = normalize(LightPosition[i].xyz); 
		}
    }
	
	// �ü�����ϵ�¶�������
	gl_Position = Projection * vec4(pos, 1.0); 
	texCoord = vTexCoord;

	const float LOG2 = 1.442695;
    float fogDensity = 0.05;              //����������������Ũ�ȣ�Խ����ԽŨ
    float dis = abs(gl_Position.z);                                     //������þ���Ч�ʽϸ�

	fogFactor = exp2( -fogDensity * fogDensity * dis * dis * LOG2 );//2��X�η�
    fogFactor = clamp(fogFactor, 0.0, 1.0);			//��ֹԽ��    
}
