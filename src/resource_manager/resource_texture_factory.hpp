#ifndef RESOURCE_TEXTURE_FACTORY
#define RESOURCE_TEXTURE_FACTORY

#include "resource_factory.hpp"
#include "resource_texture.hpp"

#ifndef LOW_LEVEL_RENDERER_2D
class LowLevelRenderer2D;
#endif

class ResourceTextureFactory : public ResourceFactory
{

	LowLevelRenderer2D* renderer;

public:

	ResourceTexture* createResource(std::string name);
	void destroyResource(ResourceTexture* resource);
	void destroyResource(Resource* resource);

};

#endif
