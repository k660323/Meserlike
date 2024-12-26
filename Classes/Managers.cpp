#include "Managers.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "MapManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "DataManager.h"

Managers Managers::instance;

Managers::Managers()
{
    scene = new SceneManager();
    sound = new SoundManager();
    input = new InputManager();
    data = new DataManager();

    ui = new UIManager();
    map = new MapManager();
    game = new GameManager();
}

Managers::~Managers()
{
    delete scene;
    delete sound;
    delete input;
    delete data;
    
    delete ui;
    delete game;
    delete map;
}

Managers& Managers::GetInstance()
{
    return instance;
}

SceneManager* Managers::Scene()
{
    return instance.scene;
}

SoundManager* Managers::Sound()
{
    return instance.sound;
}

InputManager* Managers::Input()
{
    return instance.input;
}

DataManager* Managers::Data()
{
    return instance.data;
}

UIManager* Managers::UI()
{
    return instance.ui;
}

MapManager* Managers::Map()
{
    return instance.map;
}

GameManager* Managers::Game()
{
    return instance.game;
}

void Managers::Clear()
{
    scene->Clear();
    sound->Clear();
    ui->Clear();
    input->Clear();
    game->Clear();
}
