#version 430

in vec3 worldNormal;
in vec3 vertWorldPos;
in vec3 vertColour;

uniform vec4 ambientLight;
uniform vec3 spotLightWorldPos;
uniform vec3 cameraWorldPos;

out vec4 fragColour;

void main()
{
	//Diffuse
	vec3 lightDirection = spotLightWorldPos - vertWorldPos;
	vec3 lightVector = normalize(lightDirection);
	vec3 vertNormal = normalize(worldNormal);

	float distance = length(lightDirection);
	float intensity =  clamp((dot(lightVector, vertNormal)),0,1);

	vec4 diffuse = vec4(vertColour * intensity,1.0);

	//Specular
	vec3 reflectVector = reflect(-lightVector,worldNormal);
	vec3 eyeVecWorld = normalize(cameraWorldPos - vertWorldPos);
	float s = pow(dot(reflectVector,eyeVecWorld),48);
	vec4 specularLight = vec4(s,s,s,1);

	fragColour = ambientLight + diffuse + clamp(specularLight,0,1);
}