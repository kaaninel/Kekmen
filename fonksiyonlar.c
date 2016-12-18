/*
*
* Necati Kaan Inel
* 2. Proje Ödevi
* Bilgisayar Mühendisliği  
* Yalova Üniversitesi 
* 2016 
*
* Based on: https://www.dropbox.com/sh/1m6nb22t1oaboro/AADvn2LD6Mejd9MjjM7FR2Zpa?dl=0&preview=fonksiyonlar.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#define py Player1.Loc.y
#define px Player1.Loc.x
#define en Enemies[i]
#define ey en.Loc.y
#define ex en.Loc.x
#define MAPc(y,x) Map[((x)*(Height)) + (y)]

CChar *Map;
int Height = 40;
int Width  = 80;
int Turn = 0;

void printChar(CChar c){
  attron(COLOR_PAIR(c.Type));
  printw("%c%c", c.Char, c.CharS);
  attroff(COLOR_PAIR(c.Type));
}

void printPlayer(Player p){
  CChar c = p.CType;
  attron(COLOR_PAIR(c.Type));
  mvprintw(p.Loc.y,p.Loc.x*2,"%c%c", c.Char, c.CharS);
  attroff(COLOR_PAIR(c.Type));
  attron(COLOR_PAIR(Text.Type));
  mvprintw(Height, 0, "Health: %d\t Points: %d\n Turn: %d", p.Health, p.Points, (Turn/60));
  attroff(COLOR_PAIR(Text.Type));
}

void printEnemy(Enemy e){
  CChar c = e.CType;
  attron(COLOR_PAIR(c.Type));
  mvprintw(e.Loc.y,e.Loc.x*2,"%c%c", c.Char, c.CharS);
  attroff(COLOR_PAIR(c.Type));
}

Player Player1;
EnemyArray Enemies;

void olustur(int h, int w){
  Height = h;
  Width  = w;
  Map = (CChar*) malloc(Height * Width * sizeof(CChar));
  int i,j;
  for(i=0;i<Height;i++){
    for(j=0;j<Width;j++){
      MAPc(i,j)=Air;
    }
  }
  
  for(i=0;i<Height;i++){
    MAPc(i,0)=Border;
    MAPc(i,Width-1)=Border;
  }

  for(i=0;i<Width;i++){
    MAPc(0,i)=Border;
    MAPc(Height-1,i)=Border;
  }
    

  rastgeleEngel(Map);
  Player1 = (Player){ 3, 0 , { 10, 10 }, Playr};
  Enemies = DynamicArray();
  Push(Enemis,(Enemy){ 0, {1,1}, Ghost });
}


void rastgeleEngel(){
    int i,j,r;
    srand(time(NULL));
    
    for(i=1;i<Height-1;i++){
        for(j=1;j<Width-1;j++){
                r=rand()%Height;
                if(r<Height/4)
                    MAPc(i,j)=Wall;
        }
    }
    for(i=1;i<Height-1;i++){
      for(j=1;j<Width-1;j++){
          r=rand()%Height;
          if(r<Height/4 && MAPc(i,j).Type != Border.Type)
            MAPc(i,j)=Star;
        }
    }

    for(i=1;i<Height-1;i++){
        for(j=1;j<Width-1;j++){
            if(MAPc(i-1,j).Type==Wall.Type 
                && MAPc(i+1,j).Type==Wall.Type 
                  && MAPc(i,j-1).Type==Wall.Type 
                    && MAPc(i,j+1).Type==Wall.Type )
                      MAPc(i,j)=Air;
        }
    }
     
}
 
void yaz(){
    int i,j;
    move(0,0);
     
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
            printChar(MAPc(i,j));
        }
        printw("\n");
    }
    printPlayer(Player1);
    for(int i = 0; i < 4; i++) printEnemy(Enemies[i]);
}

char isMovable(int y, int x){
  CChar t = MAPc(py+y,px+x);
  return t.Type != Wall.Type && t.Type != Border.Type;
}

void Event(char pressed){
  if(pressed == 0) pressed = getch();
  switch(pressed){
    case 'A':
      if(isMovable(-1,0))
        Player1.Loc.y--;
      break;
    case 'D':
      if(isMovable(0,-1))
        Player1.Loc.x--;
      break;
    case 'B':
      if(isMovable(1,0))
        Player1.Loc.y++;
      break;
    case 'C':
      if(isMovable(0,1))
        Player1.Loc.x++;
      break;
  }
  if(MAPc(py,px).Type == Star.Type){
    MAPc(py,px) = Air;
    Player1.Points++;
  }
}

char Random(int min, int max){
  return (rand()%(max-min))+min;
}

int Tick(){
  if(Turn % 120)  
  if(Turn % 60 == 0) {
    int i, j;
    for(i=1;i<Height-1;i++){
        for(j=1;j<Width-1;j++){
            if(MAPc(i,j).Type == Portal.Type){
              MAPc(i,j).CharS--;
              if(MAPc(i,j).CharS == '0') MAPc(i,j) = Wall;
            }
        }
    }
  }
  if(Turn % 30 == 0) {
    for(int i = 0;i < 4;i++){
      int dx = px - ex;
      int dy = py - ey;
      if(abs(dx) > abs(dy)){
        if(dx > 0) ex++;
        else ex--;
      }else{
        if(dy > 0) ey++;
        else ey--;
      }
      for(int w = 0; w < 4; w++){
        if(i==w) continue;
        if(Enemies[w].Loc.y == ey && Enemies[w].Loc.x == ex)
        { ey++; ex++; }
      }
      if(ex == px && ey == py){
        Player1.Health--;
        if(!Player1.Health) return Player1.Points;
        en.Loc = (Point){ 1, 1 };
      } 
      if(MAPc(ey,ex).Type == Star.Type){
        MAPc(ey,ex) = Air;
        MAPc(Random(1,Height-1),Random(1,Width-1)) = Star;
        MAPc(Random(1,Height-1),Random(1,Width-1)) = Star;
      }
      if(MAPc(ey,ex).Type == Wall.Type){
        MAPc(ey,ex) = Portal;
        MAPc(ey,ex).Char  = '0';
        MAPc(ey,ex).CharS = '9';
      }
    }
  }
  Turn++;
  return -1;
}


EnemyArray DynamicArray(int step = 3){
  IntArray a;
  a.size = 0;
  a.step = step;
  a.p = (Enemy*) malloc(step * sizeof(Enemy));
}

Push(EnemyArray a, int n){
  if(a.size % a.step == 0) 
    a.p = (int*) realloc(a.p, (a.size+a.step) * sizeof(Enemy));
  a.p[a.size] = n;
  a.size++;
}

Pop(EnemyArray a){
  if(a.size % a.step == 0) 
    a.p = (int*) realloc(a.p, (a.size-a.step) * sizeof(Enemy));
  a.size--;
  return a.p[a.size];
}