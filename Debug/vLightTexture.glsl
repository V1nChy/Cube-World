#version 140 
//光照，贴图，法向贴图

const int LightNum = 3; // 光源数量

in vec2 vTexCoord;
in  vec3 vPosition;	// 顶点位置(建模坐标系)
in  vec3 vNormal;	// 顶点法向(建模坐标系)
in  vec3 vTangent;	// 切向量(建模坐标系)

out vec2 texCoord;
out vec3 fN;	// 法向(观察坐标系)
out vec3 fE;	// 观察向量(观察坐标系)
out vec3 fL[LightNum];	// 光照向量(观察坐标系)
out float dist;	// 顶点到手电筒光源距离
out vec3 SpotDirect; // 切向量空间坐标系下聚光灯照射方向
out float fogFactor;

uniform mat4 ModelView;		// 模视矩阵
uniform mat4 Projection;	// 投影矩阵
uniform vec4 LightPosition[LightNum];	// 光源位置(观察坐标系)
uniform vec3 SpotDirection;
uniform bool TexNormalOn=false;

void main()
{
    // 将顶点坐标转到观察坐标系下(在观察坐标系计算光照)
    vec3 pos = (ModelView * vec4(vPosition, 1.0)).xyz;
	// 将顶点法向转到观察坐标系下(针对模视变换不含非均匀缩放情况)
    fN = normalize((ModelView * vec4(vNormal, 0.0)).xyz);
	
	dist = distance(pos, LightPosition[2].xyz);

	if(TexNormalOn)
	{
		vec3 T  = normalize((ModelView * vec4(vTangent, 0.0)).xyz);
		vec3 B  = cross(fN, T);
		for(int i = 0; i < LightNum; i++){
			/* 计算切向量空间下的光源向量*/
			if(LightPosition[i].w != 0){ // 近距离光源
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

		/* 切向量空间下的观察向量 */
		fE.x = dot(T, -pos);
		fE.y = dot(B, -pos);
		fE.z = dot(fN, -pos);
		fE   = normalize(fE);

		/* 切向量空间下的聚光灯照射方向向量 */
		SpotDirect.x = dot(T, SpotDirection);
		SpotDirect.y = dot(B, SpotDirection);
		SpotDirect.z = dot(fN, SpotDirection);
		SpotDirect = normalize(SpotDirect);
	}
	else
	{
		fE = normalize(-pos);		// 观察者方向向量

		for(int i = 0; i < LightNum; i++)
		{	
			if(LightPosition[i].w != 0) // 近距离光源
				fL[i] = normalize(LightPosition[i].xyz - pos);
			else					 	// 远距离光源
				fL[i] = normalize(LightPosition[i].xyz); 
		}
    }
	
	// 裁剪坐标系下顶点坐标
	gl_Position = Projection * vec4(pos, 1.0); 
	texCoord = vTexCoord;

	const float LOG2 = 1.442695;
    float fogDensity = 0.05;              //这个参数代表了雾的浓度，越大雾越浓
    float dis = abs(gl_Position.z);                                     //这样获得距离效率较高

	fogFactor = exp2( -fogDensity * fogDensity * dis * dis * LOG2 );//2的X次方
    fogFactor = clamp(fogFactor, 0.0, 1.0);			//防止越界    
}
