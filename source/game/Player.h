#pragma once
#include "GameResources.h"

namespace B2DOLC
{
    class Player : public GameObject
    {
    public:
        Player(b2World* world, const b2Vec2& pos);
        virtual bool OnGameCreation(olc::PixelGameEngine* pge) override;
        virtual bool OnUserInput(float dt, olc::PixelGameEngine* pge, b2World* world) override;

        float GetFlyingPower() const { return _fly_power_left; }
    private:
        float _fly_power_left;
        bool _flying;
    };
}