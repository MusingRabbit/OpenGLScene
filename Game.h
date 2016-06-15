#ifndef GAME_H
#define GAME_H

#include "glew.h"
#include "Util.h"
#include <iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "Primitives\Vertex.h"
#include "Primitives\ShapeFactory.h"
#include "Display.h"
#include "Camera.h"
#include "InputController.h"

using namespace std;
using namespace glm;

class Game
{
public:
	Game();
	~Game();
	void Init(Display& value);
	void Draw();
	void SetDisplay(Display& value);
	void Update();
private :
	void InitShaders();
	
	bool CheckShaderCompileStatus(int ShaderId);
	bool CheckProgramLinkStatus(int ProgramId);
	bool CheckStatus(GLuint objectId,
		PFNGLGETSHADERIVPROC getIvCallback,
		PFNGLGETSHADERINFOLOGPROC getInfoCallback,
		GLenum statusType);
	void BufferGeometryData();

	const float X_DELTA = 0.1f;
	const GLuint NUM_VERTS_PER_TRI = 3;
	const GLuint NUM_FLOAT_PER_VERT = 9;
	const GLuint VERTEX_BYTE_SIZE =  NUM_FLOAT_PER_VERT * sizeof(GLfloat);
	const GLuint MAX_TRIANGLE_COUNT = 20;

	GLuint TriCount = 0;
	
	
	GLint m_diffuseProgramId = 0;
	GLuint m_ambProgramId = 0;
	InputController* m_input = NULL;
	Camera* m_camera = NULL;
	Display* m_display = NULL;

	GLuint m_iTeaPotIndexCount, m_iArrowIndexCount, m_iPlaneIndexCount, m_iCubeIndexCount;
	GLuint iIndexCount, iVertexCount;
	GLuint iVertexBufferId, iIndexBufferId;
	GLuint iCubeVertexArrayId, iTeaPotVertexArrayId, iArrowVertexArrayId, iPlaneVertexArrayId;

	GLuint iArrowIndexDataByteOffset;
	GLuint iPlaneIndexDataByteOffset;
	GLuint iCubeIndexDataByteOffset;

	float rotatef = 0.0f;
};

#endif //GAME_H