#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include <math.h>
#include <time.h>

#define PLAYER_SHIP '>'
#define PLAYER_MISSILE '-'
#define SIGHT 23
#define HEIGHT 7
#define ESC 27


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

int getPosPlayer() {
  for (int n=0; n<HEIGHT; n++) {
    if (playground[n][0] == '>') {
      return n;
    }
  }
}

void movePlayer (int dirX) {

  int posPlayer = getPosPlayer();

  if (posPlayer < 0 || posPlayer > HEIGHT) {
    printf("sorry you cant move in that direction\n\n");
    return;
  }

  switch (dirX) {
    case -1:
      playground[posPlayer][0] = ' ';
      playground[posPlayer + dirX][0] = '>';
      break;

    case 1:
      playground[posPlayer][0] = ' ';
      playground[posPlayer + dirX][0] = '>';
      break;
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
  printf("\n");
  

}

int main() {
  
  srand(time(0));
  
  int game = 0;
  int delay = 5;
  initGame();
  dispGame();
  while (game != 1)
    {
      //system("clear");
      if (delay == 5 ) {
        spawnRandomAst();
        delay = 0;
      }
      char frappe;
        while( !_kbhit() ){

          switch(_getch())
          {
            case 'z':
              movePlayer(-1);
              moveAst();
              delay++;
              break;
            case 's':
              movePlayer(1);
              moveAst();
              delay++;
              break;
            case 27:
              game = 1;
              break;
          }
         break;

        }
      dispGame();
    }
  return 0;
}
  