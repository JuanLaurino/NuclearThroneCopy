#include "Scene.h"

Scene::Scene(){
	mReinit = true;
}

Scene::~Scene(){
}

void Scene::init(){
	mReinit = true;
}

void Scene::reinit(){
	mReinit = false;
}
