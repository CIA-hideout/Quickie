// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
    spriteData.width = playerNS::WIDTH;           // size of PLAYER
    spriteData.height = playerNS::HEIGHT;
    spriteData.x = playerNS::X;                   // location on screen
    spriteData.y = playerNS::Y;
    spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = playerNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
    startFrame = playerNS::START_FRAME;     // first frame of PLAYER animation
    endFrame     = playerNS::END_FRAME;     // last frame of PLAYER animation
    currentFrame = startFrame;
    radius = playerNS::WIDTH/2.0;
    mass = playerNS::MASS;
    collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the PLAYER.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the PLAYER
//=============================================================================
void Player::draw()
{
    Image::draw();              // draw PLAYER
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.angle += frameTime * playerNS::ROTATION_RATE;  // rotate the PLAYER
    spriteData.x += frameTime * velocity.x;         // move PLAYER along X 
    spriteData.y += frameTime * velocity.y;         // move PLAYER along Y

    // Bounce off walls
    if (spriteData.x > GAME_WIDTH-playerNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH-playerNS::WIDTH;    // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT-playerNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-playerNS::HEIGHT;  // position at bottom screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }
}

//=============================================================================
// damage
//=============================================================================
void Player::damage(WEAPON weapon)
{

}

