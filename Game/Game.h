#pragma once

#include "libs.h"
#include "Camera.h"

//enums
enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_CORSE = 0, TEX_CORSE_SPECULAR =1, TEX_WOOD = 2, TEX_WOOD_SPECULAR=3, TEX_CUPCAKE =4, TEX_PLUS=5, TEX_BIRTH=6};
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };
enum light_enu { MAIN_LIGHT = 0 };


class Game
{
private:
	//variables
	//window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//Delta time
	float dt;
	float curTime;
	float lastTime;

	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//Camera
	Camera camera;

	//openGL context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;
	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Models
	std::vector<Model*> models;

	//Lights
	std::vector<PointLight*> pointLights;



	//private functions
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW(); //after context cration
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initOBJModels();
	void initPointLights();
	void initModels();
	void initLights();
	void wrongLights();
	void rightLights();
	void initUniforms();

	void updateUniforms();


public:
	Game(const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable);
	virtual ~Game();

//Accessors
	int getWindowShouldClose();
//Modifiers
	void setWindowShouldClose();

//Funtions
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update();
	void render();

//static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);
};

