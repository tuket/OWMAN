#include "sprite_factory.hpp"
#include "../resource_manager/resource_manager.hpp"


SpriteFactory::SpriteFactory(GraphicsSystem* graphicsSystem)
{
	this->myGraphicsSystem = graphicsSystem;
}

void SpriteFactory::destroyGraphicsComponent(GraphicsComponent* graphicsComponent)
{

	delete graphicsComponent;

}

Sprite* SpriteFactory::createSprite(std::string fileName, const Vec2f& scale)
{

	Sprite* sprite = new Sprite(this);
	ResourceManager* resourceManager = ResourceManager::getSingleton();
	sprite->resourceTexture = resourceManager->obtainTexture(fileName);

	sprite->scale = scale;
	sprite->position = Vec2f(0, 0);

	return sprite;

}

void SpriteFactory::destroySprite(Sprite* sprite)
{

	ResourceManager* resMan = ResourceManager::getSingleton();
	delete sprite;

}

GraphicsSystem* SpriteFactory::getGraphicsSystem()
{
	return myGraphicsSystem;
}
