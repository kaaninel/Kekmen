/*
*
* Necati Kaan Inel
* 2. Proje Ödevi
* Bilgisayar Mühendisliği  
* Yalova Üniversitesi 
* 2016 
*
* Based on: https://www.dropbox.com/sh/1m6nb22t1oaboro/AADvn2LD6Mejd9MjjM7FR2Zpa?dl=0&preview=oyun.h
*/


#include <ncurses.h>

typedef struct {
  char y;
  char x;
} Point;

typedef struct {
  char Char;
  char CharS;
  char Type; 
  NCURSES_COLOR_T FG;
  NCURSES_COLOR_T BG;
} CChar;

typedef struct {
  char Health;
  int Points;
  Point Loc;
  CChar CType;
} Player;

typedef struct {
  Point Loc;
  CChar CType;
} Enemy;

typedef struct {
  int size;
  int step;
  Enemy *p;
} EnemyArray;

void SetTickRate(char nt){
  timeout((int)1000/nt);
}

void initChar(CChar c){
  init_pair(c.Type, c.FG, c.BG);
}

CChar Air    = { ' ', ' ', 0, COLOR_BLACK, COLOR_BLACK}; 
CChar Wall   = { ' ', ' ', 1, COLOR_WHITE, COLOR_WHITE}; 
CChar Playr  = { '{', '}', 2, COLOR_BLUE , COLOR_BLACK}; 
CChar Ghost  = { '[', ']', 3, COLOR_WHITE, COLOR_RED  }; 
CChar Star   = { '<', '>', 4, COLOR_GREEN, COLOR_BLACK}; 
CChar Portal = { ' ', ' ', 5, COLOR_WHITE, COLOR_BLUE }; 
CChar Border = { ' ', ' ', 8, COLOR_WHITE, COLOR_WHITE}; 
CChar Text   = { ' ', ' ', 9, COLOR_WHITE, COLOR_BLACK}; 

void olustur();
void rastgeleEngel();
void yaz();