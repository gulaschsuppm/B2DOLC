#include "GameEngine.h"
#include "box2d/box2d.h"
#include "Player.h"

namespace B2DOLC
{
    constexpr float TIME_STEP = 0.010f;

    void GameEngine::Run()
    {
        if (Construct(1200, 800, 1, 1))
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
        // where to draw the box 2 d world origin
        _renderer->SetOrigin({float(ScreenWidth())/2.0f, float(ScreenHeight())/2.0f});
        // OLC starts top left, box 2 d y-axis is upwards though
        _renderer->SetProjection({ 1.0,-1.0 });
        // How many pixels per meter?
        _renderer->SetZoom(8.0f);

        _gravity.Set(0.0f, -10.0f);
        _b2d_world = new b2World(_gravity);


        // Create Simple L-shaped world
        GameObject* obj;
        obj = new Brick(_b2d_world, { 0.0, 0.0 }, 20.0, 1.0f);
        AddObject(obj);
        obj = new Brick(_b2d_world, { 5.0, 10.0 }, 5.0f, 2.0f);
        AddObject(obj);

        obj = new Player(_b2d_world, { 0.0 , 10.0f });
        AddObject(obj);
        _player = (Player*) obj;

        for (auto object : _game_objects)
        {
            object->OnGameCreation(this);
        }

        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

        for (auto object : _game_objects)
        {
            object->OnUserInput(fElapsedTime, this, _b2d_world);
        }

        if (_player->destroy)
        {
            DrawString(100, 100, "You died!", olc::BLACK, 2);
        }
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

        // Print Player info:
        {
            std::stringstream ss;
            ss << "Player: " << (_player ? "Alive" : "Dead");
            ss << "\n";
            if (_player)
            {
                ss << "Pos: X: " << _player->body->GetWorldPoint({ 0,0 }).x;
                ss << " Y: " << _player->body->GetWorldPoint({ 0,0 }).y;
                ss << "\n";
                ss << "Flying Power: " << _player->GetFlyingPower();
                ss << "\n";
            }
            DrawString(20, 20, ss.str());
        }

        return true;
    }
}
