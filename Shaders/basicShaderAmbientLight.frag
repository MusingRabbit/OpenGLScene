#version 430

in vec3 vertWorldPos;
in vec3 vertColour;

uniform vec4 ambientLight;

out vec4 fragColour;

void main()
{
	fragColour = ambientLight + vec4(vertColour,1);
}