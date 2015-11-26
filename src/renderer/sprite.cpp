#include "sprite.hpp"
#include "graphics_system.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "../resource_manager/resource_texture.hpp"
#include "../resource_manager/resource_text.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "../dependencies/rapidxml/rapidxml.hpp"
#include "../util/exception.hpp"

using namespace std;
using namespace rapidxml;

Sprite::Sprite(SpriteManager* spriteManager, const std::string& name)
:GraphicsComponent(spriteManager->getGraphicsSystem())
{
    mySpriteManager = spriteManager;
    this->name = name;
}

SpriteManager* Sprite::getSpriteManager()
{
    return mySpriteManager;
}

bool Sprite::isReady()const
{
	return Status::EVERYTHING_LOADED == status;
}

void Sprite::update()
{
    if(Status::LOADING_XML == status)
    {
        if(Resource::Status::LOADED == resourceText->getStatus())
        {
            ResourceManager* resMan = ResourceManager::getSingleton();
            TextureManager* texMan =
            // parse XML
            xmlText = resourceText->getText();
            xml_document<> doc;
            doc.parse<0>((char*)xmlText.c_str());

            xml_node<>* root = doc.first_node("sprite");
            if(0 == root) throw Exception("expected <sprite> node");

            // parse textures
            xml_node<>* nodeTextures = root->first_node("textures");
            if(0 == nodeTextures) throw Exception("expected <textures> node");

            xml_node<>* nodeTex = nodeTextures->first_node("tex");
            if(0 == nodeTex) throw Exception("expected <tex> node");

            map<string, string> idToName;
            do
            {
                xml_attribute<>* attrId = nodeTex->first_attribute("id");
                string id = string(attrId->value());
                if(0 == attrId) throw Exception("expected \"id\" attribute in <tex>" );
                nodeTex = nodeTex->next_sibling("tex");
                string name = string(nodeTex->value());
                map<string, string>::iterator it = idToName.find(id);
                if(it != idToName.end()) throw Exception("there is already a \"tex\" with id="+id);
                idToName[id] = name;
            }
            while(0 != nodeTex);

            resourceTextures.reserve( idToName.size() );
            textures.reserve( idToName.size() );

            unsigned i = 0;
            for
            (
                map<string, string>::iterator it = idToName.begin();
                it != idToName.end();
                ++it
            )
            {
                string name = it->second;
                ResourceTexture* res = resMan->obtain<ResourceTexture>(name);
                resourceTextures.push_back(res);
                textureNameToId[name] = i;
                i++;
            }

        }

    }
    else if(Status::LOADING_TEXTURES == status)
    {
        bool allLoaded = true;
        for(unsigned i=0; i<resourceTextures.size(); i++)
        {
            if(Resource::Status::LOADED == resourceTextures[i]->getStatus())
            {
                allLoaded = false;
                break;
            }
        }

        if(allLoaded)
        {

            for(unsigned i=0; i<resourceTextures.size(); i++)
            {
                Texture texture;
            }

        }
    }
}

void Sprite::draw(const SpriteStatus& status)const
{

}

const std::string& Sprite::getName()const
{
    return name;
}

Sprite::~Sprite()
{


}

void Sprite::destroyDispatcher()
{

    myGraphicsSystem->destroySprite( this );

}
