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

#### **매니저**

+ Managers - 아래의 매니저들을 관리하는 매니저

[[Managers.h](https://github.com/k660323/Meserlike/blob/main/Classes/Managers.h) / [Managers.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Managers.cpp)]

<br>

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

       
#### **컨텐츠 매니저**

+ MapManager
  + 게임 맵을 불러오거나, 맵정보 기반으로 오브젝트를 스폰하기 위한 매니저

[[MapManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/MapManager.h) / [MapManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/MapManager.cpp)]

<br>

+ GameManager
  + 게임 정보 및 로직을 수행하는 매니저

[[GameManager.h](https://github.com/k660323/Meserlike/blob/main/Classes/GameManager.h) / [GameManager.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/GameManager.cpp)]

<br>

---

<br>
     
### **씬**

전체적인 씬은 로비, 게임 씬으로 나눠서 구현
   
#### **로비 씬**
+ LobbyScene
  + 씬 초기화
  + UI_LobbyScene 생성 및 배경음악 실행

[[LobbyScene.h](https://github.com/k660323/Meserlike/blob/main/Classes/LobbyScene.h) / [LobbyScene.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/LobbyScene.cpp)]

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

[[UI_LobbyScene.h](https://github.com/k660323/Meserlike/blob/main/Classes/UI_LobbyScene.h) / [UI_LobbyScene.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/UI_LobbyScene.cpp)]

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

[[GameScene.h](https://github.com/k660323/Meserlike/blob/main/Classes/GameScene.h) / [GameScene.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/GameScene.cpp)]

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
  + 애니메이션, 스탯, 컨트롤러, 스킬북 등 각종 클래스를 초기화 및 관리하는 클래스
  + Player, Monster 클래스가 사용할 공통적인 기능들을 정의한 클래스

[[Creature.h](https://github.com/k660323/Meserlike/blob/main/Classes/Creature.h) / [Creature.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Creature.cpp)]

<br>

+ Player
  + Creature  클래스를 상속받은 클래스이며 게임 플레이어가 사용할 클래스
  + 플레이어 스탯, 플레이어 컨트롤러 클래스를 초기화 및 관리하는 클래스
  + 대시 - 쿨타임이 있으며 사용시 플레이어를 물리적으로 빠르게 이동시키는 스킬

[[Player.h](https://github.com/k660323/Meserlike/blob/main/Classes/Player.h) / [Player.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Player.cpp)]

<br>

+ Monster
  + Creature 클래스를 상속받은 클래스이며 몬스터 클래스가 사용하기 위한 기초 클래스 
  + 몬스터 스탯, 몬스터 컨트롤러 클래스 초기화 및 관리하는 클래스

[[Monster.h](https://github.com/k660323/Meserlike/blob/main/Classes/Monster.h) / [Monster.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Monster.cpp)]

<br>

+ NormalMonster / BossMonster
  + Monster 클래스를 상속받은 클래스
  + 생성자의 인자에 따라 스프라이트, 능력치, 기술이 설정된다.
  + 노말 몬스터 컨트롤러 / 보스 몬스터 컨트로럴르 초기화 및 관리하는 클래스
  + init() 함수에서 충돌 판정 바인딩 합니다.
  + **SpawningPool 클래스에서 BossMonster클래스를 지닌 몬스터 스폰시 전용 UI를 출력합니다.**

[[NormalMonster.h](https://github.com/k660323/Meserlike/blob/main/Classes/NormalMonster.h) / [NormalMonster.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/NormalMonster.cpp)]

[[BossMonster.h](https://github.com/k660323/Meserlike/blob/main/Classes/BossMonster.h) / [BossMonster.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/BossMonster.cpp)]


<br>

---

<br>

### **컨트롤러**

+ BaseController
  + Creature클래스를 다루기 위한 기초 컨트롤러 클래스
  + 공통적으로 사용되는 기능을 정의한 클래스 (Stat, Creature 멤버변수를 가지고 있으며 매 프레임 마다 처리할 함수 Update를 스케줄러에 등록한다.)
  + 애니메이션은 SetState 가상함수가 상태변경시 애니메이션이 전환되도록 설정 구체적인 로직은 자식 클래스에서 정의
  + 게임 로직은 Update 가상함수가 매프레임마다 처리할 로직을 정의한다 구체적인 로직은 자식 클래스에서 정의

[[BaseController.h](https://github.com/k660323/Meserlike/blob/main/Classes/BaseController.h) / [BaseController.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/BaseController.cpp)]

<br>

+ PlayerController
  + BaseController를 상속받은 클래스
  + FSM(유한 상태 머신) 패턴으로 플레이어 로직 구현
  + Update()함수에서 각 상태에 대한 함수 실행하여 유기적으로 상태전환이 되도록 설계 (Idle, Move, Dead)

[[PlayerController.h](https://github.com/k660323/Meserlike/blob/main/Classes/PlayerController.h) / [PlayerController.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/PlayerController.cpp)]

<br>

+ NormalMonsterController / BossMonsterController
  + MonsterController를 상속받은 클래스
  + FSM(유한 상태 머신) 패턴으로 몬스터 로직 구현
  + Update()함수에서 각 상태를 대한 함수를 실행하여 유기적으로 상태전환이 되도록 설계 (Idle, Move, Dead)

[[NormalMonsterController.h](https://github.com/k660323/Meserlike/blob/main/Classes/NormalMonsterController.h) / [NormalMonsterController.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/NormalMonsterController.cpp)]

[[BossMonsterControoler.h](https://github.com/k660323/Meserlike/blob/main/Classes/BossMonsterController.h) / [BossMonsterController.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/BossMonsterController.cpp)]

<br>

---

<br>

### **스킬**

+ SkillBook
  + 플레이어 및 몬스터가 사용할 스킬들을 관리하는 클래스
  + 스킬 추가, 가져오기, 반복적인 스킬 멈추기, 순차적 스킬 작동 기능 구현

[[SkillBook.h](https://github.com/k660323/Meserlike/blob/main/Classes/SkillBook.h) / [SkillBook.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/SkillBook.cpp)]

<br>

+ SkillBase
  + 스킬 클래스의 기초가 되는 클래스
  + 스킬 레벨과 레벨에 따른 스텟, 스킬 소유자 등 여러 클래스에서 사용할 기능들을 구현한 클래스

[[SkillBase.h](https://github.com/k660323/Meserlike/blob/main/Classes/SkillBase.h) / [SkillBase.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/SkillBase.cpp)]

<br>

+ RepeatSkill
  + SkillBase를 상속받은 클래스
  + 반복적인 스킬을 사용하는 기초 클래스
  + 반복동작을 담당하는 델리게이트 함수 Action을 매개변수로 가진다.
 
  **스킬 동작**
  1. SkillBook클래스에서 AddSkill() 함수 호출하여 RepeatSkill을 상속받은 클래스 객체 생성
  2. 객체 생성 후 ActivateSkill() 함수 호출
  3. ActivateSkill()함수는 StartSkillAction(), 스킬 쿨타임을 하나의 시퀀스 액션으로 만들어 Action 매개변수에 담아 반복 실행한다.

  **실직적인 동작은 StartSkillAction()안의 DoSkillJob()함수를 호출하여 동작한다. 즉 DoSkillJob()에서 구체적인 동작을 구현해야 한다.**

[[RepeatSkill.h](https://github.com/k660323/Meserlike/blob/main/Classes/RepeatSkill.h) / [RepeatSkill.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/RepeatSkill.cpp)]

<br>

+ SequenceSkill
  + SkillBase를 상속받은 클래스
  + 순차적으로 스킬을 사용하는 기초 클래스
  + 스킬 사용이 끝나면 알려줄 사용자 지정 클래스인 DelegateAction을 매개변수로 가진다.
 
  **스킬 동작**
  1. SkillBook클래스에서 AddSkill() 함수 호출하여 SequenceSkill 상속받은 클래스 객체 생성
  2. 객체 생성 후 DoSKill() 함수 호출
  3. 해당 클래스는 부모 클래스 호출 후 실행 및 스케줄러에 등록해준다.
  4. 함수 수행 조건을 만족하면 스케줄러를 제거하고 매개변수로 받은 callback함수를 호출한다.
  5. callback함수는 SkillBook의 OnFinishedSequenceSKill()이며 다음 SequenceSkill을 수행하게 해준다.

[[SequenceSkill.h](https://github.com/k660323/Meserlike/blob/main/Classes/SequenceSkill.h) / [SequenceSkill.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/SequenceSkill.cpp)]

<br>

+ PassiveSkill
  + SkillBase를 상속받은 클래스
  + 단순히 플레이어 및 몬스터의 능력치를 영구적으로 올려주는 클래스

[[PassiveSkill.h](https://github.com/k660323/Meserlike/blob/main/Classes/PassiveSkill.h) / [PassiveSkill](https://github.com/k660323/Meserlike/blob/main/Classes/PassiveSkill.cpp)]

<br>

+ SkillDefine
  + Skill을 추가하기 위한 유틸 함수
  + ENum으로 정의된 SkillID에 따라 지정된 스킬 객체를 만들어 반환해주는 클래스

[[SkillDefine.h](https://github.com/k660323/Meserlike/blob/main/Classes/SkillDefine.h)]

<br>

---

<br>

### **무기**

+ Weapon
  + SkillBook에 스킬을 등록시 생성되는 무기 오브젝트를 담당하는 클래스 입니다.
  + 게임 월드에 스폰되어 오브젝트를 공격합니다.
 
[[Weapon.h](https://github.com/k660323/Meserlike/blob/main/Classes/Weapon.h) / [Weapon.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Weapon.cpp)]

<br>

+ Melee
  + Weapon 클래스를 상속받은 클래스
  + 근접 공격을 담당
  + 충돌 함수가 가상 함수(onContactEnter, onContactExit)로 구현되어 있어 근접 공격을 구현할려면 이 클래스를 상속받아 구현한다.

[[Melee.h](https://github.com/k660323/Meserlike/blob/main/Classes/Melee.h) / [Melee.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Melee.cpp)]

<br>

+ Range
  + Weapon 클래스를 상속받은 클래스
  + 원거리 공격을 담당하여 투사체를 발사한다.
  + 물리 충돌을 감지하는 함수(DetectedNearObject) 가상 함수로 구현 되어 있고 공격 함수 Fire() 함수도 가상 함수로 구현 되어 있어 원거리 공격을 구현할라면 이 클래스를 상속받아 구현한다.

[[Range.h](https://github.com/k660323/Meserlike/blob/main/Classes/Range.h) / [Range.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Range.cpp)]

<br>

+ Projectile
  + 투사체 클래스
  + Range에서 스폰하는 원거리 공격 클래스이다.
  + 일정한 방향과 속도로 이동하는 투사체이다.
  + 생성자에서 초기화 하며 충돌 및 생명주기가 끝나면 자동으로 제거된다.
  + 원거리 투사체를 구현하고 싶으면 해당 클래스를 상속받아 구현하면 된다.

[[Projectile.h](https://github.com/k660323/Meserlike/blob/main/Classes/Projectile.h) / [Projectile.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Projectile.cpp)]


<br>

---

<br>

### **스탯**

+ Stat
  + Creature클래스가 사용하는 객체의 능력치를 관리하는 클래스
  + 각 능력치마다 Get,Set 함수 구현
  + 옵저버 패턴(DelegateAction라는 델리게이트 변수가 있어 함수를 미리 바인딩 해놓았으면 수치 변화에 따른 브로드 캐스팅이 가능하다.)
  + 필요에 따라 상속받아 추가 구현한다.

[[Stat.h](https://github.com/k660323/Meserlike/blob/main/Classes/Stat.h) / [Stat.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/Stat.cpp)]

<br>

---

<br>

### **애니메이션**

+ AnimateEx
  + Creature클래스가 사용하는 사용자 지정 애니메이션 클래스
  + 애니메이트 등록, 재생, 정지가 가능한 매니저 클래스
  + cocos2d-x는 스프라이트를 묶어서 하나의 애니메이트를 만들어 한번 실행이 끝이라 효율적으로 실행 및 재사용하기 위해 만든 클래스
 
[[AnimateEx.h](https://github.com/k660323/Meserlike/blob/main/Classes/AnimateEx.h) / [AnimateEx.cpp](https://github.com/k660323/Meserlike/blob/main/Classes/AnimateEx.cpp)]


<br>

---

<br>

### **기타**

+ Utils 클래스
  + 각종 기능들을 static함수로 구현하여 자주 사용하는 함수들을 쉽게 접근하여 사용하기 위한 클래스 모음집

  **구현 기능**
  + 비율에 맞게 UI를 배치하기 위한 함수 기능 구현
  + DataManager에 있는 애니메이션 데이터 가지고 애니메이션을 생성해주는 함수 구현
  + 이미지 경로 및 사이즈만 입력하여 애니메이션을 생성해주는 함수 구현
  + 두 방향 벡터에 따른 각도를 반환해주는 함수 구현
  + etc...

[[Utils.h](https://github.com/k660323/Meserlike/blob/main/Classes/Utils.h)]

<br>

+ Define 클래스
  + 각종 매크로 함수 정의 및 Enum을 정의한 클래스

[[Define.h](https://github.com/k660323/Meserlike/blob/main/Classes/Define.h)]

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

+ Cocos2d 충돌은 Dispatcher에 바인딩하는 방식이라 충돌시 바인딩된 모든 함수가 호출되서 예상치 못한 충돌 처리가 되서 오작동되는 경우가 발생했습니다.
  + 예외 처리를 둬서 매개변수로 오는 충돌 객체와 해당 객체와 비교하여 충돌처리하도록 처리했습니다. 
 
## 6. 느낀점
+ 상용엔진에서 제공하는 유틸 함수 툴 기능을 직접 구현하다 보니 게임 구조에 대해 좀 더 깊이 있게 이해가 되었습니다.


## 7. 플레이 영상
+ https://www.youtube.com/watch?v=zycwzQuWkkU
