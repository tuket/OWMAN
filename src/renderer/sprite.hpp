#ifndef SPRITE
#define SPRITE

#include "graphics_component.hpp"
#include "low_level_renderer_2d.hpp"
#include "../math/vec2f.hpp"
#include <map>
#include <vector>
#include "animation.hpp"

class SpriteManager;
class ResourceTexture;
class GraphicsSystem;
class Texture;
class ResourceText;
class SpriteStatus;

/** \brief Represents a static sprite
 * This sprite has no animations
 */
class Sprite
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
	friend class SpriteStatus;

	SpriteManager* mySpriteManager;

	std::string name;
	std::string fileName;

    std::map<std::string, unsigned> textureNameToIndex;
	std::vector<Texture*> textures;

    std::map<std::string, unsigned> animNameToIndex;
	std::vector<Animation> animations;

    Status status;
	ResourceText* resourceText;
	std::string xmlText;
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root;

public:

	Sprite(SpriteManager* spriteManager, const std::string& name);

	SpriteManager* getSpriteManager();
	GraphicsSystem* getGraphicsSystem();

	void update();

    /** \brief return if this component is ready
     */
	bool isReady()const;

	const std::string& getName()const;

	~Sprite();

private:

    /**
    * \brief release all the resources of this sprite
    * This function is only to be called by SpriteManager::releaseSprite
    */
    void release();

};

#endif
