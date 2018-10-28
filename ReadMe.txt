본 게임은 맵을 다니며 아이템을 획득하고, 총을 발사하여 적 몬스터를 모두 쓰러뜨리면 승리하는 게임이다.

본 프로그램을 실행하기 위해서는 Grahics Assn.sln 파일을 실행하여야 하며 x86 버전에서 디버깅 혹은 릴리즈 하여야 한다.

본 게임의 플레이 방법은 다음과 같다.

키보드의 상하좌우 방향키를 이용하여 플레이어 캐릭터를 움직일 수 있다.

또한 스페이스바를 눌러 총알을 발사하여 적 몬스터를 사살할 수 있다. 

<File Description>
1. main.cpp
GLUT을 초기화 하고, 창을 띄우기 위한 display, reshape 함수와, keystroke을 처리하는 함수들이 구현되어있다.

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