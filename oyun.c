/*
*
* Necati Kaan Inel
* 2. Proje Ödevi
* Bilgisayar Mühendisliği  
* Yalova Üniversitesi 
* 2016 
*
* Based on: https://www.dropbox.com/sh/1m6nb22t1oaboro/AADySiEDZdBfymGS6PT2Jpbva/oyun.c?dl=0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "oyun.h"
#include "fonksiyonlar.c"
 
int main(){ 
  initscr();
  //raw();
  noecho();
  curs_set(0);
  start_color();
  initChar(Air);
  initChar(Wall);
  initChar(Playr);
  initChar(Ghost);
  initChar(Portal);
  initChar(Bomb);
  initChar(Star);
  initChar(Border);
  initChar(Text);
  SetTickRate(60);
  olustur(LINES / 1.1, COLS / 2); 
  int points;
  while((points = Tick()) == -1){
    yaz();
    Event(getch());
  }
  endwin();
  printf("\nOyun Bitti!\n Puan: %d\n", points);
  return 0;
}