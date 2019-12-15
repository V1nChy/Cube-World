#version 140

in vec2 texCoord;
in float fogFactor;
uniform sampler2D tex;

out vec4 fragColor;
void main()
{
	vec4 fogColor = vec4(0.0,0.4,0.6,1.0);
	vec4 texColor=texture( tex, texCoord );
	fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	fragColor=mix(fogColor, texColor, fogFactor ); 
}