#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform vec3 uVertColor;

void main()
{
	gl_Position = vec4(aPos, 1.f);
	vertexColor = vec4(uVertColor, 1.f);
}

#type fragment
#version 330 core

out vec4 fragColor;

in vec4 vertexColor;

uniform mat4 viewMatrix;
uniform mat4 perspMatrix;

void main()
{
  if(viewMatrix != perspMatrix)
  {
  
  }
	fragColor = vertexColor;
}