/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#include "Ball.hpp"
#include <iostream>


Ball::Ball() { }

Ball::~Ball() {
    delete bud;
}

void Ball::launch(std::string direction) {
    if(direction == "left") {
        ballBody->ApplyLinearImpulse(b2Vec2(-10, -15), ballBodyDef.position, true);
        paddleHasBall = false;
    }
    if(direction == "right") {
        ballBody->ApplyLinearImpulse(b2Vec2(10, -15), ballBodyDef.position, true);
        paddleHasBall = false;
    }
}

void Ball::setBodyAndSprite(b2World* world) {
    // Define a body.
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(700 / PTM_RATIO, 700 / PTM_RATIO);

    // Use the body definition to create the actual body instance.
    ballBody = world->CreateBody(&ballBodyDef);
    ballBody->SetUserData(static_cast<Entity*>(this));

    // Define shape.
    b2CircleShape ballShape;
    ballShape.m_radius = 12.f / PTM_RATIO;

    b2PolygonShape ballShape2;
    ballShape2.SetAsBox(HALF_HEIGHT / PTM_RATIO, HALF_HEIGHT / PTM_RATIO);


    // Define fixture.
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 1.f;
    ballFixtureDef.friction = 0.f;
    ballFixtureDef.restitution = 1.f;

    // Create user data.
    bUserData* bud = new bUserData;
    bud->entityType = BALL;
    ballFixtureDef.userData = bud;

    // Create fixture.
    ballBody->CreateFixture(&ballFixtureDef);

    if(texture.loadFromFile("data/images/ball_24x24.png")) {
        sprite.setTexture(texture);
    }
    sprite.setOrigin(sf::Vector2f(HALF_WIDTH, HALF_HEIGHT));
}

void Ball::update(Paddle paddle, sf::Time deltaTime) {
    if(paddleHasBall) {
        ballBody->SetLinearVelocity(b2Vec2(0, 0));
        ballBody->SetTransform(b2Vec2(paddle.paddleBody->GetPosition().x + 1 / PTM_RATIO, paddle.paddleBody->GetPosition().y - 24 / PTM_RATIO), 0);
    }
    else {
        int maxSpeed = 25;
        b2Vec2 velocity = ballBody->GetLinearVelocity();
        float32 speed = velocity.Length();

        std::cout << "Ball speed: " << speed << std::endl;
        


        // If the ball is too fast, apply linear damping to gradually slow down the ball.
        if(speed > maxSpeed) {
            ballBody->SetLinearDamping(0.5);
        }
        // If the ball is too slow, apply linear impulse to gradually fasten the ball.
        else if(speed < maxSpeed - 1) {
            ballBody->SetLinearDamping(0.0);
            // Apply horizontal speed
            if(velocity.x > 0) {
                ballBody->ApplyLinearImpulse(b2Vec2(0.25f, 0), ballBodyDef.position, true);
            }
            else {
                ballBody->ApplyLinearImpulse(b2Vec2(-0.25f, 0), ballBodyDef.position, true);
            }
            // Apply vertical speed
            if(velocity.y > 0) {
                ballBody->ApplyLinearImpulse(b2Vec2(0, 0.25f), ballBodyDef.position, true);
            }
            else {
                ballBody->ApplyLinearImpulse(b2Vec2(0, -0.25f), ballBodyDef.position, true);
            }
        }
    }
}

void Ball::draw(sf::RenderWindow& window) {
    sprite.setPosition(sf::Vector2f(ballBody->GetPosition().x * PTM_RATIO, ballBody->GetPosition().y * PTM_RATIO));
    window.draw(sprite);
}