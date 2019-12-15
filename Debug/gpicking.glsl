#version 430 

layout (triangles) in;
layout (points, max_vertices = 1) out;

in vec3 posModel[];		   // ģ������ϵ�¶�������
in vec3 posWorld[];

uniform vec2 ptMouse;  	   // �淶���豸����ϵ�����λ��
uniform uvec2 idIn;		   // ��ǰ����id���丸����id
uniform uvec3 xyzPos;
uniform float near;        // ���ü��浽�ӵ����
uniform float far;		   // Զ�ü��浽�ӵ����

out GS_OUTPUT
{
	out vec3  FacePos[3]; // ������������(ģ������ϵ)
	out float depth;	   // ���ֵ
	out uvec2 id;		   // ��ǰ����id���丸����id
	out uvec3 mPos;
};
 
void main()
{
	// ������������(�ü�����ϵ)
	vec4 A = gl_in[0].gl_Position;
	vec4 B = gl_in[1].gl_Position;
	vec4 C = gl_in[2].gl_Position;
	
	bool AIn = (A.w >= near && A.w <= far && abs(A.x) <= abs(A.w) && abs(A.y) <= abs(A.w));
	bool BIn = (B.w >= near && B.w <= far && abs(B.x) <= abs(B.w) && abs(B.y) <= abs(B.w));
	bool CIn = (C.w >= near && C.w <= far && abs(C.x) <= abs(C.w) && abs(C.y) <= abs(C.w));

	if((A.w >= near && A.w <= far) || (B.w >= near && B.w <= far) || (C.w >= near && C.w <= far)){  // ������1��������Զ���ü���֮��
	if(AIn || BIn || CIn)
	{  // ������1����������������

		// ͸�����(�任���淶���豸����ϵ��)
		A /= A.w;
		B /= B.w;
		C /= C.w;
	
		/* �ж����λ���Ƿ����������� */
		// ������ʱ�����������������
		vec3 AB = vec3((B - A).xy, 0);
		vec3 BC = vec3((C - B).xy, 0);
		vec3 CA = vec3((A - C).xy, 0);
	
		// ����Ӷ���ָ��ʰȡ�������
		vec3 AM = vec3(ptMouse - A.xy, 0);
		vec3 BM = vec3(ptMouse - B.xy, 0);
		vec3 CM = vec3(ptMouse - C.xy, 0);
	
		// ������
		vec3 CrossA = cross(AB, AM);
		vec3 CrossB = cross(BC, BM);
		vec3 CrossC = cross(CA, CM);
	
		// ��˽��zֵ�����ڵ���0
		if(CrossA.z >= 0 && CrossB.z >=0 && CrossC.z >= 0)
		{
			// ���������������
			FacePos[0] = posWorld[0];
			FacePos[1] = posWorld[1];
			FacePos[2] = posWorld[2];

			// ������Ȳ�ֵ�����
			float AreaMBC = CrossB.z;
			float AreaMCA = CrossC.z;
			float AreaMAB = CrossA.z;
		
			depth = dot(vec3(A.z, B.z, C.z), 
					vec3(AreaMBC, AreaMCA, AreaMAB)) 
					/ (AreaMBC + AreaMCA + AreaMAB);
		
			if(depth >= -1.0 && depth <= 1.0)
			{ // ��֤����������
				// ���id
				id = idIn;
				mPos= xyzPos;

				EmitVertex();
			}
		}
	}
	}
}