#include "Vector2D.hpp"
#include <cmath>

namespace boids{
    Vector2D::Vector2D(){
        this->x = 0.0f;
        this->y = 0.0f;
    }

    Vector2D::Vector2D(float x, float y){
        this->x = x;
        this->y = y;
    }

    Vector2D::~Vector2D(){

    }

    void Vector2D::limit(float max){
        float length = this->length();
        if (length > max) {
            this->normalize();
            this->x *= max;
            this->y *= max;
        }
    }

    float Vector2D::length(){
        return static_cast<float>(std::sqrt((this->x * this->x) + (this->y * this->y)));
    }

    void Vector2D::normalize(){
        float length = this->length();
        if (length != 0.0f){
            this->x /= length;
            this->y /= length;
        }
    }

    float Vector2D::distance(Vector2D other){
        Vector2D v = Vector2D::subtract(other, *this);
        return v.length();

    }

    void Vector2D::divide(int amount){
        this->x /= amount;
        this->y /= amount;
    }

    Vector2D Vector2D::subtract(Vector2D v1, Vector2D v2){
        return Vector2D(v1.x - v2.x, v1.y - v2.y);
    }
}