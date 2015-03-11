#include "Scene.h"

Scene::SceneEnd::SceneEnd(Command command, Scene* nextScene) {
	this->command = command;
	this->nextScene = nextScene;
}