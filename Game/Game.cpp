#include "Game.h"


//Private functions
void Game::initGLFW()
{
	//init glfw
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);


	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLEW__WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);

	glfwMakeContextCurrent(this->window);
}

void Game::initGLEW()
{
	//init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);
}

void Game::initShaders()
{
	this->shaders.push_back(new Shader (this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,"vertex_core.glsl", "fragment_core.glsl", NULL));
}

void Game::initTextures()
{
	this->textures.push_back(new Texture("Images/texture1.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/texture1_specular.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/wood.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/wood_spec.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/cupcake.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/red.jpg", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/birthday.jpg", GL_TEXTURE_2D));

}

void Game::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.5f), glm::vec3(1.f), 0, 1 ));
}

void Game::initOBJModels()
{

}

void Game::initModels()
{
	std::vector<Mesh*>meshes;
	std::vector<Mesh*>meshes2;
	std::vector<Mesh*>meshes3;

	meshes.push_back(new Mesh(&Quad(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f), glm::vec3(-90.f,0.f,0.f), glm::vec3(10.f)));

	this->models.push_back(new Model(glm::vec3(0.0f, 0.f, -1.0f),
		this->materials[0], this->textures[TEX_CORSE],
		this->textures[TEX_CORSE_SPECULAR], meshes));

	meshes2.push_back(new Mesh(&Quad(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(.25f,0.1f,1.f)));
	meshes2.push_back(new Mesh(&Quad(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(.25f, 0.1f, 1.f)));

	this->models.push_back(new Model(glm::vec3(0.0f, 0.7f, -2.0f),
		this->materials[0], this->textures[TEX_PLUS],
		this->textures[TEX_PLUS], meshes2));

	this->models.push_back(new Model(glm::vec3(2.0f, 0.01f, -2.0f), this->materials[0],
		this->textures[TEX_WOOD], this->textures[TEX_WOOD_SPECULAR], "OBJFiles/TriTable.obj", glm::vec3(0.f, 90.f, 0.f), glm::vec3(1.f)));

	this->models.push_back(new Model(glm::vec3(-2.0f, 0.01f, -2.0f), this->materials[0],
		this->textures[TEX_WOOD], this->textures[TEX_WOOD_SPECULAR], "OBJFiles/TriTable.obj", glm::vec3(0.f, 90.f, 0.f), glm::vec3(1.f)));

	meshes3.push_back(new Mesh(&Quad(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(10.f)));

	this->models.push_back(new Model(glm::vec3(0.0f, 5.f, -6.0f),
		this->materials[0], this->textures[TEX_BIRTH],
		this->textures[TEX_BIRTH], meshes3));

	this->models.push_back(new Model(glm::vec3(-1.f, 0.60f, -3.f), this->materials[0],
		this->textures[TEX_CUPCAKE], this->textures[TEX_CUPCAKE], "OBJFiles/TriCupcake.obj", glm::vec3(90.f, 180.f, 0.f), glm::vec3(.05f, .05f, .05f)));

	this->models.push_back(new Model(glm::vec3(-1.5f, 0.60f, -3.f), this->materials[0],
		this->textures[TEX_CUPCAKE], this->textures[TEX_CUPCAKE], "OBJFiles/TriCupcake.obj", glm::vec3(90.f, 180.f, 0.f), glm::vec3(.05f, .05f, .05f)));

	this->models.push_back(new Model(glm::vec3(-0.5f, 0.60f, -3.f), this->materials[0],
		this->textures[TEX_CUPCAKE], this->textures[TEX_CUPCAKE], "OBJFiles/TriCupcake.obj", glm::vec3(90.f, 180.f, 0.f), glm::vec3(.05f, .05f, .05f)));

	this->models.push_back(new Model(glm::vec3(2.5f, 0.60f, -3.f), this->materials[0],
		this->textures[TEX_CUPCAKE], this->textures[TEX_CUPCAKE], "OBJFiles/TriCupcake.obj", glm::vec3(90.f, 180.f, 0.f), glm::vec3(.05f, .05f, .05f)));

	this->models.push_back(new Model(glm::vec3(3.0f, 0.60f, -3.f), this->materials[0],
		this->textures[TEX_CUPCAKE], this->textures[TEX_CUPCAKE], "OBJFiles/TriCupcake.obj", glm::vec3(90.f, 180.f, 0.f), glm::vec3(.05f, .05f, .05f)));

	for (auto*& i : meshes)
	{
		delete i;
	}

	for (auto*& i : meshes2)
	{
		delete i;
	}

	for (auto*& i : meshes3)
	{
		delete i;
	}
}

void Game::initPointLights()
{
	this->pointLights.push_back(new PointLight(glm::vec3(0.f, 2.f, 1.f)));
}

void Game::wrongLights()
{

	this->pointLights.push_back(new PointLight(glm::vec3(0.f, 2.f, 1.f), 0.1f, glm::vec3(1.f, 0.f, 0.f)));
}

void Game::rightLights()
{
	this->pointLights.push_back(new PointLight(glm::vec3(0.f, 2.f, 1.f), 0.1f, glm::vec3(0.f, 1.f, 0.f)));
}

void Game::initLights()
{
	this->initPointLights();
}

void Game::initUniforms()
{

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	for (PointLight* pl : this->pointLights){
		pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}
}

void Game::updateUniforms()
{
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");
	for (PointLight* pl : this->pointLights) {
		pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

}

//Constructors / Destructor
Game::Game(const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable)
	:WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 2.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	//Init variables
	this->window = nullptr;
	this->framebufferHeight = this->WINDOW_HEIGHT;
	this->framebufferWidth = this->WINDOW_WIDTH;

	this->camPosition = glm::vec3(0.f, 1.f, -1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->dt = 0.0f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;

	
	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initOBJModels();
	this->initModels();
	this->initLights();
	this->initUniforms();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
	{
		delete this->shaders[i];
	}

	for (size_t i = 0; i < this->textures.size(); i++)
	{
		delete this->textures[i];
	}

	for (size_t i = 0; i < this->materials.size(); i++)
	{
		delete this->materials[i];
	}

	for (auto*& i : this->models)
	{
		delete i;
	}

	for (size_t i = 0; i < this->pointLights.size(); i++)
	{
		delete this->pointLights[i];
	}
}

//accessor
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//modifier
void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//functions

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	//move light
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		this->pointLights[0]->setPosition(this->camera.getPosition());
	}
}

void Game::updateInput()
{
	glfwPollEvents();

	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::updateKeyboardInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	//camera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->dt, RIGHT);
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		this->camera.move(this->dt, UPWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		this->camera.move(this->dt, DOWNWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		this->camera.move(this->dt, UP);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		this->camera.move(this->dt, FRONT);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		this->rightLights();
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		this->wrongLights();
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		this->wrongLights();
	}
}

void Game::update()
{
	this->updateDt();
	//update input
	this->updateInput();
}

void Game::render()
{
	//clear
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();

	for (auto& i : this->models)
	{
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}

	//end draw
	glfwSwapBuffers(window);
	glFlush();

	//reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//static functions
void Game::framebuffer_resize_callback(GLFWwindow* window , int frameBufferWidth, int frameBufferHeight)
{
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}
