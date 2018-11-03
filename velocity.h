#ifndef VELOCITY
#define VELOCITY

class Velocity
{
public:
   Velocity();
   Velocity(float, float);
   float getDx();
   float getDy();
   void setDx(float);
   void setDy(float);
   void addDy(float);
   void addDx(float);
private:
   float dx;
   float dy;
};

#endif //VELOCITY
