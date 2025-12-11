#include "renju.h"

#define GRID 3
#define IS_BOUNDARY(x, limit) (((x==0)||(x==limit))?(true):(false))

ChessBoard::ChessBoard(int num, Ctrl *parent): Ctrl(parent) {
  int height=num*GRID+1, width=num*GRID*2+1;
  this->num=num;
  this->x=this->y=num/2;
  this->height=height;
  this->width=width;
  for(int i=0; i<height; i++) {
	for(int j=0; j<width; j++) {
	  if(IS_BOUNDARY(i, height-1) && IS_BOUNDARY(j, width-1)) {
	    data[i][j]='+';
	  } else if(IS_BOUNDARY(i%GRID, height-1) && IS_BOUNDARY(j%(GRID*2), width-1)) {
		data[i][j]='+';
	  } else if(IS_BOUNDARY(i, height-1)) {
        data[i][j]='-';
	  } else if(IS_BOUNDARY(j, width-1)) {
		data[i][j]='|';
	  } else if(IS_BOUNDARY(i%GRID, height-1)) {
		data[i][j]='-';
	  } else if(IS_BOUNDARY(j%(GRID*2), width-1)) {
		data[i][j]='|';
	  } else {
	    this->data[i][j]=0;
	  }
	}
  }

  this->shape[0]='O';
  this->shape[1]='X';
  this->current=0;
}

void ChessBoard::toShow(int focus) {
  for(int i=0; i<this->height; i++) {
    for(int j=0; j<this->width; j++) {
	  this->setCursor(this->pos.X+j, this->pos.Y+i);
      if(this->data[i][j]) {
        printf("%c", this->data[i][j]);
	  } else {
		printf(" ");
	  }
	}
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0070);
  this->setCursor(this->pos.X+this->x*GRID*2, this->pos.Y+this->y*GRID);
  printf("%c", this->data[this->y*GRID][this->x*GRID*2]);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}

int ChessBoard::Up() {
  if(this->y<=0) {
    return 0;
  }
  this->y--;
  return 1;
}

int ChessBoard::Down() {
  if(this->y>=this->num) {
    return 0;
  }
  this->y++;
  return 1;
}

int ChessBoard::Left() {
  if(this->x<=0) {
    return 0;
  }
  this->x--;
  return 1;
}

int ChessBoard::Right() {
  if(this->x>=this->num) {
    return 0;
  }
  this->x++;
  return 1;
}

int ChessBoard::Enter() {
  if(this->data[this->y*GRID][this->x*GRID*2]!='+') {
	return 0;
  }
  this->data[this->y*GRID][this->x*GRID*2]=this->shape[this->current];
  if(this->isWin(this->x, this->y)) {
	return -1;
  }
  this->current=!this->current;
  return 1;
}

bool ChessBoard::isWin(int x, int y) {
  char c=this->data[y*GRID][x*GRID*2];
  for(int i=-1;i<=1;i++) {
    for(int j=-1;j<=1;j++) {
	  if(i==0 && j==0) {
		continue;
	  }

	  int count=0;
	  for(int p=0;p<5;p++) {
		int m=(y+i*p)*GRID;
		int n=(x+j*p)*GRID*2;
		if(x+j*p < 0 || y+i*p < 0 || x+j*p > num || y+i*p > num) {
		  break;
		}
		if(this->data[m][n] == c) {
		  count++;
		} else {
		  break;
		}
	  }
	  if(count==5) {
		return true;
	  }
	}
  }
  return false;
}