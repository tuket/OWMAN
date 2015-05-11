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

class ResourceTexture : public Resource
{

	friend class ResourceTextureFactory;
	friend class ResourceManager;

	unsigned char* imageData;
	LowLevelRenderer2D::Texture texture;
	int width, height;

	ResourceTextureFactory* myFactory;

protected:

	void load();
	void free();

public:

	ResourceTexture();

	LowLevelRenderer2D::Texture* getTexture();

	void loadToGraphicsCard();

	void destroyDispatcher();

	~ResourceTexture(){}

};

#endif
