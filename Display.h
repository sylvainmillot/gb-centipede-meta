#include <Gamebuino-Meta.h>

#include "Constants.h"

void draw(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score);

const uint8_t drawMenu();
void drawBackground();
void drawPlayer(Player &player);
void drawBullets(Player &player);
void drawCentipede(CentipedeBlock * centipede);
void drawMushrooms(Mushroom * mushrooms);
void drawScore(int &score);


