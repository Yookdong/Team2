# Team Project
# GOYO Base on the Moon
- [YouTube](https://youtu.be/xiD04p96tTI?feature=shared)
- [PPT](https://pitch.com/embed/c8171681-0bc9-4358-bc47-825c9b42e1d2/f85780fc-bd37-414e-a218-140ff49f3ee0?controls-mode=chin&share=true)

## 프로젝트 소개
멀티 기반 방 탈출 게임

### 멤버 구성
- 육동혁 : Main Developer / QA
- 김찬영 : Sub Delveloper / QA
- 이재학 : PM / Level & Concept Designer
- 여범구 : Delveloper / AI / Video Creater

### 개발 환경
- `C++`
- `Unreal Engine 5.2`
- `Visual Studio 2022`
- `Photo Shop 2022`
- `Premiere Pro 2021`

### 주요 기능
#### Session Create / Find / Join
- 언리얼이 제공하는 session기능 활용 -> 추후 FSOCKET을 이용한 TCP 서버로 교체 예정

#### Game Instance를 이용한 데이터 동기화 작업
- Lobby Level에서 선택한 캐릭터의 정보를 InGame Level로 넘겨 줌

#### Laser Reflection
- Interface를 활용하여 actor 간의 상호작용
- 해당 머터리얼을 검출하여 레이저의 반사와 굴절을 구현함

#### AI
- 시야와 사운드에 영향을 받음

#### Meta Human
- 캐릭터의 대사 장면 촬영

#### Niagara VFX System 
