#pragma once

#include <glew.h>
#include "Vertex.h"

struct ShapeData
{
	ShapeData() :
		vertices(0), numVertices(0), indices(0), numIndices(0)
	{

	}

	Vertex* vertices;
	GLushort* indices;
	GLuint numVertices;
	GLuint numIndices;
	GLsizeiptr getVertexBufferSize() const {
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr getIndexBufferSize() const {
		return numIndices * sizeof(GLushort);
	}

	void clear() {
		delete[] indices;
		delete[] vertices;
		numIndices = numVertices = 0;
	}
};