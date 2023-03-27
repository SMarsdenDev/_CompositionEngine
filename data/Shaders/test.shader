#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uPerspMatrix;

void main()
{
    vNormal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
	gl_Position = uPerspMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1.f);
	vFragPos = vec3(uModelMatrix * vec4(aPos, 1.f));
}

#type fragment
#version 330 core

out vec4 fragColor;

in vec4 vertexColor;
in vec3 vNormal;
in vec3 vFragPos;

uniform vec3 uObjectColor;

uniform int uActiveLightCount;
uniform vec3[16] uLightColor;
uniform vec3[16] uLightPosition;
uniform float uAmbientIntensity;

uniform vec3 uCameraPosition;

vec3 CalculateAmbient()
{
  vec3 totalAmbient;
  for(int i = 0; i < uActiveLightCount; ++i)
  {
    totalAmbient += (uAmbientIntensity * uLightColor[i]);
  }
  return totalAmbient;
}
vec3 CalculateDiffuse()
{
  vec3 totalDiff;
  for(int i = 0; i < uActiveLightCount; ++i)
  {
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(uLightPosition[i] - vFragPos);

	float diff = max(dot(norm, lightDir), 0.f);
	totalDiff += (diff * uLightColor[i]);  
  }
  return totalDiff;
}

vec3 CalculateSpecular()
{
  vec3 totalSpec;
  for(int i = 0; i < uActiveLightCount; ++i)
  {
	vec3 lightDir = normalize(uLightPosition[i] - vFragPos);
	float specIntensity = 0.5f;
	vec3 viewDir = normalize(uCameraPosition - vFragPos);
	vec3 reflectDir = reflect(-lightDir, normalize(vNormal));

	float spec = pow(max(dot(viewDir, reflectDir), 0.f), 32);

	totalSpec += (specIntensity * spec * uLightColor[i]);  
  }
  return totalSpec;
}

void main()
{
    vec3 result = (CalculateAmbient() + CalculateDiffuse() + CalculateSpecular()) * uObjectColor;
	//fragColor = vec4(vNormal/2 + 0.5, 1.f);
	fragColor = vec4(result,1.f);
}