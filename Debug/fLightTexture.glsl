#version 140
const int LightNum = 3; // ��Դ����

uniform sampler2D tex;
uniform sampler2D nTex;

in vec2 texCoord;
in vec3 fN;	// ����(�۲�����ϵ)
in vec3 fE;	// �۲�����(�۲�����ϵ)
in vec3 fL[LightNum];	// ��������(�۲�����ϵ)
in float dist;	// ƬԪ���ֵ�Ͳ��Դ����
in vec3 SpotDirect; // �۹�����䷽��(�۲�����ϵ)
in float fogFactor;

// ���շ���
uniform vec4 LightAmbientProduct[LightNum];
uniform vec4 LightDiffuseProduct[LightNum]; 
uniform vec4 LightSpecularProduct[LightNum];
//���ʷ���
uniform vec4 MaterialAmbientProduct;
uniform vec4 MaterialDiffuseProduct; 
uniform vec4 MaterialSpecularProduct;
uniform vec4 Emission;		// �����
uniform float Shininess;	// �߹�ϵ��

// ���һ����Դ�ľ۹�Ʋ���
uniform vec3 SpotDirection;   // �۹�����䷽��(�۲�����ϵ)
uniform float SpotCutOff;	  // �۹�ƽ�ֹ��(�Ƕ�)
uniform float SpotExponent;   // �۹��˥��ָ��

uniform bool bOnlyTexture;
uniform bool LightOn[LightNum];	// ��Դ����
uniform bool TexNormalOn=false;
uniform bool FogOn=false;


out vec4 fragColor;		 // ���ƬԪ��ɫ

void main()
{
	// ��һ�����������
	 vec3 N;
	 vec3 spotDir;
	if(TexNormalOn)
	{
		vec3 NN = texture(nTex, texCoord).rgb;	// �������л�ȡ�ķ���
		N =  normalize(2.0 * NN - 1.0);			    // ��[0,1]ӳ���[-1,1]

		spotDir = -normalize(SpotDirect);
	}
    else
	{
		// ��һ�����������
		N = normalize(fN);
		spotDir = -normalize(SpotDirection);
	}
    vec3 E = normalize(fE);
	
	vec4 specular=vec4(0.0,0.0,0.0,0.0);
	fragColor = vec4(0.0, 0.0, 0.0, 0.0); // ��ʼΪ0�����ATI�Կ�
	for(int i = 0; i < LightNum; i++){	
		if(!LightOn[i]) continue; // ��Դ�رգ��򲻼���ù�Դ�Ĺ���
		
		vec3 L = normalize(fL[i]); // ��Դ��������(�Ӷ���ָ���Դ)
		
		float KSpot = 1.0;	// �ܾ۹��Ӱ���˥��ϵ��(1.0����˥��)
		if(i == 2){
			// �����䷽���һ��������(��ΪLҲ�ǴӶ���ָ���Դ)
			//vec3 spotDir = -normalize(SpotDirection); 
			float cutoff = radians(SpotCutOff); // �Ƕ�ת����
			float c = dot(L, spotDir);	// ƫ��ǵ�cosֵ
			if( c < cos(cutoff)) // ƫ��Ƕȳ�����ֹ��
				KSpot = 0.0;	// ��ȫ˥��
			else {// ǿ��˥��������c^f
				// dΪ�����˥����ʽ�ķ�ĸ
				float d = 1.0 + 0.5 * dist; 
				KSpot = max(pow(c, SpotExponent), 0) / d;
			}
		}
		
		vec3 H = normalize( L + E );	// �������

		// �����������
		vec4 ambient = LightAmbientProduct[i]*MaterialAmbientProduct;

		// ���������
		float Kd = max( dot(L, N), 0.0 );
		vec4 diffuse = KSpot * Kd * LightDiffuseProduct[i]*MaterialDiffuseProduct;
	
		// ���淴�����
		if(Kd!=0)
		{
			float Ks = pow( max(dot(N, H), 0.0), Shininess );
			specular += KSpot * Ks * LightSpecularProduct[i]*MaterialSpecularProduct;
		}

		// �õ�������ɫ
		fragColor += ambient + diffuse; 
    }
	if(bOnlyTexture)
		fragColor=texture( tex, texCoord );
	else
	{
		fragColor += Emission;	// ������������ķ����
		fragColor = fragColor*texture( tex, texCoord )+specular; 
		fragColor.a=(LightAmbientProduct[0].a*MaterialAmbientProduct.a+LightDiffuseProduct[0].a*MaterialDiffuseProduct.a+LightSpecularProduct[0].a*MaterialSpecularProduct.a)/3;
	}
	if(FogOn)
	{
		vec4 fogColor = vec4(0.5,0.5,0.5,1.0);
		fragColor=mix(fogColor, fragColor, fogFactor ); 
	}
}