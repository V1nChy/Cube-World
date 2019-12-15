#version 140
//平面的水波效果

in vec3 vPosition;
in vec3 vNormal; 
in vec2 vTexCoord;

out vec2 texCoord;
out vec2 texCoord1;

out vec3 fE;	// 观察向量(观察坐标系)
out vec3 fL;	// 光照向量(观察坐标系)

out vec4 ambient, diffuse, specular;
uniform vec3 tangent=vec3(0.0,1.0,0.0);          //顶点切线;
uniform float time;                       //时间更新;
uniform vec4 LightPosition=vec4(0.0,0.0,0.0,0.0);         //灯光的位置;

uniform mat4 ModelView;		// 模视矩阵
uniform mat4 Projection;	// 投影矩阵
void main()
{
		vec3 pos = (ModelView * vec4(vPosition, 1.0)).xyz;
		vec3 N= normalize((ModelView * vec4(vNormal, 0.0)).xyz);
		vec3 E = normalize(-pos);	// 观察者方向向量
		vec3 L;			
         if(LightPosition.w != 0) 		 //定点到光源向量;
			L = normalize(LightPosition.xyz - pos);
		else					
			L = normalize(LightPosition.xyz); 
  
         vec3 H = normalize(L + E);
         //获取漫反射， 镜面反射量;
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
         //计算切线空间量;
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
         //根据时间获取法线纹理位置;
         texCoord1.x = texCoord.x + time * 0.05;
         texCoord1.y = texCoord.y + time * 0.05;
 
         gl_Position = Projection * vec4(pos, 1.0); 
}