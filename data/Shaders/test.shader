#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main()
{
	gl_Position = vec4(aPos, 1.f);
	vertexColor = vec4(1.f,0.f,0.5f,1.f);
}

#type fragment
#version 330 core

out vec4 fragColor;

in vec4 vertexColor;

void main()
{
	fragColor = vertexColor;
}