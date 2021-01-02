#pragma once
#include "box2d/box2d.h"
#include "olcPixelGameEngine.h"
#include <assert.h>

namespace B2DOLC
{
    class GameObject
    {
    public:
        virtual bool OnGameCreation(olc::PixelGameEngine* pge) { return true; }
        virtual bool OnUserInput(float dt, olc::PixelGameEngine* pge, b2World* world) { return true; }

        b2Body* body;
        olc::Pixel color;
        bool destroy;
    };

    class Brick : public GameObject
    {
    public:
        Brick(b2World* world, const b2Vec2& pos, float length, float height)
        {
            assert(world);
            b2BodyDef brick_body_def;
            brick_body_def.position = pos;

            body = world->CreateBody(&brick_body_def);

            b2PolygonShape groundBox;
            groundBox.SetAsBox(length/2.0f, height/2.0f);

            body->CreateFixture(&groundBox, 0.0f);

            color = olc::RED;
            destroy = false;
        }
    };
}