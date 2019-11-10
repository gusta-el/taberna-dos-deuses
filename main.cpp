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

#define MAX_HAND 4

#define IMAGEM_MENU_SEM_SELECAO 0
#define IMAGEM_JOGAR_SELECIONADO 1
#define IMAGEM_OPCOES_SELECIONADO 2
#define IMAGEM_CREDITOS_SELECIONADO 3

#define GOD_CARD 0
#define PRAYER_CARD 1
#define MAGIC_CARD 2

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

#define TIME_NORMAL 0
#define TIME_ATTACK 1
#define TIME_ATTACKING 2
#define TIME_BACK_ATTACK 3

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
    Deus deus;
    int type;
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

void new_SpaceField(int left, int top, int right, int bottom, SpaceField *spaceField, bool active){
        spaceField->left = left;
        spaceField->top = top;
        spaceField->right = right;
        spaceField->bottom = bottom;
        spaceField->active = active;
}

void new_SpaceFields(int xSize, int ySize, Card card, SpaceField sizeFields[20]){

    int posXDark = xSize*0.025;
    int posYDark = ySize/2;
    int index = 0;

    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false);
        posXDark = posXDark + card.X*1.2;
        index++;
    }

    posXDark = xSize*0.025;
    posYDark = ySize/2 + card.Y + card.spaceY;
    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false);
        posXDark = posXDark + card.X*1.2;
        index++;
    }
    posXDark = xSize*0.025;
    posYDark = ySize/2 - card.Y - card.spaceY;
    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false);
        posXDark = posXDark + card.X*1.2;
        index++;
    }
    posXDark = xSize*0.025;
    posYDark = posYDark - card.Y - card.spaceY;
    for (size_t j = 0; j < 5; j++){
        new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false);
        posXDark = posXDark + card.X*1.2;
        index++;
    }

}

void new_SpaceHandFields(int xSize, int yHandPos, Card card, SpaceField sizeHandFields[5]){

  int xHandPos = xSize*0.53;
  int index = 0;

    for (size_t j = 0; j < 5; j++){
        new_SpaceField(xHandPos, yHandPos, xHandPos + card.X, yHandPos + card.Y, &sizeHandFields[index], true);
        xHandPos = xHandPos + card.X*1.2;
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
void buildDeck(Card deck[20], Deus deuses[5]){
      for(int i = 0; i < 20; i ++){
        int num = rand();
            if(num >= 0 && num < 5){
                deck[i].deus = deuses[num];
                deck[i].type = GOD_CARD;
            } else {
                i--;
            }
  }
}

//=========================SETUP CAMPO DE BATALHA=========================//
int verifyCardFieldClick(int *tela, int x, int y, int cardOn, int *cardOnPointer, bool *backFullCard, SpaceField sizeFields[20]){

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

int verifyCardHandClick(int *tela, int x, int y, int cardOn, int *cardOnPointer, bool *backFullCard, SpaceField sizeHandFields[5]){

    if(cardOn == CARD_OFF){
        for (size_t i = 0; i < 4; i++){
            if(x >= sizeHandFields[i].left && y >= sizeHandFields[i].top  && x <= sizeHandFields[i].right && y <= sizeHandFields[i].bottom){
                if(sizeHandFields[i].active){
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

void selectCardField(int xSize, int cardOn, int cardField, SpaceField sizeFields[20], Card cardFull, Card *cardFullPointer, bool backFullCard, bool *backFullCardPointer){

    if(cardOn == CARD_ON && cardField != BLANK_CLICK){
        setcolor(WHITE);
        rectangle(sizeFields[cardField].left, sizeFields[cardField].top, sizeFields[cardField].right, sizeFields[cardField].bottom);
            if(cardFull.spaceX > cardFull.limitSpace){
                cardFullPointer->spaceX = cardFull.spaceX - cardFull.passo;
            }
    } else {
        if(backFullCard) {
            if(cardFull.spaceX < xSize){
                cardFullPointer->spaceX = cardFull.spaceX + cardFull.passo;
            } else {
                *backFullCardPointer = false;
            }
        }
    }

}

void selectCardHand(int xSize, int cardOn, int cardField, SpaceField sizeHandFields[5], Card cardFull, Card *cardFullPointer, bool backFullCard, bool *backFullCardPointer){

    if(cardOn == CARD_ON && cardField != BLANK_CLICK){
        setcolor(WHITE);
        rectangle(sizeHandFields[cardField].left, sizeHandFields[cardField].top, sizeHandFields[cardField].right, sizeHandFields[cardField].bottom);
            if(cardFull.spaceX > cardFull.limitSpace){
                cardFullPointer->spaceX = cardFull.spaceX - cardFull.passo;
            }
    } else {
        if(backFullCard) {
            if(cardFull.spaceX < xSize){
                cardFullPointer->spaceX = cardFull.spaceX + cardFull.passo;
            } else {
                *backFullCardPointer = false;
            }
        }
    }

}

int verifyMenuClick(int x, int y, void *menuImages[4], int tela){

        if(mousex() > x*0.07 && mousex() < x*0.22 && mousey() > 0.37*y && mousey() < 0.46*y){
            putimage(0, 0, menuImages[IMAGEM_JOGAR_SELECIONADO], 0);
            if(ismouseclick(WM_LBUTTONDOWN)){
                 tela =  TELA_FADE_OUT;
            }
        }

        if(mousex() > x*0.07 && mousex() < x*0.24 && mousey() > 0.50*y && mousey() < 0.59*y){
            putimage(0, 0, menuImages[IMAGEM_OPCOES_SELECIONADO], 0);
            if(ismouseclick(WM_LBUTTONDOWN)){
                tela =  TELA_FADE_OUT;
            }
        }

        if(mousex() > x*0.07 && mousex() < x*0.27 && mousey() > 0.63*y && mousey() < 0.72*y){
            putimage(0, 0, menuImages[IMAGEM_CREDITOS_SELECIONADO], 0);
            if(ismouseclick(WM_LBUTTONDOWN)){
                tela =  TELA_FADE_OUT;
            }
        }

    return tela;

}

int main()  {

  int ySize = 700; //GetSystemMetrics(SM_CYSCREEN);  760
  int xSize = ySize*1.8; //GetSystemMetrics(SM_CXSCREEN); 1360
  initwindow(xSize, ySize);

  char tecla = 0;
  int pg = 2;
  int fadeOut = 0;
  int fadeIn = 255;
  int tela = TELA_MENU_PRINCIPAL;
  int cardOn = CARD_OFF;
  int cardField = BLANK_CLICK;
  int cardHand = BLANK_CLICK;
  int x, y, posXDark, posYDark;
  int xDeckPos = xSize*0.53;
  int yDeckPos = ySize*0.26;
  int yHandPos = ySize*0.73;
  bool backFullCard = false;

  srand(time(0));

  Card card;
  new_Card(&card, xSize*0.085, ySize*0.21, xSize*0.05, ySize*0.03, 0, 0);
  Card cardFull;
  new_Card(&cardFull, card.X*3, card.Y*3, xSize, (ySize/2) - (card.Y*1.5), card.X*7.5, 20);
  SpaceField spaceField;
  new_SpaceField(xSize*0.67, card.spaceY, xSize*0.67 + card.X, card.spaceY + card.Y, &spaceField, false);
  SpaceField sizeFields[20];
  new_SpaceFields(xSize, ySize, card, sizeFields);

  int cardSize = imagesize(0, 0, card.X, card.Y);
  int cardFullSize = imagesize(0, 0, cardFull.X, cardFull.Y);
  int deusSize = imagesize(0, 0, card.X*0.8, card.Y*0.6);
  int fieldSize = imagesize(0, 0, xSize, ySize);

  void *menuImage = addImage(xSize, ySize);
  void *jogarOpImage = addImage(xSize, ySize);
  void *optionsOpImage = addImage(xSize, ySize);
  void *creditsOpImage = addImage(xSize, ySize);
  setupImage(xSize, ySize, menuImage, menuImage, "images/menu.bmp", "images/menu.bmp");
  setupImage(xSize, ySize, jogarOpImage, jogarOpImage, "images/jogarSelected.bmp", "images/jogarSelected.bmp");
  setupImage(xSize, ySize, optionsOpImage, optionsOpImage, "images/opcoesSelected.bmp", "images/opcoesSelected.bmp");
  setupImage(xSize, ySize, creditsOpImage, creditsOpImage, "images/creditosSelected.bmp", "images/creditosSelected.bmp");
  void *menuImages[4];
  menuImages[IMAGEM_MENU_SEM_SELECAO] = menuImage;
  menuImages[IMAGEM_JOGAR_SELECIONADO] = jogarOpImage;
  menuImages[IMAGEM_OPCOES_SELECIONADO] = optionsOpImage;
  menuImages[IMAGEM_CREDITOS_SELECIONADO] = creditsOpImage;

  void *field = addImage(xSize, ySize);
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
  setupImage(card.X, card.Y, cardFaceUp, cardFaceUpMask, "images/deusCard.bmp", "images/cardFaceUpMask.bmp");
  setupImage(card.X, card.Y, cardFaceUpEnemy, cardFaceUpMaskEnemy, "images/cardFaceUpEnemy.bmp", "images/cardFaceUpMaskEnemy.bmp");
  setupImage(cardFull.X, cardFull.Y, deuses[0].image, deuses[0].imageMask, "images/cardFaceUp.bmp", "images/cardFaceUpMask.bmp");
  setupImage(card.X*0.8, card.Y*0.6, deusImagem, deusImagemMask, "images/kuriboh.bmp", "images/kuribohMask.bmp");
  setupImage(card.X, card.Y, cardfaceDown, cardfaceDownMask, "images/cardFaceDown.bmp", "images/cardFaceDownMask.bmp");
  setupImage(card.X, card.Y, cardfaceDownEnemy, cardfaceDownMaskEnemy, "images/cardFaceDownEnemy.bmp", "images/cardFaceDownMaskEnemy.bmp");
  setupImage(xSize, ySize, field, field, "images/campo.bmp", "images/campo.bmp");

  int x1FadeSize = 0;
  int y1FadeSize = ySize/2;
  int x2FadeSize = xSize;
  int y2FadeSize = ySize/2;
  int stangle = 90;
  int endangle = 270;

  int changeFade = 0;
  int change = 0;
  int tempo = 0;
  int velocidade = 0;
  double aceleration = 0.03;

  Card deck[20];
  buildDeck(deck, deuses);
  int amountHand = 3;

  SpaceField sizeHandFields[5];
  new_SpaceHandFields(xSize, ySize/2 + card.Y + card.spaceY, card, sizeHandFields);
  SpaceField sizeHandFieldsEnemy[5];
  new_SpaceHandFields(xSize, card.spaceY, card, sizeHandFieldsEnemy);

  int g = 150;
  int aux_r = 0;

  while(tecla != 27) {
    if (pg == 1) pg = 2; else pg=1;
    setactivepage(pg);
    cleardevice();

    setbkcolor(COLOR(30,g,50));

    if(aux_r == 0){
        if(g < 150){
            g++;
        } else {
            aux_r = 1;
        }
    } else {
        if(g > 70){
            g--;
        } else {
            aux_r = 0;
        }
    }
    printf("valor: %d \n", g);
    //outtextxy(10, 10, );

    if(tela == TELA_MENU_PRINCIPAL || tela == TELA_FADE_OUT){
        putimage(0, 0, menuImages[IMAGEM_MENU_SEM_SELECAO], 0);
        tela = verifyMenuClick(xSize, ySize, menuImages, tela);
        clearmouseclick(WM_LBUTTONDOWN);
    }

    if(tela == TELA_DUELO || tela == TELA_FADE_IN){

        //putimage(0, 0, field, 0);
        //Deck
        putCardField(xSize*0.53, ySize/2, cardfaceDown, cardfaceDownMask);
        putCardField(xSize*0.53, (ySize/2) - card.Y - card.spaceY, cardfaceDownEnemy, cardfaceDownMaskEnemy);

        //Mão
        for (size_t i = 0; i < 4; i++)
        {
            putCardField(sizeHandFields[i].left, sizeHandFields[i].top, cardFaceUp, cardFaceUpMask);
            putCardField(sizeHandFieldsEnemy[i].left, sizeHandFieldsEnemy[i].top, cardfaceDownEnemy, cardfaceDownMaskEnemy);
        }



        int posClickX = 0;
        int posClickY = 0;
        bool clickOn = ismouseclick(WM_LBUTTONDOWN);
        if(clickOn){
            getmouseclick(WM_LBUTTONDOWN, posClickX, posClickY);
            if(cardField == BLANK_CLICK){
                cardHand = verifyCardHandClick(&tela, posClickX, posClickY, cardOn, &cardOn, &backFullCard, sizeHandFields);
            }
            if(cardHand == BLANK_CLICK){
                cardField = verifyCardFieldClick(&tela, posClickX, posClickY, cardOn, &cardOn, &backFullCard, sizeFields);
            }
        }

        selectCardField(xSize, cardOn, cardField, sizeFields, cardFull, &cardFull, backFullCard, &backFullCard);
        selectCardHand(xSize, cardOn, cardHand, sizeHandFields, cardFull, &cardFull, backFullCard, &backFullCard);

        putCardField(cardFull.spaceX, cardFull.spaceY, cardFaceUpFull, cardFaceUpMaskFull);

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
