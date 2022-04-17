#ifndef SEMILLA_H
#define SEMILLA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QMainWindow>
#include "game.h"

class semilla: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    semilla(float x,float y,bool dir); //Este es el constructor
    void posicion();
    void posicion(int newX,int newY);
private:
    QTimer *mov_timer=new QTimer();
    float posx;
    float posy;
    bool dir=0;
public slots:
    void mov(); //movimiento de semilla
};


#endif // SEMILLA_H
