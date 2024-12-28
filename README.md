# [Cocos2d-x] Meserlike
## 1. 소개

<div align="center">
  <img src="https://github.com/k660323/FunnyLand/blob/main/Images/%EC%B5%9C%ED%9B%84%EC%9D%98%20%EC%83%9D%EC%A1%B4%EC%9E%90.JPG" width="49%" height="230"/>
  <img src="https://github.com/k660323/FunnyLand/blob/main/Images/%EC%A2%80%EB%B9%84%20%EC%84%9C%EB%B0%94%EC%9D%B4%EB%B2%8C.JPG" width="49%" height="230"/>
  <img src="https://github.com/k660323/FunnyLand/blob/main/Images/%EC%8A%88%ED%8C%85%EC%8A%88%ED%84%B0.JPG" width="49%" height="230"/>
  <img src="https://github.com/k660323/FunnyLand/blob/main/Images/%EB%A6%BF%EC%A7%80%20%EB%B8%94%EB%A1%9D%EC%BB%A4.JPG" width="49%" height="230"/>
  
  < 게임 플레이 사진 >
</div>

+ Mserlike란?
  + Cocos2d-x로 만든 메이플 리소스에 뱀파이어 서바이벌 게임 요소를 모방하여 만든 프로젝트입니다.
 
+ 목표
  + 라운드마다 몰려오면 몬스터를 잡고 레벨업을 통해 스킬을 강화시켜 마지막 라운드 까지 생존하는 것이 목표입니다.

+ 게임 흐름
  + 시작시 공격 스킬 하나 선택합니다.
  + 매 턴 마다 몰려오는 몬스터를 처치해야합니다.
  + 몬스터를 처치하여 얻은 경험치로 레벨업을 하여 스킬을 강화 또는 추가합니다.
  + 마지막 라운드 까지 생존하여 출연하는 보스 몬스터를 처치하면 결과창을 출력하여 게임이 종료가 됩니다.      

<br>

## 2. 프로젝트 정보

+ 사용 엔진 : Cocos2d-x
  
+ 엔진 버전 : 3.17.2

+ 사용 언어 : C++
  
+ 작업 인원 : 1명
  
+ 작업 영역 : 콘텐츠 제작, 디자인, 기획
  
+ 장르      : 서바이벌 생존
  
+ 소개      : 메이플 리소스 + 뱀파이벌 서바이벌 게임 요소
  
+ 플랫폼    : PC
  
+ 개발기간  : 2024.09.1 ~ 2024.10.2
  
+ 형상관리  : GitHub Desktop

<br>

## 3. 사용 기술
| 기술 | 설명 |
|:---:|:---|
| 디자인 패턴 | ● **싱글톤** 패턴 Managers클래스에 적용하여 여러 객체 관리 <br> ● **FSM** 패턴을 사용하여 플레이어 및 AI 기능 구현 <br> ● **옵저버** 패턴을 사용하여 플레이어 상태, 스킬 상태를 변경시에만 UI 업데이트|
| GameData | Json형태의 파일로 관리 |

<br>

## 4. 구현 기능

### **구조 설계**

대부분 Cocos2d-x 프로젝트에서 사용되고 자주 사용하는 기능들을 구현하여 싱글톤 클래스인 Managers에서 접근할 수 있도록 구현
      
#### **코어 매니저**

+ SceneManager - 생성된 씬을 관리하는 매니저

[[SceneManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/SceneManager.h) / [SceneManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/SceneManager.cpp)]

<br>

+ SoundManager - 사운드 매니저

[[SoundManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/SoundManager.h) / [SoundManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/SoundManager.cpp)]

<br>

+ InputManager - 사용자 입력 관리 매니저

[[InputManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/InputManager.h) / [InputManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/InputManager.cpp)]

<br>

+ DataManager  - 데이터 관리 매니저

[[DataManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/DataManager.h) / [DataManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/DataManager.cpp)]

<br>

+ UIManager    - UI 매니저

[[UIManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/UIManager.h) / [UIManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/UIManager.cpp)]

<br>
  
        
#### **컨텐츠 매니저**

+ MapManager
  + 게임 맵을 불러오거나, 맵정보 기반으로 오브젝트를 스폰하기 위한 매니저
    
+ GameManager
  + 게임 정보 및 로직을 수행하는 매니저


[Managers.h](https://github.com/k660323/Meserlike/blob/main/Classes/Managers.h)

[Managers.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Managers.cpp)

<br>

---

<br>
     
### **씬**

전체적인 씬은 로비, 게임 씬으로 나눠서 구현
   
#### **로비 씬**
+ LobbyScene
  + 씬 초기화
  + UI_LobbyScene 생성 및 배경음악 실행

[LobbyScene.h](https://github.com/k660323/Meserlike/blob/main/Classes/LobbyScene.h)

[LobbyScene.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/LobbyScene.cpp)

<br>
    
+ UI_LobbyScene
  + 플레이어와 상호작용하는 UI
  + 해당 씬에서는 모든 기능이 UI_LobbyScene을 통해 상호작용하도록 구현
  + 게임시작, 설정, 게임 종료 버튼 들이 각 함수마다 바인딩되어 구현
  + 게임 시작
    + GameScene으로 전환 후 메서라이크의 본 컨텐츠를 수행합니다.
  + 설정
    + 배경음악, 효과음을 설정할 수 있는 UI_Setting을 띄웁니다.
  + 게임종료
    + 애플리케이션을 종료합니다.  

[UI_LobbyScene.h](https://github.com/k660323/Meserlike/blob/main/Classes/UI_LobbyScene.h)

[UI_LobbyScene.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/UI_LobbyScene.cpp)

<br>

----

<br>

#### **게임 씬**
+ GameScene
  + 플레이어가 생성되고 매 라운드마다 데이터를 참고하여 몬스터를 스폰하여 컨텐츠를 진행하는 클래스

**게임 시작 과정**
1. Init() - 오브젝트 첫 생성시 호출되는 함수, 초기화, 물리 초기화, spawningPool 메모리 할당
2. onEnter() - 씬 활성화시 호출 함수, 씬 타입 설정, 맵 로드 및 배치, GameStart()함수 지연 호출
3. GameStart() - 플레이어 오브젝트 생성 및 배치, 랜덤 물약 스폰, UI_GameScene 생성, 키입력 바인딩, 몬스터 스폰 시작

[GameScene.h](https://github.com/k660323/Meserlike/blob/main/Classes/GameScene.h)

[GameScene.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/GameScene.cpp)

<br>

+ SpawningPool
  + DataManager클래스의 RoundSpawnData를 가져와 데이터 기반으로 몬스터를 스폰하는 클래스 입니다.

 **스폰 과정**

TrySpawn() (라운드 초기화)
  + TrySpawn을 통해 현재 라운드가 마지막일 경우 종료 이벤트 발생 아닐 경우 몬스터를 스폰할 준비를 합니다.
  + DataManager클래스 GetRounSpawnDataData()를 통해 RoundSpawnData를 가져옵니다.
  + 해당 라운드의 스폰 주기, 스폰 리스트를 설정 및 관련 데이터들을 초기화 합니다.
  + 초기화 후 FindSpawnData() 함수를 지연 호출하기 위해 Sequecne를 이용하여 구현하였습니다.
    
FindSpawnData() (웨이브 초기화)
  + 현재 라운드의 웨이브의 데이터를 가져와 초기화 후 몬스터를 스폰하기 위한 WaveSpawnMonster()함수를 지연호출 하도록 Sequence를 이용하여 구현하였습니다.

WaveSpawnMonster() (몬스터 초기화)
  + 현재 웨이브 인덱스를 통해 몬스터 정보 및 개수 설정 후 스폰 위치 지정 한후 SpawnMosnter를 지정한 횟수만큼 호출 하도록 Repeat를 사용하여 구현하였습니다.

SpawnMosnter() (몬스터 생성)
  + Repeat를 통해 지정한 횟수만큼 호출되며 몬스터를 스폰
  + 모두 스폰 되었으면 다음 웨이브가 존재 여부에 따라 스폰 및 종료 한다.
    

[[SpawningPool.h](https://github.com/k660323/Meserlike/blob/main/Classes/SpawningPool.h) / [SpawningPool.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/SpawningPool.cpp)]

<br>

---

<br>

### **월드 오브젝트**
+ Creature
  + 여러 오브젝트를 가지고 있고 상호 작용 가능한 컨텐츠 오브젝트
  + Player, Monster 클래스가 사용할 공통적인 기능들을 정의한 클래스
  + 이 클래스르 직접적으로 쓰이지 않고 상속받아 사용한다.

[[Creature.h](https://github.com/k660323/Meserlike/blob/main/Classes/Creature.h) / [Creature.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Creature.cpp)]

<br>

+ Player
  + Creature  클래스를 상속받은 클래스이며 게임 플레이어가 사용할 클래스
  + 
  
+ NormalMonster

+ BossMonster

<br>

---

<br>

### **컨트롤러**

+ BaseController

+ PlayerController

+ NormalMonsterController

+ BossMonsterController

<br>

---

<br>

### **스킬**

<br>

---

<br>

### **무기**


<br>

---

<br>

### **스탯**


<br>

---

<br>

## 5. 구현에 어려웠던 점과 해결과정
+ GUI없이 구현하다 보니 에디터 및 런타임에 UI 배치 또는 직접 값을 수정할 수 없어 UI 배치에 어려움을 겪었습니다.
  + 비효율적이지만 배치 및 수정시 많은 컴파일을 통해 확인하여 배치 하였습니다. 그 덕분에 상용엔진의 소중함을 알게되었습니다.
  
+ GUI도 없고 상용엔진에서 지원하는 기능들이 없어서 직접 구현해야 했습니다.
  + 하드 코딩이긴 했지만 툴 기능을 직접 만들어보는 것도 나쁘지 않고 좋은 경험이 되었습니다.
    
+ Cocos2d 클래스를 사용하지 않고 사용자 지정 클래스를 사용할 때의 메모리 관리에 애를 먹었습니다.
  + 사용자 정의 클래스는 cocos2d-x에서 관리되지 않아 개발자가 스스로 메모리를 관리해야기 때문에 메모리 생명주기를 신경써서 코딩함으로써 메모리 관리에 대한 경험 및 이해가 생겼습니다.

 
## 6. 느낀점
+ 상용엔진에서 제공하는 유틸 함수 툴 기능을 직접 구현하다 보니 게임 구조에 대해 좀 더 깊이 있게 이해가 되었습니다.


## 7. 플레이 영상
+ https://www.youtube.com/watch?v=zycwzQuWkkU
