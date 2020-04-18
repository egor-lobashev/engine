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
object.getComponent<qqq::Renderer>->loadTexture("image.png");
object.getComponent<qqq::Renderer>->createSprite();
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
### BallReflection()
Add this components to objects that are moving by inertia.
They will reflect when colliding with objects that have Collider and BallReflection components.
```
## Functions
### runGame()
Use it in the end of the code
### Time
There are two functions:
absoluteTime() - returns time since the start of the game cycle
relativeTime() - returns time since the previous frame (dt)