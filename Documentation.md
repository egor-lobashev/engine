# qqqStudio engine documentation
## GameObject
You can add or remove different components (e.g. `qqq::Renderer`)
of gameObject  (named e.g. `object`)
```
my_object.deleteComponent<qqq::Renderer>();
```
to work with a component, write:
```
my_object.getComponent<qqq::Renderer>();
```
To register the game object, you must write:
my_object.record()
```
## Components
These are to provide interaction with gameObject
### Renderer
Provides graphic display of gameObject
Example of using after creating a gameObject
```
qqq::GameObject object;
object.addComponent<qqq::Renderer>()
object.getComponent<qqq::Renderer>()->loadTexture("image.png");
object.getComponent<qqq::Renderer>()->createSprite();
```
### Script
Use it to write logic
```
class YourScript: public qqq::Script
{
public:
    update()
    {
        // your code
        // will be executed in each frame
    }

    void ifCollision(qqq::GameObject* another)
    {
        // your code
        // will be executed when colliding with "another"
    }
};
```
### Collider
Use it to add gameobjects' interaction
```
You can make a rectangle hitbox:
object.getComponent<Collider>()->setHitboxRectangle(60, 80);
```
hitbox forms can be more complex, but Eugene's going to make it more convenient
```
## Default scripts
We provide some common scripts
```
### BallReflection
Add this components to objects that are moving by inertia.
They will reflect when colliding with objects that have Collider and BallReflection components.
```
### ParticleSource
the object will produce particles.
example:
```
qqq::GameObject source;
    source.addComponent<qqq::ParticleSource>();
    source.getComponent<qqq::ParticleSource>()->setParameters(1, 10);
    source.getComponent<qqq::ParticleSource>()->setCircle(5, 0, 130, 160);

    source.position = {300,300};

    source.record("source");
```
#### setParameters(1, 10)
1 particle per second
10 pixels per second
Other parameters:
##### float direction = -1
direction of particles (0-360 degrees, like in trigonometric circle).
if direction is -1, particles fly in all directions
##### float resistance = 0
resistance of environmemt
##### std::vector<int> source_size = {5,5}
particles will spawn randomly in a rectangle with this size. Center of the rectangle is position of GameObject.
##### float direction_variation = 10
particles will fly randomly in direction:
direction +- direction_variation
```
example of full use of setParameters():
source.getComponent<qqq::ParticleSource>()->setParameters(10, 50, 270, 0, {300, 1}, 0);
```
#### setCircle(5, 0, 130, 160)
circle particles
5 is radius of circle
(0,130,160) - RGB color of particle
```
instead of setCircle() you can use:
#### setSquare(5, 0, 130, 160)
square particles
5 is side of square
(0,130,160) - RGB color of particle
#### setPicture("image.png")
paticles with picture "image.png"
```
## Functions
### runGame()
Use it in the end of the code
### Time
There are two functions:
absoluteTime() - returns time since the start of the game cycle
relativeTime() - returns time since the previous frame (dt)