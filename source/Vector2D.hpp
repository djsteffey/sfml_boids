#ifndef boids_Vector2D_hpp
#define boids_Vector2D_hpp

#include <SFML/System.hpp>

namespace boids{
    class Vector2D : public sf::Vector2f{
        public:
            Vector2D();
            Vector2D(float x, float y);
            ~Vector2D();
            void limit(float max);
            float length();
            void normalize();
            float distance(Vector2D other);
            void divide(int amount);
            static Vector2D subtract(Vector2D v1, Vector2D v2);
            

        protected:

        private:
    };
}
#endif