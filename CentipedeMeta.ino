#include <Gamebuino-Meta.h>

#include "Constants.h"
#include "Controls.h"
#include "AI.h"
#include "Display.h"



int h = gb.display.width() / 2;
int v = gb.display.height() - 3;
int score = 0;


CentipedeBlock centipede[NB_BLOCKS];
Mushroom mushrooms[NB_MUSHROOMS_MAX];
Player player;


void setup() {
  gb.begin();

  initGame();
}

void initGame() {
  score = 0;
  
  spawnCentipede();

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

  if (gb.buttons.pressed(BUTTON_MENU)) {
    initGame();
  }


  runAI(player, centipede, mushrooms);
  controls(player);
  draw(player, centipede, mushrooms, score);

  testCollisions();

  if(centipedeDead()) {
    spawnCentipede();
  }
}







void spawnMushroom(int x, int y) {
   for (int i = 0; i < NB_MUSHROOMS_MAX; i++) {
    if (mushrooms[i].life == 0) {
      mushrooms[i].life = 3;
      mushrooms[i].point.x = x;
      mushrooms[i].point.y = y;
      break;
    }
  }
}

void spawnCentipede() {
  centipede[0].point.x = 0;
  centipede[0].point.y = 0;
  centipede[0].direction.x = 1;
  centipede[0].direction.y = 1;
  centipede[0].alive = true;
  centipede[0].linked = -1;

  for(int i = 1; i < NB_BLOCKS; i++) {
    centipede[i].point.x = centipede[i-1].point.x - 1 - CENTIPEDE_SIZE;
    centipede[i].point.y = centipede[0].point.y;
    centipede[i].direction.x = 1;
    centipede[i].direction.y = 1;
    centipede[i].alive = true;
    centipede[i].linked = i-1;
  }
}

bool centipedeDead() {
  for(int i = 1; i < NB_BLOCKS; i++) {
    if(centipede[i].alive) {
      return false;
    }
  }

  return true;
}

void testCollisions() {
  for(int i = 0; i < NUM_PLAYER_BULLETS; i++) {
    if(player.bullets[i].enabled) {
      for(int j = 0; j < NB_BLOCKS; j++) {
        if(centipede[j].alive) {
          if (gb.collide.rectRect(player.bullets[i].point.x, player.bullets[i].point.y, 1, 2, centipede[j].point.x, centipede[j].point.y, CENTIPEDE_SIZE, CENTIPEDE_SIZE)) {
            //gb.sound.playOK();
            centipede[j].alive = false;
            player.bullets[i].enabled = false;

            spawnMushroom(centipede[j].point.x, centipede[j].point.y);

            score+= SCORE_CENTIPEDE;
          }
        }    
      }

      if(player.bullets[i].enabled) {
        for(int j = 0; j != NB_MUSHROOMS_MAX; j++) {
          if(mushrooms[j].life > 0) {
            if (gb.collide.rectRect(player.bullets[i].point.x, player.bullets[i].point.y, 1, 2, mushrooms[j].point.x, mushrooms[j].point.y, CENTIPEDE_SIZE, CENTIPEDE_SIZE)) {
              player.bullets[i].enabled = false;
              
              mushrooms[j].life--;
    
              if(mushrooms[j].life == 0) {
                //gb.sound.playOK();
                score+= SCORE_MUSHROOM;
              }
            }
          }
        }
      }
    }
  }
}

