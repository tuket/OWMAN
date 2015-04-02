#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SOIL/SOIL.h>
#include "../math/vec2f.hpp"
#include <string>
#include "color.hpp"

#ifndef LOW_LEVEL_RENDERER_2D
#define LOW_LEVEL_RENDERER_2D

class LowLevelRenderer2D
{
	
public:

	class Camera
	{
		
		friend class LowLevelRenderer2D;
		Vec2f pos;
		float width, height;
		
		Camera();
		
	public:
		
		Vec2f getPosition()const;
		void setPosition(const Vec2f& pos);
		
		float getWidth()const;
		float getHeight()const;
		
		void setWidth(float width);
		void setHeight(float height);
		
	};
	
	// Wraper for a lwo level OpenGL texture
	class Texture
	{
		
		friend class LowLevelRenderer2D;
		
		GLuint textureID;
		int width, height;
		
		Texture(unsigned char* image, int width, int height);
		
	public:
		Texture(){}
		Texture operator=(const Texture& texture);
		~Texture();
		
	};
	
private:
	
	static LowLevelRenderer2D uniqueInstance;
	
	Camera camera;
	GLuint textureShaderProgram;
	GLuint colorShaderProgram;
	SDL_Window* window;
	
	GLint texModelMatrix;
	GLint texViewMatrix;
	GLint texProjMatrix;
	GLint colModelMatrix;
	GLint colViewMatrix;
	GLint colProjMatrix;
	GLint color;
	
	GLuint texVAO;
	GLuint colVAO;
	
	
public:

	LowLevelRenderer2D(){}
	
	LowLevelRenderer2D
	(
		std::string windowTitle,
		unsigned int width, unsigned int height,
		bool fullScreen
	);
	
	Camera* getCamera();
	
	Texture createTexture(unsigned char* image, int width, int height);
	void destroyTexture(Texture* texture);
	
	void clear();
	void draw(const Vec2f& pos, const Vec2f& scale, Texture* texture);
	void drawColorSquare(const Vec2f& pos, const Vec2f& scale, const Color& color);
	void swap();
	
};

#endif
