// https://rosettacode.org/wiki/Boids/Java

#include <SFML/Graphics.hpp>
#include "Flock.hpp"
#include "Vector2D.hpp"

int main(int argc, char** argv){
    // make the boids
    boids::Flock flock;
    for (int i = 0; i < 10; ++i){
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        flock.addBoid(x, y);
    }

    // make a window
    sf::RenderWindow rw;
    rw.create(sf::VideoMode(800, 600), "Boids", sf::Style::Close | sf::Style::Titlebar);

    // sprite for drawing boids
    sf::Texture texture;
    texture.loadFromFile("boid.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // loop while the window is open
    while (rw.isOpen()){
        // process events
        sf::Event event;
        while (rw.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                rw.close();
            }
        }

        // update the flock
        flock.update();

        // draw
        rw.clear();
        for (boids::Boid* boid : flock.getBoids()){
            boids::Vector2D position = boid->getPosition();
            sprite.setPosition(position);
            rw.draw(sprite);
        }
        rw.display();
    }
}