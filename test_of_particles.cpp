#include <SFML/Graphics.hpp>
#include <random>
#include "GameObject.h"
#include "particles.h"


int main()
{
    qqq::GameObject source;
    source.addComponent<qqq::ParticleSource>();
    source.getComponent<qqq::ParticleSource>()->setParameters(10, 50, 270, 0, {300, 1}, 0);
    source.getComponent<qqq::ParticleSource>()->setCircle(5, 0, 130, 160);

    source.position = {300,0};

    source.record("source");


    qqq::GameObject source_2;
    source_2.addComponent<qqq::ParticleSource>();
    source_2.getComponent<qqq::ParticleSource>()->setParameters(10, 100, -1, 1);
    source_2.getComponent<qqq::ParticleSource>()->setSquare(8, 200, 80, 50);

    source_2.position = {450,350};

    source_2.record("source_2");


    qqq::GameObject source_3;
    source_3.addComponent<qqq::ParticleSource>();
    source_3.getComponent<qqq::ParticleSource>()->setParameters(1, 10, 0);
    source_3.getComponent<qqq::ParticleSource>()->setPicture("image.png");

    source_3.position = {0,500};

    source_3.record("source_3");

    qqq::runGame(600, 600, "Particles");

    return 0;
}

// g++ test_of_particles.cpp Component.cpp DataStorage.cpp PhysicsManager.cpp GraphicsManager.cpp ScriptManager.cpp Singleton.cpp qqq_functions.cpp particles.cpp -o test_of_particles -lsfml-graphics -lsfml-window -lsfml-system
// ./test_of_particles