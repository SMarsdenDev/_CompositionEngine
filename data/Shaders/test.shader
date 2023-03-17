#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform vec3 uVertColor;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uPerspMatrix;

void main()
{
	gl_Position = uPerspMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1.f);
	vertexColor = vec4(uVertColor, 1.f);
}

#type fragment
#version 330 core

out vec4 fragColor;

in vec4 vertexColor;

void main()
{
	fragColor = vertexColor;
}