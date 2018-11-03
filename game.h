/*************************************************************
 * File: game.h
 * Author: Br. Burton
 *
 * Description: Contains the definition of the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#ifndef GAME_H
#define GAME_H

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"
#include <vector>

#define FUEL        500    // initial fuel for the game
#define MIN_SPEED   3.0    // minimal landing speed

#define GRAVITY_AMOUNT 0.1

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);

   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);

   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();

   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);

   /*********************************************
    * Function: reset
    * Description: reset the game to play again
    *********************************************/
   void reset();

private:
   /*********************************************
    * Function: justLanded
    * Description: Returns true if the lander has
    *  just successfully landed.
    *********************************************/
   bool justLanded() const;

   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;

   Ground ground;
   Lander lander;

};

#endif /* GAME_H */
