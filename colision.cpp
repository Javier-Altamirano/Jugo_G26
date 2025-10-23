#include <iostream>
#include "colision.h"
using namespace std;


bool Colision::isColision(Colision& obj) const
{
    return getBounds().intersects(obj.getBounds());
}
