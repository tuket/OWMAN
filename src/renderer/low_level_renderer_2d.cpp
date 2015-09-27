#include "low_level_renderer_2d.hpp"
#include "graphics_system.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void loadTexture(string fileName, int* width, int* height);

//  CAMERA
// --------

LowLevelRenderer2D::Camera::Camera()
{
	pos = Vec2f(0, 0);
	width = 1;
	height = 1;
}

Vec2f LowLevelRenderer2D::Camera::getPosition()const
{
	return pos;
}

void LowLevelRenderer2D::Camera::setPosition(const Vec2f& pos)
{
	this->pos = pos;
}

float LowLevelRenderer2D::Camera::getWidth()const
{
	return width;
}

float LowLevelRenderer2D::Camera::getHeight()const
{
	return height;
}

void LowLevelRenderer2D::Camera::setWidth(float width)
{
	this->width = width;
}

void LowLevelRenderer2D::Camera::setHeight(float height)
{
	this->height = height;
}

//  TEXTURE
// ---------

LowLevelRenderer2D::Texture::Texture(unsigned char* image, int width, int height)
{

	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(1, &textureID);
	GLenum error = glGetError();
	cout << "texture: " << textureID << endl;
	cout << "error: " << error << endl;
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	// specify a 2-dimensional texture image
	glTexImage2D
	(
		GL_TEXTURE_2D,		// target
		0,					// level of detail (0 is base level)
		GL_RGBA,			// internal format
		width,				// width
		height,			// height
		0,					// border (must be 0)
		GL_RGBA,			// format of the pixel data
		GL_UNSIGNED_BYTE,	// data type of the pixel data
		image				// pointer to iamge data
	);

}

LowLevelRenderer2D::Texture
LowLevelRenderer2D::Texture::operator=(const Texture& texture)
{
	this->textureID = texture.textureID;
	this->width = texture.width;
	this->height = texture.height;
	return *this;
}

LowLevelRenderer2D::Texture::~Texture()
{

}

float LowLevelRenderer2D::Texture::getWidth()const
{
	return width;
}

float LowLevelRenderer2D::Texture::getHeight()const
{
	return height;
}

void LowLevelRenderer2D::Texture::setWidth(float width)
{
	this->width = width;
}

void LowLevelRenderer2D::Texture::setHeight(float height)
{
	this->height = height;
}


//  LOW LEVEL RENDERER 2D
// -----------------------


// Constructor
LowLevelRenderer2D::LowLevelRenderer2D
(
	string windowTitle,
	unsigned int width, unsigned int height,
	bool fullScreen
)
{

	SDL_Init(SDL_INIT_VIDEO);

	const int glMajorVersion = 2;
	const int glMinorVersion = 1;

	cout << "Using OpenGL version: " <<
	glMajorVersion << "." << glMinorVersion << endl;

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	// make the window
	window =
	SDL_CreateWindow(
		windowTitle.c_str(),
		40, 40,
		width, height,
		SDL_WINDOW_OPENGL
	);

	/*SDL_GLContext context = */SDL_GL_CreateContext(window);

	// init glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  cerr << "Error: " << glewGetErrorString(err) << endl;
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;

	glClearColor(0, 0.5, 0, 0);

	// vertices of the default textured quad
	const GLfloat vertices[] =
	{
		-0.5, 0.5, 0, 0,
		0.5, 0.5, 1, 0,
		0.5, -0.5, 1, 1,
		-0.5, -0.5, 0, 1
	};

	// create one vertex buffer object
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// make VBO the current active vertex array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// upload the vertex data to the video card
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// triangles of the default quad
	const GLuint elements[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	// create one element buffer object
	GLuint EBO;
	glGenBuffers(1, &EBO);

	// make EBO the current active element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// upload the element data to the video card
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	const char* vertShaderSource =
	"#version 120\n"
	"attribute vec2 inPosition;"
	"attribute vec2 inTexCoords;"
	"uniform mat4 modelMatrix;"
	"uniform mat4 viewMatrix;"
	"uniform mat4 projMatrix;"
	"void main()"
	"{"
		"vec4 transfPosition = vec4 (inPosition, 0.0, 1.0);"
		"transfPosition = modelMatrix * transfPosition;"
		"transfPosition = viewMatrix * transfPosition;"
		"transfPosition = projMatrix * transfPosition;"
		"gl_Position = vec4(transfPosition);"
		"gl_TexCoord[0] = vec4(inTexCoords, 0, 0);"
	"}";

	const char* fragShaderSource =
	"#version 120\n"
	"uniform sampler2D tex;"
	"void main()"
	"{"
		"vec4 color = texture2D(tex, gl_TexCoord[0].st);"
		"gl_FragColor = color;"
	"}";

	const char* colFragShaderSource =
	"#version 120\n"
	"uniform vec4 col;"
	"void main()"
	"{"
		"vec4 color = col;"
		"gl_FragColor = color;"
	"}";

	// compiling shaders
	// compile vertex shader
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource
	(
		vertShader,			// shader id
		1,					// number of strings
		&vertShaderSource,			// array of strings
		0					// length of each string(0 means stop at null char)
	);
	glCompileShader(vertShader);

	// check if the shader compiled OK
	GLint status;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
	if( status != GL_TRUE )
	{
		cerr << "Error: compiling vertex shader" << endl;
		exit(1);
	}

	// compile fragment shader(texture)
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource
	(
		fragShader,
		1,
		&fragShaderSource,
		0
	);
	glCompileShader(fragShader);

	// check if the shader compiled OK
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
	if( status != GL_TRUE )
	{
		cerr << "Error: compiling fragment shader(texture)" << endl;
		exit(1);
	}

	// compile fragment shader(color)
	GLuint colFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource
	(
		colFragShader,
		1,
		&colFragShaderSource,
		0
	);
	glCompileShader(colFragShader);

	// check if the shader compiled OK
	glGetShaderiv(colFragShader, GL_COMPILE_STATUS, &status);
	if( status != GL_TRUE )
	{
		cerr << "Error: compiling fragment shader(color)" << endl;
		exit(1);
	}

	// combining shaders into a program (texture)
	textureShaderProgram = glCreateProgram();
	glAttachShader(textureShaderProgram, vertShader);
	glAttachShader(textureShaderProgram, fragShader);

	// combining shaders into a program (color)
	colorShaderProgram = glCreateProgram();
	glAttachShader(colorShaderProgram, vertShader);
	glAttachShader(colorShaderProgram, colFragShader);

	// Since fragment shader is allowed to write to multiple buffers,
	// you need to specify which output is written to which buffer.
	// You must do this before linking.
	// However, since 0 is the default and there is only one output
	// the following line is not necessary.
	/// glBindFragDataLocation(textureShaderProgram, 0, "outColor");

	// We must connect the two shaders.
	// We do this with the "linking" step.
	glLinkProgram(textureShaderProgram);
	glLinkProgram(colorShaderProgram);

	// TEXTURE SHADER ATTRIBS
	// use the program
	glUseProgram(textureShaderProgram);

	// VAO
	// ---
	// VAOs are used to save "settings"
	// VAOs store all the links between the attributes and
	// your VBO with raw vertex data.
	glGenVertexArrays(1, &texVAO);
	glBindVertexArray(texVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// making the link between vertex data and attributes
	// OpenGL needs to know how the attributes are formatted
	// and ordered

	// POSITION ATTRIBUTE
	GLint posAttrib = glGetAttribLocation(textureShaderProgram, "inPosition");

	// specify how the data is structured in the array
	glVertexAttribPointer
	(
		posAttrib,			// input
		2,					// num of vals
		GL_FLOAT,			// type of vals
		GL_FALSE,			// should they be normalized?
		4*sizeof(float),	// stride: how many bytes between each pos
		0					// offset: offset of the attribute wrt pos
	);

	// enable vertex attribute array
	glEnableVertexAttribArray(posAttrib);

	// TEXCOORD ATTRIBUTE
	GLint texAttrib = glGetAttribLocation(textureShaderProgram, "inTexCoords");

	// specify how the data is structured in the array
	glVertexAttribPointer
	(
		texAttrib,			// input
		2,					// num of vals
		GL_FLOAT,			// type of vals
		GL_FALSE,			// should they be normalized?
		4*sizeof(float),			// stride: how many bytes between each pos
		(void*)(2*sizeof(float))	// offset: offset of the attribute wrt pos
	);

	// enable vertex attribute array
	glEnableVertexAttribArray(texAttrib);

	// COLOR SHADER ATTRIBS
	glUseProgram(colorShaderProgram);

	glGenVertexArrays(1, &colVAO);
	glBindVertexArray(colVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// POSITION ATTRIBUTE
	posAttrib = glGetAttribLocation(colorShaderProgram, "inPosition");

	// specify how the data is structured in the array
	glVertexAttribPointer
	(
		posAttrib,			// input
		2,					// num of vals
		GL_FLOAT,			// type of vals
		GL_FALSE,			// should they be normalized?
		4*sizeof(float),	// stride: how many bytes between each pos
		0					// offset: offset of the attribute wrt pos
	);

	// enable vertex attribute array
	glEnableVertexAttribArray(posAttrib);

	// enable using textures
	glBindVertexArray(texVAO);
	glUseProgram(textureShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(textureShaderProgram, "tex"), 0);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(colVAO);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// transform matrices
	glBindVertexArray(texVAO);
	texModelMatrix = glGetUniformLocation(textureShaderProgram, "modelMatrix");
	texViewMatrix = glGetUniformLocation(textureShaderProgram, "viewMatrix");
	texProjMatrix = glGetUniformLocation(textureShaderProgram, "projMatrix");
	glBindVertexArray(colVAO);
	colModelMatrix = glGetUniformLocation(colorShaderProgram, "modelMatrix");
	colViewMatrix = glGetUniformLocation(colorShaderProgram, "viewMatrix");
	colProjMatrix = glGetUniformLocation(colorShaderProgram, "projMatrix");

	// color uniform
	color = glGetUniformLocation(colorShaderProgram, "col");

}

// Get reference to camera
LowLevelRenderer2D::Camera* LowLevelRenderer2D::getCamera()
{
	return &camera;
}


LowLevelRenderer2D::Texture LowLevelRenderer2D::createTexture(unsigned char* image, int width, int height)
{

	glBindVertexArray(texVAO);
	glUseProgram(textureShaderProgram);

	Texture res(image, width, height);
	return res;

}


void LowLevelRenderer2D::destroyTexture(Texture* texture)
{

	glUseProgram(textureShaderProgram);
	glBindVertexArray(texVAO);

	glDeleteTextures(1, &(texture->textureID));
	texture->width = 0;
	texture->height = 0;

}

// clear color buffer
void LowLevelRenderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void LowLevelRenderer2D::draw(const Vec2f& pos, const Vec2f& scale, Texture* texture)
{

	Vec2f camPos = camera.getPosition();

	// compute model matrix
	glm::mat4 modelMat =
	glm::translate(glm::mat4(1.0), glm::vec3(pos.x, pos.y, 0)) *
	glm::scale(glm::mat4(1.0), glm::vec3(scale.x, scale.y, 1));

	// compute view matrix
	glm::mat4 viewMat = glm::translate(glm::mat4(1.0), glm::vec3(camPos.x, camPos.y, 0));

	// compute projection matrix
	glm::mat4 projMat =
	glm::scale
	(
		glm::mat4(1.0),
		glm::vec3(1.0/camera.getWidth(), 1.0/camera.getHeight(), 1.0)
	);

	glBindVertexArray(texVAO);
	glUseProgram(textureShaderProgram);

	// upload matrices
	glUniformMatrix4fv(texModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(texViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(texProjMatrix, 1, GL_FALSE, glm::value_ptr(projMat));

	glBindTexture
	(
		GL_TEXTURE_2D,
		texture->textureID
	);

	glDrawElements
	(
		GL_TRIANGLES,		// primitive to draw
		6,					// how many vertices to skip
		GL_UNSIGNED_INT,	// how many vertices to draw
		0
	);

}

void LowLevelRenderer2D::drawColorSquare(const Vec2f& pos, const Vec2f& scale, const Color& color)
{

	Vec2f camPos = camera.getPosition();

	// compute model matrix
	glm::mat4 modelMat =
	glm::translate(glm::mat4(1.0), glm::vec3(pos.x, pos.y, 0)) *
	glm::scale(glm::mat4(1.0), glm::vec3(scale.x, scale.y, 1));

	// compute view matrix
	glm::mat4 viewMat = glm::translate(glm::mat4(1.0), glm::vec3(camPos.x, camPos.y, 0));

	// compute projection matrix
	glm::mat4 projMat =
	glm::scale
	(
		glm::mat4(1.0),
		glm::vec3(1.0/camera.getWidth(), 1.0/camera.getHeight(), 1.0)
	);

	glUseProgram(colorShaderProgram);
	glBindVertexArray(colVAO);

	// upload matrices
	glUniformMatrix4fv(colModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(colViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(colProjMatrix, 1, GL_FALSE, glm::value_ptr(projMat));

	// set color uniform
	glUniform4fv(this->color, 1, (GLfloat*)(&color));

	glDrawElements
	(
		GL_TRIANGLES,		// primitive to draw
		6,					// how many vertices to skip
		GL_UNSIGNED_INT,	// how many vertices to draw
		0
	);


}

void LowLevelRenderer2D::swap()
{
	SDL_GL_SwapWindow(window);
}


//  LOAD TEXTURE
// --------------
void loadTexture(string fileName, int* width, int* height)
{

	unsigned char* image =
	SOIL_load_image
	(
		fileName.c_str(),	// file name
		width,				// pointer where width will be saved
		height,				// pointer where height will be saved
		0,					// pointer where num of chanel will be saved
		SOIL_LOAD_RGBA		// RGB
	);

	if(image == 0)
	{
		cerr << "Error loading: " << fileName << endl;
		return;
	}

	// specify a 2-dimensional texture image
	glTexImage2D
	(
		GL_TEXTURE_2D,		// target
		0,					// level of detail (0 is base level)
		GL_RGBA,			// internal format
		*width,				// width
		*height,			// height
		0,					// border (must be 0)
		GL_RGBA,			// format of the pixel data
		GL_UNSIGNED_BYTE,	// data type of the pixel data
		image				// pointer to iamge data
	);

	SOIL_free_image_data(image);

}
