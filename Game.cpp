#include "Game.h"

const uint8_t globalGame(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score, int &lives, int &level) {
  testCollisionsBullets(player, centipede, mushrooms, score);

  if(centipedeDead(centipede)) {
    spawnCentipede(centipede);
    level++;
  }

  if(playerHitted(player, centipede)) {
    lives--;
    gb.lights.setColor(RED);
    gb.lights.drawRect(0, 0, 1, 4);
    gb.lights.drawRect(1, 0, 1, 4);

    delay(1000);

    player.point.x = gb.display.width() / 2;
    player.point.y = gb.display.height() - 7;

    spawnCentipede(centipede);

    if(lives == 0) {
      return HOME_STATE;
    }
  }

  return PLAY_STATE;
}

void testCollisionsBullets(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score) {
  for(int i = 0; i < NUM_PLAYER_BULLETS; i++) {
    if(player.bullets[i].enabled) {
      for(int j = 0; j < NB_BLOCKS; j++) {
        if(centipede[j].alive) {
          if (gb.collide.rectRect(player.bullets[i].point.x, player.bullets[i].point.y, 1, 2, centipede[j].point.x, centipede[j].point.y, CENTIPEDE_SIZE, CENTIPEDE_SIZE)) {
            //gb.sound.playOK();
            centipede[j].alive = false;
            player.bullets[i].enabled = false;

            spawnMushroom(mushrooms, centipede[j].point.x, centipede[j].point.y);

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


void spawnMushroom(Mushroom * mushrooms, int x, int y) {
   for (int i = 0; i < NB_MUSHROOMS_MAX; i++) {
    if (mushrooms[i].life == 0) {
      mushrooms[i].life = 3;
      mushrooms[i].point.x = x;
      mushrooms[i].point.y = y;
      break;
    }
  }
}

void spawnCentipede(CentipedeBlock * centipede) {
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

bool centipedeDead(CentipedeBlock * centipede) {
  for(int i = 1; i < NB_BLOCKS; i++) {
    if(centipede[i].alive) {
      return false;
    }
  }

  return true;
}

bool playerHitted(Player &player, CentipedeBlock * centipede) {
  for(int i=0; i<NB_BLOCKS; i++) {
    if(centipede[i].alive) {
      if (gb.collide.rectRect(player.point.x, player.point.y, PLAYER_WIDTH, PLAYER_HEIGHT, centipede[i].point.x, centipede[i].point.y, CENTIPEDE_SIZE, CENTIPEDE_SIZE)) {
        return true;
      }
    }
  }
}
