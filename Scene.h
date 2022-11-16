#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Game;
class Scene{
public:
	virtual void Update(Game&) =0;
	virtual void Draw(RenderWindow&) =0;
	virtual void ProcessEvents(RenderWindow&) =0;
	
	virtual ~Scene()=default;
};
