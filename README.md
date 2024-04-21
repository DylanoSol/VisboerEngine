# VisboerEngine
Self Study project. A solo developed engine type project, started to learn more about API design and the fundamentals of Engine Programming. The goal will be to create a very simple 3D Platformer along with the Engine to verify my approaches. 

## Project Plan 
Within the project plan, every single part will be seen as a mini-goal. I will figure out the dependencies per system as we go. 

### 1. Rendering API
The first thing I want to do within the engine project is create a very simple rendering API. I want to do this, since it would be a good way to refresh some of my Graphics programming knowledge, and I want to write something in a way that I can eventually tie it into other systems. 

I will be using OpenGL for this, since it's by far the simplest Graphics API to integrate into other systems, and since I have written a renderer with it before. My main resource will be https://learnopengl.com/. 

The current scope for the rendering API is very simple: I want to have the minimum amount of features that can make me do most of the things I want to do. This generally comes down to: 
- Model drawing
- Texture support
- Line drawing

### 2. Entity system
After finishing the renderer, I want to work on implementing an Entity / GameObject system to tie into the rendering. I want to investigate what type of entity system I need. 

My goal for this system is to easily be able to entities that automatically get moved to the world, while they automatically get rendered. 

