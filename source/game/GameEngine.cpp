#include "GameEngine.h"
#include "box2d/box2d.h"

namespace B2DOLC
{
    constexpr float TIME_STEP = 0.010f;

    void GameEngine::Run()
    {
        if (Construct(256, 240, 4, 4))
        {
            Start();
        }
    }

    void GameEngine::AddObject(GameObject* body)
    {
        _game_objects.push_back(body);
    }

    bool GameEngine::OnUserCreate()
    {
        _renderer = new Renderer();
        _renderer->SetPGE(this);
        _renderer->SetOrigin({float(ScreenWidth())/2.0f, float(ScreenHeight())/2.0f});
        _renderer->SetProjection({ 1,-1 });

        _gravity.Set(0.0f, -10.0f);
        _b2d_world = new b2World(_gravity);


        // Create Simple L-shaped world
        GameObject* obj;
        obj = new Brick(_b2d_world, { -60.0,-60.0f }, false);
        AddObject(obj);
        obj = new Brick(_b2d_world, { -20.0,-60.0f }, false);
        AddObject(obj);
        obj = new Brick(_b2d_world, { 20.0,-60.0f }, false);
        AddObject(obj);
        obj = new Brick(_b2d_world, { 60.0,-60.0f }, false);
        AddObject(obj);
        obj = new Brick(_b2d_world, { 70.0,-30.0f }, true);
        AddObject(obj);
        obj = new Brick(_b2d_world, { 70.0,10.0f }, true);
        AddObject(obj);
        obj = new Brick(_b2d_world, { 70.0,50.0f }, true);
        AddObject(obj);

        obj = new Player(_b2d_world, { -40.0,-20.0f });
        AddObject(obj);

        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

        //if (GetMouse(0).bPressed)
        //{
        //    b2Vec2 pos = _renderer->ToWorld({ float(GetMouseX()), float(GetMouseY()) });

        //    b2BodyDef bodyDef;
        //    bodyDef.type = b2_dynamicBody;
        //    bodyDef.position = pos;
        //    b2Body* body = _b2d_world->CreateBody(&bodyDef);

        //    b2PolygonShape dynamicBox;
        //    dynamicBox.SetAsBox(4.0f, 4.0f);

        //    b2FixtureDef fixtureDef;
        //    fixtureDef.shape = &dynamicBox;
        //    fixtureDef.density = 1.0f;
        //    fixtureDef.friction = 0.3f;

        //    body->CreateFixture(&fixtureDef);
        //}
        //if (GetMouse(1).bPressed)
        //{
        //    b2Vec2 pos = _renderer->ToWorld({ float(GetMouseX()), float(GetMouseY()) });

        //    b2BodyDef bodyDef;
        //    bodyDef.type = b2_dynamicBody;
        //    bodyDef.position = pos;
        //    b2Body* body = _b2d_world->CreateBody(&bodyDef);

        //    b2CircleShape circle_shape;
        //    circle_shape.m_radius = 6.0f;

        //    b2FixtureDef fixtureDef;
        //    fixtureDef.shape = &circle_shape;
        //    fixtureDef.density = 1.0f;
        //    fixtureDef.friction = 0.3f;

        //    body->CreateFixture(&fixtureDef);
        //}

        _acc_time += fElapsedTime;
        if (_acc_time > TIME_STEP)
        {
            _acc_time -= TIME_STEP;
            _b2d_world->Step(TIME_STEP, 6, 2);
        }

        for (auto object : _game_objects)
        {
            _renderer->Draw(object);
        }

        DrawString(20,20,"Hello World");

        return true;
    }
}
