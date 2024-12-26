#include "MapManager.h"
#include "cocos2d.h"
USING_NS_CC;

MapManager::MapManager()
{
    tmap = nullptr;
}

MapManager::~MapManager()
{
    tmap = nullptr;
    background = nullptr;
    block = nullptr;
    objectPos = nullptr;
}

void MapManager::LoadMap(std::string path, cocos2d::Node* node, int layer, int tag)
{
    // 타일맵 불러오기
    tmap = TMXTiledMap::create(path);
    background = tmap->getLayer("Background");
    block = tmap->getLayer("Block");
    block->setVisible(false);
    // 타일맵에서 Objects라고 지정한 오브젝트 레이어의 객체들 가져오기
    objectPos = tmap->getObjectGroup("ObjectLayer1");
    // z-order를 -1로 하면 화면에 출력이 되지 않으니 0이상으로 설정한다.
    node->addChild(tmap, layer, tag);

    // 중력이 적용되는 범위와 세기를 설정
    // auto visibleSize = Director::getInstance()->getVisibleSize();
    auto mapSize = tmap->getContentSize();
    // 강체 생성 (물리 연산이 가능한 객체를 만든다)
    auto body = PhysicsBody::createEdgeBox
     (Size(mapSize.width * 0.8f, mapSize.height * 0.7f), PHYSICSBODY_MATERIAL_DEFAULT, 30);

    // 물리 시뮬레이션을 적용하기 위해 Node 객체 생성
    auto edgeNode = Node::create();

    // Node 위치 조정
    edgeNode->setPosition(Vec2(mapSize) * 0.5f);
    edgeNode->setAnchorPoint(Vec2(0.5f, 0.5f));
    // 강체를 적용한다.
    edgeNode->setPhysicsBody(body);

    //tmap->addChild(edgeNode, layer + 1);
    node->addChild(edgeNode, layer + 1);
}

bool MapManager::IsValidMap()
{
    return tmap;
}

cocos2d::Vec2 MapManager::GetObjectPos(std::string name)
{
    // 오브젝트 레이어에서 SpawnPoint라고 명명한 오브젝트를 가져오기
    ValueMap spawnPoint = objectPos->getObject(name);

    int x = spawnPoint["x"].asInt();
    int y = spawnPoint["y"].asInt();

    return Vec2(x, y);
}

// 화면에 터치한 부분에 위치한 타일의 좌표를 가져오기
cocos2d::Vec2 MapManager::tileCoordForPosition(cocos2d::Vec2 position)
{
    float x = position.x / tmap->getTileSize().width;
    float y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;

    return Vec2(x, y);
}

cocos2d::Vec2 MapManager::positionForTileCoord(cocos2d::Vec2 position)
{
    float x = position.x * tmap->getTileSize().width;
    float y = (tmap->getMapSize().height - position.y) * tmap->getTileSize().height;

    return Vec2(x,y);
}

bool MapManager::CanGo(cocos2d::Vec2 position)
{
    // 현재 좌표를 타일 좌표로 변환
    Vec2 tileCoord = tileCoordForPosition(position);

    // 현재 위치의 타일 ID 구하기
    int tileGid = block->getTileGIDAt(tileCoord);

    if (tileGid)
    {
        // 타일맵에서 GID에 해당하는 속성을 불러오기
        Value properties = tmap->getPropertiesForGID(tileGid);
        ValueMap valueMap = properties.asValueMap();
        if (valueMap.find("IsBlock") != valueMap.end())
            return valueMap["IsBlock"].asBool();
    }

    return true;
}

cocos2d::Size MapManager::GetMapSize()
{
    return tmap->getMapSize();
}

cocos2d::Size MapManager::GetTileSize()
{
    return tmap->getTileSize();
}

cocos2d::Size MapManager::GetContentSize()
{
    return tmap->getContentSize();
}

cocos2d::Vec2 MapManager::GetViewpointCenter(cocos2d::Vec2 position)
{
    // 화면 크기 구하기
    Size winHalfSize = Director::getInstance()->getWinSize() * 0.5f;

    float x = MAX(position.x, winHalfSize.width);
    float y = MAX(position.y, winHalfSize.height);

    Size contentSize = GetContentSize();
   
    x = MIN(x, (contentSize.width) - (winHalfSize.width));
    y = MIN(y, (contentSize.height) - (winHalfSize.height));

    Vec2 actualPosition = Vec2(x, y);
    Vec2 centerOfView = winHalfSize;
    Vec2 viewPoint = centerOfView - actualPosition;

    return viewPoint;
}

