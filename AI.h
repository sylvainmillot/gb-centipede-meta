#include <Gamebuino-Meta.h>

#include "Constants.h"

void runAI(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &level);
void moveBullets(Player &player);
void moveCentipede(CentipedeBlock * centipede, Mushroom * mushrooms, int &level);
bool xCollision(CentipedeBlock * centipede, Mushroom * mushrooms, int i);
bool yCollision(CentipedeBlock * centipede, Mushroom * mushrooms, int i);
