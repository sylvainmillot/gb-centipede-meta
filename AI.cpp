#include "AI.h"

void runAI(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &level) {
  moveBullets(player);
  moveCentipede(centipede, mushrooms, level);
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

void moveCentipede(CentipedeBlock * centipede, Mushroom * mushrooms, int &level) {
  // For each Centipede block
  for(int i=0; i<NB_BLOCKS; i++) {
    bool dontMoveX = false;

    // If the Centipede hits left or right side of the screen
    if(xCollision(centipede, mushrooms, i)) {
      // We change its "x" direction
      centipede[i].direction.x = -centipede[i].direction.x;

      // If the Centipede hits top or bottom of the screen 
      if(yCollision(centipede, mushrooms, i)) {
        // We change its "y" direction
        centipede[i].direction.y = -centipede[i].direction.y;

        // Don't move in "x" direction the next frame (seems it's not working?)
        dontMoveX = true;
      }

      centipede[i].point.y+= centipede[i].direction.y * CENTIPEDE_SPEED_Y;
    }

    if(!dontMoveX) {
      centipede[i].point.x+= centipede[i].direction.x * CENTIPEDE_SPEED_X;
    }
  }
}

bool xCollision(CentipedeBlock * centipede, Mushroom * mushrooms, int i) {
  bool screenCollision = false;
  bool centipedeCollision = false;
  bool mushroomCollision = false;

  // We first check screen collision
  screenCollision = ((centipede[i].direction.x > 0 && centipede[i].point.x + CENTIPEDE_SIZE + 1 >= gb.display.width()) || (centipede[i].direction.x < 0 && centipede[i].point.x - 1 <= 0));

  if(!screenCollision) {
    // Then, mushroom collision
    if(centipede[i].direction.x > 0) {
      for(int j = 0; j < NB_MUSHROOMS_MAX; j++) {
        if(mushrooms[j].life > 0) {
          if(centipede[i].point.x + CENTIPEDE_SIZE + 1 >= mushrooms[j].point.x && centipede[i].point.x + CENTIPEDE_SIZE + 1 <= mushrooms[j].point.x + CENTIPEDE_SIZE && centipede[i].point.y == mushrooms[j].point.y) {
            mushroomCollision = true;
          }
        } 
      }
    }else {
      for(int j = 0; j < NB_MUSHROOMS_MAX; j++) {
        if(mushrooms[j].life > 0) {
          if(centipede[i].point.x - 1 >= mushrooms[j].point.x && centipede[i].point.x - 1 <= mushrooms[j].point.x + CENTIPEDE_SIZE && centipede[i].point.y == mushrooms[j].point.y) {
            mushroomCollision = true;
          }
        } 
      }
    }

    if(!mushroomCollision) {
      // Then, Centipede collision

      // Source of bugs, maybe not necessary?
    }
  }
  
  return screenCollision || centipedeCollision || mushroomCollision;
}

bool yCollision(CentipedeBlock * centipede, Mushroom * mushrooms, int i) {
  bool screenCollision = false;
  bool centipedeCollision = false;
  bool mushroomCollision = false;
  
  screenCollision = ((centipede[i].direction.y > 0 && centipede[i].point.y + CENTIPEDE_SIZE + 1 >= gb.display.height()) || (centipede[i].direction.y < 0 && centipede[i].point.y - 1 <= 0));

  return screenCollision || centipedeCollision || mushroomCollision;
}


/*void old() {
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

}*/

