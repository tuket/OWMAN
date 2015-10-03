#ifndef SPRITE
#define SPRITE

#include "graphics_component.hpp"
#include "low_level_renderer_2d.hpp"
#include "../math/vec2f.hpp"
#include <map>
#include <vector>
#include "animation.hpp"

#ifndef SPRITE_FACTORY
class SpriteFactory;
#endif

#ifndef RESOURCE_TEXTURE
class ResourceTexture;
#endif

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

/** \brief Represents a static sprite
 * This sprite has no animations
 */
class Sprite : public GraphicsComponent
{

	friend class Entity;
	friend class GraphicsSystem;

	friend class SpriteFactory;

	SpriteFactory* myFactory;

    std::map<std::string, unsigned> textureNameToId;
	std::vector<ResourceTexture*> resourceTextures;

	std::vector<Animation> animations;

public:

	Sprite(SpriteFactory* factory)
	:GraphicsComponent(),
	myFactory(factory){}

	void update(unsigned int delta){}
	void draw()const;

    /** \brief return if this components is ready
     * To be ready means that is has been loaded to video \
     * memory
     */
	bool isReady()const;

	/** \brief return if this component is loaded
	 * To be loaded means that it has been loaded to main \
	 * memory
	 */
	bool isLoaded()const;

    /** \brief load to video memory
     * Once the resource of this component has been loaded \
     * into main memory it has to be loaded to video memory \
     * this functions loads it into video memory
     */
	void becomeReady()const;

    /** \brief Creates a graphics XML node
     * Returns an XML node representing the class itself
     * \param The XML document
     * \return The XML node
     */
	rapidxml::xml_node<>* createXmlNode(rapidxml::xml_document<>* doc);

	~Sprite();

    /** \brief this will call to the corresponding GraphicsSystem function \
     * in charge of deleting this GraphicsComponent
     */
	void destroyDispatcher();

};

#endif
