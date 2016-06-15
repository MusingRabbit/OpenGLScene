#version 430

in layout(location=0) vec4 vertexPosModel;
in layout(location=1) vec3 vertexColour;

uniform mat4 MVPMatrix;
uniform mat4 modelToWorldMatrix;

out vec3 vertColour;

void main()
{
	gl_Position = modelToWorldMatrix * vertexPosModel;
	vertColour = vertexColour;
}