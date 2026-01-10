#pragma once
#include "math.h"
#include "Define.h"
#include "cocos2d.h"
#include "Manager/Managers.h"
#include "Manager/Core/DataManager.h"

USING_NS_CC;
class Utils
{
public:
	static float Clamp(float v, float a, float b)
	{
		float tmp = a, tmp2 = b;

		a = fminf(tmp, tmp2);
		b = fmaxf(tmp, tmp2);

		if (v < a)
			return a;
		if (v > b)
			return b;
		return v;
	}

	static cocos2d::Size Utils::GetVisibleSize()
	{
		return  Director::getInstance()->getVisibleSize();
	}


	// 해상도 크기 기반 위치 잡기
	static Size Utils::GetScreenPos(PivotPoint pivot)
	{
		Size s = GetVisibleSize();

		switch (pivot)
		{
		case PivotPoint::LeftTop:
			s.width = 0;
			break;
		case PivotPoint::Top:
			s.width *= 0.5f;
			break;
		case PivotPoint::RightTop:
			s.width *= 1;
			s.height *= 1;
			break;
		case PivotPoint::Left:
			s.width = 0;
			s.height *= 0.5f;
			break;
		case PivotPoint::Center:
			s.width *= 0.5f;
			s.height *= 0.5f;
			break;
		case PivotPoint::Right:
			s.height *= 0.5f;
			break;
		case PivotPoint::LeftBottom:
			s.width = 0;
			s.height = 0;
			break;
		case PivotPoint::CenterBottom:
			s.width *= 0.5f;
			s.height = 0;
			break;
		case PivotPoint::RightBottom:
			s.height = 0;
			break;
		}

		return s;
	}

	static cocos2d::Size Utils::GetScreenPos(PivotPoint pivot, float xRate, float yRate)
	{
		Size s = GetVisibleSize();
		Size pos = GetScreenPos(pivot);

		// x 왼쪽 -, 오른쪽 + (-1 ~ 1)
		// y 아래 -, 위 + (-1 ~ 1)

		s.width *= xRate;
		s.height *= yRate;

		pos.width += s.width;
		pos.height += s.height;

		return pos;
	}

	// 부모 노드의 기반 위치 잡기
	static Size Utils::GetRelativeNodePosFromParent(PivotPoint pivot, Node* node)
	{
		Size s = node->getParent()->getContentSize() * 0.5f;
		const Size contentSize = node->getParent()->getContentSize();

		switch (pivot)
		{
		case PivotPoint::LeftTop:
			s.width -= (contentSize.width * 0.5f);
			s.height += (contentSize.height * 0.5f);
			break;
		case PivotPoint::Top:
			s.height += (contentSize.height * 0.5f);
			break;
		case PivotPoint::RightTop:
			s.width += (contentSize.width * 0.5f);
			s.height += (contentSize.height * 0.5f);
			break;
		case PivotPoint::Left:
			s.width -= (contentSize.width * 0.5f);
			break;
		case PivotPoint::Center:
			break;
		case PivotPoint::Right:
			s.width += (contentSize.width * 0.5f);
			break;
		case PivotPoint::LeftBottom:
			s.width -= (contentSize.width * 0.5f);
			s.height -= (contentSize.height * 0.5f);
			break;
		case PivotPoint::CenterBottom:
			s.height -= (contentSize.height * 0.5f);
			break;
		case PivotPoint::RightBottom:
			s.width += (contentSize.width * 0.5f);
			s.height -= (contentSize.height * 0.5f);
			break;
		}

		return s;
	}

	static cocos2d::Size Utils::GetRelativeNodePosFromParent(PivotPoint pivot, Node* node, float xRate, float yRate)
	{
		Size s = GetRelativeNodePosFromParent(pivot, node);
		Size contentSize = node->getParent()->getContentSize();

		// x 왼쪽 -, 오른쪽 + (-1 ~ 1)
		// y 아래 -, 위 + (-1 ~ 1)

		contentSize.width *= xRate;
		contentSize.height *= yRate;

		s.width += contentSize.width;
		s.height += contentSize.height;

		return s;
	}

	// 해당 노드의 Pivot과 contentSize기준으로 배치
	// 해당 노드의 Pivot이 Vec2(0.5, 0.5) 기준으로 작성 적용하는 노드의 Pivot은 상관x
	static Size Utils::GetRelativeNodePos(PivotPoint pivot, Node* node)
	{
		Size s = static_cast<Size>(node->getPosition());
		const Size contentSize = node->getContentSize();
	
		switch (pivot)
		{
		case PivotPoint::LeftTop:
			s.width -= (contentSize.width * 0.5f);
			s.height += (contentSize.height * 0.5f);
			break;
		case PivotPoint::Top:
			s.height += (contentSize.height * 0.5f);
			break;
		case PivotPoint::RightTop:
			s.width += (contentSize.width * 0.5f);
			s.height += (contentSize.height * 0.5f);
			break;
		case PivotPoint::Left:
			s.width -= (contentSize.width * 0.5f);
			break;
		case PivotPoint::Center:
			break;
		case PivotPoint::Right:
			s.width += (contentSize.width * 0.5f);
			break;
		case PivotPoint::LeftBottom:
			s.width -= (contentSize.width * 0.5f);
			s.height -= (contentSize.height * 0.5f);
			break;
		case PivotPoint::CenterBottom:
			s.height -= (contentSize.height * 0.5f);
			break;
		case PivotPoint::RightBottom:
			s.width += (contentSize.width * 0.5f);
			s.height -= (contentSize.height * 0.5f);
			break;
		}

		return s;
	}

	static cocos2d::Size Utils::GetRelativeNodePos(PivotPoint pivot, Node* node, float xRate, float yRate)
	{
		Size s = node->getContentSize();
		Size pos = GetRelativeNodePos(pivot, node);

		// x 왼쪽 -, 오른쪽 + (-1 ~ 1)
		// y 아래 -, 위 + (-1 ~ 1)

		s.width *= xRate;
		s.height *= yRate;

		pos.width += s.width;
		pos.height += s.height;

		return pos;
	}
	

	static void RegisterBlockTouchOneByOne(Node* node)
	{
		// 이벤트 리스너 싱글 터치 초기화
		EventListenerTouchOneByOne* _listener = EventListenerTouchOneByOne::create();
		_listener->setSwallowTouches(true);

		// 콜백 함수는 람다식으로 전개한다.
		_listener->onTouchBegan = [=](Touch* touch, Event* event)
			{
				// getCurrentTarget() : 터치 이벤트에 반응한 모든 타겟의 정보를 가지고 온다.
				auto target = static_cast<Sprite*>(event->getCurrentTarget());

				// convertToNodeSpace() : 인수로 전달된 좌표를 특정 노드 기준으로 좌표로 변경한다.
				Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

				// target의 크기를 기반으로 가상의 RECT 생성
				Size s = target->getContentSize();
				Rect rect = Rect(0, 0, s.width, s.height);
				return rect.containsPoint(locationInNode);
			};
		_listener->onTouchMoved = [](Touch* touch, Event* event)
			{
				
			};
		_listener->onTouchEnded = [](Touch* touch, Event* event)
			{

			};

		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, node);
	}

	static Animation* SimpleCreateAnimation(std::string path, float sizeY, float sizeX, int minY, int maxY, int minX, int maxX, float delayPerUnit = 1.0f)
	{
		Vector<SpriteFrame*> animFrames;
		// SpriteFrame 추출
		for (int row = minY; row < maxY; row++)
		{
			for (int col = minX; col < maxX; col++)
			{
				animFrames.pushBack(SpriteFrame::create(path, Rect(col * sizeX, row * sizeY, sizeX, sizeY)));
			}
		}

		// 프레임을 캐싱해두고 나중에 재사용
		// SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);

		auto Animation = Animation::createWithSpriteFrames(animFrames, delayPerUnit);

		return Animation;
	}

	static Animation* SimpleCreateAnimation(AnimationData animData)
	{
		// 스프라이트 시트 가져오기
		// 좌표와 크기를 지정하여 첫 번째 프레임 추출

		Vector<SpriteFrame*> animFrames;
		// SpriteFrame 추출
		for (int row = animData.rowMinY; row < animData.rowMaxY; row++)
		{
			for (int col = animData.colMinX; col < animData.colMaxX; col++)
			{
				animFrames.pushBack(SpriteFrame::create(animData.path, Rect(col * animData.sizeX, row * animData.sizeY, animData.sizeX, animData.sizeY)));
			}
		}

		// 프레임을 캐싱해두고 나중에 재사용
		// SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animData.path);

		auto Animation = Animation::createWithSpriteFrames(animFrames, animData.animSpeed);

		return Animation;
	}

	static Dir XDir(float x)
	{
		return (x > 0.0f ? Dir::Right : Dir::Left);
	}

	static cocos2d::Sprite* SetDefaultSprite(std::string key)
	{
		auto spriteData = Managers::Data()->GetSpriteData(key);

		auto defaultSpriteData = spriteData.dspriteData;

		// 스프라이트 시트 가져오기
		// 좌표와 크기를 지정하여 첫 번째 프레임 추출
		auto spriteFrame = SpriteFrame::create(defaultSpriteData.path, Rect(0, 0, defaultSpriteData.sizeX, defaultSpriteData.sizeY));  

		// 스프라이트 생성
		auto sprite = Sprite::createWithSpriteFrame(spriteFrame);

		return sprite;
	}

	static cocos2d::Animation* CreateAnimation(std::string spriteId, std::string state)
	{
		auto spriteData = Managers::Data()->GetSpriteData(spriteId);

		auto animationSpriteData = spriteData.animData.find(state);

		if (animationSpriteData == spriteData.animData.end())
			return nullptr;

		auto animData = animationSpriteData->second;

		auto animation = SimpleCreateAnimation(animData);
		
		return animation;
	}

	static std::map<std::string,std:: pair<AnimationData ,cocos2d::Animation*>> CreateAllAnimation(std::string spriteId)
	{
		auto spriteData = Managers::Data()->GetSpriteData(spriteId);

		auto animationData = spriteData.animData;

		std::map<std::string, std::pair<AnimationData, cocos2d::Animation*>> animMap;
		
		for (auto it : animationData)
		{
			auto animData = it.second;
			auto animation = SimpleCreateAnimation(animData);
			
			animMap.insert({ it.first, {it.second , animation} });
		}

		return animMap;
	}

	static Vec2 RotateVec2(const Vec2& vec, float angle) {
		float rad = CC_DEGREES_TO_RADIANS(angle); // 각도를 라디안으로 변환
		float newX = vec.x * cos(rad) - vec.y * sin(rad);
		float newY = vec.x * sin(rad) + vec.y * cos(rad);
		return Vec2(newX, newY);
	}

	static float GetDirAngle(Vec2& vec, Vec2& vec2)
	{
		// 벡터를 정규화
		Vec2 normVec = vec.getNormalized();
		Vec2 normVec2 = vec2.getNormalized();

		// 내적(dot product) 계산
		float dotProduct = normVec.dot(normVec2);

		// 내적 값이 허용 범위를 벗어나지 않도록 클램핑
		dotProduct = std::max(-1.0f, std::min(1.0f, dotProduct));

		// 각도를 라디안으로 계산
		float angleRad = std::acos(dotProduct);

		// 외적(cross product) 계산
		float crossProduct = normVec.cross(normVec2);

		// 외적 값에 따라 360도 회전을 위한 방향 조정
		if (crossProduct < 0)
		{
			angleRad = -angleRad; // 시계 방향이면 음수
		}

		// 라디안을 도(degree)로 변환
		float angleDeg = CC_RADIANS_TO_DEGREES(angleRad);

		// 각도가 음수일 경우 360도 방식으로 변환
		if (angleDeg < 0)
		{
			angleDeg += 360.0f;
		}

		return angleDeg;
	}
};

