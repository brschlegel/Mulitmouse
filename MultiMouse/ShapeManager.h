#include "Physics.h"
#include "ShapeStorage.h"
#include "MouseManager.h"

#pragma once
class ShapeManager;
class ShapeManager
{
public:
	void HandleCollision(ShapeStorage* shapes);
	void update(ShapeStorage* storage);
	

};

