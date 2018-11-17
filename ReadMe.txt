본 게임은 맵을 다니며 아이템을 획득하고, 총을 발사하여 적 몬스터를 모두 쓰러뜨리면 승리하는 게임이다.

본 프로그램을 실행하기 위해서는 Grahics Assn.sln 파일을 실행하여야 하며 x86 버전에서 디버깅 혹은 릴리즈 하여야 한다.

본 게임의 플레이 방법은 다음과 같다.

키보드의 w키를 이용하여 플레이어를 직진시킬 수 있다.

키보드의 a, d키를 이용하여 플레이어의 이동 방향을 바꿀 수 있다.

또한 마우스 왼쪽 버튼을 클릭하여 총알을 발사하여 적 몬스터를 사살할 수 있다. 

스페이스바를 클릭하여 시점을 3인칭에서 1인칭으로 1인칭에서 3인칭으로 변경할 수 있다.

플레이어에게는 2개의 라이프가 주어지며 이를 다 소진할 시 패배하게 된다.

맵에 랜덤하게 위치한 아이템을 줍게 되면 라이프가 늘어나며 이는 우측 하단의 라이프/인벤토리 창에서 확인 가능하다.

우측 상단에 표시되는 제한시간 내에 게임을 클리어하지 못해도 패배한다.

게임 종료 후 R키를 누르면 재시작 할 수 있다.

<File Description>
1. test.cpp
GLSL을 초기화 하며 쉐이더를 호출한다. OBJ 파일을 읽으며 Key stroke, Mouse Event에 대한 처리를 하는 클래스이다.

2.Entity.h/Entity.cpp
Bullet,Enemy, Player의 부모 클래스이다.

3.Bullet.h/Bullet.cpp
게임에서 총알에 대응되는 클래스이다.

4.Enemy.h/Enemy.cpp
게임에서 몬스터에 대응되는 클래스이다.

5.Player.h/Player.cpp
게임에서 플레이어에 대응되는 클래스이다.

6.Map.h/Map.cpp
전체적인 게임을 관리하는 클래스이다.

7.display.h/display.cpp
Shader를 이용하여 그림을 그리는 함수와 변수의 집합이다.

8.Node.h
계층모델을 구성할 node이다. --> 본 어싸인에서는 사용하지 않는다.

9.sevenseg.h/sevenseg.cpp
숫자를 표현하는 7-segment와 관련된 함수들이다.

10.sixtennseg.h/sixtennseg.cpp
문자를 표현하는 16-segment와 관련된 함수들이다.

11.vshader1.glsl
ctm을 받아 position을 output으로 주는 vertex shader이다.

12.fshader1.glsl
fragment의 color를 ouput으로 주는 fragment shader이다.

13. OBJ files
OBJ 파일들과 mtl 파일들이 저장되어 있는 폴더로 mesh를 로딩할 수 있는 폴더이다.