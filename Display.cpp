#include "Display.h"

Image player_image = Image(playerData);
Image mushroom_image = Image(mushroomData);
Image centipede_right_image = Image(centipedeData_right);
Image centipede_left_image = Image(centipedeData_left);

void draw(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score) {
  // drawBackground();
  drawBullets(player);
  drawPlayer(player);
  drawCentipede(centipede);
  drawMushrooms(mushrooms);
  drawScore(score);
}

void drawBackground() {
  gb.display.setColor(GREEN);
  gb.display.fillRect(0,0,gb.display.width(),gb.display.height());
}

void drawPlayer(Player &player) {
  //gb.display.setColor(YELLOW);
  //gb.display.fillRect(player.point.x, player.point.y, 3, 3);
  //gb.display.setColor(RED);
  //gb.display.fillRect(player.point.x+1, player.point.y-1, 1, 1);

  gb.display.drawImage(player.point.x, player.point.y, player_image);
}

void drawBullets(Player &player) {
  for (int i = 0; i < NUM_PLAYER_BULLETS; i++) {
    if (player.bullets[i].enabled) {
      gb.display.drawRect(player.bullets[i].point.x, player.bullets[i].point.y, 1, 2);
    }
  }
}

void drawCentipede(CentipedeBlock * centipede) {
  for(int i=0; i<NB_BLOCKS; i++) {
    /*if(centipede[i].alive) {
      if(centipede[i].linked == -1 || !centipede[centipede[i].linked].alive) {
        gb.display.setColor(RED);
      }else {
        gb.display.setColor(GREEN);
      }
      gb.display.fillRect(centipede[i].point.x, centipede[i].point.y, CENTIPEDE_SIZE, CENTIPEDE_SIZE);
    }*/

    if(centipede[i].alive) {
      if(centipede[i].direction.x > 0) {
        gb.display.drawImage(centipede[i].point.x, centipede[i].point.y, centipede_right_image);
      }else {
        gb.display.drawImage(centipede[i].point.x, centipede[i].point.y, centipede_left_image);
      }
    }
  }
}

void drawMushrooms(Mushroom * mushrooms) {
  for(int i=0; i<NB_MUSHROOMS_MAX; i++) {
    if(mushrooms[i].life > 0) {
      //gb.display.setColor(BROWN);
      //gb.display.fillRect(mushrooms[i].point.x, mushrooms[i].point.y, CENTIPEDE_SIZE, CENTIPEDE_SIZE);

      gb.display.drawImage(mushrooms[i].point.x, mushrooms[i].point.y, mushroom_image);
    }
  }
}

void drawScore(int &score) {
  gb.display.setColor(WHITE);
  gb.display.setCursor(2, 2);
  gb.display.print(score);
}
