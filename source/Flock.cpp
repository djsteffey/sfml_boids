#include "Flock.hpp"

namespace boids{
    Flock::Flock(){

    }

    Flock::~Flock(){
        for (Boid* boid : this->m_boids){
            delete boid;
        }
        this->m_boids.clear();
    }

    void Flock::update(){
        for (Boid* boid : this->m_boids){
            boid->flock(this->m_boids);
            boid->update();
        }
    }

    void Flock::addBoid(float x, float y){
        this->m_boids.push_back(new Boid(x, y));
    }
}
