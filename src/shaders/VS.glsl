#version 400 core

layout (location = 0) in vec2 inPos;

uniform vec2 minPos;
uniform vec2 maxPos;

void main()
{
	vec2 pos = (inPos - minPos) / (maxPos - minPos) * 2.0 - 1.0;
	gl_Position = vec4(pos.y, -pos.x, 0, 1);
}
