#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SOIL/SOIL.h>
#include "../math/vec2f.hpp"
#include <string>

#ifndef LOW_LEVEL_RENDERER_2D
#define LOW_LEVEL_RENDERER_2D

class LowLevelRenderer2D
{
	
public:

	class Camera
	{
		
		friend class LowLevelRenderer2D;
		Vec2f pos;
		
		Camera();
		
	public:
		
		Vec2f getPosition()const;
		void setPosition(const Vec2f& pos);
		
	};
	
	// Wraper for a lwo level OpenGL texture
	class Texture
	{
		
		friend class LowLevelRenderer2D;
		
		GLuint textureID;
		int width, height;
		
	public:
	
		Texture(std::string fileName);
		~Texture();
		
	};
	
private:
	
	Camera camera;
	GLuint shaderProgram;
	SDL_Window* window;
	
public:
	
	LowLevelRenderer2D
	(
		std::string windowTitle,
		unsigned int width, unsigned int height,
		bool fullScreen
	);
	
	Camera& getCamera();
	
	void clear();
	void draw(const Vec2f& pos, const Vec2f& scale, Texture* texture);
	void swap();
	
};

#endif
