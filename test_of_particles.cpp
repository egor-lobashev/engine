#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "API.h"

class ParticleDirectMotion: public qqq::Script
{
public:
    float resistance=0;

    void setParameters(float vx, float vy, float r)
    {
        owner->velocity[0] = vx;
        owner->velocity[1] = vy;
        resistance = r;
    }

    void update()
    {
        owner->moveVdt();

        float dt = qqq::relativeTime();
        owner->velocity[0] -= resistance * owner->velocity[0] * dt;
        owner->velocity[1] -= resistance * owner->velocity[1] * dt;
    }
};

class ParticleSource: public qqq::Script
{
public:
    std::string type;
    float frequency;
    sf::Color color;
    float v;

    float timer;
    static int quantity_of_particles;

    void setParameters(std::string type, float frequency, sf::Color color, float v)
    {
        this->type = type;
        this->frequency = frequency;
        this->color = color;
        this->v = v;

        timer = 1/frequency;
    }

    void update()
    {
        timer -= qqq::relativeTime();
        if(timer <= 0)
        {
            timer = 1/frequency;

            qqq::GameObject *particle = new qqq::GameObject;

            particle->addComponent<ParticleDirectMotion>();
            float phi = (random()%100)/100.0 * (2*M_PI);
            float vx = v*cos(phi);
            float vy = v*sin(phi);
            particle->getComponent<ParticleDirectMotion>()->setParameters(vx, vy, 0);

            particle->addComponent<qqq::Renderer>();
            particle->getComponent<qqq::Renderer>()->loadTexture("image.png");
            particle->getComponent<qqq::Renderer>()->createSprite();

            particle->position[0] = owner->position[0] + (random()%10 - 5);
            particle->position[1] = owner->position[1] + (random()%10 - 5);

            particle->record("particle_" + std::to_string(quantity_of_particles++));
        }
    }
};

int ParticleSource::quantity_of_particles = 0;

int main()
{
    qqq::GameObject source;
    source.addComponent<ParticleSource>();
    source.getComponent<ParticleSource>()->setParameters("ab", 1, sf::Color(0,0,0), 10);

    source.position = {300,300};

    source.record("source");

    qqq::runGame(600, 600, "Particles");

    return 0;
}
















// g++ test_of_particles.cpp Component.cpp DataStorage.cpp PhysicsManager.cpp GraphicsManager.cpp ScriptManager.cpp Singleton.cpp qqq_functions.cpp -o test_of_particles -lsfml-graphics -lsfml-window -lsfml-system
// ./test_of_particles