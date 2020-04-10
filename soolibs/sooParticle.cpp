#include "sooParticle.h"

namespace soo
{

void
Particle::setRandomDirection()
{
    float x = ofRandom(-1, 1);
    float y = ofRandom(-1, 1);
    direction = speed * (ofVec2f(x, y)).normalize();
}

} // namespace soo
