#ifndef GAME_H
#define GAME_H
//Para esta parte del codigo se toma como referencia (y solo referencia) el codigo puesto en el classroom de las monitorias
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <stdlib.h>
#include <stdio.h>
#include "tico.h"
#include "button.h"
#include "platform.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    QGraphicsScene *scene;
    Tico *tico;
    void clearscene(QGraphicsScene *scene);
    void menu();
    void clean_scene(); //metodo para limpiar escena
    //Aquí se van agregando escenarios (o en slots, dependiendo de lo que se necesite)
private:
    //bool juego; //esta variable servirá para notar si se está en sesión o no
    int level=0; //nivel donde está el jugador, se guardara

public slots:
    void start();
    void close();
    void backMenu();
};

#endif // GAME_H
