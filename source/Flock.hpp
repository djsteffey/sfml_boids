#ifndef boids_Flock_hpp
#define boids_Flock_hpp

#include "Boid.hpp"

namespace boids{
    class Flock{
        public:
            Flock();
            ~Flock();
            void update();
            void addBoid(float x, float y);
            

        protected:

        private:
        std::list<Boid*> m_boids;
    };
}
#endif
