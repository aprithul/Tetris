// Link statically with GLEW
//#define GLEW_STATIC

// Headers
#include <GL/glew.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <iostream>

// Shader sources
const GLchar* vertexShaderSource =
"#version 150 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"void main() {"
"   Color = color;"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";

const GLchar* fragmentShaderSource =
"#version 150 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(Color, 1.0);"
"}";

SDL_GLContext context;
SDL_Window* window;
bool isRunning;
void init();
void createContext(int maj_v, int min_v, char* title, float originX, float originY, float width, float height);


int main(int args, char* argv[])
{
	

	init();
	
	// vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top-left
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//create vertex shader
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vShader);

	GLint status;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		printf("error compiling vertex shader");
		return -1;
	}

	// create fragment shader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fShader);

	glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		printf("error compiling fragment shader");
		return -2;
	}
	
	// create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}


		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		//std::cout << sin(time) << std::endl;

		// Draw a triangle from the 3 vertices
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);
		SDL_Delay(.1f);
	}
	
	glDeleteProgram(shaderProgram);
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);


	return 0;
}

void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	createContext(3,2,"opengl",300,300,800,600);
	isRunning = true;
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

}


void createContext(int maj_v, int min_v, char* title, float originX, float originY, float width, float height)
{

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, maj_v);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, min_v);

	window = SDL_CreateWindow(title, originX, originY, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
}
