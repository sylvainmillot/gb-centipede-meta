#include "Controls.h"

int playerVLimitTop = gb.display.height() - 24;
int playerVLimitBottom = gb.display.height() - 8;
int playerHLimitRight = gb.display.width() - 7;
int playerHLimitLeft = 1;

int speed = 2;

void controls(Player &player) {
  movePlayer(player);
}

void movePlayer(Player &player) {
  if (gb.buttons.repeat(BUTTON_RIGHT, 0)) {
    if(player.point.x < playerHLimitRight) {
      player.point.x+=speed;
    }
  }

  if (gb.buttons.repeat(BUTTON_LEFT, 0)) { 
    if(player.point.x > playerHLimitLeft) {
      player.point.x-=speed;
    }
  }

  if (gb.buttons.repeat(BUTTON_UP, 0)) { 
    if(player.point.y > playerVLimitTop) {
      player.point.y-=speed;  
    }
  }

  if (gb.buttons.repeat(BUTTON_DOWN, 0)) { 
    if(player.point.y < playerVLimitBottom) {
      player.point.y+=speed;  
    }
  }

  if(gb.buttons.repeat(BUTTON_A, 3) || gb.buttons.repeat(BUTTON_B, 3)) {
    for (int i = 0; i < NUM_PLAYER_BULLETS; i++) {
      if (!player.bullets[i].enabled) {
        //gb.sound.playTick();
        spawnBullet(player, i);
        break;
      }
    }
  }
}

void spawnBullet(Player &player, int i) {
  player.bullets[i].enabled = true;
  player.bullets[i].point.x = player.point.x + 2;
  player.bullets[i].point.y = player.point.y - 3;
}
