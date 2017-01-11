// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "Quickie.h"

//=============================================================================
// Constructor
//=============================================================================
Quickie::Quickie()
{}

//=============================================================================
// Destructor
//=============================================================================
Quickie::~Quickie()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Quickie::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // player 1
	if (!player_1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	player_1.setFrames(playerNS::START_FRAME, playerNS::END_FRAME);
    player_1.setCurrentFrame(playerNS::START_FRAME);
    player_1.setX(GAME_WIDTH/4);
    player_1.setY(GAME_HEIGHT/4);
	player_1.setVelocity(VECTOR2(playerNS::SPEED, -playerNS::SPEED)); // VECTOR2(X, Y)
    
	// player 2
	if (!player_2.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
	player_2.setFrames(playerNS::START_FRAME, playerNS::END_FRAME);
	player_2.setCurrentFrame(playerNS::START_FRAME);
	player_2.setX(GAME_WIDTH - GAME_WIDTH / 4);
	player_2.setY(GAME_HEIGHT / 4);
	player_2.setVelocity(VECTOR2(-playerNS::SPEED, -playerNS::SPEED)); // VECTOR2(X, Y)

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Quickie::update()
{
    player_1.update(frameTime);
    player_2.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Quickie::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Quickie::collisions()
{
    
}

//=============================================================================
// Render game items
//=============================================================================
void Quickie::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    player_1.draw();                           // add the spaceship to the scene
    player_2.draw();                           // add the spaceship to the scene

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Quickie::releaseAll()
{
    gameTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Quickie::resetAll()
{
    gameTextures.onResetDevice();
    Game::resetAll();
    return;
}
