#version 430
layout( points ) in;
layout( triangle_strip, max_vertices = 4 ) out;

uniform float Size2=0.04;   // Half the width of the quad

uniform mat4 Projection;
uniform float time;
out vec2 TexCoord;

void main()
{
    mat4 m = Projection;
	vec4 nowPos=vec4(gl_in[0].gl_Position.x,gl_in[0].gl_Position.y+time,gl_in[0].gl_Position.z,gl_in[0].gl_Position.w);
    gl_Position = m * (vec4(-Size2,-Size2,0.0,0.0) + nowPos);
    TexCoord = vec2(0.0,0.0);
    EmitVertex();

    gl_Position = m * (vec4(Size2,-Size2,0.0,0.0) + nowPos);
    TexCoord = vec2(1.0,0.0);
    EmitVertex();

    gl_Position = m * (vec4(-Size2,Size2,0.0,0.0) + nowPos);
    TexCoord = vec2(0.0,1.0);
    EmitVertex();

    gl_Position = m * (vec4(Size2,Size2,0.0,0.0) + nowPos);
    TexCoord = vec2(1.0,1.0);
    EmitVertex();

    EndPrimitive();
}