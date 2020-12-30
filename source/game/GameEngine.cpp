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

    void GameEngine::AddObject(b2Body* body)
    {
        _physics_objects.push_back(body);
    }

    bool GameEngine::OnUserCreate()
    {
        _renderer = new Renderer();
        _renderer->SetPGE(this);
        _renderer->SetOrigin({float(ScreenWidth())/2.0f, float(ScreenHeight())/2.0f});
        _renderer->SetProjection({ 1,-1 });

        _gravity.Set(0.0f, -10.0f);
        _b2d_world = new b2World(_gravity);

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -10.0f);

        b2Body* groundBody = _b2d_world->CreateBody(&groundBodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.0f);

        groundBody->CreateFixture(&groundBox, 0.0f);

        AddObject(groundBody);

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 40.0f);
        b2Body* body = _b2d_world->CreateBody(&bodyDef);
        
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(4.0f, 4.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);

        AddObject(body);

        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

        if (GetMouse(0).bPressed)
        {
            b2Vec2 pos = _renderer->ToWorld({ float(GetMouseX()), float(GetMouseY()) });

            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position = pos;
            b2Body* body = _b2d_world->CreateBody(&bodyDef);

            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(4.0f, 4.0f);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.3f;

            body->CreateFixture(&fixtureDef);
        }
        if (GetMouse(1).bPressed)
        {
            b2Vec2 pos = _renderer->ToWorld({ float(GetMouseX()), float(GetMouseY()) });

            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position = pos;
            b2Body* body = _b2d_world->CreateBody(&bodyDef);

            b2CircleShape circle_shape;
            circle_shape.m_radius = 6.0f;

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &circle_shape;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.3f;

            body->CreateFixture(&fixtureDef);
        }

        _acc_time += fElapsedTime;
        if (_acc_time > TIME_STEP)
        {
            _acc_time -= TIME_STEP;
            _b2d_world->Step(TIME_STEP, 6, 2);
        }

        for (b2Body* b = _b2d_world->GetBodyList(); b; b = b->GetNext())
        {
            _renderer->Draw(b);
        }

        DrawString(20,20,"Hello World");

        return true;
    }
}
