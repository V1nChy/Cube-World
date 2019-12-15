#version 430 

layout (triangles) in;
layout (points, max_vertices = 1) out;

in vec3 posModel[];		   // 模型坐标系下顶点坐标
in vec3 posWorld[];

uniform vec2 ptMouse;  	   // 规范化设备坐标系下鼠标位置
uniform uvec2 idIn;		   // 当前对象id及其父对象id
uniform uvec3 xyzPos;
uniform float near;        // 近裁剪面到视点距离
uniform float far;		   // 远裁剪面到视点距离

out GS_OUTPUT
{
	out vec3  FacePos[3]; // 三个顶点坐标(模型坐标系)
	out float depth;	   // 深度值
	out uvec2 id;		   // 当前对象id及其父对象id
	out uvec3 mPos;
};
 
void main()
{
	// 三个顶点坐标(裁剪坐标系)
	vec4 A = gl_in[0].gl_Position;
	vec4 B = gl_in[1].gl_Position;
	vec4 C = gl_in[2].gl_Position;
	
	bool AIn = (A.w >= near && A.w <= far && abs(A.x) <= abs(A.w) && abs(A.y) <= abs(A.w));
	bool BIn = (B.w >= near && B.w <= far && abs(B.x) <= abs(B.w) && abs(B.y) <= abs(B.w));
	bool CIn = (C.w >= near && C.w <= far && abs(C.x) <= abs(C.w) && abs(C.y) <= abs(C.w));

	if((A.w >= near && A.w <= far) || (B.w >= near && B.w <= far) || (C.w >= near && C.w <= far)){  // 至少有1个顶点在远近裁剪面之间
	if(AIn || BIn || CIn)
	{  // 至少有1个顶点在视域体内

		// 透视相除(变换到规范化设备坐标系下)
		A /= A.w;
		B /= B.w;
		C /= C.w;
	
		/* 判断鼠标位置是否在三角形内 */
		// 计算逆时针绕向的三条边向量
		vec3 AB = vec3((B - A).xy, 0);
		vec3 BC = vec3((C - B).xy, 0);
		vec3 CA = vec3((A - C).xy, 0);
	
		// 计算从顶点指向拾取点的向量
		vec3 AM = vec3(ptMouse - A.xy, 0);
		vec3 BM = vec3(ptMouse - B.xy, 0);
		vec3 CM = vec3(ptMouse - C.xy, 0);
	
		// 计算叉乘
		vec3 CrossA = cross(AB, AM);
		vec3 CrossB = cross(BC, BM);
		vec3 CrossC = cross(CA, CM);
	
		// 叉乘结果z值均大于等于0
		if(CrossA.z >= 0 && CrossB.z >=0 && CrossC.z >= 0)
		{
			// 输出顶点世界坐标
			FacePos[0] = posWorld[0];
			FacePos[1] = posWorld[1];
			FacePos[2] = posWorld[2];

			// 计算深度插值并输出
			float AreaMBC = CrossB.z;
			float AreaMCA = CrossC.z;
			float AreaMAB = CrossA.z;
		
			depth = dot(vec3(A.z, B.z, C.z), 
					vec3(AreaMBC, AreaMCA, AreaMAB)) 
					/ (AreaMBC + AreaMCA + AreaMAB);
		
			if(depth >= -1.0 && depth <= 1.0)
			{ // 保证在视域体内
				// 输出id
				id = idIn;
				mPos= xyzPos;

				EmitVertex();
			}
		}
	}
	}
}