#ifndef LOW_LEVEL_RENDERER_2D
#define LOW_LEVEL_RENDERER_2D

#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SOIL/SOIL.h>
#include "../math/vec2f.hpp"
#include <string>
#include <array>
#include "color.hpp"

class AARect;

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

	// Wraper for a low level OpenGL texture
	class Texture
	{

		friend class LowLevelRenderer2D;

		GLuint textureID;
		int width, height;

		Texture(const unsigned char* image, int width, int height);

	public:

	    enum FilterMode
	    {
	        LINEAR,
	        NEAREST,

	        NUM_FILTER_MODES
	    };
	    static const std::array<GLuint, NUM_FILTER_MODES> filterModesGL;

		Texture(){}
		Texture operator=(const Texture& texture);
		~Texture();

		float getWidth()const;
		float getHeight()const;

		void setWidth(float width);
		void setHeight(float height);

		void setFilterMode(FilterMode filterMode);

	};

	class SpriteVbo
	{

        friend class LowLevelRenderer2D;

        GLuint VBO;

        static GLfloat verts[];

    public:

        SpriteVbo(){}
        SpriteVbo(const AARect& rect);
        SpriteVbo(const SpriteVbo& spriteVbo);

        const SpriteVbo& operator=(const SpriteVbo&);

    private:

        void setRectVerts(const AARect& rect);

	};

private:

	static LowLevelRenderer2D uniqueInstance;

	static const GLuint posAttrib, texAttrib;

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

    GLuint colVBO;
    GLuint EBO;     //< the default EBO

public:

	LowLevelRenderer2D(){}

	LowLevelRenderer2D
	(
		std::string windowTitle,
		unsigned int width, unsigned int height,
		bool fullScreen
	);

	void setFullScreen(bool b);

	Camera* getCamera();

	Texture createTexture(const unsigned char* image, int width, int height);
	void destroyTexture(Texture* texture);

	void clear();
	void draw
	(
        const Vec2f& pos,
        const Vec2f& scale,
        const Texture& texture,
        const SpriteVbo& sVao
    );
	void drawColorSquare(const Vec2f& pos, const Vec2f& scale, const Color& color);
	void swap();

	void end();

};

typedef LowLevelRenderer2D::Texture::FilterMode LLRFilterMode;
typedef LowLevelRenderer2D::SpriteVbo LLRSpriteVbo;

#endif
