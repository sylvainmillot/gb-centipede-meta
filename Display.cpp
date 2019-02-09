#include "Display.h"

Image player_image = Image(playerData);
Image mushroom_image = Image(mushroomData);
Image centipede_right_image = Image(centipedeData_right);
Image centipede_left_image = Image(centipedeData_left);

void draw(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score, int lives) {
  // drawBackground();
  drawBullets(player);
  drawPlayer(player);
  drawCentipede(centipede);
  drawMushrooms(mushrooms);
  drawScore(score, lives);
}

const uint8_t drawMenu() {
  const char* items[] = {
    "Play"
  };

  const uint8_t indexItem = gb.gui.menu("Centipede META", items);
  uint8_t choice = HOME_STATE;
  if(items[indexItem] == "Play") {
    choice = LAUNCH_PLAY_STATE;
  }
  return choice;
}

void drawBackground() {
  gb.display.setColor(GREEN);
  gb.display.fillRect(0,0,gb.display.width(),gb.display.height());
}

void drawPlayer(Player &player) {
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
      gb.display.drawImage(mushrooms[i].point.x, mushrooms[i].point.y, mushroom_image);
    }
  }
}

void drawScore(int &score, int lives) {
  gb.display.setColor(WHITE);
  gb.display.setCursor(2, 2);
  gb.display.print(score);

  int cursor = gb.display.width() - (MAX_LIVES * PLAYER_WIDTH) - MAX_LIVES*2;

  for(int i = 1; i <= lives; i++) {
    gb.display.drawImage(cursor , 1, player_image);

    cursor+= PLAYER_WIDTH + 2;
  }
  
}
