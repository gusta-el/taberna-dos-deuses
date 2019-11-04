#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<iostream>
#include<time.h>

#define ESC = 27

#define TIME_NORMAL 0
#define TIME_ATTACK 1
#define TIME_ATTACKING 2
#define TIME_BACK_ATTACK 3


void desenhaFundo(){

    int x = 40;
    int y = 35;

    int xPasso = 130;
    int yPasso = 160;

    int xCard = 105 + x;
    int yCard = 135 + y;

    for(int i = 0; i < 2; i++){
        for(int i = 0; i < 6; i++){
            setfillstyle(1,COLOR(192,192,192));
            bar( x, y, xCard, yCard);
            x = x + xPasso;
            xCard = xCard + xPasso;
        }
        x = 40;
        xCard = 105 + x;
        y = y + yPasso;
        yCard = yCard + yPasso;
    }

    y = y + 20;
    yCard = yCard + 20;

    for(int i = 0; i < 2; i++){
        for(int i = 0; i < 6; i++){
            setfillstyle(1,COLOR(192,192,192));
            bar( x, y, xCard, yCard);
            x = x + xPasso;
            xCard = xCard + xPasso;
        }
        x = 40;
        xCard = 105 + x;
        y = y + yPasso;
        yCard = yCard + yPasso;
    }

    x = 840;
    y = 35;
    yCard = y + 135;
    setfillstyle(1,COLOR(192,192,192));
    bar( x, y, x+105, yCard);

    x = 840;
    y = 535;
    yCard = y + 135;
    setfillstyle(1,COLOR(192,192,192));
    bar( x, y, x+105, yCard);

    setfillstyle(1,BLACK);
    setcolor(BLACK);
    fillellipse(845,255,30,30);
    fillellipse(845,435,30,30);
    bar(845,235,970,275);
    bar(845,415,970,455);
}

void dimensions(){



}


void explode(int *NomeArq){

}

int main()  {

  int pg = 2;
  int tam, x, tam2;
  double y;
  char tecla = 0;
  void *R;
  void *RM;
  int *posExplosions = NULL;
  posExplosions = (int *) malloc(sizeof(int) * 4);







  int posXDark = 450;
  int posYDark = 199;
  int timeFight = 0;
  int timeAttack = 0;
  int explosions = 0;
  int numberOfExplosions = 5;

  int xSize = 1000;//GetSystemMetrics(SM_CXSCREEN); 1360
  int ySize = 700; //GetSystemMetrics(SM_CYSCREEN);  760

  initwindow(xSize, ySize);
  tam2 = imagesize(0, 0, 100, 144);

  RM = malloc(tam2);
  readimagefile("dark.bmp", 0, 0, 100, 144);
  getimage(0, 0, 100, 144, RM);

  y = 100;
  x = 700;
  setbkcolor(BLUE);
  srand(time(0));

  while(tecla != 27) {
    if (pg == 1) pg = 2; else pg=1;
    setactivepage(pg);
    cleardevice();

    desenhaFundo();

    putimage(posXDark, posYDark, RM, 0);

    if(timeFight == TIME_NORMAL){
        if(GetKeyState(VK_RIGHT)&0x80){
          timeFight = TIME_ATTACK;
        }
    }

    if(timeFight == TIME_ATTACK){
        posYDark = posYDark - 10;
        if(posYDark == 15){
            timeFight = 3;
        }
    }

    if(timeFight == 3){
        if(timeAttack == 100){
            timeFight = 2;
            timeAttack = 0;
            explosions = 0;
            numberOfExplosions = 0;
        } else {
            timeAttack++;
        }
    }





    setvisualpage(pg);
    if (kbhit())
      tecla = getch();
    delay(50);
  }

  closegraph();
  return 0;
}

