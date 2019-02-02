#include "AI.h"

void runAI(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms) {
  moveBullets(player);
  if(gb.frameCount % 2 == 0) {
    moveCentipede(centipede, mushrooms);
  }
}

void moveBullets(Player &player) {
  for (int i = 0; i < NUM_PLAYER_BULLETS; i++) {
    if(player.bullets[i].enabled) {
      if(player.bullets[i].point.y < 0) {
        player.bullets[i].enabled = false;
      }else {
        player.bullets[i].point.y-= 2;
      }
    }
  }
}

void moveCentipede(CentipedeBlock * centipede, Mushroom * mushrooms) {
  for(int i=0; i<NB_BLOCKS; i++) {
    bool dontMove = false;
    
    if((centipede[i].direction.y > 0 && centipede[i].point.y + CENTIPEDE_SIZE + 1 >= gb.display.height())
    || (centipede[i].direction.y < 0 && centipede[i].point.y - 1 <= 0)) {
      centipede[i].direction.y = -centipede[i].direction.y;
      centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
      dontMove = true;
    }else if((centipede[i].direction.x > 0 && centipede[i].point.x + CENTIPEDE_SIZE + 1 >= gb.display.width())
    || (centipede[i].direction.x < 0 && centipede[i].point.x - 1 <= 0)) {
      centipede[i].direction.x = -centipede[i].direction.x;
      centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
      dontMove = true;
    }else if(centipede[i].direction.x > 0) {
      for(int j = 0; j < NB_MUSHROOMS_MAX; j++) {
        if(mushrooms[j].life > 0) {
          if(centipede[i].point.x + CENTIPEDE_SIZE + 1 >= mushrooms[j].point.x 
             && centipede[i].point.x + CENTIPEDE_SIZE + 1 <= mushrooms[j].point.x + CENTIPEDE_SIZE 
             && centipede[i].point.y == mushrooms[j].point.y) {
            centipede[i].direction.x = -centipede[i].direction.x;
            centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
            dontMove = true;
          }
        } 
      }

      if(!dontMove) {
        for(int j = 0; j < NB_BLOCKS; j++) {
          if(centipede[j].alive && i != j) {
            if(centipede[i].point.x + CENTIPEDE_SIZE + 1 >= centipede[j].point.x 
               && centipede[i].point.x + CENTIPEDE_SIZE + 1 <= centipede[j].point.x + CENTIPEDE_SIZE 
               && centipede[i].point.y == centipede[j].point.y) {
              centipede[i].direction.x = -centipede[i].direction.x;
              centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
              dontMove = true;
            }
          } 
        }
      }
    }else if(centipede[i].direction.x < 0) {
      for(int j = 0; j < NB_MUSHROOMS_MAX; j++) {
        if(mushrooms[j].life > 0) {
          if(centipede[i].point.x - 1 >= mushrooms[j].point.x 
             && centipede[i].point.x - 1 <= mushrooms[j].point.x + CENTIPEDE_SIZE 
             && centipede[i].point.y == mushrooms[j].point.y) {
            centipede[i].direction.x = -centipede[i].direction.x;
            centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
            dontMove = true;
          }
        } 
      }

      if(!dontMove) {
        for(int j = 0; j < NB_BLOCKS; j++) {
          if(centipede[j].alive && i != j) {
            if(centipede[i].point.x - 1 >= centipede[j].point.x 
               && centipede[i].point.x - 1 <= centipede[j].point.x + CENTIPEDE_SIZE 
               && centipede[i].point.y == centipede[j].point.y) {
              centipede[i].direction.x = -centipede[i].direction.x;
              centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
              dontMove = true;
            }
          } 
        }
      }
    }

    if(!dontMove) {
      centipede[i].point.x+= centipede[i].direction.x * CENTIPEDE_SPEED_X;
    }
  }
}
