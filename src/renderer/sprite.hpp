#ifndef SPRITE
#define SPRITE

#include "graphics_component.hpp"
#include "low_level_renderer_2d.hpp"
#include "../math/vec2f.hpp"
#include <map>
#include <vector>
#include "animation.hpp"

class SpriteFactory;
class ResourceTexture;
class GraphicsSystem;
class Texture;
class ResourceText;

/** \brief Represents a static sprite
 * This sprite has no animations
 */
class Sprite : public GraphicsComponent
{

    enum class Status
    {
        START,
        LOADING_XML,
        LOADING_TEXTURES,
        EVERYTHING_LOADED
    };

	friend class Entity;
	friend class GraphicsSystem;
	friend class SpriteManager;

    std::map<std::string, unsigned> textureNameToId;
	std::vector<Texture*> textures;

	std::vector<Animation> animations;

    Status status;
	ResourceText* resourceText;
	std::string xmlText;
	std::vector<ResourceTexture*> resourceTextures;

public:

	Sprite()
	:GraphicsComponent()
	{}

	void update();
	void draw()const;

    /** \brief return if this components is ready
     */
	bool isReady()const;

	~Sprite();

    /** \brief this will call to the corresponding GraphicsSystem function \
     * in charge of deleting this GraphicsComponent
     */
	void destroyDispatcher();

};

#endif
