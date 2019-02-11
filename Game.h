#include <Gamebuino-Meta.h>

#include "Constants.h"

const uint8_t globalGame(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score, int &lives, int &level);
void testCollisionsBullets(Player &player, CentipedeBlock * centipede, Mushroom * mushrooms, int &score);
void spawnMushroom(Mushroom * mushrooms, int x, int y);
void spawnCentipede(CentipedeBlock * centipede);
bool centipedeDead(CentipedeBlock * centipede);
bool playerHitted(Player &player, CentipedeBlock * centipede);
