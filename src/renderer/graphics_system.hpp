#ifndef GRAPHICS_SYSTEM
#define GRAPHICS_SYSTEM

#include "low_level_renderer_2d.hpp"
#include <string>
#include <set>
#include <vector>
#include "camera.hpp"

#ifndef ENGINE
class Engine;
#endif

#ifndef GRAPHICS_COMPONENT
class GraphicsComponent;
#endif

#ifndef SPRITE
class Sprite;
#endif

class GraphicsSystem
{

	enum class PendingTaskType
	{
		DESTROY_SPRITE
	};

	class PendingTask
	{
	public:
		PendingTask(const PendingTaskType& type, void* pointer);

		PendingTaskType pendingTaskType;
		void* pointer;
	};

	std::vector<PendingTask> pendingTasks;

	Engine* myEngine;

	Camera camera;
	LowLevelRenderer2D renderer;

	std::set<GraphicsComponent*> components;

public:

	GraphicsSystem
	(
		std::string windowTitle,
		unsigned int width, unsigned int height,
		bool fullScreen
	);

    /** \brief update animations
     */
	void update(unsigned int delta);

    /** \brief set fullscreen mode
     */
    void setFullScreen(bool b);

	void draw();

	/** \brief Swap buffers
	 * Once you ave drawn all the components \
	 * call this function to swap buffers
	 */
	void swap();

	Sprite* createSprite(std::string fileName, const Vec2f& scale);
	void destroySprite(Sprite* sprite);

	void destroyGraphicsComponent(GraphicsComponent* graphicsComponent);

	LowLevelRenderer2D* getRenderer();
	Camera* getCamera();

	void end();

};

#endif
