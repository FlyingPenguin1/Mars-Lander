
#include "lander.h"
#include <cmath>

/********************************************
 * Lander - settup
 ********************************************/
Lander::Lander()
{
   position = Point();
   velocity = Velocity();
   alive = true;
   landed = false;
   int fuel = 100;
   canthrust = true;
}

/********************************************
 * Lander - custom settup
 ********************************************/
Point Lander::getPoint() const
{
   return position;
}

/********************************************
 * Velocity
 ********************************************/
Velocity Lander::getVelocity() const
{
   return velocity;
}

/********************************************
 * is alive
 ********************************************/
bool Lander::isAlive()
{
   return alive;
}

/********************************************
 * is landed
 ********************************************/
bool Lander::isLanded()
{
   return landed;
}

/********************************************
 * get fuel
 ********************************************/
int Lander::getFuel()
{
   return fuel;
}

/********************************************
 * can thrust
 ********************************************/
bool Lander::canThrust()
{
   return(canthrust);
}

/********************************************
 * set landed
 ********************************************/
void Lander::setLanded(bool l)
{
   landed = l;
}

/********************************************
 * set alive
 ********************************************/
void Lander::setAlive(bool a)
{
   alive = a;
}

/********************************************
 * set fuel
 ********************************************/
void Lander::setFuel(int f)
{
   fuel = f;
}

/********************************************
 * apply gravity
 ********************************************/
void Lander::applyGravity(float y)
{
   yAcceleration -= y;
}

/********************************************
 * apply thrust left
 ********************************************/
void Lander::applyThrustLeft()
{
   if(canthrust)
   {
      xAcceleration = 0.111;
      if (fuel > 0)
      {
         fuel -= 1;
         if(fuel < 0)
         {
            fuel = 0;
         }
      }
   }
}

/********************************************
 * apply thrust right
 ********************************************/
void Lander::applyThrustRight()
{
   if(canthrust)
   {
      xAcceleration = -0.111;
      if (fuel > 0)
      {
         fuel -= 1;
         if(fuel < 0)
         {
            fuel = 0;
         }
      }
   }
}

/********************************************
 * apply thrust bottom
 ********************************************/
void Lander::applyThrustBottom()
{
   if(canthrust)
   {
      yAcceleration = 0.311;
      if (fuel > 0)
      {
         fuel -= 3;
         if(fuel < 0)
         {
            fuel = 0;
         }
      }
   }
}

/********************************************
 * advance - update all the stuff
 ********************************************/
void Lander::advance()
{
   velocity.addDx(xAcceleration);
   position.addX(velocity.getDx());
   velocity.addDy(yAcceleration);
   position.addY(velocity.getDy());
   xAcceleration = 0;
   yAcceleration = 0;
   if(fuel <= 0)
   {
      canthrust = false;
   }
}

/********************************************
 * draw the lander
 ********************************************/
void Lander::draw(float r, float g, float b)
{
   drawLander(position, r, g, b);
}

/********************************************
 * reset the lander
 ********************************************/
void Lander :: reset()
{
   position = Point();
   velocity = Velocity();
   alive = true;
   landed = false;
   int fuel = 100;
   canthrust = true;
   setAddedPointFalse();
}

/********************************************
 * get the total velocity
 ********************************************/
float Lander :: getTotalVelocity() const
{
   return (sqrt(pow(getVelocity().getDx(), 2) +
      pow(getVelocity().getDy(), 2)));
}

void Lander :: setAddedPointTrue()
{
   addedPoint = true;
}

void Lander :: setAddedPointFalse()
{
   addedPoint = false;
}

bool Lander :: getAddedPoint()
{
   return(addedPoint);
}
