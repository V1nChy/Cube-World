#version 140
//ƽ���ˮ��Ч��

in vec3 vPosition;
in vec3 vNormal; 
in vec2 vTexCoord;

out vec2 texCoord;
out vec2 texCoord1;

out vec3 fE;	// �۲�����(�۲�����ϵ)
out vec3 fL;	// ��������(�۲�����ϵ)

out vec4 ambient, diffuse, specular;
uniform vec3 tangent=vec3(0.0,1.0,0.0);          //��������;
uniform float time;                       //ʱ�����;
uniform vec4 LightPosition=vec4(0.0,0.0,0.0,0.0);         //�ƹ��λ��;

uniform mat4 ModelView;		// ģ�Ӿ���
uniform mat4 Projection;	// ͶӰ����
void main()
{
		vec3 pos = (ModelView * vec4(vPosition, 1.0)).xyz;
		vec3 N= normalize((ModelView * vec4(vNormal, 0.0)).xyz);
		vec3 E = normalize(-pos);	// �۲��߷�������
		vec3 L;			
         if(LightPosition.w != 0) 		 //���㵽��Դ����;
			L = normalize(LightPosition.xyz - pos);
		else					
			L = normalize(LightPosition.xyz); 
  
         vec3 H = normalize(L + E);
         //��ȡ�����䣬 ���淴����;
         ambient = vec4(0.8,0.8,0.8,1.0);
         diffuse = vec4(0.6,0.6,0.6,1.0);
         specular = vec4(0.5,0.5,0.5,1.0);
         float _diffuse = max(dot(L, N), 0.0);
         if(_diffuse > 0.0)
         {
                 diffuse = diffuse * _diffuse;
                 float _specular = max(dot(H,N),0.0);
                 specular = specular * pow(_specular , 64.0);
         }
         //�������߿ռ���;
         vec3 T = normalize((ModelView * vec4(tangent, 0.0)).xyz);
         vec3 B = normalize(cross(N,T));
 
         fL.x = dot(L,T);
         fL.y = dot(L,B);
         fL.z = dot(L,N);
         fL = normalize(fL);
 
         fE.x = dot(E,T);
         fE.y = dot(E,B);
         fE.z = dot(E,N);
         fE = normalize(fE);
 
         texCoord=vTexCoord;
         //����ʱ���ȡ��������λ��;
         texCoord1.x = texCoord.x + time * 0.05;
         texCoord1.y = texCoord.y + time * 0.05;
 
         gl_Position = Projection * vec4(pos, 1.0); 
}