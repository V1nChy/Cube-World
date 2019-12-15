#version 140

in vec3 fE;
in vec3 fL;
in vec2 texCoord;
in vec2 texCoord1;

in vec4 ambient, diffuse, specular;
uniform sampler2D tex;
uniform sampler2D nTex;
uniform samplerCube cubeTex;
void main()
{
         vec3 L = normalize(fL);
         vec3 E = normalize(fE);
         vec4 _baseColor = texture(tex, texCoord);
         vec3 _normColor = texture(tex, texCoord1).xyz;
        
         _baseColor = texture(tex, (texCoord.xy + _normColor.xy * 0.35)); //调制底面纹理波动;
         _normColor = texture(nTex, (texCoord1.xy + _normColor.xy * 0.02)).xyz;
         vec3 N = normalize(_normColor * 2.0 - vec3(1.0));     //将法线转到[-1,1]范围;
         float _diff = max(dot(L,N),0.0);
         float _spec = max(dot(E,N),0.0);
         if(_diff > 0.0)
         {
                 _spec = pow(_spec, 64.0);
         }
		 vec3 R=reflect(E,-N);
		 vec4 cubeColor=texture(cubeTex,R);

		vec4 finalColor=(ambient + diffuse * _diff)*_baseColor+specular * _spec;

		gl_FragColor=finalColor;
		gl_FragColor.a=0.72;
}