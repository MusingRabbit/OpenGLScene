#version 430

in layout(location=0) vec4 vertexPosModel;
in layout(location=1) vec3 vertexColour;
in layout(location=2) vec3 normalModel;

uniform mat4 MVPMatrix;
uniform mat4 modelToWorldMatrix;

out vec3 worldNormal;
out vec3 vertWorldPos;
out vec3 vertColour;

void main()
{
	gl_Position = MVPMatrix * vertexPosModel;
	worldNormal =  vec3(modelToWorldMatrix * vec4(normalModel,0));
	vertWorldPos = vec3(modelToWorldMatrix * vertexPosModel);
	vertColour = vertexColour;
}