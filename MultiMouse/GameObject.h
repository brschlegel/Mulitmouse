#pragma once
#include <Box2D/Box2D.h>
#include "Color.h"
#include <string>
#include <vector>

enum class LevelName { DebugLevel, Juggling, Pong, Dodgeball, LevelSelect, PlayerSelect, TeamSelect, Musical, Maze };
enum class Tag{Ball, Pong, Unscorable, Unselectable};

class GameObject
{
public:
	float x, y;
	std::string name;
	bool hasTag(Tag tag);
	void addTag(Tag tag);
	virtual void draw() = 0;

	GameObject(float x, float y, std::string name = "unnamed");
	GameObject(std::string name = "unnamed");
private:
	std::vector<Tag> tags;
	
};

