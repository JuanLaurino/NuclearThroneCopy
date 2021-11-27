#include "Scene.h"

Scene::Scene(){
	mReinit = true;
}

Scene::~Scene(){
}

void Scene::init(){
	mReinit = false;
}

void Scene::reinit(){
	mReinit = true;
}
