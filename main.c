#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

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

int getPosPlayer() {
  int count;
  for (int n=0; n<HEIGHT; n++) {
    if (playground[n][0] == PLAYER_SHIP) {
      return n;
    } else { count++; }
  }
  if (count == HEIGHT-1) {return 10;} //case where the ship disapeared
}

void spawnRandomAst() {
  struct asteroide asteroide = {rand() % HEIGHT, SIGHT-1};
  playground[asteroide.x][asteroide.y] = '*';

}

void moveAst() {
  for (int l=0; l<HEIGHT; l++) {

    for (int c=0; c<SIGHT; c++) {

      if (playground[l][c] == '*') {
        if (c == 0)
        {
          playground[l][c-1] = ' ';
          playground[l][c] = ' ';
        }
        else
        {
          playground[l][c-1] = '*';
          playground[l][c] = ' ';
        }

      }
    }
  }
}

int isOnAst() {
  int posPlayer = getPosPlayer();
  if (playground[posPlayer][0] == '*' || posPlayer == 10) {
    return 1;
  } else {
    return 0;
  }
}

void moveShoot() {
  for (int l=HEIGHT; l>0; l--) {
    for (int c=SIGHT; c>0; c--) {
      if (playground[l][c] == PLAYER_MISSILE) {
        if (c == SIGHT-1)
        {
          playground[l][c+1] = ' ';
          playground[l][c] = ' ';
        }
        else
        {
          playground[l][c+1] = '-';
          playground[l][c] = ' ';
        }
      }
    }
  }

}

void shoot(int playerPos) {
  struct missile missile = {playerPos, 2};
  playground[missile.x][missile.y] = PLAYER_MISSILE;

}

void movePlayer (int dirX) {

  int posPlayer = getPosPlayer();

  if (posPlayer <= 0 && dirX == -1) {
    printf("sorry you cant move in that direction\n\n");
    return;
  } else if (posPlayer >= HEIGHT && dirX == 1) {
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

int getKey () {
  int stop = 1;
  while( !_kbhit() ){
    switch(_getch())
    {
      case 'z':
        movePlayer(-1);
        moveAst();
        moveShoot();
        break;
      case 's':
        movePlayer(1);
        moveAst();
        moveShoot();
        break;
      case ' ':
        moveShoot(); 
        shoot(getPosPlayer());
        break;
      case 27:
        stop = 2;
        break;
    }
    break;
  } //gets keyboard key and moves player
  if (stop == 1) { return 1;}
  else if (stop == 2) { return 2;}
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
  printf("*We deeply thank Vincent Altmann (GTech1) for his contribution");
  srand(time(0));
  
  int game = 0;
  int stop = 0;
  int delay = 5;
  initGame();
  while (game != 1)
    {
      system("cls");
      dispGame(); 
      //system("clear");
      if (delay >= 5 ) {
        spawnRandomAst();
        delay = 0;
      }
      game = isOnAst(); 
      if ((stop = getKey()) == 1) { delay++;}
      else if ((stop = getKey()) == 2) { game = 1; } 
      game = isOnAst(); 
    }
  return 0;
}
  