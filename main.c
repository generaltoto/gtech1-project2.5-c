#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define PLAYER_SHIP '>'
#define PLAYER_MISSILE '-'
#define SIGHT 23
#define HEIGHT 7


char playground[HEIGHT][SIGHT];

struct asteroide{
  int x;
  int y;
  
};

struct missile{
  int x;
  int y;
  
};


void spawnRandomAst() {
  struct asteroide asteroide = {rand() % HEIGHT, SIGHT-1};
  playground[asteroide.x][asteroide.y] = '*';

}

void moveAst() {
  for (int l=0; l<HEIGHT; l++) {

    for (int c=0; c<SIGHT; c++) {

      if (playground[l][c] == '*') {
        playground[l][c-1] = '*';
        playground[l][c] = ' ';
      }
    }
  }
}

void initGame() {
  int playerInitPos = floor(HEIGHT/2);
  //printf(" %i ", &playerInitPos]);
  for(int l=0; l<HEIGHT; l++) {
    
    for(int c=0; c<SIGHT; c++) {
      
      if (l == playerInitPos && c == 0) {
        
        playground[l][c] = PLAYER_SHIP;
        
      } else {
        
        playground[l][c] = ' ';
        
      }
    }
  }
}

void dispGame() {
  for (int n=0; n<SIGHT; n++) { printf(" - "); }
  printf("\n");
  
  for (int l=0; l<HEIGHT; l++) {
    for (int c=0; c<SIGHT; c++) {
      printf(" %c ", playground[l][c]);
    }
    printf("\n");
  }
  
  for (int n=0; n<SIGHT; n++) { printf(" - "); }
  printf("\n\n\n\n");

}

int main() {
  
  srand(time(0));
  
  int game = 0;
  int delay = 5;
  initGame();
  dispGame();
  while (game != 1)
    {
      //system('clear');
      moveAst();
      if (delay != 5 ) {delay++;}
      else {
        spawnRandomAst();
      }
      dispGame();
      game = 1;
      
    }
  return 0;
}
  