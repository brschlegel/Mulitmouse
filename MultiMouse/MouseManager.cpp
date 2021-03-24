#include "MouseManager.h"
#include "manymouse.h"

MouseManager* MouseManager::instance;

Mouse* MouseManager::buildMouse(int deviceNum)
{
	Color color = potentialMiceColors[mice.size()];
	Mouse* mouse = new Mouse(color);
	mice.push_back(mouse);
	miceByColor[color] = mouse;
	miceDeviceMap[deviceNum] = mouse;
	return mouse;
}

MouseManager::MouseManager()
{
	ManyMouse_Init();
	potentialMiceColors[0] = Color::getRed();
	potentialMiceColors[1] = Color::getBlue();
	potentialMiceColors[2] = Color::getGreen();
}

MouseManager* MouseManager::getInstance()
{
	if (!instance)
	{
		instance = new MouseManager();
	}
	return instance;
}

void MouseManager::update()
{
	ManyMouseEvent event;
	while (ManyMouse_PollEvent(&event) != 0)
	{
		//Build the mouse if it doesn't exist
		if (miceDeviceMap.find(event.device) == miceDeviceMap.end())
		{
			buildMouse(event.device);
		}
		switch (event.type)
		{

		case MANYMOUSE_EVENT_RELMOTION:
			if (event.item == 0)
			{
				miceDeviceMap[event.device]->updateX((float)event.value);
			}
			else
			{
				miceDeviceMap[event.device]->updateY((float)event.value);
			}
			break;
		case MANYMOUSE_EVENT_BUTTON:
			//if left click
			if (event.item == 0)
			{
				miceDeviceMap[event.device]->leftButtonPressed = event.value;
				//mice[event.device]->physicsSelect = NULL;
				if (!event.value && miceDeviceMap[event.device]->physicsSelect != NULL)
				{
					miceDeviceMap[event.device]->releasePhysicsSelect();
				}
			}
			else
			{
				miceDeviceMap[event.device]->rightButtonPressed = event.value;
				
			}
		}


	}

	for (unsigned int i = 0; i < mice.size(); ++i)
	{
		mice[i]->update();
	}
}

void MouseManager::draw()
{
	for (unsigned int i = 0; i < mice.size(); ++i)
	{
		mice[i]->draw();
	}
}

void MouseManager::setAllMiceActive(bool cond)
{
	for (int i = 0; i < mice.size();i++)
	{
		mice[i]->active = cond;
		mice[i]->frozen = false;
	}
}

void MouseManager::unfreezeAllMice()
{
	for (int i = 0; i < mice.size(); i++)
	{
		mice[i]->frozen = false;
	}
}

int MouseManager::getNumOfActiveMice()
{
	int count = 0;
	for (int i = 0; i < mice.size(); i++)
	{
		if (mice[i]->active)
			count++;
	}
	return count;
}

vector<Mouse*> MouseManager::getActiveMice()
{
	vector<Mouse*> activeMice;
	for (int i = 0; i < mice.size(); i++)
	{
		if (mice[i]->active)
			activeMice.push_back(mice[i]);
	}
	return activeMice;
}
