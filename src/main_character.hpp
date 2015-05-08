#include "entity.hpp"
#include "math/vec2i.hpp"

#ifndef ENTITY_FACTORY
class EntityFactory;
#endif

#ifndef MAIN_CHARACTER
#define MAIN_CHARACTER

class MainCharacter : public Entity
{

    friend class EntityFactory;

private:

    Vec2i cell;

    MainCharacter();

public:

    const Vec2i& getCell()const;
    Vec2i& getCell();
    void setCell( const Vec2i& cell );

};

#endif
