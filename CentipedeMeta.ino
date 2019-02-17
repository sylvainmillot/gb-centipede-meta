#include <Gamebuino-Meta.h>

#include "Constants.h"
#include "Controls.h"
#include "AI.h"
#include "Game.h"
#include "Highscore.h"
#include "Display.h"

extern const char g_highScoreName[] = "";
HighScore<int, 6, 13, g_highScoreName> g_highScore;
#define SAVE_HIGHSCORE 0

const SaveDefault savefileDefaults[] = {
  { SAVE_HIGHSCORE, SAVETYPE_BLOB, sizeof(g_highScore), 0 }
};

uint8_t stateOfGame;

int h = gb.display.width() / 2;
int v = gb.display.height() - 3;
int score = 0;
int lives = 0;
int level = 1;

CentipedeBlock centipede[NB_BLOCKS];
Mushroom mushrooms[NB_MUSHROOMS_MAX];
Player player;


void setup() {
  gb.begin();

  gb.save.config(savefileDefaults);
  gb.save.get(SAVE_HIGHSCORE, g_highScore);
  g_highScore.setTextColor(YELLOW);
  g_highScore.setBgColor(BLACK);

  stateOfGame = HOME_STATE;

  initGame();
}

void initGame() {
  score = 0;
  level = 1;
  lives = 3;
  
  spawnCentipede(centipede);

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
  gb.lights.clear();

  if (gb.buttons.pressed(BUTTON_MENU)) {
    initGame();
  }

  switch(stateOfGame) {
    case HOME_STATE:
      stateOfGame = drawMenu();
      break;
      
    case LAUNCH_PLAY_STATE:
      initGame();
      stateOfGame = PLAY_STATE;
      break;
      
    case PLAY_STATE:
      stateOfGame = gameCommands();
    
      runAI(player, centipede, mushrooms, level);
      controls(player);
      draw(player, centipede, mushrooms, score, lives);
      stateOfGame = globalGame(player, centipede, mushrooms, score, lives, level);
      
      break;
  
    case ENDGAME_STATE:
      {
        bool newHighScore = g_highScore.checkHighScore(score);
        g_highScore.showScore(score);
        if (newHighScore)  {
          g_highScore.updateHighscore(score);
          gb.save.set( SAVE_HIGHSCORE, g_highScore);
        }
        g_highScore.drawHighScores();
  
        if (gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B) || gb.buttons.pressed(BUTTON_MENU)) {
          stateOfGame = HOME_STATE;
        }
      }
      
      
      break;

    case HIGHSCORES_STATE:
      g_highScore.drawHighScores();

      if (gb.buttons.pressed(BUTTON_B)) {
        stateOfGame = HOME_STATE;
      }
      
      break;
  }
}
