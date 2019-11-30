#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<iostream>
#include<time.h>
#include <string.h>
#include <windows.h>
#include <Mmsystem.h>


//CONSTANTES
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
    #define DEFAULT_CARD 3

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
    #define IZANAGI 5
    #define IZANAMI 6
    #define AMATERASU 7
    #define TSUKI_YOMI 8
    #define SUSANO 9
    #define TUPA 10
    #define JACI 11
    #define GUARACI 12
    #define ANHANGA 13
    #define RUDA 14

    #define TIME_NORMAL 0
    #define TIME_ATTACK 1
    #define TIME_ATTACKING 2
    #define TIME_BACK_ATTACK 3

    #define BOTAO_INVOCAR 0
    #define BOTAO_ATACAR 1
    #define BOTAO_ATIVAR_EFEITO 2
    #define BOTAO_FINALIZAR 3
    #define BOTAO_DESISTIR 4
//============================================================================

//UTILS
    int generateRandom(int rangeBegin, int rangeFinal){

        int num = -1;
        while(num <= rangeBegin || num >= rangeFinal){
            num = rand();
        }

        return num;

    }

    bool verifyMouseCheck(int posX, int posY, int x0, int y0, int x, int y){
            if(posX > x0 && posY > y0 && posX < x0+x && posY < y0+y){
                return true;
            }
            return false;
    }
//============================================================================

//METODOS PARA OS DEUSES
    struct Deus {
            int id;
            int attackPoints;
            int lifePoints;
            int specialPower;
            int mithology;
            bool enableAttack;
            int teste;
            int x;
            int y;
            char *nick;
            void *image_card_full;
            void *image_card_full_mask;
            void *image_card;
            void *image_card_mask;
    };


    void new_Deus(Deus *deus, int id, char *path, int attackPoints, int lifePoints, int specialPower, int mithology){

        deus->id = id;
        deus->nick = path;
        deus->attackPoints = attackPoints;
        deus->lifePoints = lifePoints;
        deus->specialPower = specialPower;
        deus->mithology = mithology;
        deus->enableAttack = false;
    }

    void new_Deuses(Deus deuses[15]){

        Deus kukulcan;
        new_Deus(&kukulcan, KUKULCAN,
        "images/deuses/kukulcan.bmp", generateRandom(1,10), generateRandom(1,10), 0, MAYA);
        Deus camazotz;
        new_Deus(&camazotz, CAMAZOTZ,
        "images/deuses/camazotz.bmp", generateRandom(1,10), generateRandom(1,10), 0, MAYA);
        Deus ixtab;
        new_Deus(&ixtab, IXTAB,
        "images/deuses/ixtab.bmp", generateRandom(1,10), generateRandom(1,10), 0, MAYA);
        Deus ixchel;
        new_Deus(&ixchel, IXCHEL,
        "images/deuses/ixchel.bmp", generateRandom(1,10), generateRandom(1,10), 0, MAYA);
        Deus xamanEk;
        new_Deus(&xamanEk, XAMN_EK,
        "images/deuses/xaman_ek.bmp", generateRandom(1,10), generateRandom(1,10), 0, MAYA);
        Deus izanagi;
        new_Deus(&izanagi, IZANAGI,
        "images/deuses/izanagi.bmp", generateRandom(1,10), generateRandom(1,10), 0, JAPONESE);
        Deus izanami;
        new_Deus(&izanami, IZANAMI,
        "images/deuses/izanami.bmp", generateRandom(1,10), generateRandom(1,10), 0, JAPONESE);
        Deus amaterasu;
        new_Deus(&amaterasu, AMATERASU,
        "images/deuses/amaterasu.bmp", generateRandom(1,10),generateRandom(1,10), 0, JAPONESE);
        Deus tsukuyomi;
        new_Deus(&tsukuyomi, TSUKI_YOMI,
        "images/deuses/tsukuyomi.bmp", generateRandom(1,10),generateRandom(1,10), 0, JAPONESE);
        Deus susano;
        new_Deus(&susano, SUSANO,
        "images/deuses/susano.bmp", generateRandom(1,10),generateRandom(1,10), 0, JAPONESE);
        Deus tupa;
        new_Deus(&tupa, TUPA,
        "images/deuses/tupa.bmp", generateRandom(1,10),generateRandom(1,10), 0, BRAZILIAN);
        Deus jaci;
        new_Deus(&jaci, JACI,
        "images/deuses/jaci.bmp", generateRandom(1,10),generateRandom(1,10), 0, BRAZILIAN);
        Deus guaraci;
        new_Deus(&guaraci, GUARACI,
        "images/deuses/guaraci.bmp", generateRandom(1,10),generateRandom(1,10), 0, BRAZILIAN);
        Deus anhanga;
        new_Deus(&anhanga, ANHANGA,
        "images/deuses/anhanga.bmp", generateRandom(1,10),generateRandom(1,10), 0, BRAZILIAN);
        Deus ruda;
        new_Deus(&ruda, RUDA,
        "images/deuses/ruda.bmp", generateRandom(1,10),generateRandom(1,10), 0, BRAZILIAN);

        deuses[KUKULCAN] = kukulcan;
        deuses[CAMAZOTZ] = camazotz;
        deuses[IXTAB] = ixtab;
        deuses[IXCHEL] = ixchel;
        deuses[XAMN_EK] = xamanEk;
        deuses[IZANAGI] = izanagi;
        deuses[IZANAMI] = izanami;
        deuses[AMATERASU] = amaterasu;
        deuses[TSUKI_YOMI] = tsukuyomi;
        deuses[SUSANO] = susano;
        deuses[TUPA] = tupa;
        deuses[JACI] = jaci;
        deuses[GUARACI] = guaraci;
        deuses[ANHANGA] = anhanga;
        deuses[RUDA] = ruda;

    }

    struct Deus_Imagem {
            int id;
            char *path;
            char *path_mask;
            void *imagem_holograma;
            void *imagem_holograma_mask;
    };

    void new_Deus_Imagem(Deus_Imagem *deus, int id, char *path, char *path_mask){
        deus->id = id;
        deus->path = path;
        deus->path_mask = path_mask;

    }

    void new_Deuses_Imagem(Deus_Imagem deuses[15]){

        Deus_Imagem kukulcan;
        new_Deus_Imagem(&kukulcan, KUKULCAN, "images/deuses/holograma/kukulcan.bmp", "images/deuses/holograma/kukulcan_mask.bmp");
        Deus_Imagem camazotz;
        new_Deus_Imagem(&camazotz, CAMAZOTZ, "images/deuses/holograma/camazotz.bmp", "images/deuses/holograma/camazotz_mask.bmp");
        Deus_Imagem ixtab;
        new_Deus_Imagem(&ixtab, IXTAB, "images/deuses/holograma/ixtab.bmp", "images/deuses/holograma/ixtab_mask.bmp");
        Deus_Imagem ixchel;
        new_Deus_Imagem(&ixchel, IXCHEL, "images/deuses/holograma/ixchel.bmp", "images/deuses/holograma/ixchel_mask.bmp");
        Deus_Imagem xamanEk;
        new_Deus_Imagem(&xamanEk, XAMN_EK, "images/deuses/holograma/xaman_ek.bmp", "images/deuses/holograma/xaman_ek_mask.bmp");
        Deus_Imagem izanagi;
        new_Deus_Imagem(&izanagi, IZANAGI, "images/deuses/holograma/izanagi.bmp", "images/deuses/holograma/izanagi_mask.bmp");
        Deus_Imagem izanami;
        new_Deus_Imagem(&izanami, IZANAMI, "images/deuses/holograma/izanami.bmp", "images/deuses/holograma/izanami_mask.bmp");
        Deus_Imagem amaterasu;
        new_Deus_Imagem(&amaterasu, AMATERASU, "images/deuses/holograma/amaterasu.bmp", "images/deuses/holograma/amaterasu_mask.bmp");
        Deus_Imagem tsukuyomi;
        new_Deus_Imagem(&tsukuyomi, TSUKI_YOMI, "images/deuses/holograma/tsukuyomi.bmp", "images/deuses/holograma/tsukuyomi_mask.bmp");
        Deus_Imagem susano;
        new_Deus_Imagem(&susano, SUSANO, "images/deuses/holograma/susano.bmp", "images/deuses/holograma/susano_mask.bmp");
        Deus_Imagem tupa;
        new_Deus_Imagem(&tupa, TUPA, "images/deuses/holograma/tupa.bmp", "images/deuses/holograma/tupa_mask.bmp");
        Deus_Imagem jaci;
        new_Deus_Imagem(&jaci, JACI, "images/deuses/holograma/jaci.bmp", "images/deuses/holograma/jaci_mask.bmp");
        Deus_Imagem guaraci;
        new_Deus_Imagem(&guaraci, GUARACI, "images/deuses/holograma/guaraci.bmp", "images/deuses/holograma/guaraci_mask.bmp");
        Deus_Imagem anhanga;
        new_Deus_Imagem(&anhanga, ANHANGA, "images/deuses/holograma/anhanga.bmp", "images/deuses/holograma/anhanga_mask.bmp");
        Deus_Imagem ruda;
        new_Deus_Imagem(&ruda, RUDA, "images/deuses/holograma/ruda.bmp", "images/deuses/holograma/ruda_mask.bmp");

        deuses[KUKULCAN] = kukulcan;
        deuses[CAMAZOTZ] = camazotz;
        deuses[IXTAB] = ixtab;
        deuses[IXCHEL] = ixchel;
        deuses[XAMN_EK] = xamanEk;
        deuses[IZANAGI] = izanagi;
        deuses[IZANAMI] = izanami;
        deuses[AMATERASU] = amaterasu;
        deuses[TSUKI_YOMI] = tsukuyomi;
        deuses[SUSANO] = susano;
        deuses[TUPA] = tupa;
        deuses[JACI] = jaci;
        deuses[GUARACI] = guaraci;
        deuses[ANHANGA] = anhanga;
        deuses[RUDA] = ruda;

    }

    struct Holograma{
        float velocity_holograma;
        float time_holograma;
        float aceleration_holograma;
        float change_holograma;
    };

    void new_Holograma(Holograma *holograma){

        holograma->velocity_holograma = 1;
        holograma->time_holograma = 0;
        holograma->aceleration_holograma = 0.1;
        holograma->change_holograma = 0;
    }

//============================================================================

//METODO PARA DEVOCOES

    struct Devocao {
        int id;
        int mithology;
        char * nick;
        int manaValue;
        int x;
        int y;
        void * image;
        void * imageMask;
        void * imageCard;
        void * imageCardMask;

    };

    void new_Devocao(Devocao *devocao, int id, char * nick, int manaValue, int mithology){
        devocao->id = id;
        devocao->nick = nick;
        devocao->manaValue = manaValue;
        devocao->mithology = mithology;
    }

    void new_Devocoes(Devocao devocoes[3]){

        Devocao devocao_japonesa_1;
        new_Devocao(&devocao_japonesa_1, 0,
        "images/adoradores/adorador_japones.bmp", 3, JAPONESE);

        Devocao devocao_maia_1;
        new_Devocao(&devocao_maia_1, 1,
        "images/adorador_maia/kukulcan.bmp", 3, MAYA);

        Devocao devocao_brasileira_1;
        new_Devocao(&devocao_brasileira_1, 2,
        "images/adoradores/adorador_brasileiro.bmp", 3, BRAZILIAN);

        devocoes[JAPONESE] = devocao_japonesa_1;
        devocoes[MAYA] = devocao_maia_1;
        devocoes[BRAZILIAN] = devocao_brasileira_1;

    }


//============================================================================

//METODOS PARA AS CARTAS
    struct Card{
        int X;
        int Y;
        int spaceX;
        int spaceY;
        int limitSpace;
        int passo;
        Deus deus;
        //Devocao devocao;
        int type;
    };

    void new_Card(Card *card, int x, int y, int spaceX, int spaceY, int limitSpace, int passo, int type){

            card->X = x;
            card->Y = y;
            card->spaceX = spaceX;
            card->spaceY = spaceY;
            card->limitSpace = limitSpace;
            card->passo = passo;
            card->type = type;

    }

    void buildDeck(Card deck[20], Deus deuses[15]){
        for(int i = 0; i < 20; i ++){
            int num = rand();
                if(num >= 0 && num < 9){
                    deck[i].deus = deuses[num];
                    deck[i].type = GOD_CARD;
                } else {
                    i--;
                }
        }
    }
//============================================================================

//METODOS PARA O CAMPO DE BATALHA
    struct SpaceField{
        int left;
        int top;
        int bottom;
        int right;
        bool active;
        bool available;
        Card card;
    };

    struct Radius{
        int xradius;
        int yradius;
    };

    void new_Radius(Radius *radius){

            radius->xradius = 0;
            radius->yradius = 0;

    }


    void new_SpaceField(int left, int top, int right, int bottom, SpaceField *spaceField, bool active, int type){
            spaceField->left = left;
            spaceField->top = top;
            spaceField->right = right;
            spaceField->bottom = bottom;
            spaceField->active = active;
            spaceField->available = true;
            spaceField->card.type = type;

    }

    void new_SpaceField(int left, int top, int right, int bottom, SpaceField *spaceField){
            spaceField->left = left;
            spaceField->top = top;
            spaceField->right = right;
            spaceField->bottom = bottom;
    }

    void new_SpaceFields(int xSize, int ySize, Card card, SpaceField sizeFields[20]){

        int posXDark = xSize*0.025;
        int posYDark = ySize/2;
        int index = 0;

        for (size_t j = 0; j < 5; j++){
            new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false, GOD_CARD);
            posXDark = posXDark + card.X*1.2;
            index++;
        }

        posXDark = xSize*0.025;
        posYDark = ySize/2 + card.Y + card.spaceY;
        for (size_t j = 0; j < 5; j++){
            new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false, MAGIC_CARD);
            posXDark = posXDark + card.X*1.2;
            index++;
        }
        posXDark = xSize*0.025;
        posYDark = ySize/2 - card.Y - card.spaceY;
        for (size_t j = 0; j < 5; j++){
            new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false, DEFAULT_CARD);
            posXDark = posXDark + card.X*1.2;
            index++;
        }
        posXDark = xSize*0.025;
        posYDark = posYDark - card.Y - card.spaceY;
        for (size_t j = 0; j < 5; j++){
            new_SpaceField(posXDark, posYDark, posXDark + card.X, posYDark + card.Y, &sizeFields[index], false, DEFAULT_CARD);
            posXDark = posXDark + card.X*1.2;
            index++;
        }

    }

    void new_SpaceHandFields(int xSize, int yHandPos, Card card, SpaceField sizeHandFields[5]){

        int xHandPos = xSize*0.53;
        int index = 0;

            for (size_t j = 0; j < 5; j++){
                new_SpaceField(xHandPos, yHandPos, xHandPos + card.X, yHandPos + card.Y, &sizeHandFields[index], true, sizeHandFields[index].card.type);
                xHandPos = xHandPos + card.X*1.2;
                index++;
            }

    }

    int verifyDeckClick(int x, int y, SpaceField deckSize){

        if(x >= deckSize.left && y >= deckSize.top  && x <= deckSize.right && y <= deckSize.bottom){
            return 25;
        }

        return 0;
    }

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

    //verifica e retorna se o usuario selecionou em algum card da mão. Caso retorne, retorna o indice do card da mão
    int verifyCardHandClick(int *tela, int x, int y, int cardOn, int *cardOnPointer, bool *backFullCard, SpaceField sizeHandFields[5], int amountHand){

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
            setlinestyle(SOLID_LINE, 4, NORM_WIDTH);
            rectangle(sizeFields[cardField].left-1, sizeFields[cardField].top-1, sizeFields[cardField].right+1, sizeFields[cardField].bottom+1);
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
            setlinestyle(SOLID_LINE, 4, NORM_WIDTH);
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

    void selectAmountDeck(int x, int y, int passoDeck, int *passoDeckPointer, int amountDeck){

        if(passoDeck > 0){
            *passoDeckPointer -= 1;
            char amount[2];
            sprintf(amount, "%d", amountDeck + 1);
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
            outtextxy(x - 2, y - 2, amount);
        }

    }

    void withdrawCard(){

    }

//============================================================================

//METODOS PARA IMAGENS
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

    void setupOneImage(int x, int y, void *image, char imagem[50]){
        readimagefile(imagem, 0, 0, x, y);
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

//============================================================================

//METODOS PARA O MENU INICIAL
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
//============================================================================

//METODOS PARA BOTOES
    struct Botao {
        bool available;
        bool active;
        int xSize;
        int ySize;
        int yPasso;
        void * imagemBotaoOn;
        void * imagemBotaoOff;
        char * nickOn;
        char * nickOff;
    };

    void new_Botao(Botao *botao, int xSize, int ySize, char * nickOn, char * nickOff, int yPasso, bool available){

        botao->xSize = xSize;
        botao->ySize = ySize;
        botao->nickOn = nickOn;
        botao->nickOff = nickOff;
        botao->available = available;
        botao->active = false;
        botao->yPasso = yPasso;

    }

    void new_Botoes(Botao botoes[5], int xSize, int ySize){

        Botao botao_invocar;
        new_Botao(&botao_invocar, xSize/10, ySize/10, "images/botoes/botao_on_invocar.bmp", "images/botoes/botao_off_invocar.bmp", 3*(ySize/10), false);

        Botao botao_atacar;
        new_Botao(&botao_atacar, xSize/10, ySize/10, "images/botoes/botao_on_atacar.bmp", "images/botoes/botao_off_atacar.bmp", 3*(ySize/10), false);

        Botao botao_ativar_efeito;
        new_Botao(&botao_ativar_efeito, xSize/10, ySize/10, "images/botoes/botao_on_ativar.bmp", "images/botoes/botao_off_ativar.bmp", 3*(ySize/10), false);

        Botao botao_finalizar;
        new_Botao(&botao_finalizar, xSize/10, ySize/10, "images/botoes/botao_on_finalizar.bmp", "images/botoes/botao_off_finalizar.bmp", 9*(ySize/20), true);

        Botao botao_desistir;
        new_Botao(&botao_desistir, xSize/10, ySize/10, "images/botoes/botao_on_desistir.bmp", "images/botoes/botao_off_desistir.bmp", 3*(ySize/5), true);

        botoes[BOTAO_INVOCAR] = botao_invocar;
        botoes[BOTAO_ATACAR] = botao_atacar;
        botoes[BOTAO_ATIVAR_EFEITO] = botao_ativar_efeito;
        botoes[BOTAO_FINALIZAR] = botao_finalizar;
        botoes[BOTAO_DESISTIR] = botao_desistir;

    }

    bool verifyMouseCheckButton(int x0, int y0, int x, int y){
            if(mousex() > x0 && mousey() > y0 && mousex() < x0+x && mousey() < y0+y){
                return true;
            }
            return false;
    }

    updateButtons(int qtd_botoes, Botao botoes[5], int xSize, int ySize){

        for (size_t i = 0; i < qtd_botoes; i++)
        {
            if(botoes[i].available == true){
                if(verifyMouseCheckButton(xSize - botoes[i].xSize, botoes[i].yPasso, botoes[i].xSize, botoes[i].ySize)){
                    putimage(xSize-botoes[i].xSize, botoes[i].yPasso, botoes[i].imagemBotaoOff, COPY_PUT);
                } else {
                     putimage(xSize-botoes[i].xSize, botoes[i].yPasso, botoes[i].imagemBotaoOn, COPY_PUT);
                }
            }
            if(i != BOTAO_DESISTIR){
                    botoes[i].available = false;
            }
        }

    }

    verifyAvailableButtons(int cardOn, int cardHand, SpaceField sizeHandFields[5], Botao botoes[5], bool turn){
        if(cardOn == CARD_ON && cardHand != BLANK_CLICK){
            if(sizeHandFields[cardHand].card.type == MAGIC_CARD){
                botoes[BOTAO_ATIVAR_EFEITO].available = true;
            }

            if(sizeHandFields[cardHand].card.type == GOD_CARD){
                botoes[BOTAO_INVOCAR].available = true;
            }
        }
        botoes[BOTAO_FINALIZAR].available = turn;
    }

    int verifyButtonClick(int x, int y, int xSize, int ySize, Botao botoes[5]){

            for (size_t i = 0; i < 5; i++){
                if(x >= xSize - botoes[i].xSize && y >= botoes[i].yPasso  && x <= xSize && y <= botoes[i].yPasso + botoes[i].ySize){

                        if(botoes[i].available){
                            printf("Valor: %d \n", i);
                            return i;
                        }
                }
            }

        return BLANK_CLICK;
    }
//============================================================================

//METODOS PARA PONTUACOES
    struct Points {
        int value;
        void * imageAttackMask;
        void * imageAttack;
        void * imageLifeMask;
        void * imageLife;
        char * nickAttack;
        char * nickLife;


    };

    void new_Points(Points *points, int value, char * nickAttack, char * nickLife){
        points->value = value;
        points->nickAttack = nickAttack;
        points->nickLife = nickLife;
    }

    void new_Points(Points pontos[11]){

        char nickAttack[50];
        char nickLife[50];

            Points points_0;
            new_Points(&points_0, 0, "images/pontuacoes/ataque/Ataque0.bmp", "images/pontuacoes/vida/Vida0.bmp");
            Points points_1;
            new_Points(&points_1, 1, "images/pontuacoes/ataque/Ataque1.bmp", "images/pontuacoes/vida/Vida1.bmp");
            Points points_2;
            new_Points(&points_2, 2, "images/pontuacoes/ataque/Ataque2.bmp", "images/pontuacoes/vida/Vida2.bmp");
            Points points_3;
            new_Points(&points_3, 3, "images/pontuacoes/ataque/Ataque3.bmp", "images/pontuacoes/vida/Vida3.bmp");
            Points points_4;
            new_Points(&points_4, 4, "images/pontuacoes/ataque/Ataque4.bmp", "images/pontuacoes/vida/Vida4.bmp");
            Points points_5;
            new_Points(&points_5, 5, "images/pontuacoes/ataque/Ataque5.bmp", "images/pontuacoes/vida/Vida5.bmp");
            Points points_6;
            new_Points(&points_6, 6, "images/pontuacoes/ataque/Ataque6.bmp", "images/pontuacoes/vida/Vida6.bmp");
            Points points_7;
            new_Points(&points_7, 7, "images/pontuacoes/ataque/Ataque7.bmp", "images/pontuacoes/vida/Vida7.bmp");
            Points points_8;
            new_Points(&points_8, 8, "images/pontuacoes/ataque/Ataque8.bmp", "images/pontuacoes/vida/Vida8.bmp");
            Points points_9;
            new_Points(&points_9, 9, "images/pontuacoes/ataque/Ataque9.bmp", "images/pontuacoes/vida/Vida9.bmp");
            Points points_10;
            new_Points(&points_10, 10, "images/pontuacoes/ataque/Ataque10.bmp", "images/pontuacoes/vida/Vida10.bmp");

            pontos[0] = points_0;
            pontos[1] = points_1;
            pontos[2] = points_2;
            pontos[3] = points_3;
            pontos[4] = points_4;
            pontos[5] = points_5;
            pontos[6] = points_6;
            pontos[7] = points_7;
            pontos[8] = points_8;
            pontos[9] = points_9;
            pontos[10] = points_10;

    }
//============================================================================

    void getVelocityHologram(Holograma holograma, Holograma * holograma_pointer, int cardY){

        if(holograma.velocity_holograma <= cardY && holograma.change_holograma == 0){
            holograma_pointer->time_holograma =  2.5 + holograma.time_holograma;
        } else {
            holograma_pointer->time_holograma =  holograma.time_holograma - 2;
            holograma_pointer->change_holograma = 1;
            if(holograma.velocity_holograma <= 0){
                holograma_pointer->change_holograma = 0;
            }
        }
    }

int main()  {

    //CONFIGURACOES E VARIAVEIS INICIAIS
        int ySize = 700; //GetSystemMetrics(SM_CYSCREEN);  760
        int xSize = ySize*1.8; //GetSystemMetrics(SM_CXSCREEN); 1360

        initwindow(xSize, ySize);
        setbkcolor(COLOR(0,0,0));

        char tecla = 0;
        int pg = 2;
        int fadeOut = 0;
        int passoDeck = 0;
        int fadeIn = 255;
        int tela = TELA_MENU_PRINCIPAL;
        int cardOn = CARD_OFF;
        int cardField = BLANK_CLICK;
        int cardHand = BLANK_CLICK;
        int buttonSelected = BLANK_CLICK;
        int x, y, posXDark, posYDark;
        int xDeckPos = xSize*0.53;
        int yDeckPos = ySize*0.26;
        int yHandPos = ySize*0.73;
        int xBotaoSize = xSize/10;
        int yBotaoSize = ySize/10;
        int xLogoSize = xSize/4;
        int yLogoSize = ySize/7;
        int image_god_size = ySize*0.03;

        bool backFullCard = false;
        bool turn = true;
        bool withdraw = true;

        srand(time(0));

        Card card;
        new_Card(&card, xSize*0.085, ySize*0.21, xSize*0.05, ySize*0.03, 0, 0, DEFAULT_CARD);
        Card cardFull;
        new_Card(&cardFull, card.X*3, card.Y*3, xSize, (ySize/2) - (card.Y*1.5), card.X*7.5, 20, DEFAULT_CARD);
        SpaceField spaceField;
        new_SpaceField(xSize*0.67, card.spaceY, xSize*0.67 + card.X, card.spaceY + card.Y, &spaceField, false, DEFAULT_CARD);
        SpaceField sizeFields[20];
        new_SpaceFields(xSize, ySize, card, sizeFields);

        int cardSize = imagesize(0, 0, card.X, card.Y);
        int cardFullSize = imagesize(0, 0, cardFull.X, cardFull.Y);
        int deusSize = imagesize(0, 0, card.X*0.8, card.Y*0.6);
        int fieldSize = imagesize(0, 0, xSize, ySize);

        void *logo = addImage(xLogoSize, yLogoSize);
        void *logoMask = addImage(xLogoSize, yLogoSize);

        void *card_face_up = addImage(card.X, card.Y);
        void *card_face_up_mask = addImage(card.X, card.Y);

        void *cardFaceUpFull = addImage(cardFull.X, cardFull.Y);
        void *cardFaceUpMaskFull = addImage(cardFull.X, cardFull.Y);
        void *cardAttackPoints = addImage(cardFull.X, cardFull.Y);
        void *cardAttackPointsMask = addImage(cardFull.X, cardFull.Y);
        void *cardfaceDown = addImage(card.X, card.Y);
        void *cardfaceDownMask = addImage(card.X, card.Y);
        void *cardfaceDownEnemy = addImage(card.X, card.Y);
        void *cardfaceDownMaskEnemy = addImage(card.X, card.Y);
        void *menuImages[4];
        int qtd_botoes = 5;
        Botao botoes[qtd_botoes];
        int qtd_points = 11;
        Points pontos[qtd_points];
        int qtd_deuses = 15;
        Deus deuses[qtd_deuses];
        Deus_Imagem deuses_holograma[qtd_deuses];
        //Holograma hologramas[15];
        //new_Hologramas(hologramas);
        Holograma holograma;
        new_Holograma(&holograma);


        PlaySound(TEXT("audio/SOUNDTRACK/loading.wav"), 0, SND_LOOP | SND_ASYNC);
    //============================================================================

    //LOADING...

        int pagina = 1;
        int pagina3 = 3;
        bool menu_carregado = false;
        bool funcoes_carregado = false;
        bool campo_carregado = false;

        char *loading;
        int barra_loading = 0;
        int barra_loading_full = 500;

        while(barra_loading < barra_loading_full){

            if (pagina == 1) pagina = 2; else pagina=1;

                setactivepage(pagina);
                cleardevice();

                int xText = textwidth("CARREGANDO");
                int yText = textheight("C");
                outtextxy (xSize/2-(xText/2), ySize/2-yText, "CARREGANDO");
                xText = textwidth("...");
                outtextxy (xSize/2-(xText/2), ySize/2+(2*yText)+5, "...");

                int load = generateRandom(0,25);
                barra_loading += load;

                char porcentagem[3];
                int porcetagemValue = barra_loading*100/barra_loading_full;
                if(porcetagemValue > 100){
                    porcetagemValue = 100;
                }

                itoa(porcetagemValue,porcentagem,10);
                xText = textwidth(porcentagem);
                yText = textheight(porcentagem);
                outtextxy (xSize/2-(xText/2), ySize/2+yText+5, porcentagem);

                rectangle (xSize/2 - (barra_loading_full/2), ySize/2, xSize/2 + (barra_loading_full/2), ySize/2 + 20);
                bar (xSize/2 - (barra_loading_full/2), ySize/2, xSize/2 - (barra_loading_full/2) + barra_loading, ySize/2 + 20);
                int delayValue = generateRandom(100,300);

                setvisualpage(pagina);

                if(barra_loading > barra_loading_full/4 && menu_carregado == false){

        //IMAGENS DO MENU
                            int xText = textwidth("Carregando menu inicial...");
                            outtextxy (xSize/2-(xText/2), ySize/2+(2*yText)+5, "Carregando menu inicial...");
                            setactivepage(pagina3);

                            setupOneImage(xLogoSize, yLogoSize, logo, "images/GODS_INN_mask.bmp");
                            setupOneImage(xLogoSize, yLogoSize, logoMask, "images/GODS_INN.bmp");

                            void *menuImage = addImage(xSize, ySize);
                            void *jogarOpImage = addImage(xSize, ySize);
                            void *optionsOpImage = addImage(xSize, ySize);
                            void *creditsOpImage = addImage(xSize, ySize);

                            setupOneImage(xSize, ySize, menuImage, "images/menu/menu.bmp");
                            setupOneImage(xSize, ySize, jogarOpImage, "images/menu/jogarSelected.bmp");
                            setupOneImage(xSize, ySize, optionsOpImage, "images/menu/opcoesSelected.bmp");
                            setupOneImage(xSize, ySize, creditsOpImage, "images/menu/creditosSelected.bmp");

                            menuImages[IMAGEM_MENU_SEM_SELECAO] = menuImage;
                            menuImages[IMAGEM_JOGAR_SELECIONADO] = jogarOpImage;
                            menuImages[IMAGEM_OPCOES_SELECIONADO] = optionsOpImage;
                            menuImages[IMAGEM_CREDITOS_SELECIONADO] = creditsOpImage;

                            menu_carregado = true;
        //============================================================================
                }

                if(barra_loading > barra_loading_full/2 && funcoes_carregado == false){
        //IMAGENS DO BOTOES
                            int xText = textwidth("Carregando funcionalidades...");
                            outtextxy (xSize/2-(xText/2), ySize/2+(2*yText)+5, "Carregando funcionalidades...");
                            setactivepage(pagina3);
                            new_Botoes(botoes, xSize, ySize);

                            for (size_t i = 0; i < qtd_botoes; i++){
                                void *botaoOn = addImage(botoes[i].xSize, botoes[i].ySize);
                                botoes[i].imagemBotaoOn = botaoOn;
                                setupOneImage(botoes[i].xSize, botoes[i].ySize, botoes[i].imagemBotaoOn, botoes[i].nickOn);

                                void *botaoOff = addImage(botoes[i].xSize, botoes[i].ySize);
                                botoes[i].imagemBotaoOff = botaoOff;
                                setupOneImage(botoes[i].xSize, botoes[i].ySize, botoes[i].imagemBotaoOff, botoes[i].nickOff);
                            }

                            funcoes_carregado = true;
        //============================================================================
                }

                if(barra_loading > 3*(barra_loading_full/4) && campo_carregado == false){
        //IMAGENS DO CAMPO
                        int xText = textwidth("Carregando imagens do campo de batalha...");
                        outtextxy (xSize/2-(xText/2), ySize/2+(2*yText)+5, "Carregando imagens do campo de batalha...");
                        setactivepage(pagina3);

                        //CARREGANDO PONTUACAO
                            new_Points(pontos);

                            for (size_t i = 0; i < qtd_points; i++){
                                void *imageAttackValue = addImage(cardFull.X, cardFull.Y);
                                void *imageAttackValueMask = addImage(cardFull.X, cardFull.Y);

                                pontos[i].imageAttack = imageAttackValue;
                                pontos[i].imageAttackMask = imageAttackValueMask;

                                void *imageLifeValue = addImage(cardFull.X, cardFull.Y);
                                void *imageLifeValueMask = addImage(cardFull.X, cardFull.Y);

                                pontos[i].imageLife = imageLifeValue;
                                pontos[i].imageLifeMask = imageLifeValueMask;

                                setupImage(cardFull.X, cardFull.Y, pontos[i].imageAttack, pontos[i].imageAttackMask, pontos[i].nickAttack, "images/pontuacoes/ataque_mask.bmp");
                                setupImage(cardFull.X, cardFull.Y, pontos[i].imageLife, pontos[i].imageLifeMask, pontos[i].nickLife, "images/pontuacoes/vida_mask.bmp");

                            }
                        //============================================================================

                        //CARREGANDO DEUSES
                            new_Deuses(deuses);
                            new_Deuses_Imagem(deuses_holograma);

                            for (size_t deusIndex = 0; deusIndex < qtd_deuses; deusIndex++){
                                void *image_card_full = addImage(cardFull.X, cardFull.Y);
                                void *image_card_full_mask = addImage(cardFull.X, cardFull.Y);
                                void *image_card = addImage(card.X, card.Y);
                                void *image_card_mask = addImage(card.X, card.Y);

                                deuses[deusIndex].image_card_full = image_card_full;
                                deuses[deusIndex].image_card_full_mask = image_card_full_mask;
                                deuses[deusIndex].image_card = image_card;
                                deuses[deusIndex].image_card_mask = image_card_mask;

                                setupImage(cardFull.X, cardFull.Y, deuses[deusIndex].image_card_full, deuses[deusIndex].image_card_full_mask, deuses[deusIndex].nick, "images/card_face_up_mask.bmp");
                                setupImage(card.X, card.Y, deuses[deusIndex].image_card, deuses[deusIndex].image_card_mask, deuses[deusIndex].nick, "images/card_face_up_mask.bmp");

                                void *deus_holograma = addImage(card.X+image_god_size, card.X+image_god_size);
                                void *deus_holograma_mask = addImage(card.X+image_god_size, card.X+image_god_size);
                                deuses_holograma[deusIndex].imagem_holograma = deus_holograma;
                                deuses_holograma[deusIndex].imagem_holograma_mask = deus_holograma_mask;

                                setupImage(card.X+image_god_size, card.X+image_god_size, deuses_holograma[deusIndex].imagem_holograma, deuses_holograma[deusIndex].imagem_holograma_mask, deuses_holograma[deusIndex].path, deuses_holograma[deusIndex].path_mask);

                            }
                        //============================================================================


                            setupImage(card.X, card.Y, cardfaceDown, cardfaceDownMask, "images/cards/card_face_down.bmp", "images/cards/card_face_down_mask.bmp");
                            setupImage(card.X, card.Y, cardfaceDownEnemy, cardfaceDownMaskEnemy, "images/cards/card_face_down_enemy.bmp", "images/cards/card_face_down_enemy_mask.bmp");
                            setupImage(card.X, card.Y, card_face_up, card_face_up_mask, "images/card_face_up.bmp", "images/card_face_up_mask.bmp");

                            campo_carregado = true;
        //============================================================================
                }
                delay(delayValue);
        }

        PlaySound(TEXT("audio/SOUNDTRACK/menu.wav"), 0, SND_FILENAME | SND_ASYNC);
    //============================================================================

    //FADE IN FADE OUT e VELOCIDADE
        int x1FadeSize = 0;
        int y1FadeSize = ySize/2;
        int x2FadeSize = xSize;
        int y2FadeSize = ySize/2;
        int stangle = 90;
        int endangle = 270;
        int stangleSpaceSize = 90;
        int endangleSpaceSize = 270;

        int changeFade = 0;
        int change = 0;
        int tempo = 0;
        int velocidade = 0;
        double aceleration = 0.03;
    //============================================================================

    //Construindo a mão própria e do adversário
        SpaceField deckSize;
        new_SpaceField(xSize*0.53, ySize/2, xSize*0.53+card.X, ySize/2 + card.Y, &deckSize);
        SpaceField deckEnemySize;
        new_SpaceField(deckSize.left, deckSize.top - card.Y - card.spaceY, deckSize.left + card.X, deckSize.top - card.spaceY, &deckEnemySize);

        Card deck[20];
        buildDeck(deck, deuses);

        int amountHand = 3;
        int amountHandEnemy = 4;
        int amountDeck = 19 - amountHand;

        SpaceField sizeHandFields[5];
        new_SpaceHandFields(xSize, ySize/2 + card.Y + card.spaceY, card, sizeHandFields);
        sizeHandFields[0].card = deck[19];
        sizeHandFields[1].card = deck[18];
        sizeHandFields[2].card = deck[17];
        sizeHandFields[2].card.type = MAGIC_CARD;
        sizeHandFields[3].card = deck[16];

        SpaceField sizeHandFieldsEnemy[5];
        new_SpaceHandFields(xSize, card.spaceY, card, sizeHandFieldsEnemy);
    //============================================================================

    //COR DO CAMPO
        int cor_g_campo = 100;
        int cor_g_campo_aux = 0;
        int cor_g_campo_aux2 = 0;

        int cor_g_holograma = cor_g_campo;
        int cor_g_holograma_aux = 0;
    //============================================================================

    Radius radiuses[20];
    Radius radius;
    new_Radius(&radius);

    for (size_t i = 0; i < 20; i++)
    {
        radiuses[i] = radius;
    }

    int holograma_summon_color = cor_g_campo;

    while(tecla != 27) {

    //CONFIGURACOES / PAGINACAO
        if (pg == 1) pg = 2; else pg=1;
        setactivepage(pg);
        cleardevice();
    //============================================================================

        //NUANCES DO HOMOLOGRAMA
            int holograma_color = COLOR(30,cor_g_holograma,50);
            holograma_summon_color = COLOR(30,cor_g_holograma,50);
            if(cardOn == CARD_OFF){
                holograma_color = cor_g_campo;
            }

            if(cor_g_holograma_aux == 0){
                if(cor_g_holograma < 150){
                    cor_g_holograma += 2;
                } else {
                    cor_g_holograma_aux = 1;
                }
            } else {
                if(cor_g_holograma > 100){
                    cor_g_holograma -= 2;
                } else {
                    cor_g_holograma_aux = 0;
                }
            }
        //=======================================

        //NUANCES DO CAMPO
            int campo_color = COLOR(50,cor_g_campo,50);
            setbkcolor(campo_color);

            if(cor_g_campo_aux == 0){
                if(cor_g_campo < 80){

                    if(cor_g_campo_aux2 % 5 == 0){
                        cor_g_campo++;
                    }
                    cor_g_campo_aux2++;
                } else {
                    cor_g_campo_aux = 1;
                }

            } else {
                if(cor_g_campo > 70){

                    if(cor_g_campo_aux2 % 5 == 0){
                        cor_g_campo--;
                    }
                    cor_g_campo_aux2++;
                } else {
                    cor_g_campo_aux = 0;
                }
            }
        //=======================================

    //TELA DO MENU PRINCIPAL
        if(tela == TELA_MENU_PRINCIPAL || tela == TELA_FADE_OUT){
            putimage(0, 0, menuImages[IMAGEM_MENU_SEM_SELECAO], 0);
            tela = verifyMenuClick(xSize, ySize, menuImages, tela);
            clearmouseclick(WM_LBUTTONDOWN);
            putCardField(xSize/2, (ySize/2) - (yLogoSize/2), logo, logoMask);

        }
    //============================================================================

    //TELA DE DUELO
        if(tela == TELA_DUELO || tela == TELA_FADE_IN){

            if(turn == true){

                putCardField(xSize*0.635, (ySize/2) - (yLogoSize/2) , logo, logoMask);
                if(withdraw == true && turn == true && amountHand < 4 && amountDeck >= 0){
                    amountHand += 1;
                    sizeHandFields[amountHand].card = deck[amountDeck];
                    amountDeck -= 1;
                    withdraw = false;
                }

                //Deck
                putCardField(deckSize.left, deckSize.top, cardfaceDown, cardfaceDownMask);
                putCardField(deckEnemySize.left, deckEnemySize.top, cardfaceDownEnemy, cardfaceDownMaskEnemy);

                //Mão
                for (size_t i = 0; i < 4; i++){
                    if(sizeHandFields[i].active){
                        putCardField(sizeHandFields[i].left, sizeHandFields[i].top, sizeHandFields[i].card.deus.image_card, sizeHandFields[i].card.deus.image_card_mask);
                    }
                    putCardField(sizeHandFieldsEnemy[i].left, sizeHandFieldsEnemy[i].top, cardfaceDownEnemy, cardfaceDownMaskEnemy);
                }

                verifyAvailableButtons(cardOn, cardHand, sizeHandFields, botoes, turn);

            //CONTROLE (MOUSE)
                int posClickX = 0;
                int posClickY = 0;
                bool clickOn = ismouseclick(WM_LBUTTONDOWN);
                if(clickOn){
                    getmouseclick(WM_LBUTTONDOWN, posClickX, posClickY);

                        buttonSelected = verifyButtonClick(posClickX, posClickY, xSize, ySize, botoes);

                        if(cardField == BLANK_CLICK && buttonSelected == BLANK_CLICK){
                            cardHand = verifyCardHandClick(&tela, posClickX, posClickY, cardOn, &cardOn, &backFullCard, sizeHandFields, amountHand);
                        }
                        if(cardHand == BLANK_CLICK && buttonSelected == BLANK_CLICK){
                            cardField = verifyCardFieldClick(&tela, posClickX, posClickY, cardOn, &cardOn, &backFullCard, sizeFields);
                        }

                        passoDeck = verifyDeckClick(posClickX, posClickY, deckSize);

                }
            //======================    ======================================================

            if(buttonSelected == BOTAO_INVOCAR){
                int cont_spaces_summon = 0;
                bool summon = false;

                if(sizeHandFields[cardHand].card.type == GOD_CARD){
                    while (cont_spaces_summon < 20 && summon == false){
                        if(sizeFields[cont_spaces_summon].card.type == GOD_CARD && sizeFields[cont_spaces_summon].available == true){
                            sizeFields[cont_spaces_summon].card = sizeHandFields[cardHand].card;
                            sizeFields[cont_spaces_summon].active = true;
                            sizeFields[cont_spaces_summon].available = false;
                            sizeHandFields[cardHand].active = false;
                            buttonSelected = BLANK_CLICK;
                            cardHand = BLANK_CLICK;
                            summon = true;
                            amountHand--;
                        }
                        cont_spaces_summon++;
                    }
                }
            }

            if(buttonSelected == BOTAO_FINALIZAR){
                turn = false;
            }

            updateButtons(qtd_botoes, botoes, xSize, ySize);

            selectCardField(xSize, cardOn, cardField, sizeFields, cardFull, &cardFull, backFullCard, &backFullCard);
            selectCardHand(xSize, cardOn, cardHand, sizeHandFields, cardFull, &cardFull, backFullCard, &backFullCard);
            selectAmountDeck(deckSize.left + (card.X/2), deckSize.top + (card.Y/2), passoDeck, &passoDeck, amountDeck);

            putCardField(cardFull.spaceX, cardFull.spaceY, deuses[sizeHandFields[cardHand].card.deus.id].image_card_full, deuses[sizeHandFields[cardHand].card.deus.id].image_card_full_mask);
            putCardField(cardFull.spaceX, cardFull.spaceY, pontos[sizeHandFields[cardHand].card.deus.attackPoints].imageAttack, pontos[sizeHandFields[cardHand].card.deus.attackPoints].imageAttackMask);
            putCardField(cardFull.spaceX, cardFull.spaceY, pontos[sizeHandFields[cardHand].card.deus.lifePoints].imageLife, pontos[sizeHandFields[cardHand].card.deus.lifePoints].imageLifeMask);

            //Verifica e coloca cards no campo
            holograma.velocity_holograma = holograma.time_holograma * holograma.aceleration_holograma;
            getVelocityHologram(holograma, &holograma, card.Y*0.12);
            for (size_t i = 0; i < 20; i++){
                if(sizeFields[i].available == false){

                    //putCardField(sizeFields[i].left, sizeFields[i].top, card_face_up, card_face_up_mask);
                    //bar(xRand, yRand, xRand+15, yRand+15);
                    //putCardField(sizeFields[i].left-(image_god_size/2), sizeFields[i].top-holograma.velocity_holograma, deuses_holograma[sizeFields[i].card.deus.id].imagem_holograma, deuses_holograma[sizeFields[i].card.deus.id].imagem_holograma_mask);
                    setcolor(holograma_summon_color);
                    setfillstyle(INTERLEAVE_FILL, holograma_summon_color);
                    fillellipse(sizeFields[i].left+(card.X/2), sizeFields[i].top+(3*(card.Y/4)), radiuses[i].xradius, radiuses[i].yradius);

                    if(radiuses[i].xradius < card.X/2){
                        radiuses[i].yradius += 1;
                        radiuses[i].xradius += 2;
                    } else {
                        putCardField(sizeFields[i].left-(image_god_size/2), sizeFields[i].top-holograma.velocity_holograma, deuses_holograma[sizeFields[i].card.deus.id].imagem_holograma, deuses_holograma[sizeFields[i].card.deus.id].imagem_holograma_mask);

                        /**
                        for(int j = 0; j < 200;j++){
                            int xRand = generateRandom(sizeFields[i].left, sizeFields[i].right);
                            int yRand = generateRandom(sizeFields[i].top, sizeFields[i].bottom);
                            setfillstyle(1, YELLOW);
                            fillellipse(xRand, yRand, 3, 3);
                            fillellipse(xRand-1, yRand+1, 3, 3);
                            fillellipse(xRand+1, yRand-1, 3, 3);
                            fillellipse(xRand+1, yRand+1, 3, 3);
                            fillellipse(xRand-1, yRand-1, 3, 3);
                            //bar(xRand, yRand, xRand+7, yRand+7);
                        }**/

                        //for(int j = 0; j < 500;j++){
                        //    int xRand = generateRandom(sizeFields[i].left, sizeFields[i].right);
                        //    int yRand = generateRandom(sizeFields[i].top, sizeFields[i].bottom);
                        //    setfillstyle(1, campo_color);
                        //    bar(xRand, yRand, xRand+15, yRand+15);
                        //}
                    }
                }
            }


            if(cardField != BLANK_CLICK){
                putCardField(cardFull.spaceX, cardFull.spaceY, deuses[sizeFields[cardField].card.deus.id].image_card_full, deuses[sizeFields[cardField].card.deus.id].image_card_full_mask);
                putCardField(cardFull.spaceX, cardFull.spaceY, pontos[sizeFields[cardField].card.deus.lifePoints].imageLife, pontos[sizeFields[cardField].card.deus.lifePoints].imageLifeMask);
                putCardField(cardFull.spaceX, cardFull.spaceY, pontos[sizeFields[cardField].card.deus.lifePoints].imageAttack, pontos[sizeFields[cardField].card.deus.lifePoints].imageAttackMask);
            }

                //HOLOGRAMA: SLOTS
                    int left_holo[20];
                    int right_holo[20];
                    if(cardOn == CARD_OFF){
                        for (size_t j = 0; j < 20; j++){
                                left_holo[j] = sizeFields[j].left + (card.X/2);
                                right_holo[j] = sizeFields[j].right - (card.X/2);
                        }
                    }

                    if(cardOn == CARD_ON && cardHand != BLANK_CLICK){
                        for (size_t j = 0; j < 20; j++){
                            setfillstyle(WIDE_DOT_FILL, holograma_color);
                            if(sizeHandFields[cardHand].card.type == MAGIC_CARD){
                                if(sizeFields[j].card.type == MAGIC_CARD && sizeFields[j].available == true){

                    setcolor(holograma_summon_color);
                    setfillstyle(INTERLEAVE_FILL, holograma_summon_color);
                    fillellipse(sizeFields[j].left+(card.X/2), sizeFields[j].top+(3*(card.Y/4)), radiuses[j].xradius, radiuses[j].yradius);

                    if(radiuses[j].xradius < card.X/2){
                        radiuses[j].yradius += 1;
                        radiuses[j].xradius += 2;
                    }

                                    //bar(left_holo[j], sizeFields[j].top , right_holo[j], sizeFields[j].bottom);
                                    //setcolor(WHITE);
                                    //pieslice(left_holo[j], (sizeFields[j].top + card.Y/2), stangleSpaceSize, endangleSpaceSize, 5);
                                    //pieslice(right_holo[j], (sizeFields[j].top + card.Y/2), endangleSpaceSize, stangleSpaceSize, 5);
                                    //setfillstyle(SOLID_FILL, BLACK);

                                }
                            }
                            if(sizeHandFields[cardHand].card.type == GOD_CARD){
                                if(sizeFields[j].card.type == GOD_CARD && sizeFields[j].available == true){

                    setcolor(holograma_summon_color);
                    setfillstyle(INTERLEAVE_FILL, holograma_summon_color);
                    fillellipse(sizeFields[j].left+(card.X/2), sizeFields[j].top+(3*(card.Y/4)), radiuses[j].xradius, radiuses[j].yradius);

                    if(radiuses[j].xradius < card.X/2){
                        radiuses[j].yradius += 1;
                        radiuses[j].xradius += 2;
                    }


                                    //bar(left_holo[j], sizeFields[j].top , right_holo[j], sizeFields[j].bottom);
                                    //setcolor(WHITE);
                                    //pieslice(left_holo[j], (sizeFields[j].top + card.Y/2), stangleSpaceSize, endangleSpaceSize, 5);
                                    //pieslice(right_holo[j], (sizeFields[j].top + card.Y/2), endangleSpaceSize, stangleSpaceSize, 5);
                                    //setfillstyle(SOLID_FILL, BLACK);
                                }
                            }
                            if(left_holo[j] > sizeFields[j].left){
                                left_holo[j] -= 2;
                                right_holo[j] += 2;
                            }
                        }
                        setfillstyle(SOLID_FILL, BLACK);
                    }
                //==========================================
        }
    }

    //============================================================================

    //FADE IN FADE OUT
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
                setfillstyle(SOLID_FILL, BLACK);}

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
    //============================================================================

    //CONFIGURACOES / PAGINACAO
        setvisualpage(pg);
        if (kbhit())
        tecla = getch();
        delay(15);
    //============================================================================

    }

    closegraph();
    return 0;
}















































    // posXDark = xSize*0.025;
    // posYDark = ySize/2;

    // for (size_t j = 0; j < 5; j++){
    //     putCardField(posXDark, posYDark, cardFaceUp, cardFaceUpMask);


    //     putCardField(posXDark + (card.X*0.1), posYDark + (card.Y*0.2) - velocidade, deusImagem, deusImagemMask);
    //     posXDark = posXDark + card.X*1.2;
    // }

    // putCardField(posXDark, posYDark, cardfaceDown, cardfaceDownMask);


