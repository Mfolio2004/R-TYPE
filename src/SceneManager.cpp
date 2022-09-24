#include "SceneManager.hpp"
#include <iostream>

namespace R_TYPE {

    void SceneManager::addScene(std::unique_ptr<IScene> scene, SceneType sceneType)
    {
        if (_scenes.find(sceneType) != _scenes.end())
            throw std::invalid_argument("SceneManager: Scene already exists");
        _scenes[sceneType] = std::move(scene);
    }

    IScene &SceneManager::getCurrentScene()
    {
        if (_scenes.find(_currentScene) == _scenes.end())
            throw std::runtime_error("SceneManager: Invalid current scene");
        return *_scenes[_currentScene];
    }

    void SceneManager::setCurrentScene(SceneType sceneType, bool initScene)
    {
        std::cout << "SetCurrentScene\n";
    }

    void SceneManager::setShouldClose(bool shouldClose)
    {
        _shouldClose = shouldClose;
    }

    bool SceneManager::getShouldClose()
    {
        return _shouldClose;
    }
}