#include "Scene.h"

Scene::Scene(b2Vec2 gravity, std::string name)
{
	shapes = new ShapeStorage(gravity);
	ui =  UIManager();
	this->name = name;
	//Default keyboard func
	keyboardFunc = DoNothing;

	
}

void Scene::draw(sf::RenderWindow* window)
{
	
	shapes->draw();
	ui.draw(window);
}

void Scene::update()
{
	Scene* scene = this;
	//ShapeStorage updated in source
	for (FuncTimer* t : funcTimers)
	{
		t->update(scene);
	}
}

FuncTimer* Scene::getTimerByName(std::string name)
{
	for (FuncTimer* t : funcTimers)
	{
		if (t->name == name)
		{
			return t;
		}
	}
	return nullptr;
}

PolygonPhysicsObject* Scene::getBodyByName(std::string name)			
{
	return shapes->getObjectByNameT<PolygonPhysicsObject>(name);
}

Label* Scene::getLabelByName(std::string name)
{
	return ui.getLabelByName(name);
}

Trigger* Scene::getTriggerByName(std::string name)
{
	return shapes->getObjectByNameT<Trigger>(name);
}

std::vector<PolygonPhysicsObject*> Scene::getBodyByTag(Tag tag)
{
	return shapes->getObjectsByTagT<PolygonPhysicsObject>(tag);
}

void Scene::init()
{
	startFuncTimers();
	initSignal();
	if (initDel.GetSize() > 0)
	{
		initDel.Execute();
	}
}

void Scene::frameScene()
{
	shapes->AddRectBarrier(0, -5, 20, 1);
	shapes->AddRectBarrier(1, 5, 20, 1);
	shapes->AddRectBarrier(-9, 0, 1, 10);
	shapes->AddRectBarrier(9, 0, 1, 10);
}

void Scene::unload()
{
	shapes->unload();
	delete shapes;
	ui.unload();
	for (int i = 0; i < funcTimers.size(); i++)
	{
		delete funcTimers[i];
	}
}

void Scene::buildInstructionScene(std::string levelName, std::string instructionText, std::string imageName)
{
	Label* l = ui.buildLabel(levelName, 0, 4, 30);
	Label* description = ui.buildLabel(ui.fitInBox(instructionText, 30, 4), -5, 0, 30);
	readyUpButton = shapes->buildMouseAssignmentButton(0, -4, 1.5, .75f, Color::getRed(), MouseManager::getInstance()->getActiveMice().size(), "PlayButton");
	ui.buildSprite(imageName, 4, 0, 8, 8);
	ui.buildLabelInTrigger("Ready Up", readyUpButton);
}

void Scene::buildGameOverScene(std::string losingMessage)
{
	ui.buildLabel(losingMessage, 0, 0, 40);
	LevelButton* lb = shapes->buildLevelButton(0, -2, 2.75f, 1, Color::getGreen(), LevelName::LevelSelect);
	lb->active = true;
	ui.buildLabelInTrigger("Back to Level Select", lb);
	initDel.BindLambda([this]
		{
			MouseManager::getInstance()->resetMice();
		});

}

void Scene::startFuncTimers()
{
	for (FuncTimer* t : funcTimers)
	{
		t->start();
	}
}


