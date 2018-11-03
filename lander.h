#ifndef LANDER
#define LANDER

#include "velocity.h"
#include "point.h"
#include "uiDraw.h"

class Lander
{
public:
   Lander();
   Point getPoint() const;
   Velocity getVelocity() const;
   bool isAlive();
   bool isLanded();
   int getFuel();
   bool canThrust();
   void setLanded(bool);
   void setAlive(bool);
   void setFuel(int);
   void applyGravity(float);
   void applyThrustLeft();
   void applyThrustRight();
   void applyThrustBottom();
   void advance();
   void draw(float r, float g, float b);
   void reset();
   float getTotalVelocity() const;
private:
   Point position;
   Velocity velocity;
   bool alive;
   bool landed;
   bool canthrust;
   int fuel;
   float yAcceleration;
   float xAcceleration;
   //bool canThrust;
};

#endif //LANDER
