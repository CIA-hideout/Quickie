// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _QUICKIE_H             // Prevent multiple definitions if this 
#define _QUICKIE_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "player.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Quickie : public Game
{
private:
    // game items
    TextureManager gameTextures;    // game texture
    Player    player_1, player_2;           // spaceships

public:
    // Constructor
    Quickie();

    // Destructor
    virtual ~Quickie();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
