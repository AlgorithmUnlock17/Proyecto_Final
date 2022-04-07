#ifndef GAME_H
#define GAME_H
//Para esta parte del codigo se toma como referencia (y solo referencia) el codigo puesto en el classroom de las monitorias
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "tico.h"
#include "button.h"
class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    QGraphicsScene *scene;
    Tico *tico;
    void menu();
    void clean_scene();
    //Aquí se van agregando escenarios (o en slots, dependiendo de lo que se necesite)
private:
    //bool juego; //esta variable servirá para notar si se está en sesión o no
    int level=0; //nivel donde está el jugador, se guardara

public slots:
    void start();
};

#endif // GAME_H

