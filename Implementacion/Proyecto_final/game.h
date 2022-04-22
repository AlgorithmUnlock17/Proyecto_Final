#ifndef GAME_H
#define GAME_H
//Para esta parte del codigo se toma como referencia (y solo referencia) el codigo puesto en el classroom de las monitorias
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <stdlib.h>
#include <stdio.h>
#include <QTextStream>
#include "tico.h"
#include "button.h"
#include "platform.h"
#include "bacteria.h"
#include "pajaro.h"
#include "dialog.h"
#include <QGraphicsTextItem>
#include <vector>
#include <QLCDNumber>
using namespace std;
class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    QGraphicsScene *scene;
    QLCDNumber *levelnumber,*livesnumber;
    void clearscene(QGraphicsScene *scene);
    void menu();
    void save_game();
    //Aquí se van agregando escenarios (o en slots, dependiendo de lo que se necesite)
    int getLevel() const;
    void setLevel(int newLevel);
    void lev1();
    void lev2();
    void lev3();
    void lev4();
    void lev5();
    void lev6();
    void lev7();
    void lev8();
    int getTico_vidas() const;
    void setTico_vidas(int newTico_vidas);

    void setUsuarios(const std::list<std::pair<std::string, int> > &newUsuarios);

    void setPlayer(const std::string &newPlayer);

private:
    Tico *tico=new Tico(50,650);;
    int level; //nivel donde está el jugador, se guardara
    bool check=true;
    // botones del menu principal y otros
    Button *playButton,*saveButton,*quitButton,*Bmenu;
    std::list<std::pair<std::string,int>> usuarios;
    std::string player;
    //textos del juego
    QGraphicsTextItem *number,*level_display,*lives_display,*titleText;
    vector <QGraphicsRectItem *> Vplataformas;
    vector <QGraphicsItem *> Vbacterias,Vpajaros;

    // mapas de cada level, divido la scena en cuadros de 50x50 px
    // el 1 representa plataforma inmovil, el 2 representa plataforma con movimiento
    // el 3 representa plataforma tipo resorte, como las plataformas son de 100 de ancho, es necesario dejar minimo un espacio
    // entre plataforma y plataforma
    int tico_vidas=3;
    unsigned short int MapLevel1[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {1,0,1,0,1,0,1,0,1,0,1,0}};
    unsigned short int MapLevel2[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    unsigned short int MapLevel3[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    unsigned short int MapLevel4[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,3,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    unsigned short int MapLevel5[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    unsigned short int MapLevel6[15][12]={
        {0,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,2,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,3,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    unsigned short int MapLevel7[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};


public slots:
    void start();
    void reanudar();
    void decero();
    void close();
    void backMenu();
};

#endif // GAME_H

