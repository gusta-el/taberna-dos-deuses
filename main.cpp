#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<iostream>
#include<time.h>

#define ESC = 27
#define QTD_GODS 5

#define TELA_MENU_PRINCIPAL 0
#define TELA_DUELO 1
#define TELA_FADE_OUT 2
#define TELA_FADE_IN 3

#define TIME_NORMAL 0
#define TIME_ATTACK 1
#define TIME_ATTACKING 2
#define TIME_BACK_ATTACK 3

#define JAPONESE 0
#define MAYA 1
#define BRAZILIAN 2

#define DECK 0
#define HAND 1
#define FIELD 2
#define FIELD_HIDE 3
#define GRAVEYARD 4

#define COLOSSO 0
#define ESCUDO_DIVINO 1
#define FURIA_DA_HARPIA 2
#define GRITO_DE_GUERRA 3
#define ENCORAJAR 4
#define MASSACRE 5
#define ULTIMO_SUSPIRO 6
#define MORTE_SUBITA 7

#define CARD_ON 1
#define CARD_OFF 0
#define BLANK_CLICK 20

#define ABLE_TO_CLICK 21

#define CARD_FULL 0
#define CARD_FACE_UP 1
#define CARD_FACE_DOWN 2
#define CARD_FACE_UP_ENEMY 3
#define CARD_FACE_DOWN_ENEMY 4
#define IMAGE_GOD 5

#define KUKULCAN 0
#define CAMAZOTZ 1
#define IXTAB 2
#define IXCHEL 3
#define XAMN_EK 4

//=========================SETUP DEUS=========================//
struct Deus {
    int id;
    char * nome;
    char * descricao;
    int attackPoints;
    int lifePoints;
    int specialPower;
    int mithology;
    bool enableAttack;
    int x;
    int y;
    void * image;
    void * imageMask;
};

void new_Deus(Deus *deus, int id, char * nome, char * descricao, int attackPoints, int lifePoints, int specialPower, int mithology){

    deus->id = id;
    deus->nome = nome;
    deus->descricao  = descricao;
    deus->attackPoints = attackPoints;
    deus->lifePoints = lifePoints;
    deus->specialPower = specialPower;
    deus->mithology = mithology;
    deus->enableAttack = false;


}

Deus new_Deus(int id, char** deusData){

    struct Deus deus;
    deus.id = id;
    deus.nome = deusData[0];
    deus.descricao  = deusData[1];
    deus.attackPoints = (int)deusData[2];
    deus.lifePoints = (int)deusData[3];
    deus.specialPower = (int)deusData[4];
    deus.mithology = (int)deusData[5];
    deus.enableAttack = false;
    return deus;

}

//=========================SETUP CARTA=========================//
struct Card{
    int X;
    int Y;
    int spaceX;
    int spaceY;
    int limitSpace;
    int passo;
    Deus carta;
};

void new_Card(Card *card, int x, int y, int spaceX, int spaceY, int limitSpace, int passo){

        card->X = x;
        card->Y = y;
        card->spaceX = spaceX;
        card->spaceY = spaceY;
        card->limitSpace = limitSpace;
        card->passo = passo;

}

//=========================SETUP CAMPO DE BATALHA=========================//
struct SpaceField{
    int left;
    int top;
    int bottom;
    int right;
    bool active;
};

void new_SpaceField(int left, int top, int right, int bottom, SpaceField *spaceField){
        spaceField->left = left;
        spaceField->top = top;
        spaceField->right = right;
        spaceField->bottom = bottom;
        spaceField->active = true;
}

void new_SpaceFields(int xSize, int ySize, Card card, SpaceField sizeFields[20]){

    int posXDark = xSize*0.025;
    int posYDark = ySize/2;
    int index = 0;

    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index]);
        posXDark = posXDark + card.X*1.2;
        index++;
    }

    posXDark = xSize*0.025;
    posYDark = ySize/2 + card.Y + card.spaceY;
    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index]);
        posXDark = posXDark + card.X*1.2;
        index++;
    }
    posXDark = xSize*0.025;
    posYDark = ySize/2 - card.Y - card.spaceY;
    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index]);
        posXDark = posXDark + card.X*1.2;
        index++;
    }
    posXDark = xSize*0.025;
    posYDark = posYDark - card.Y - card.spaceY;
    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index]);
        posXDark = posXDark + card.X*1.2;
        index++;
    }

}

void new_Deuses(Deus deuses[5]){

  Deus kukulcan;
  new_Deus(&kukulcan, 0,
  "Kukulcán - A Serpente Alada", "Kukulcán, com seus ventos da mudança, pode trocar uma carta no campo adversário com uma carta no seu campo."
  , 3, 3, 0, MAYA);
  Deus camazotz;
  new_Deus(&camazotz, 1,
  "Camazotz - Deus Morcego", "Caso um alvo estiver com menos de 25 de pontos de vida, ele o executa instantaneamente."
  , 3, 3, 0, MAYA);
  Deus ixtab;
  new_Deus(&ixtab, 2,
  "Ixtab - Deusa do Suicídio", "Ao ser invocada, faz com que uma carta dê dano a si mesmo."
  , 3, 3, 0, MAYA);
  Deus ixchel;
  new_Deus(&ixchel, 3,
  "Ixchel - Deusa da Medicina", "Seleciona uma carta aliada e a cura por 50 dos pontos de vida. Ao usar esse efeito, deve-se esperar 2 rodadas para usar novamente."
  , 3, 3, 0, MAYA);
  Deus xamanEk;
  new_Deus(&xamanEk, 4,
  "Xaman Ek - Deus dos viajantes e mercadores", "Ao ser invocado em campo, Xaman Ek conjura o totem do mercador, que possui 0 de ataque e 4 de vida."
  , 3, 3, 0, MAYA);

  deuses[KUKULCAN] = kukulcan;
  deuses[CAMAZOTZ] = camazotz;
  deuses[IXTAB] = ixtab;
  deuses[IXCHEL] = ixchel;
  deuses[XAMN_EK] = xamanEk;

}

void readFile(){

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "c:\\Users\\gustavocabrera\\Desktop\\testesMitologia\\gods.txt";

    char** deusesFiles;
    deusesFiles = (char**)malloc(QTD_GODS*10 * sizeof(char*));

    Deus* deuses;
    deuses = NULL;

    int qtdGods = 0;
    int id = 1;

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
    }

    while (fgets(str, MAXCHAR, fp) != NULL){
        if(qtdGods < QTD_GODS*10){
            deusesFiles[qtdGods] = str;
            //printf("valor: %s \n", deusesFiles[qtdGods]);
            qtdGods++;
        }
    }

  Deus deus;
  //new_Deus(&deus, (int) deusesFiles[0], deusesFiles[1], deusesFiles[2], (int)deusesFiles[3], (int) deusesFiles[4], (int) deusesFiles[5], (int) deusesFiles[6]);
  new_Deus(&deus, 1, "teste", "teste", 2, 3, 3, 7);
  //printf("valor: %d \n", deus.id);
  //printf("valor: %s \n", deus.nome);
  //printf("valor: %s \n", deus.descricao);
  //printf("valor: %d \n", deus.attackPoints);
  //printf("valor: %d \n", deus.lifePoints);
  //printf("valor: %d \n", deus.specialPower);
  //printf("valor: %d \n", deus.mithology);

    fclose(fp);
}

//=========================SETUP IMAGE=========================//

void* addImage(int x, int y){
    void *image;
    image = malloc(imagesize(0, 0, x, y));
    return image;
}

void setupImage(int x, int y, void *image, void *imageMask, char imagem[50], char mask[50]){
  readimagefile(imagem, 0, 0, x, y);
  getimage(0, 0, x, y, imageMask);
  readimagefile(mask, 0, 0, x, y);
  getimage(0, 0, x, y, image);
}

void setupAllImages(int x, int y, void *image, void *imageMask, char imagem[50], char mask[50]){
  readimagefile(imagem, 0, 0, x, y);
  getimage(0, 0, x, y, imageMask);
  readimagefile(mask, 0, 0, x, y);
  getimage(0, 0, x, y, image);
}

void putCardField(int posX, int posY, void *image, void *imageMask){
   putimage(posX, posY, image, AND_PUT);
   putimage(posX, posY, imageMask, OR_PUT);
}


//=========================SETUP DECK=========================//
void buildDeck(Card card[]){

}

//=========================SETUP CAMPO DE BATALHA=========================//
int verifyCardClick(int *tela, int x, int y, int cardOn, int *cardOnPointer, bool *backFullCard, SpaceField sizeFields[20]){

    if(cardOn == CARD_OFF){
        for (size_t i = 0; i < 20; i++){
            if(x >= sizeFields[i].left && y >= sizeFields[i].top  && x <= sizeFields[i].right && y <= sizeFields[i].bottom){
                if(sizeFields[i].active){
                    *cardOnPointer = CARD_ON;
                    return i;
                }
            }
        }
    } else {
        *cardOnPointer = CARD_OFF;
        *backFullCard = true;
    }

    return BLANK_CLICK;
}




int main()  {




  int ySize = 700; //GetSystemMetrics(SM_CYSCREEN);  760
  int xSize = ySize*1.8; //GetSystemMetrics(SM_CXSCREEN); 1360
  initwindow(xSize, ySize);

  readFile();
  int pg = 2;
  char tecla = 0;
  int tela = TELA_MENU_PRINCIPAL;
  int tela1 = TELA_MENU_PRINCIPAL;
  int fadeIn = 255;
  int fadeOut = 0;


  int x, y, posXDark, posYDark;
  int cardOn = CARD_OFF;
  int cardField = CARD_OFF;
  bool backFullCard = false;
  srand(time(0));

  Card card;
  new_Card(&card, xSize*0.085, ySize*0.21, xSize*0.05, ySize*0.03, 0, 0);
  Card cardFull;
  new_Card(&cardFull, card.X*3, card.Y*3, xSize, (ySize/2) - (card.Y*1.5), card.X*6.9, 20);
  SpaceField deck;
  new_SpaceField(xSize*0.67, card.spaceY, xSize*0.67 + card.X, card.spaceY + card.Y, &deck);

  SpaceField sizeFields[20];
  new_SpaceFields(xSize, ySize, card, sizeFields);

  int cardSize = imagesize(0, 0, card.X, card.Y);
  int cardFullSize = imagesize(0, 0, cardFull.X, cardFull.Y);
  int deusSize = imagesize(0, 0, card.X*0.8, card.Y*0.6);
  int fieldSize = imagesize(0, 0, xSize, ySize);

  int itemMenuSizeX = 120;
  int itemMenuSizeY = 60;
  int stangle = 90;
  int endangle = 270;

  void *menuImage = addImage(xSize, ySize);
  void *field = addImage(xSize, ySize);
  void *itemMenu = addImage(itemMenuSizeX, itemMenuSizeY);
  void *itemMenuSelected = addImage(itemMenuSizeX, itemMenuSizeY);
  void *cardFaceUp = addImage(card.X, card.Y);
  void *cardFaceUpMask = addImage(card.X, card.Y);
  void *cardFaceUpEnemy = addImage(card.X, card.Y);
  void *cardFaceUpMaskEnemy = addImage(card.X, card.Y);
  void *cardFaceUpFull = addImage(cardFull.X, cardFull.Y);
  void *cardFaceUpMaskFull = addImage(cardFull.X, cardFull.Y);
  void *deusImagem = addImage(card.X*0.8, card.Y*0.6);
  void *deusImagemMask = addImage(card.X*0.8, card.Y*0.6);
  void *cardfaceDown = addImage(card.X, card.Y);
  void *cardfaceDownMask = addImage(card.X, card.Y);
  void *cardfaceDownEnemy = addImage(card.X, card.Y);
  void *cardfaceDownMaskEnemy = addImage(card.X, card.Y);
  
  Deus deuses[5];
  new_Deuses(deuses);
  deuses[KUKULCAN].image = cardFaceUpFull;
  deuses[KUKULCAN].imageMask = cardFaceUpMaskFull;
  deuses[CAMAZOTZ].image = cardFaceUpFull;
  deuses[CAMAZOTZ].imageMask = cardFaceUpMaskFull;
  deuses[IXTAB].image = cardFaceUpFull;
  deuses[IXTAB].imageMask = cardFaceUpMaskFull;
  deuses[IXCHEL].image = cardFaceUpFull;
  deuses[IXCHEL].imageMask = cardFaceUpMaskFull;
  deuses[XAMN_EK].image = cardFaceUpFull;
  deuses[XAMN_EK].imageMask = cardFaceUpMaskFull;

  setupImage(card.X, card.Y, cardFaceUp, cardFaceUpMask, "deusCard.bmp", "cardFaceUpMask.bmp");
  setupImage(card.X, card.Y, cardFaceUpEnemy, cardFaceUpMaskEnemy, "cardFaceUpEnemy.bmp", "cardFaceUpMaskEnemy.bmp");
  setupImage(cardFull.X, cardFull.Y, deuses[0].image, deuses[0].imageMask, "cardFaceUp.bmp", "cardFaceUpMask.bmp");
  setupImage(card.X*0.8, card.Y*0.6, deusImagem, deusImagemMask, "kuriboh.bmp", "kuribohMask.bmp");
  setupImage(card.X, card.Y, cardfaceDown, cardfaceDownMask, "cardFaceDown.bmp", "cardFaceDownMask.bmp");
  setupImage(card.X, card.Y, cardfaceDownEnemy, cardfaceDownMaskEnemy, "cardFaceDownEnemy.bmp", "cardFaceDownMaskEnemy.bmp");
  setupImage(xSize, ySize, menuImage, menuImage, "menu.bmp", "menu.bmp");
  setupImage(itemMenuSizeX, itemMenuSizeY, itemMenu, itemMenu, "jogar.bmp", "jogar.bmp");
  setupImage(itemMenuSizeX, itemMenuSizeY, itemMenuSelected, itemMenuSelected, "jogar2.bmp", "jogar2.bmp");
  setupImage(xSize, ySize, field, field, "campo.bmp", "campo.bmp");

  int x1FadeSize = 0;
  int y1FadeSize = ySize/2;
  int x2FadeSize = xSize;
  int y2FadeSize = ySize/2;

    setbkcolor(COLOR(60,179,113));

    int changeFade = 0;
    int change = 0;
    int tempo = 0;
    int velocidade = 0;
    double aceleration = 0.03;

    int Xasd = 0;
    int Yasd = 0;

  while(tecla != 27) {
    if (pg == 1) pg = 2; else pg=1;
    setactivepage(pg);
    cleardevice();

    if(tela == TELA_MENU_PRINCIPAL || tela == TELA_FADE_OUT){
        putimage(0, 0, menuImage, 0);
        putimage(150, 280, itemMenu, 0);

        if(mousex() > 150 && mousex() < (150 + itemMenuSizeX) && mousey() > 280 && mousey() < (280 + itemMenuSizeY)){
            putimage(150, 280, itemMenuSelected, 0);
            if(ismouseclick(WM_LBUTTONDOWN)){
                tela = TELA_FADE_OUT;
            }
        }
        clearmouseclick(WM_LBUTTONDOWN);
    }

    if(tela == TELA_DUELO || tela == TELA_FADE_IN){

        putimage(0, 0, field, 0);

    int posClickX = 0;
    int posClickY = 0;
    bool clickOn = ismouseclick(WM_LBUTTONDOWN);
    if(clickOn){
        getmouseclick(WM_LBUTTONDOWN, posClickX, posClickY);
        cardField = verifyCardClick(&tela, posClickX, posClickY, cardOn, &cardOn, &backFullCard, sizeFields);
    }

    if(cardOn == CARD_ON && cardField != BLANK_CLICK){
        setcolor(WHITE);
        rectangle(sizeFields[cardField].left, sizeFields[cardField].top, sizeFields[cardField].right, sizeFields[cardField].bottom);
            if(cardFull.spaceX > cardFull.limitSpace){
                cardFull.spaceX = cardFull.spaceX - cardFull.passo;
            }
    } else {
        if(backFullCard) {
            if(cardFull.spaceX < xSize){
                cardFull.spaceX = cardFull.spaceX + cardFull.passo;
            } else {
                backFullCard = false;
            }
        }
    }

    putCardField(cardFull.spaceX, cardFull.spaceY, cardFaceUpFull, cardFaceUpMaskFull);
    //putCardField(xSize*0.835, 175, cardfaceDownEnemy, cardfaceDownMaskEnemy);

}

if (tela == TELA_FADE_OUT){
        if(x1FadeSize < xSize/2){
            x1FadeSize += 10;
            x2FadeSize -= 10;
            setfillstyle(SOLID_FILL, BLACK);
        } else {
            tela = TELA_FADE_IN;
            delay(300);
        }
        bar(0, 0, x1FadeSize, ySize);
        bar(x2FadeSize, 0, xSize, ySize);

        setfillstyle(SOLID_FILL, COLOR(85,107,47));
        setcolor(COLOR(60,179,113));
        setlinestyle(SOLID_LINE, USERBIT_LINE, THICK_WIDTH);
        pieslice(x1FadeSize, ySize/2, stangle, endangle, 100);
        pieslice(x2FadeSize, ySize/2, endangle, stangle, 100);
        setfillstyle(SOLID_FILL, BLACK);

}

if(tela == TELA_FADE_IN){

        if(stangle != 0){
            stangle-= 2;
            endangle-= 2;
        bar(0, 0, x1FadeSize, ySize);
        bar(x2FadeSize, 0, xSize, ySize);

            setfillstyle(SOLID_FILL, COLOR(85,107,47));
            setcolor(COLOR(60,179,113));
            setlinestyle(SOLID_LINE, USERBIT_LINE, THICK_WIDTH);
            pieslice(x1FadeSize, ySize/2, stangle, endangle, 100);
            pieslice(x2FadeSize, ySize/2, endangle, stangle, 100);
            setfillstyle(SOLID_FILL, BLACK);

            if(stangle == 0){
                delay(300);
            }

        } else {
            y1FadeSize -= 10;
            y2FadeSize += 10;
            if(x1FadeSize == 0){
                x1FadeSize = 0;
                x2FadeSize = xSize;
                tela = TELA_DUELO;
            }
        bar(0, 0, xSize, y1FadeSize);
        bar(0, y2FadeSize, xSize, ySize);

        setfillstyle(SOLID_FILL, COLOR(85,107,47));
        setcolor(COLOR(60,179,113));
        setlinestyle(SOLID_LINE, USERBIT_LINE, THICK_WIDTH);
        pieslice(xSize/2, y1FadeSize, stangle, endangle, 100);
        pieslice(xSize/2, y2FadeSize, endangle, stangle, 100);
        setfillstyle(SOLID_FILL, BLACK);
    }

}




    setvisualpage(pg);
    if (kbhit())
      tecla = getch();
    delay(15);
  }

  closegraph();
  return 0;
}



    // posXDark = xSize*0.025;
    // posYDark = ySize/2;

    // for (size_t j = 0; j < 5; j++){
    //     putCardField(posXDark, posYDark, cardFaceUp, cardFaceUpMask);
    //     velocidade = tempo * aceleration;

    //     if(velocidade <= (card.Y*0.05) && change == 0){
    //         tempo +=  2.5;
    //     } else {
    //         tempo -= 2;
    //         change = 1;
    //         if(velocidade <= 0){
    //             change = 0;
    //         }
    //     }

    //     putCardField(posXDark + (card.X*0.1), posYDark + (card.Y*0.2) - velocidade, deusImagem, deusImagemMask);
    //     posXDark = posXDark + card.X*1.2;
    // }

    // putCardField(posXDark, posYDark, cardfaceDown, cardfaceDownMask);

    // posXDark = xSize*0.025;
    // posYDark = ySize/2 + card.Y + card.spaceY;

    // for (size_t j = 0; j < 5; j++){
    //     putCardField(posXDark, posYDark, cardFaceUp, cardFaceUpMask);
    //     posXDark = posXDark + card.X*1.2;
    // }


    // for (size_t j = 0; j < 4; j++){
    //     putCardField(posXDark, posYDark, cardfaceDown, cardfaceDownMask);
    //     posXDark = posXDark + card.X*1.2;
    // }

    // posXDark = xSize*0.025;
    // posYDark = ySize/2 - card.Y - card.spaceY;

    // for (size_t j = 0; j < 5; j++){
    //     putCardField(posXDark, posYDark, cardFaceUpEnemy, cardFaceUpMaskEnemy);
    //     posXDark = posXDark + card.X*1.2;
    // }


    // putCardField(posXDark, posYDark, cardfaceDownEnemy, cardfaceDownMaskEnemy);

    // posXDark = xSize*0.025;
    // posYDark = posYDark - card.Y - card.spaceY;

    // for (size_t j = 0; j < 5; j++){
    //     putCardField(posXDark, posYDark, cardFaceUpEnemy, cardFaceUpMaskEnemy);
    //     posXDark = posXDark + card.X*1.2;
    // }

    // for (size_t j = 0; j < 4; j++){
    //     putCardField(posXDark, posYDark, cardfaceDownEnemy, cardfaceDownMaskEnemy);
    //     posXDark = posXDark + card.X*1.2;
    // }
