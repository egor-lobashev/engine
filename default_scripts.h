#include "Component.h"
#include "API.h"

class qqq::BallReflection: public qqq::Script
{
public:
    void update();  // move this function to PhysicsManager or somwhere else
    void ifCollision(qqq::GameObject* another);
};