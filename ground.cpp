/***********************************************************************
 * Implementation File:
 *    GROUND : A class representing the lunar landscape
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything you needed to know about the ground but were afraid to ask
 ************************************************************************/

#include "ground.h"

/********************************************
 * GROUND :: CONSTRUCTOR
 ********************************************/
Ground :: Ground(Point tl, Point br) : topLeft(tl), bottomRight(br)
{
   Point pt; // create a point to get the dimensions
   xSize = bottomRight.getX() - topLeft.getX();

   // create the ground
   ground = new float[xSize];
   generateGround();
}

//within platform bounds
bool Ground :: isInPlatform(Point p) const
{
   if (p.getY() < platform.getY()
      && p.getX() < platform.getX() + PLATFORM/2 + 7
      && p.getX() > platform.getX() - PLATFORM/2 - 7)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/*********************************************
 * GROUND :: GET GROUND HEIGHT
 * For a given x position, determine the height
 * of the ground at that point;
 *********************************************/
Point Ground :: getGround(const Point & ptSrc) const
{
   Point pt(ptSrc);

   // handle invalid cases
   if (ptSrc.getX() < topLeft.getX() || ptSrc.getX() > bottomRight.getX())
      pt.setY(bottomRight.getY());

   // handle the platform case
   else if (ptSrc.getX() - platform.getX() < PLATFORM / 2.0 &&
       platform.getX() - ptSrc.getX() < PLATFORM / 2.0)
      pt.setY(platform.getY());

   // otherwise, the normal ground
   else
      pt.setY(ground[(int)(ptSrc.getX() - bottomRight.getX())]);

   return pt;
}


/***************************************
 * GROUND :: DRAW
 * display the ground on the screen
 ***************************************/
void Ground :: draw(float darkness, int shift) const
{
   // set the initial position at the platform location
   Point pt1 = platform;
   Point pt2 = platform;

   // draw the platform
   pt1.addX(-PLATFORM / 2.0);
   pt2.addX( PLATFORM / 2.0);
   drawLine(pt1, pt2, 0.0, 0.7, 0.2);

   // draw the platform supports
   pt2.setY(bottomRight.getY());
   pt2.setX(pt1.getX());
   for (int i = 0; i < PLATFORM; i += 5)
   {
      drawLine(pt1, pt2, 0.0, 0.7, 0.2);
      pt1.addX(5);
      pt2.addX(5);
   }

   // draw the ground now
   for (int i = 0; i < xSize; i++)
   {
      Point ptBottom(topLeft.getX() + i, bottomRight.getY());
      Point ptTop   (topLeft.getX() + i, ground[i] - shift);
      drawLine(ptBottom, ptTop, 0.7*darkness, 0.1, 0.1);
   }

}

/*********************************************
 * GROUND :: IS ABOVE GROUND
 * did we leave the screen or enter the ground?
 *********************************************/
bool Ground :: isAboveGround(const Point & point) const
{
   return point.getX() > topLeft.getX()     &&
          point.getY() > bottomRight.getY() &&
          point.getX() < bottomRight.getX() &&
          point.getY() > ground[(int)(point.getX() - topLeft.getX())];
}

/*****************************************
 * GROUND :: GENERATE GROUND
 * generate a new terrain
 *******************************************/
void Ground :: generateGround()
{
   Point pt;                              // to get the screen size
   float yMiddle = bottomRight.getY() +         // the midpoint of the screen
         (topLeft.getY() - bottomRight.getY()) / 2.0;

   // create the ground
   ground[0] = 0.0 + bottomRight.getY();
   float slope = 1.0;
   for (int i = 1; i < xSize; i++)
   {
      bool up =   // can the ground slope up?
         (ground[i - 1] < yMiddle) &&                    // not too high
         (ground[i - 1] - bottomRight.getY() < xSize - i) &&   // not near the end
         (slope < 3.0);                                  // not too steep

      bool down =   // can the ground slope down
         (ground[i - 1] > bottomRight.getY() + 10) &&          // not too low
         (i > 10) &&                                     // not near the beginning
         (slope > -3.0);                                 // not too steep;

      slope += random((down ? -BUMPY : 0.0), (up ? BUMPY : 0.0));
      ground[i] = ground[i - 1] + slope;
   }

   // create the platform
   int iPlatform = random(xSize / 4, xSize * 3 / 4);
   int yMax = ground[iPlatform - PLATFORM / 2];
   for (int i = iPlatform - PLATFORM / 2 + 1; i < iPlatform + PLATFORM / 2; i++)
      if (ground[i] > yMax)
         yMax = ground[i];
   platform.setX(iPlatform + topLeft.getX());
   platform.setY(yMax + 10);
}

/*********************************************
 * RESET: RESET THE GROUND
 * make a new ground
 *********************************************/
void Ground :: reset()
{
   generateGround();
}
