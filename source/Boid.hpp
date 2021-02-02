#ifndef boids_Boid_hpp
#define boids_Boid_hpp

#include "Vector2D.hpp"
#include <list>

namespace boids{
    class Boid{
        public:
            Boid(float x, float y);
            ~Boid();
            void update();
            void flock(std::list<Boid*>& boids);
            Vector2D getPosition();

        protected:

        private:
            void applyForce(Vector2D force);
            Vector2D seek(Vector2D target);
            Vector2D separation(std::list<Boid*>& boids);
            Vector2D alignment(std::list<Boid*>& boids);
            Vector2D cohesion(std::list<Boid*>& boids);

            static constexpr float s_max_speed = 3.0f;
            static constexpr float s_max_force = 0.05f;
            Vector2D m_position;
            Vector2D m_velocity;
            Vector2D m_acceleration;
            float m_heading;
    };
}
#endif
