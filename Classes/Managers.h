#pragma once

class SceneManager;
class SoundManager;
class UIManager;
class MapManager;
class InputManager;
class GameManager;
class DataManager;

class Managers
{

public:	
	Managers();
	virtual ~Managers();

	static Managers& GetInstance();
	
	static SceneManager* Scene();

	static SoundManager* Sound();

	static InputManager* Input();

	static DataManager* Data();

	static UIManager* UI();

	static MapManager* Map();

	static GameManager* Game();


	void Clear();

private:
	static Managers instance;

	SceneManager* scene;
	SoundManager* sound;
	InputManager* input;
	DataManager* data;
	
	UIManager* ui;
	MapManager* map;
	GameManager* game;
};