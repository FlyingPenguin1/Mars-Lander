/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"

#include <vector>

static float landerRed = 0.0;
static float landerGreen = 1.0;
static float landerBlue = 0.0;
static int wins = 0;
static int losses = 0;

static std::vector <Point> path;
static std::vector <Point> stars;

Game :: Game(Point tl, Point br) : topLeft(tl), bottomRight(br),
   ground(Ground(topLeft, bottomRight))
{
   // Set up the initial conditions of the game
   lander.setFuel(FUEL);
   setStars(stars);
}

/******************************************
 * GAME :: JUST LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
   bool landed = false;

   Point platformCenter = ground.getPlatformPosition();
   int width = ground.getPlatformWidth();

   float xDiff = lander.getPoint().getX() - platformCenter.getX();
   float yDiff = lander.getPoint().getY() - platformCenter.getY();

   float margin = width / 2.0;

   if (fabs(xDiff) < margin)
   {
      // between edges

      if (yDiff < 4 && yDiff >= 0)
      {
         // right above it

         if (lander.getTotalVelocity() < MIN_SPEED)
         {
            // we're there!
            landed = true;
         }
      }
   }

   return landed;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   float totalBrightness;

   shiftStars(stars, 1);

   if (lander.isAlive() && !lander.isLanded())
   {
      // advance the lander
      lander.applyGravity(GRAVITY_AMOUNT);
      lander.advance();

      // check for crash
      if (!ground.isAboveGround(lander.getPoint()))
      {
         lander.setAlive(false);
      }

      // check for just landed
      if (justLanded())
      {
         lander.setLanded(true);
      }

      //if lander is in platform bounds it will crash
      if (ground.isInPlatform(lander.getPoint()))
      {
         lander.setAlive(false);
      }
   }

   //set path
   path.push_back(lander.getPoint());

   //set lander colors
   landerRed = (float)(FUEL - lander.getFuel()) / FUEL;
   landerGreen = (float)(lander.getFuel()) / FUEL;
   totalBrightness = landerGreen * landerRed;
   landerBlue = (float)(4*totalBrightness);
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   if (lander.isAlive() && !lander.isLanded())
   {

      if (ui.isDown())
      {
         lander.applyThrustBottom();
         if(landerRed < 0.8)
         {
            landerBlue = 0.4;
         }
      }

      if (ui.isLeft())
      {
         lander.applyThrustLeft();
         if(landerRed < 0.8)
         {
            landerBlue = 0.4;
         }
      }

      if (ui.isRight())
      {
         lander.applyThrustRight();
         if(landerRed < 0.8)
         {
            landerBlue = 0.4;
         }
      }
   }
   if (!lander.isAlive() || lander.isLanded())
   {
      if (ui.isUp())
      {
         reset();
      }
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   int total = wins + losses;

   int width1 = 95;
   int width2 = 85;

   std::string xv = "XV = ";
   std::string yv = "YV = ";
   std::string totalVelocity = "|V| = ";
   std::string winsStr = "WINS = ";
   std::string lossesStr = "LOSSES = ";
   std::string winRatioStr = "WINS = ";
   std::string totalPlayedStr = "TOTAL = ";
   std::string temp;

   temp = std::to_string(lander.getVelocity().getDx());
   temp.resize(5);
   xv.append(temp);

   temp = std::to_string(lander.getVelocity().getDy());
   temp.resize(5);
   yv.append(temp);

   temp = std::to_string(lander.getTotalVelocity());
   temp.resize(5);
   totalVelocity.append(temp);

   //WINS
   temp = std::to_string(wins);
   winsStr.append(temp);

   //LOSSES
   temp = std::to_string(losses);
   lossesStr.append(temp);

   //TOTAL
   temp = std::to_string(total);
   totalPlayedStr.append(temp);

   //WIN RATIO
   if(total > 0)
   {
      temp = std::to_string(100.0*((float)wins/total));
   }
   else
   {
      temp = "0";
   }
   temp.resize(5);
   winRatioStr.append(temp);
   winRatioStr.append("%");

   drawRect(Point(bottomRight.getX()-25, topLeft.getY()-25), 50, 130, 0.5);
   drawText(Point(bottomRight.getX(), topLeft.getY()-10), xv.c_str(), width1);
   drawText(Point(bottomRight.getX(), topLeft.getY()-25), yv.c_str(), width1);
   drawText(Point(bottomRight.getX(),
      topLeft.getY()-40), totalVelocity.c_str(), width1);

   drawText(Point(bottomRight.getX(),
      topLeft.getY()-55), winsStr.c_str(), width1);
   drawText(Point(bottomRight.getX(),
      topLeft.getY()-70), lossesStr.c_str(), width1);
   drawText(Point(bottomRight.getX(),
      topLeft.getY()-85), totalPlayedStr.c_str(), width1);

   drawText(Point(-20, topLeft.getY()-25), winRatioStr.c_str(), 10);

   //draw stars
   for (int i = 0; i < stars.size(); i++)
   {
      drawDot(stars[i], 1.0, 1.0, 1.0);
   }

   if (!lander.isLanded() || lander.isAlive())
   {
      for (int i = 1; i < path.size(); i++)
      {
         drawLine(path[i-1], path[i], 0.0, ((float)i/path.size()), 0.0);
      }
   }

   lander.draw(landerRed, landerGreen, landerBlue);

   if (lander.isLanded())
   {
      drawRect(Point(0, 2), width1+30, 30, 0);
      drawText(Point(), "SUCCESS! (press up to play again)", width1);
      for(int i = 0; i < 1700; i ++)
      {
         drawDot(Point(random(-800, 800), random(-500, 500)), 0.0, 1.0, 0.0);
      }
      if(!lander.getAddedPoint())
      {
         wins++;
         lander.setAddedPointTrue();

      }
   }

   if (!lander.isAlive())
   {
      drawRect(Point(0, 2), width2+30, 30, 0);
      drawText(Point(), "FAIL! (press up to play again)", width2);
      drawLanderFlames(lander.getPoint(), true, true, true);
      drawLanderFlames(Point(lander.getPoint().getX()+5,
      lander.getPoint().getY()), true, true, true);
      drawLanderFlames(Point(lander.getPoint().getX()-5,
      lander.getPoint().getY()), true, true, true);
      for(int i = 0; i < 1700; i ++)
      {
         drawDot(Point(random(-800, 800), random(-500, 500)), 1.0, 0.0, 0.0);
      }
      if(!lander.getAddedPoint())
      {
         losses++;
         lander.setAddedPointTrue();
      }
   }

   if (lander.canThrust())
   {
      drawLanderFlames(lander.getPoint(), ui.isDown(), ui.isLeft(), ui.isRight());
   }

   Point fuelLocation;
   fuelLocation.setX(topLeft.getX() + 5);
   fuelLocation.setY(topLeft.getY() - 5);

   drawNumber(fuelLocation, lander.getFuel());

   // draw ground
   ground.draw(1.0, 0);
   ground.draw(0.85, 30);
   ground.draw(0.7, 60);
   ground.draw(0.44, 90);
}

/*********************************************
* Function: reset
* Description: reset the game to play again
*********************************************/
void Game :: reset()
{
   path.clear();
   lander.reset();
   lander.setFuel(FUEL);
   ground.reset();
}
