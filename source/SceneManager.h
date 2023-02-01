#pragma once
#include <map>
#include <string>
#include <assert.h>

#include "Scene.h"

#define SM SceneManager::GetInstance()


class SceneManager 
{
private:
    SceneManager(); //El constructor es privado porque no queremos que no lo gestione otra gente
    
    static SceneManager* instance;
    
    std::map<std::string, Scene*> scenes;
    Scene* currentScene;

public:
    //-----singleton
    static SceneManager* GetInstance();

    //-----Agregation
    void AddScene(std::string name, Scene* s);

    //TODO template <class S> S* GetScene(); // Me va a devolver un puntero a la clase que le diga

    //-----getters
    Scene* GetScene(std::string name);
    Scene* GetCurrentScene();

    //template <class S> S* SetScene(); 

    //-----setters
    void SetScene(std::string name);
    void ClearScenes();


};