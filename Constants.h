#ifndef CONSTANTS
#define CONSTANTS

const uint8_t HOME_STATE = 1;
const uint8_t LAUNCH_PLAY_STATE = 2;
const uint8_t PLAY_STATE = 3;
const uint8_t ENDGAME_STATE = 4;
const uint8_t HIGHSCORES_STATE = 5;

const uint8_t PLAYER_WIDTH = 5;
const uint8_t PLAYER_HEIGHT = 6;

const uint8_t MAX_LIVES = 3;

const uint16_t playerData[] = {5,6,1, 1, 0x0A, 0, 0x0,0x1081,0xf798,0x1082,0x0,0x1000,0xc227,0xffb8,0xca68,0x1800,0xdd50,0xf800,0xff78,0xf800,0xdccf,0xe737,0xfff9,0xfff9,0xfff9,0xe737,0x10a2,0xc634,0xfff9,0xce74,0x18e3,0x0,0x8c6e,0xfff9,0x9cf0,0x0};
const uint16_t mushroomData[] = {4,4,1, 1, 0, 0, 0x3800,0x7be0,0x7be0,0x3800,0x7be0,0x7e0,0x7e0,0x7be0,0x7800,0xb9e0,0xb9e0,0x7800,0x0,0xb9e0,0xb9e0,0x0};
const uint16_t centipedeData_right[] = {4,4,1, 1, 0, 0, 0xf800,0x7e0,0x7e0,0x0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0xf800,0x7e0,0x7e0,0x0};
const uint16_t centipedeData_left[] = {4,4,1, 1, 0, 0, 0x0,0x7e0,0x7e0,0xf800,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x7e0,0x0,0x7e0,0x7e0,0xf800};

const int SCORE_CENTIPEDE = 10;
const int SCORE_MUSHROOM = 1;

const int NB_BLOCKS = 12;
const int CENTIPEDE_SPEED_X = 1;
const int CENTIPEDE_SPEED_Y = 5;
const int CENTIPEDE_SIZE = 4;

const int NUM_PLAYER_BULLETS = 10;



const int NB_MUSHROOMS_MAX = 150;


struct Point {
  float x;      
  float y;      
};

struct PlayerBullet {
  Point point;
  boolean enabled;
};

struct Player {
  Point point;
  PlayerBullet bullets[NUM_PLAYER_BULLETS];
};

struct CentipedeBlock {
  Point point;
  Point direction;
  bool alive;
  int linked = 0;
};

struct Mushroom {
  Point point;
  int life = 0;
};

#endif
