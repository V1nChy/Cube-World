#version 140
//天空的雾化处理。效果一般待改进
in vec2 vTexCoord;
in  vec3 vPosition;	

out vec2 texCoord;
out float fogFactor;
uniform mat4 ModelView;		// 模视矩阵
uniform mat4 Projection;	// 投影矩阵
void main()
{
    gl_Position=Projection*ModelView*vec4(vPosition,1.0);
    texCoord=vTexCoord;

	 const float LOG2 = 1.442695;
     float fogDensity = 0.02;              //这个参数代表了雾的浓度，越大雾越浓
    //gl_FogFragCoord = length(vViewPosition.xyz-gl_Vertex.xyz);   //计算视点与顶点的距离

    gl_FogFragCoord = abs(gl_Position.z);                                     //这样获得距离效率较高

	fogFactor = exp2( -fogDensity * fogDensity * gl_FogFragCoord * gl_FogFragCoord * LOG2 );//2的X次方
    fogFactor = clamp(fogFactor, 0.0, 1.0);			//防止越界               
}