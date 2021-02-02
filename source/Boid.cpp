#include "Boid.hpp"
#include "Vector2D.hpp"

namespace boids{
    Boid::Boid(float x, float y){
        this->m_position = Vector2D(x, y);
        this->m_velocity = Vector2D(0.0f, 0.0f);
        this->m_acceleration = Vector2D(0.0f, 0.0f);
        this->m_heading = 0.0f;
    }

    Boid::~Boid(){

    }

    void Boid::update(){
        this->m_velocity += this->m_acceleration;
        this->m_velocity.limit(Boid::s_max_speed);
        this->m_position += this->m_velocity;
        this->m_acceleration *= 0.0f;
    }

    void Boid::flock(std::list<Boid*>& boids){
        Vector2D rule1 = this->separation(boids);
        Vector2D rule2 = this->alignment(boids);
        Vector2D rule3 = this->cohesion(boids);
 
        rule1 *= 2.5f;
        rule2 *= 1.5f;
        rule3 *= 1.3f;
 
        this->applyForce(rule1);
        this->applyForce(rule2);
        this->applyForce(rule3);

        // applyForce(migrate);
    }

    Vector2D Boid::getPosition(){
        return this->m_position;
    }

    void Boid::applyForce(Vector2D force){
        this->m_acceleration += force;
    }

    Vector2D Boid::seek(Vector2D target){
        Vector2D steer = Vector2D::subtract(target, this->m_position);
        steer.normalize();
        steer *= Boid::s_max_speed;
        steer -= this->m_velocity;
        steer.limit(Boid::s_max_force);
        return steer;
    }

    Vector2D Boid::separation(std::list<Boid*>& boids){
        float desired_separation = 25.0f;
 
        Vector2D steer;
        int count = 0;
        for (Boid* b : boids) {
            float d = this->m_position.distance(b->m_position);
            if ((d > 0.0f) && (d < desired_separation)) {
                Vector2D diff = Vector2D::subtract(this->m_position, b->m_position);
                diff.normalize();
                diff /= d;          // weight by distance
                steer += diff;
                count++;
            }
        }
        if (count > 0) {
            steer.divide(count);
        }
 
        if (steer.length() > 0.0f) {
            steer.normalize();
            steer *= Boid::s_max_speed;
            steer -= this->m_velocity;
            steer.limit(Boid::s_max_force);
            return steer;
        }
        return Vector2D();
    }

    Vector2D Boid::alignment(std::list<Boid*>& boids){
        float preferred_dist = 50;
 
        Vector2D steer;
        int count = 0;
 
        for (Boid* b : boids) {
            float d = this->m_position.distance(b->m_position);
            if ((d > 0.0f) && (d < preferred_dist)) {
                steer += b->m_velocity;
                count++;
            }
        }
 
        if (count > 0) {
            steer.divide(count);
            steer.normalize();
            steer *= Boid::s_max_speed;
            steer -= this->m_velocity;
            steer.limit(Boid::s_max_force);
        }
        return steer;
    }

    Vector2D Boid::cohesion(std::list<Boid*>& boids){
        float preferred_dist = 50.0f;
 
        Vector2D target;
        int count = 0;
 
        for (Boid* b : boids) {
            float d = this->m_position.distance(b->m_position);
            if ((d > 0.0f) && (d < preferred_dist)) {
                target += b->m_position;
                count++;
            }
        }
        if (count > 0) {
            target.divide(count);
            return this->seek(target);
        }
        return target;
    }
}
