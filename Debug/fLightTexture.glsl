#version 140
const int LightNum = 3; // 光源数量

uniform sampler2D tex;
uniform sampler2D nTex;

in vec2 texCoord;
in vec3 fN;	// 法向(观察坐标系)
in vec3 fE;	// 观察向量(观察坐标系)
in vec3 fL[LightNum];	// 光照向量(观察坐标系)
in float dist;	// 片元到手电筒光源距离
in vec3 SpotDirect; // 聚光灯照射方向(观察坐标系)
in float fogFactor;

// 光照分量
uniform vec4 LightAmbientProduct[LightNum];
uniform vec4 LightDiffuseProduct[LightNum]; 
uniform vec4 LightSpecularProduct[LightNum];
//材质分量
uniform vec4 MaterialAmbientProduct;
uniform vec4 MaterialDiffuseProduct; 
uniform vec4 MaterialSpecularProduct;
uniform vec4 Emission;		// 发射光
uniform float Shininess;	// 高光系数

// 最后一个光源的聚光灯参数
uniform vec3 SpotDirection;   // 聚光灯照射方向(观察坐标系)
uniform float SpotCutOff;	  // 聚光灯截止角(角度)
uniform float SpotExponent;   // 聚光灯衰减指数

uniform bool bOnlyTexture;
uniform bool LightOn[LightNum];	// 光源开关
uniform bool TexNormalOn=false;
uniform bool FogOn=false;


out vec4 fragColor;		 // 输出片元颜色

void main()
{
	// 归一化输入的向量
	 vec3 N;
	 vec3 spotDir;
	if(TexNormalOn)
	{
		vec3 NN = texture(nTex, texCoord).rgb;	// 从纹理中获取的法向
		N =  normalize(2.0 * NN - 1.0);			    // 从[0,1]映射回[-1,1]

		spotDir = -normalize(SpotDirect);
	}
    else
	{
		// 归一化输入的向量
		N = normalize(fN);
		spotDir = -normalize(SpotDirection);
	}
    vec3 E = normalize(fE);
	
	vec4 specular=vec4(0.0,0.0,0.0,0.0);
	fragColor = vec4(0.0, 0.0, 0.0, 0.0); // 初始为0，针对ATI显卡
	for(int i = 0; i < LightNum; i++){	
		if(!LightOn[i]) continue; // 光源关闭，则不计算该光源的贡献
		
		vec3 L = normalize(fL[i]); // 光源方向向量(从顶点指向光源)
		
		float KSpot = 1.0;	// 受聚光灯影响的衰减系数(1.0即不衰减)
		if(i == 2){
			// 对照射方向归一化并反向(因为L也是从顶点指向光源)
			//vec3 spotDir = -normalize(SpotDirection); 
			float cutoff = radians(SpotCutOff); // 角度转弧度
			float c = dot(L, spotDir);	// 偏离角的cos值
			if( c < cos(cutoff)) // 偏离角度超过截止角
				KSpot = 0.0;	// 完全衰减
			else {// 强度衰减正比于c^f
				// d为随距离衰减公式的分母
				float d = 1.0 + 0.5 * dist; 
				KSpot = max(pow(c, SpotExponent), 0) / d;
			}
		}
		
		vec3 H = normalize( L + E );	// 半角向量

		// 环境反射分量
		vec4 ambient = LightAmbientProduct[i]*MaterialAmbientProduct;

		// 漫反射分量
		float Kd = max( dot(L, N), 0.0 );
		vec4 diffuse = KSpot * Kd * LightDiffuseProduct[i]*MaterialDiffuseProduct;
	
		// 镜面反射分量
		if(Kd!=0)
		{
			float Ks = pow( max(dot(N, H), 0.0), Shininess );
			specular += KSpot * Ks * LightSpecularProduct[i]*MaterialSpecularProduct;
		}

		// 得到最终颜色
		fragColor += ambient + diffuse; 
    }
	if(bOnlyTexture)
		fragColor=texture( tex, texCoord );
	else
	{
		fragColor += Emission;	// 加上物体自身的发射光
		fragColor = fragColor*texture( tex, texCoord )+specular; 
		fragColor.a=(LightAmbientProduct[0].a*MaterialAmbientProduct.a+LightDiffuseProduct[0].a*MaterialDiffuseProduct.a+LightSpecularProduct[0].a*MaterialSpecularProduct.a)/3;
	}
	if(FogOn)
	{
		vec4 fogColor = vec4(0.5,0.5,0.5,1.0);
		fragColor=mix(fogColor, fragColor, fogFactor ); 
	}
}