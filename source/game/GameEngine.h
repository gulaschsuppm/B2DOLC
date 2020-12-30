#pragma once
#include "olcPixelGameEngine.h"
#include "box2d/box2d.h"
#include "Renderer.h"
#include "GameResources.h"

namespace B2DOLC
{
    class GameEngine : public olc::PixelGameEngine
    {
    public:
        GameEngine() : _acc_time(0.0f) { sAppName = "Game"; }
        ~GameEngine() { delete _b2d_world; delete _renderer; }

        void Run();

        void AddObject(GameObject* body);
        bool OnUserCreate() override;
        bool OnUserUpdate(float fElapsedTime) override;
    private:
        float _acc_time;
        b2Vec2 _gravity;
        b2World* _b2d_world;
        Renderer* _renderer;

        std::list<GameObject*> _game_objects;
    };
}
