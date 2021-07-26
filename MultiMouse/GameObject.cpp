#include "GameObject.h"
#include <iostream>


bool GameObject::hasTag(Tag tag)
{
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == tag)
		{
			return true;
		}
	}
	return false;
}

void GameObject::addTag(Tag tag)
{
	tags.push_back(tag);
}


GameObject::GameObject(float x, float y, std::string name)
{
	this->x = x;
	this->y = y;
	this->name = name;
}
