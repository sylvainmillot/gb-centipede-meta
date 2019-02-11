#include <Gamebuino-Meta.h>

#include "Constants.h"
#include "Controls.h"
#include "AI.h"
#include "Game.h"
#include "Display.h"

uint8_t stateOfGame;

int h = gb.display.width() / 2;
int v = gb.display.height() - 3;
int score = 0;
int lives = 0;
int level = 1;

CentipedeBlock centipede[NB_BLOCKS];
Mushroom mushrooms[NB_MUSHROOMS_MAX];
Player player;


void setup() {
  gb.begin();

  stateOfGame = HOME_STATE;

  initGame();
}

void initGame() {
  score = 0;
  level = 1;
  lives = MAX_LIVES;
  
  spawnCentipede(centipede);

  for(int i = 0; i < NB_MUSHROOMS_MAX; i++) {
    mushrooms[i].life = 0;
    mushrooms[i].point.x = mushrooms[i].point.y = 0;
  }

  player.point.x = gb.display.width() / 2;
  player.point.y = gb.display.height() - 7;

  for (int i = 0; i < NUM_PLAYER_BULLETS; i++) {
    player.bullets[i].enabled = false;
    player.bullets[i].point.x = 0;
    player.bullets[i].point.y = 0;
  }
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  gb.lights.clear();

  if (gb.buttons.pressed(BUTTON_MENU)) {
    initGame();
  }

  switch(stateOfGame) {
    case HOME_STATE:
      stateOfGame = drawMenu();
      break;
      
    case LAUNCH_PLAY_STATE:
      initGame();
      stateOfGame = PLAY_STATE;
      break;
      
    case PLAY_STATE:
      stateOfGame = gameCommands();
    
      runAI(player, centipede, mushrooms, level);
      controls(player);
      draw(player, centipede, mushrooms, score, lives);
      stateOfGame = globalGame(player, centipede, mushrooms, score, lives, level);
      
      break;
  }
  
  //gb.lights.fill(BLACK);
}
