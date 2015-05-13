#include "../math/vec2f.hpp"
#include "../dependencies/rapidxml/rapidxml.hpp"

#ifndef ENTITY
class Entity;
#endif

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef GRAPHICS_COMPONENT
#define GRAPHICS_COMPONENT

/** Abstract class representing any type of GraphicsComponent
 */
class GraphicsComponent
{

	friend class Entity;
	friend class GraphicsSystem;

protected:

	Entity* myEntity;
	GraphicsSystem* myGraphicsSystem;
	bool visible;
	int priority;	// the higher the more priority

	Vec2f position;
	Vec2f scale;

public:

	GraphicsComponent()
	:visible(true){}

	virtual void update(unsigned int delta) = 0;
	virtual void draw()const = 0;

	bool isVisible()const;
	void setVisible(bool visible);

    /** \brief return if this components is ready
     * To be ready means that is has been loaded to video \
     * memory
     */
	virtual bool isReady()const = 0;

	/** \brief return if this component is loaded
	 * To be loaded means that it has been loaded to main \
	 * memory
	 */
	virtual bool isLoaded()const = 0;

    /** \brief load to video memory
     * Once the resource of this component has been loaded \
     * into main memory it has to be loaded to video memory \
     * this functions loads it into video memory
     */
	virtual void becomeReady()const = 0;

	const Vec2f& getPosition()const;
	Vec2f& getPosition();
	Vec2f getScale()const;
	void setPosition(const Vec2f& position);
	void setScale(const Vec2f& scale);
	int getPriority()const;
	void setPriority(int priority);

    /** \brief Creates a graphics XML node
     * Returns an XML node representing the class itself
     * \param The XML document
     * \return The XML node
     */
	virtual rapidxml::xml_node<>* createXmlNode(rapidxml::xml_document<>* doc) = 0;

	virtual ~GraphicsComponent() {};

    /** \brief this will call to the corresponding GraphicsSystem function \
     * in charge of deleting this GraphicsComponent
     */
	virtual void destroyDispatcher() = 0;

};

#endif
