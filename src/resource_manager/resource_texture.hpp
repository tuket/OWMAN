#include "resource.hpp"
#include "../renderer/low_level_renderer_2d.hpp"

#ifndef RESOURCE_TEXTURE_FACTORY
class ResourceTextureFactory;
#endif

#ifndef RESOURCE_MANAGER
class ResourceManager;
#endif


#ifndef RESOURCE_TEXTURE
#define RESOURCE_TEXTURE

/** \brief Represents a resource texture
 * Since OpenGL does not allow to make any call
 * from any other thread other than the main thread,
 * the resource manager can not load anything to video
 * memory. So for this resource, to be LOADED means to
 * be loaded in main memory and to be READY means to be
 * loaded in video memory
 */
class ResourceTexture : public Resource
{

	friend class ResourceTextureFactory;
	friend class ResourceManager;

	unsigned char* imageData;
	int width, height;

protected:

	void load();
	void free();

public:

	ResourceTexture(const std::string& name);

	const unsigned char* getTextureData()const;
	int getWidth()const;
	int getHeight()const;

	void destroyDispatcher();

	~ResourceTexture(){}

};

#endif
