#include "Player.h"

namespace B2DOLC
{
    constexpr float MAX_FLYING_POWER_S = 5.0f;
    constexpr float MAX_FLYING_SPEED_MPS = 10.0f;

    Player::Player(b2World* world, const b2Vec2& pos) :
        _flying(false), _fly_power_left(MAX_FLYING_POWER_S)
    {
        assert(world);
        b2BodyDef player_body_def;
        player_body_def.position = pos;
        player_body_def.type = b2_dynamicBody;
        player_body_def.fixedRotation = true;
        body = world->CreateBody(&player_body_def);

        b2PolygonShape playerBox;
        playerBox.SetAsBox(1.0f, 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &playerBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
        
        color = olc::WHITE;
        destroy = false;
    }

    bool Player::OnGameCreation(olc::PixelGameEngine* _pge)
    {
        return true;
    }

    bool Player::OnUserInput(float dt, olc::PixelGameEngine* pge, b2World* world)
    {
        // SPACE is jump
        if (pge->GetKey(olc::SPACE).bHeld)
        {
            if (_fly_power_left > 0)
            {
                _fly_power_left -= dt;
                if (body->GetLinearVelocity().y < MAX_FLYING_SPEED_MPS)
                {
                    float impulse = body->GetMass();
                    body->ApplyLinearImpulseToCenter(b2Vec2(0, impulse), true);
                }
            }
        }
        else
        {
            if (_fly_power_left < MAX_FLYING_POWER_S)
            {
                _fly_power_left += dt;
            }
        }

        // A or Left is going left
        if (pge->GetKey(olc::A).bHeld || pge->GetKey(olc::LEFT).bHeld)
        {
            if (body->GetLinearVelocity().x > -10.0)
            {
                float impulse = body->GetMass();
                body->ApplyLinearImpulseToCenter(b2Vec2(-impulse, 0), true);
            }
        }

        // A or Left is going left
        if (pge->GetKey(olc::D).bHeld || pge->GetKey(olc::RIGHT).bHeld)
        {
            if (body->GetLinearVelocity().x < 10.0)
            {
                float impulse = body->GetMass();
                body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
            }
        }

        auto pos = body->GetPosition();
        if (pos.y < -100.0f)
        {
            destroy = true;
        }

        return true;
    }
}
