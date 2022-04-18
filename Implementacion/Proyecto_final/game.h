#ifndef GAME_H
#define GAME_H
//Para esta parte del codigo se toma como referencia (y solo referencia) el codigo puesto en el classroom de las monitorias
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <stdlib.h>
#include <stdio.h>
#include <QFile>
#include <QTextStream>
#include "tico.h"
#include "button.h"
#include "platform.h"
#include "bacteria.h"
#include "pajaro.h"
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
    void clean_scene(); //metodo para limpiar escena
    void save_game();
    void load_game();
    //Aquí se van agregando escenarios (o en slots, dependiendo de lo que se necesite)
    int getLevel() const;
    void setLevel(int newLevel);
    void lev1();
    void lev2();
    void lev3();
    void lev4();
    int getTico_vidas() const;
    void setTico_vidas(int newTico_vidas);

private:
    Tico *tico=new Tico(50,650);;
    //bool juego; //esta variable servirá para notar si se está en sesión o no
    int level=0; //nivel donde está el jugador, se guardara
    QGraphicsTextItem * titleText; // Asigno un apuntador a item de texto para titulo de menu
    // botones del menu principal
    Button *playButton,*saveButton,*quitButton;
    //boton para volver al menu
    Button *Bmenu;
    QGraphicsTextItem *number;
    QGraphicsTextItem *level_display,*lives_display;
    vector <QGraphicsRectItem *> Vplataformas;
    vector <QGraphicsItem *> Vbacterias;
    vector <QGraphicsItem *> Vpajaros;

    // mapas de cada level, divido la scena en cuadros de 50x50 px
    // el 1 representa plataforma inmovil, el 2 representa plataforma con movimiento
    // el 3 representa plataforma tipo resorte, como las plataformas son de 100 de ancho, es necesario dejar minimo un espacio
    // entre plataforma y plataforma
    int tico_vidas=3;
    int MapLevel1[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,1,0,1,0,1,0,1,0,1,0}};
    int MapLevel2[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    int MapLevel3[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};
    int MapLevel4[15][12]={
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,3,0,0,0,0,0},
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

