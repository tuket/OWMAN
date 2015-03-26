#include "low_level_renderer_2d.hpp"
#include <iostream>

using namespace std;

void loadTexture(string fileName, int* width, int* height);

//  CAMERA
// --------

LowLevelRenderer2D::Camera::Camera()
{
	pos = Vec2f(0, 0);
}

Vec2f LowLevelRenderer2D::Camera::getPosition()const
{
	return pos;
}

void LowLevelRenderer2D::Camera::setPosition(const Vec2f& pos)
{
	this->pos = pos;
}

//  TEXTURE
// ---------

LowLevelRenderer2D::Texture::Texture(string fileName)
{
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	loadTexture(fileName.c_str(), &width, &height);
	
}

LowLevelRenderer2D::Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
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
		
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	// init glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  cerr << "Error: " << glewGetErrorString(err) << endl;
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	
	glClearColor(0, 0.2, 0, 0);
	
	// vertices of the default quad
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
	"void main()"
	"{"
		"gl_Position = vec4(inPosition, 0.0, 1.0);"
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
	
	// compile fragment shader
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
		cerr << "Error: compiling fragment shader" << endl;
		exit(1);
	}
	
	// combining shaders into a program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	
	// Since fragment shader is allowed to write to multiple buffers,
	// you need to specify which output is written to which buffer.
	// You must do this before linking.
	// However, since 0 is the default and there is only one output
	// the following line is not necessary.
	/// glBindFragDataLocation(shaderProgram, 0, "outColor");
	
	// We must connect the two shaders.
	// We do this with the "linking" step.
	glLinkProgram(shaderProgram);
	
	// use the program
	glUseProgram(shaderProgram);
	
	// VAO
	// ---
	// VAOs are used to save "settings"
	// VAOs store all the links between the attributes and
	// your VBO with raw vertex data.
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	// making the link between vertex data and attributes
	// OpenGL needs to know how the attributes are formatted
	// and ordered
	
	// POSITION ATTRIBUTE
	GLint posAttrib = glGetAttribLocation(shaderProgram, "inPosition");
	
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
	GLint texAttrib = glGetAttribLocation(shaderProgram, "inTexCoords");
	
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
	
	// enable using textures
	glEnable(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
	
}

// Get reference to camera
LowLevelRenderer2D::Camera& LowLevelRenderer2D::getCamera()
{
	return camera;
}

// clear color buffer
void LowLevelRenderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void LowLevelRenderer2D::draw(const Vec2f& pos, const Vec2f& scale, Texture* texture)
{
	
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
		SOIL_LOAD_RGB		// RGB
	);
	
	// specify a 2-dimensional texture image
	glTexImage2D
	(
		GL_TEXTURE_2D,		// target
		0,					// level of detail (0 is base level)
		GL_RGB,				// internal format
		*width,				// width
		*height,			// height
		0,					// border (must be 0)
		GL_RGB,				// format of the pixel data
		GL_UNSIGNED_BYTE,	// data type of the pixel data
		image				// pointer to iamge data
	);
	
	SOIL_free_image_data(image);
	
}
