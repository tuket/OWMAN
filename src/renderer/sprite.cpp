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
#include "sprite_manager.hpp"

using namespace std;
using namespace rapidxml;

Sprite::Sprite(SpriteManager* spriteManager, const std::string& name)
{
    mySpriteManager = spriteManager;
    this->name = name;
    status = Status::START;
}

SpriteManager* Sprite::getSpriteManager()
{
    return mySpriteManager;
}

GraphicsSystem* Sprite::getGraphicsSystem()
{
    return getSpriteManager()->getGraphicsSystem();
}

bool Sprite::isReady()const
{
	return Status::EVERYTHING_LOADED == status;
}

void Sprite::update()
{
    if(Status::START == status)
    {
         ResourceManager* resMan = ResourceManager::getSingleton();
         string fileName = name;
         resourceText = resMan->obtain<ResourceText>(fileName);
         status = Status::LOADING_XML;
    }
    else if(Status::LOADING_XML == status)
    {
        if(Resource::Status::LOADED == resourceText->getStatus())
        {
            ResourceManager* resMan = ResourceManager::getSingleton();
            GraphicsSystem* gs = mySpriteManager->getGraphicsSystem();
            TextureManager* texMan = gs->getTextureManager();
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
                string name = string(nodeTex->value());
                map<string, string>::iterator it = idToName.find(id);
                if(it != idToName.end()) throw Exception("there is already a \"tex\" with id="+id);
                idToName[id] = name;
                nodeTex = nodeTex->next_sibling("tex");
            }
            while(0 != nodeTex);

            textures.reserve( idToName.size() );

            unsigned i = 0;
            for
            (
                map<string, string>::iterator it = idToName.begin();
                it != idToName.end();
                ++it
            )
            {
                string name = TextureManager::texturesPath + it->second;
                Texture* res = texMan->getTexture(name);
                textures.push_back(res);
                textureNameToIndex[name] = i;
                i++;
            }

            xml_node<>* nodeAnimations = root->first_node("animations");
            if(0 == nodeAnimations) throw Exception("expected animations node");

            xml_node<>* nodeAnim = nodeAnimations->first_node("anim");
            if(0 == nodeAnim) throw Exception("you must provide at least one anim node");

            do
            {

                xml_attribute<>* attribAnimName = nodeAnim->first_attribute("id");
                if(0 == attribAnimName) throw Exception("no id provided for anim");
                string animName = string(attribAnimName->value());

                xml_node<>* nodeFrame = nodeAnim->first_node("frame");
                if(0 == nodeFrame)
                {
                    throw Exception("you must provide at least one frame per anim");
                }

                Animation anim;
                anim.name = animName;

                do
                {

                    xml_node<>* nodeTex = nodeFrame->first_node("tex");
                    if(0 == nodeTex) throw Exception("no tex provided for frame");
                    string texName = nodeTex->value();

                    xml_node<>* nodeRect = nodeFrame->first_node("rect");
                    if(0 == nodeRect) throw Exception("no rect provided for frame");
                    AARect rect;
                        xml_node<>* nodeX = nodeRect->first_node("x");
                        if(0 == nodeX) throw Exception("no x provided for rect");
                        rect.x = atof(nodeX->value()) / 1296;

                        xml_node<>* nodeY = nodeRect->first_node("y");
                        if(0 == nodeY) throw Exception("no y provided for rect");
                        rect.y = atof(nodeY->value()) / 2160;

                        xml_node<>* nodeW = nodeRect->first_node("w");
                        if(0 == nodeW) throw Exception("no w provided for rect");
                        rect.w = atof(nodeW->value()) / 1296;

                        xml_node<>* nodeH = nodeRect->first_node("h");
                        if(0 == nodeH) throw Exception("no h provided for rect");
                        rect.h = atof(nodeH->value()) / 2160;


                    xml_node<>* nodeTime = nodeFrame->first_node("time");
                    if(0 == nodeTime) throw Exception("no time provide for this frame");
                    float time = atof(nodeTime->value());

                    AnimationFrame frame;
                    frame.textureIndex = textureNameToIndex[texName];
                    frame.vbo = LowLevelRenderer2D::SpriteVbo(rect);
                    frame.frameDuration = time;
                    anim.frames.push_back(frame);

                    nodeFrame = nodeFrame->next_sibling("frame");

                }
                while(0 != nodeFrame);

                animations.push_back(anim);
                nodeAnim = nodeAnim->next_sibling("anim");

            }
            while(0 != nodeAnim);

            status = Status::LOADING_TEXTURES;
            resMan->release(resourceText);

        }

    }
    else if(Status::LOADING_TEXTURES == status)
    {
        bool allLoaded = true;
        for(unsigned i=0; i<textures.size(); i++)
        {
            if(textures[i]->isReady() == false)
            {
                allLoaded = false;
                break;
            }
        }

        if(allLoaded)
        {
            status = Status::EVERYTHING_LOADED;
        }
    }
}

const std::string& Sprite::getName()const
{
    return name;
}

Sprite::~Sprite()
{

}

void Sprite::release()
{
    TextureManager* texMan = getGraphicsSystem()->getTextureManager();
    for(Texture* tex : textures)
    {
        texMan->releaseTexture(tex);
    }
}
