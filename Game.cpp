#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
	glUseProgram(0);
	glDeleteProgram(m_diffuseProgramId);
	delete m_camera;
	delete m_input;
	m_camera = NULL;
	m_input = NULL;
	m_display = NULL;
}


void Game::Init(Display& display) {
	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "GLEW FAILED TO INITIALISE!" << std::endl;
		return;
	}

	m_input = new InputController();
	m_camera = new Camera();
	m_display = &display;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	BufferGeometryData();
	InitShaders();


	m_input->SetKey("forward", SDLK_w);
	m_input->SetKey("back", SDLK_s);
	m_input->SetKey("left", SDLK_a);
	m_input->SetKey("right", SDLK_d);
	m_input->SetKey("up", SDLK_SPACE);
	m_input->SetKey("down", SDLK_c);
}

bool Game::CheckStatus(GLuint objectId,
	PFNGLGETSHADERIVPROC getIvCallback,
	PFNGLGETSHADERINFOLOGPROC getInfoCallback,
	GLenum statusType)
{
	GLint iStatus;
	getIvCallback(objectId, statusType, &iStatus);
	if (iStatus != GL_TRUE)
	{
		GLint iLength;
		GLsizei iBufferSize;

		getIvCallback(objectId, GL_INFO_LOG_LENGTH, &iLength);
		GLchar* resultBuffer = new GLchar[iLength];

		getInfoCallback(objectId, iLength, &iBufferSize, resultBuffer);
		cout << resultBuffer << endl;
		return false;
	}
	return true;
}

bool Game::CheckShaderCompileStatus(GLint ShaderId) {
	return CheckStatus(ShaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool Game::CheckProgramLinkStatus(GLint ProgramId) {
	return CheckStatus(ProgramId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

void Game::Update() {
	m_input->Update();

	if (m_input->GetMouse()->isLeftDown())
		m_camera->mouseUpdate(m_input->GetMouse()->getPos());
	if (m_input->isButtonHit("Escape"))
		m_display->Close();
	if (m_input->isButtonDown("forward"))
		m_camera->moveForward();
	if (m_input->isButtonDown("back"))
		m_camera->moveBackward();
	if (m_input->isButtonDown("left"))
		m_camera->moveLeft();
	if (m_input->isButtonDown("right"))
		m_camera->moveRight();
	if (m_input->isButtonDown("up"))
		m_camera->moveUp();
	if (m_input->isButtonDown("down"))
		m_camera->moveDown();
}

void Game::InitShaders() {
	//TODO:  Refactor into code more OOP
	
	GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint vAShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fAShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string sVShader = Util::LoadFile("Shaders\\basicShader.vert");
	std::string sFShader = Util::LoadFile("Shaders\\basicShader.frag");
	std::string sVAmbShader = Util::LoadFile("Shaders\\basicShaderAmbientLight.vert");
	std::string sFAmbShader = Util::LoadFile("Shaders\\basicShaderAmbientLight.frag");


	const GLchar* charArr[1];
	charArr[0] = sVShader.c_str();
	glShaderSource(vShaderId, 1, charArr, 0);
	charArr[0] = sFShader.c_str();
	glShaderSource(fShaderId, 1, charArr, 0);
	charArr[0] = sVAmbShader.c_str();
	glShaderSource(vAShaderId, 1, charArr, 0);
	charArr[0] = sFAmbShader.c_str();
	glShaderSource(fAShaderId, 1, charArr, 0);

	//vShader->Compile();
	glCompileShader(vShaderId);
	//fShader->Compile();
	glCompileShader(fShaderId);
	glCompileShader(vAShaderId);
	glCompileShader(fAShaderId);

	bool bSuccess = (CheckShaderCompileStatus(vShaderId) && CheckShaderCompileStatus(fShaderId) && CheckShaderCompileStatus(vAShaderId) && CheckShaderCompileStatus(fAShaderId));

	if (bSuccess)
	{
		m_diffuseProgramId = glCreateProgram();
		m_ambProgramId = glCreateProgram();


		glAttachShader(m_diffuseProgramId, vShaderId);
		glAttachShader(m_diffuseProgramId, fShaderId);
		glAttachShader(m_ambProgramId, vAShaderId);
		glAttachShader(m_ambProgramId, fAShaderId);

		glLinkProgram(m_diffuseProgramId);
		glLinkProgram(m_ambProgramId);

		if (!CheckProgramLinkStatus(m_diffuseProgramId) || !CheckProgramLinkStatus(m_diffuseProgramId))
			return;

		glDeleteShader(vShaderId);
		glDeleteShader(fShaderId);
		glDeleteShader(vAShaderId);
		glDeleteShader(fAShaderId);

		

	}
}

void Game::SetDisplay(Display& value) {
	m_display = &value;
}

void Game::BufferGeometryData() {
	ShapeData teaPot = ShapeFactory::MakeTeaPot(30,glm::mat4());
	ShapeData cube = ShapeFactory::MakeCube();
	ShapeData arrow = ShapeFactory::MakeArrow();
	ShapeData plane = ShapeFactory::MakePlane(20);

	iIndexCount = arrow.numIndices + teaPot.numIndices + plane.numIndices + cube.numIndices;

	glGenBuffers(1, &iVertexBufferId);	//Create an Id for the vertex buffer
	glGenBuffers(1, &iIndexBufferId);	//Create an Id for the index buffer
	//Buffer Array -> Both Cube and Arrow vertex data into single buffer
	//Here we initialise the vertex array buffer
	//Bind the vertex buffer Id
	//Register / Create the buffers within OpenGL
	//Pass in vertices from the cube and arrow models
	glBindBuffer(GL_ARRAY_BUFFER, iVertexBufferId);	//Set the target buffer to (iVertexBufferId) | Create the buffer if it doesn't already exist
	glBufferData(GL_ARRAY_BUFFER, teaPot.getVertexBufferSize() + arrow.getVertexBufferSize() + plane.getVertexBufferSize() + cube.getVertexBufferSize(), NULL, GL_STATIC_DRAW);	//(iVertexBufferId) Set the buffer SIZE, pass in null for data
	
	GLsizei iVPos = 0;
	GLsizei iIPos = 0;
	GLsizei offset;

	glBufferSubData(GL_ARRAY_BUFFER, iVPos, teaPot.getVertexBufferSize(), teaPot.vertices);	//Sets buffer data from 0 to the size of cube's index buffer, passing in the cube's vertex data
	iVPos += teaPot.getVertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, iVPos, arrow.getVertexBufferSize(), arrow.vertices);	//Sets buffer data from 0 to the size of arrows's index buffer, passing in the arrows's vertex data
	iVPos += arrow.getVertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, iVPos, plane.getVertexBufferSize(), plane.vertices);
	iVPos += plane.getVertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, iVPos, cube.getVertexBufferSize(), cube.vertices);
	//Buffer Index Array -> Both Cube and Arrow index data into single buffer
	//Here we initialise the index array buffer
	//Bind the index buffer Id
	//Register / Create the buffers within OpenGL
	//Pass in indices from the cube and arrow models
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIndexBufferId);	//Set the target buffer to (iIndexBufferId) | Create the buffer if it doesn't already exist
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, teaPot.getIndexBufferSize() + arrow.getIndexBufferSize() + plane.getIndexBufferSize() +  cube.getIndexBufferSize(), NULL, GL_STATIC_DRAW);	//(iIndexBufferId) Set the buffer SIZE, pass in null for data
	
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iIPos, teaPot.getIndexBufferSize(), teaPot.indices);	//Sets buffer data from 0 to the size of cube's index buffer, passing in the cube's index data
	iIPos += teaPot.getIndexBufferSize();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iIPos, arrow.getIndexBufferSize(), arrow.indices);	 //Sets buffer data from 0 to the size of arrows's index buffer, passing in the arrows's index data
	iIPos += arrow.getIndexBufferSize();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iIPos, plane.getIndexBufferSize(), plane.indices);
	iIPos += plane.getIndexBufferSize();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iIPos, cube.getIndexBufferSize(), cube.indices);

	m_iArrowIndexCount = arrow.numIndices;
	m_iCubeIndexCount = cube.numIndices;
	m_iPlaneIndexCount = plane.numIndices;
	m_iTeaPotIndexCount = teaPot.numIndices;
	iArrowIndexDataByteOffset = teaPot.getIndexBufferSize();
	iPlaneIndexDataByteOffset = iArrowIndexDataByteOffset + arrow.getIndexBufferSize();
	iCubeIndexDataByteOffset = iPlaneIndexDataByteOffset + plane.getIndexBufferSize();

	glGenVertexArrays(1, &iTeaPotVertexArrayId);
	glGenVertexArrays(1, &iArrowVertexArrayId);
	glGenVertexArrays(1, &iPlaneVertexArrayId);
	glGenVertexArrays(1, &iCubeVertexArrayId);
	//TeaPot
	glBindVertexArray(iTeaPotVertexArrayId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, iVertexBufferId);
	offset = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIndexBufferId);
	// Arrow
	glBindVertexArray(iArrowVertexArrayId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, iVertexBufferId);
	offset += teaPot.getVertexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)offset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIndexBufferId);
	//plane
	glBindVertexArray(iPlaneVertexArrayId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, iVertexBufferId);
	offset += arrow.getVertexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIndexBufferId);
	//Cube
	glBindVertexArray(iCubeVertexArrayId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, iVertexBufferId);
	offset += plane.getVertexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(offset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIndexBufferId);

	//Buffer data has been sent to OpenGL, so we can clear the data within these models before they fall out of scope.
	teaPot.clear();
	arrow.clear();
	plane.clear();
	cube.clear();
}

void Game::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 mtxFullTransform;
	mat4 mtxViewToProjection = perspective(m_display->getAspectf(), (float)m_display->GetWidth() / m_display->GetHeight(), 0.1f, 50.0f);
	mat4 mtxWorldToView = m_camera->getWorldToViewMtx();
	mat4 mtxWorldToProjection = mtxViewToProjection * mtxWorldToView;

	GLint spotLightLocation = glGetUniformLocation(m_diffuseProgramId, "spotLightWorldPos");
	GLint ambientLightLocation = glGetUniformLocation(m_diffuseProgramId, "ambientLight");
	GLint transformUniformLocation = glGetUniformLocation(m_diffuseProgramId, "MVPMatrix");
	GLint modelToWorldMatrixLocation = glGetUniformLocation(m_diffuseProgramId, "modelToWorldMatrix");
	GLint cameraPosLocation = glGetUniformLocation(m_diffuseProgramId, "cameraWorldPos");

	glm::vec4 ambientLight(0.1f, 0.1f, 0.1f,1.0f);

	rotatef += (0.01);
	float cX = cosf(rotatef) * 10;
	float cY = sinf(rotatef) * 10;
	glm::vec3 lightPos(cX, cY, cX);
	glUseProgram(m_diffuseProgramId);
	glUniform3fv(spotLightLocation, 1, &lightPos[0]);
	glUniform4fv(ambientLightLocation, 1,  &ambientLight[0]);
	glUniform3fv(cameraPosLocation, 1, &m_camera->getPos()[0]);

	glBindVertexArray(iTeaPotVertexArrayId);
	mat4 mtxTeaPot = translate(vec3(2.0f, 0.0f, 3.0f)) * rotate(-1.57f, vec3(1.0f, 0.0f, 0.0f));
	mtxFullTransform = mtxWorldToProjection * mtxTeaPot;
	glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, &mtxFullTransform[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixLocation, 1, GL_FALSE,  &mtxTeaPot[0][0]);
	glDrawElements(GL_TRIANGLES, m_iTeaPotIndexCount, GL_UNSIGNED_SHORT, 0);

	mtxTeaPot = translate(vec3(6.0f, 0.0f, -3.0f)) * rotate(-1.57f, vec3(1.0f, 0.0f, 0.0f));
	mtxFullTransform = mtxWorldToProjection * mtxTeaPot;
	glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, &mtxFullTransform[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixLocation, 1, GL_FALSE, &mtxTeaPot[0][0]);
	glDrawElements(GL_TRIANGLES, m_iTeaPotIndexCount, GL_UNSIGNED_SHORT, 0);
	
	glBindVertexArray(iArrowVertexArrayId);
	mat4 mtxArrow = translate(vec3(0.0f, 1.2, -4.0f)) * rotate(0.0f, vec3(1.0f, 0.0f, 0.0f));
	mtxFullTransform = mtxWorldToProjection * mtxArrow;
	glUniformMatrix4fv(modelToWorldMatrixLocation, 1, GL_FALSE, &mtxArrow[0][0]);
	glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, &mtxFullTransform[0][0]);
	glDrawElements(GL_TRIANGLES, m_iArrowIndexCount, GL_UNSIGNED_SHORT, (void*)iArrowIndexDataByteOffset);

	glBindVertexArray(iPlaneVertexArrayId);
	mat4 mtxPlane = glm::mat4();
	mtxFullTransform = mtxWorldToProjection * mtxPlane;
	glUniformMatrix4fv(modelToWorldMatrixLocation, 1, GL_FALSE, &mtxPlane[0][0]);
	glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, &mtxFullTransform[0][0]);
	glDrawElements(GL_TRIANGLES, m_iPlaneIndexCount, GL_UNSIGNED_SHORT, (void*)iPlaneIndexDataByteOffset);

	GLint ambTransformLocation = glGetUniformLocation(m_ambProgramId, "modelToWorldMatrix");
	GLint ambModelToWorldLocation = glGetUniformLocation(m_ambProgramId, "MVPMatrix");
	mat4 mtxCube = glm::translate(lightPos) * glm::scale(vec3(0.1f, 0.1f, 0.1f));
	mtxFullTransform = mtxWorldToProjection * mtxCube;
	glUseProgram(m_ambProgramId);
	glBindVertexArray(iCubeVertexArrayId);
	glUniformMatrix4fv(ambModelToWorldLocation, 1, GL_FALSE, &mtxCube[0][0]);
	glUniformMatrix4fv(ambTransformLocation, 1, GL_FALSE, &mtxFullTransform[0][0]);
	glDrawElements(GL_TRIANGLES, m_iCubeIndexCount, GL_UNSIGNED_SHORT, (void*)iCubeIndexDataByteOffset);
}