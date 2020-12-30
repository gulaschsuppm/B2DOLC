#pragma once
#include "box2d/box2d.h"
#include "olcPixelGameEngine.h"
#include <assert.h>

namespace B2DOLC
{
    struct GameObject
    {
        b2Body* body;
        olc::Pixel color;
    };

    struct Brick : public GameObject
    {
        Brick(b2World* world, const b2Vec2& pos, bool vertical)
        {
            assert(world);
            b2BodyDef brick_body_def;
            brick_body_def.position = pos;

            body = world->CreateBody(&brick_body_def);

            b2PolygonShape groundBox;
            if (vertical)
            {
                groundBox.SetAsBox(10.0f, 20.0f);
            }
            else
            {
                groundBox.SetAsBox(20.0f, 10.0f);
            }

            body->CreateFixture(&groundBox, 0.0f);

            color = olc::RED;
        }
    };

    struct Player : public GameObject
    {
        Player(b2World* world, const b2Vec2& pos)
        {
            assert(world);
            b2BodyDef player_body_def;
            player_body_def.position = pos;

            body = world->CreateBody(&player_body_def);

            b2PolygonShape groundBox;
            groundBox.SetAsBox(5.0f, 30.0f);

            body->CreateFixture(&groundBox, 0.0f);

            color = olc::WHITE;
        }
    };
}