#pragma once
#include "string"

namespace cocos2d
{
	class Node;
	class Vec2;
	class TMXTiledMap;
	class TMXLayer;
	class TMXObjectGroup;
	class Size;
}

class MapManager
{
public:
	MapManager();
	virtual ~MapManager();

	void LoadMap(std::string path, cocos2d::Node* node, int layer = -1, int tag = 10);

	bool IsValidMap();

	cocos2d::Vec2 GetObjectPos(std::string name);

	cocos2d::Vec2 MapManager::tileCoordForPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 MapManager::positionForTileCoord(cocos2d::Vec2 position);
	bool CanGo(cocos2d::Vec2 position);

	cocos2d::Size GetMapSize();
	cocos2d::Size GetTileSize();
	cocos2d::Size GetContentSize();

	cocos2d::Vec2 GetViewpointCenter(cocos2d::Vec2 position);

private:
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* block;
	cocos2d::TMXObjectGroup* objectPos;
};