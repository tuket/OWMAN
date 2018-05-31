#include "low_level_renderer_2d.hpp"
#include "graphics_system.hpp"
#include <iostream>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../math/aarect.hpp"

using namespace std;


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

LowLevelRenderer2D::Texture::Texture(const unsigned char* image, int width, int height)
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

const array<GLuint, LLRFilterMode::NUM_FILTER_MODES>
    LowLevelRenderer2D::Texture:: filterModesGL =
(
    []() -> array<GLuint, FilterMode::NUM_FILTER_MODES>
    {
        std::array<GLuint, FilterMode::NUM_FILTER_MODES> a = {0};
        a[FilterMode::LINEAR] = GL_LINEAR;
        a[FilterMode::NEAREST] = GL_NEAREST;
        return a;
    }
)();

void LowLevelRenderer2D::Texture::setFilterMode(FilterMode filterMode)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterModesGL[filterMode]);
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

// SpriteVao
// ----------

GLfloat LowLevelRenderer2D::SpriteVbo::verts[] =
{
    -0.5, 0.5, 0, 0,
    0.5, 0.5, 1, 0,
    0.5, -0.5, 1, 1,
    -0.5, -0.5, 0, 1
};

LLRSpriteVbo::SpriteVbo(const AARect& rect)
{

    setRectVerts(rect);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

}

LLRSpriteVbo::SpriteVbo(const SpriteVbo& spriteVbo)
{
    VBO = spriteVbo.VBO;
}

const LLRSpriteVbo& LLRSpriteVbo::operator=(const LLRSpriteVbo& spriteVbo)
{
    VBO = spriteVbo.VBO;
    return *this;
}

void LowLevelRenderer2D::SpriteVbo::setRectVerts(const AARect& rect)
{
    float x1 = rect.x;
    float x2 = rect.x + rect.w;
    float y1 = rect.y;
    float y2 = rect.y + rect.h;
    verts[ 0*4 + 2 + 0 ] = x1; verts[ 0*4 + 2 + 1 ] = y1;
    verts[ 1*4 + 2 + 0 ] = x2; verts[ 1*4 + 2 + 1 ] = y1;
    verts[ 2*4 + 2 + 0 ] = x2; verts[ 2*4 + 2 + 1 ] = y2;
    verts[ 3*4 + 2 + 0 ] = x1; verts[ 3*4 + 2 + 1 ] = y2;
}



//  LOW LEVEL RENDERER 2D
// -----------------------

const GLuint LowLevelRenderer2D::posAttrib = 0;
const GLuint LowLevelRenderer2D::texAttrib = 1;

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
		SDL_WINDOW_OPENGL | (fullScreen?SDL_WINDOW_FULLSCREEN:0)
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
		-0.5, 0.5,
		0.5, 0.5,
		0.5, -0.5,
		-0.5, -0.5
	};

	// create one vertex buffer object
	GLuint colVBO;
	glGenBuffers(1, &colVBO);

	// make VBO the current active vertex array buffer
	glBindBuffer(GL_ARRAY_BUFFER, colVBO);

	// upload the vertex data to the video card
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// triangles of the default quad
	const GLuint elements[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	// create one element buffer object
	glGenBuffers(1, &EBO);

	// make EBO the current active element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// upload the element data to the video card
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    const char* colVertShaderSource =
    "#version 120\n"
	"attribute vec2 inPosition;"
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
	"}";

	const char* texVertShaderSource =
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

	const char* texFragShaderSource =
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

	// compile vertex shader (color)
	GLuint colVertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource
	(
		colVertShader,			// shader id
		1,					// number of strings
		&colVertShaderSource,			// array of strings
		0					// length of each string(0 means stop at null char)
	);
	glCompileShader(colVertShader);
	// check if the shader compiled OK
	GLint status;
	glGetShaderiv(colVertShader, GL_COMPILE_STATUS, &status);
	if( status != GL_TRUE )
	{
		cerr << "Error: compiling color vertex shader" << endl;
		exit(1);
	}

	// compile vertex shader (texture)
	GLuint texVertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource
	(
		texVertShader,			// shader id
		1,					// number of strings
		&texVertShaderSource,			// array of strings
		0					// length of each string(0 means stop at null char)
	);
	glCompileShader(texVertShader);
	// check if the shader compiled OK
	glGetShaderiv(texVertShader, GL_COMPILE_STATUS, &status);
	if( status != GL_TRUE )
	{
		cerr << "Error: compiling texture vertex shader" << endl;
		exit(1);
	}

	// compile fragment shader (texture)
	GLuint texFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource
	(
		texFragShader,
		1,
		&texFragShaderSource,
		0
	);
	glCompileShader(texFragShader);
	// check if the shader compiled OK
	glGetShaderiv(texFragShader, GL_COMPILE_STATUS, &status);
	if( status != GL_TRUE )
	{
		cerr << "Error: compiling fragment shader(texture)" << endl;
		exit(1);
	}

	// compile fragment shader (color)
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
	glAttachShader(textureShaderProgram, texVertShader);
	glAttachShader(textureShaderProgram, texFragShader);
	glBindAttribLocation(textureShaderProgram, posAttrib, "inPosition");
	glBindAttribLocation(textureShaderProgram, texAttrib, "inTexCoords");

	// combining shaders into a program (color)
	colorShaderProgram = glCreateProgram();
	glAttachShader(colorShaderProgram, colVertShader);
	glAttachShader(colorShaderProgram, colFragShader);
	glBindAttribLocation(textureShaderProgram, posAttrib, "inPosition");

	// We must connect the two shaders.
	// We do this with the "linking" step.
	glLinkProgram(textureShaderProgram);
	glLinkProgram(colorShaderProgram);

	// TEXTURE SHADER ATTRIBS
	// use the program
	glUseProgram(textureShaderProgram);

	// enable using textures
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(textureShaderProgram, "tex"), 0);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// transform matrices
	texModelMatrix = glGetUniformLocation(textureShaderProgram, "modelMatrix");
	texViewMatrix = glGetUniformLocation(textureShaderProgram, "viewMatrix");
	texProjMatrix = glGetUniformLocation(textureShaderProgram, "projMatrix");
	colModelMatrix = glGetUniformLocation(colorShaderProgram, "modelMatrix");
	colViewMatrix = glGetUniformLocation(colorShaderProgram, "viewMatrix");
	colProjMatrix = glGetUniformLocation(colorShaderProgram, "projMatrix");

	// color uniform
	color = glGetUniformLocation(colorShaderProgram, "col");

}

void LowLevelRenderer2D::setFullScreen(bool b)
{
    if(b) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    else SDL_SetWindowFullscreen(window, 0);
}

// Get reference to camera
LowLevelRenderer2D::Camera* LowLevelRenderer2D::getCamera()
{
	return &camera;
}


LowLevelRenderer2D::Texture LowLevelRenderer2D::createTexture(const unsigned char* image, int width, int height)
{
	Texture res(image, width, height);
	return res;
}


void LowLevelRenderer2D::destroyTexture(Texture* texture)
{
	glDeleteTextures(1, &(texture->textureID));
	texture->width = 0;
	texture->height = 0;
}

// clear color buffer
void LowLevelRenderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void LowLevelRenderer2D::draw
(
    const Vec2f& pos,
    const Vec2f& scale,
    const Texture& texture,
    const SpriteVbo& sVbo
)
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

	glBindBuffer(GL_ARRAY_BUFFER, sVbo.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // VERTEX DATA FORMAT
    // pos attrib
	glVertexAttribPointer
	(
		posAttrib,			// input
		2,					// num of vals
		GL_FLOAT,			// type of vals
		GL_FALSE,			// should they be normalized?
		4*sizeof(float),	// stride: how many bytes between each pos
		0					// offset: offset of the attribute wrt pos
	);
	glEnableVertexAttribArray(posAttrib);
    // tex attrib
	glVertexAttribPointer
	(
		texAttrib,			// input
		2,					// num of vals
		GL_FLOAT,			// type of vals
		GL_FALSE,			// should they be normalized?
		4*sizeof(float),			// stride: how many bytes between each pos
		(void*)(2*sizeof(float))	// offset: offset of the attribute wrt pos
	);
	glEnableVertexAttribArray(texAttrib);

	glUseProgram(textureShaderProgram);

	// upload matrices
	glUniformMatrix4fv(texModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(texViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(texProjMatrix, 1, GL_FALSE, glm::value_ptr(projMat));

	glBindTexture
	(
		GL_TEXTURE_2D,
		texture.textureID
	);

	glDrawElements
	(
		GL_TRIANGLES,		// primitive to draw
		6,					// how many vertices to draw
		GL_UNSIGNED_INT,
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
	glBindBuffer(GL_ARRAY_BUFFER, colVBO);

	// VERTEX DATA FORMAT
	// pos attrib
	glVertexAttribPointer
	(
		posAttrib,			// input
		2,					// num of vals
		GL_FLOAT,			// type of vals
		GL_FALSE,			// should they be normalized?
		4*sizeof(float),	// stride: how many bytes between each pos
		0					// offset: offset of the attribute wrt pos
	);
	glEnableVertexAttribArray(posAttrib);

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


void LowLevelRenderer2D::end()
{
    setFullScreen(false);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
