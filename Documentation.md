# qqqStudio engine documentation
## Components
These are to provide interaction with gameObject
### Renderer
Provides graphic display of gameObject
Example of using after creating a gameObject named e.g. `object`
```
qqq::GameObject object;
object.addComponent<Renderer>()
```
### Script
Use it to write logic
```
class YourScript: public qqq::Script
//place your code here//
```
### Collider
Use it to add gameobjects' interaction
```
ask Eugene or Egor
```

## Functions
### Component related functions
You can add different components
```
object.addComponent<Component>();
```
To create an image on your screen of a gameObject you need to load file from the project folder and create sprite based on the texture. E.g. you have a gameObject called `object` that has a component `Renderer` (see `Renderer` in `Components`)
```
object.getComponent<Renderer>->loadTexture("objectimage.png");
object.getComponent<Renderer>->createSprite();
```
You can remove one's gameObject component (e.g. `Renderer`)
```
object.removeComponent<Renderer>();
```
