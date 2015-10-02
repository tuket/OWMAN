#ifndef SPRITE
#define SPRITE

#include "graphics_component.hpp"
#include "low_level_renderer_2d.hpp"
#include "../math/vec2f.hpp"
#include <map>
#include <vector>
#include "animation.hpp"

#ifndef RESOURCE_TEXT
class ResourceText;
#endif

#ifndef RESOURCE_MANAGER
class ResourceManager;
#endif

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef SPRITE_MANAGER
class SpriteManager;
#endif

/** \brief Represents a static sprite
 * This sprite has no animations
 */
class Sprite : public GraphicsComponent
{

	friend class SpriteManager;

	SpriteManager* myManager;

    std::map<std::string, unsigned> textureNameToId;
	std::vector<Texture*> textures;

	std::vector<Animation> animations;

	bool ready;
    ResourceText* resourceText;

public:

	Sprite(SpriteManager* manager)
	:GraphicsComponent(),
	myManager(manager),
	ready(false){}

	void update();

	void draw(SpriteStatus* status)const;

    /** \brief return if can be rendered already
	 */
	bool isReady()const;

	/** \brief return if can be rendered already
	 */
	void becomeReady()const;

	~Sprite();

    /** \brief this will call to the corresponding GraphicsSystem function \
     * in charge of deleting this GraphicsComponent
     */
	void destroyDispatcher();

};

#endif
