#include <Box2D/Box2D.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{

    sf::VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
	videoMode.bitsPerPixel = 32;
	sf::RenderWindow window(videoMode, "Box2D");
	window.setFramerateLimit(60);


    b2Vec2 gravity(0.0f, 0.0f); // top down game
	b2World* world = new b2World(gravity);	// And create our world

    // main character
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.active = true;
    bodyDef.position.Set(100, 200);
    bodyDef.linearDamping = 1.5;
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(80/2, 80/2);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 100;
    fixtureDef.shape = &shape;

    body->CreateFixture(&fixtureDef);

    // secondary character
    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.fixedRotation = true;
    bodyDef2.active = true;
    bodyDef2.position.Set(300, 300);
    bodyDef2.linearDamping = 1.5;
    b2Body* body2 = world->CreateBody(&bodyDef2);

    b2PolygonShape shape2;
    shape2.SetAsBox(100/2, 100/2);

    b2FixtureDef fixtureDef2;
    fixtureDef2.density = 100;
    fixtureDef2.shape = &shape2;

    body2->CreateFixture(&fixtureDef2);

    bool run = true;
    while(run)
    {

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
        {
            body->SetLinearVelocity(b2Vec2(-50, 0));
        }
        else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
        {
            body->SetLinearVelocity(b2Vec2(+50, 0));
        }
        else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
        {
            body->SetLinearVelocity(b2Vec2(0, +50));
        }
        else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        {
            body->SetLinearVelocity(b2Vec2(0, -50));
        }

        else
        {
            body->SetLinearVelocity(b2Vec2(0, 0));
        }

        float timeStep = 1.0f/60.0f;
        world->Step(timeStep, 8, 3);

        window.clear(sf::Color(0,0,0,255));

        sf::RectangleShape rs1(sf::Vector2f(80, 80));
        rs1.setPosition( body->GetPosition().x-40, body->GetPosition().y-40 );
        window.draw(rs1);

        sf::RectangleShape rs2(sf::Vector2f(100, 100));
        rs2.setPosition( body2->GetPosition().x-50, body2->GetPosition().y-50 );
        rs2.setFillColor( sf::Color(0, 255, 0) );
        window.draw(rs2);

        window.display();


    }



}
