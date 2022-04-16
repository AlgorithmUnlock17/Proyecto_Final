#ifndef PAJARO_H
#define PAJARO_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QMainWindow>
#include "game.h"

class pajaro: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    pajaro(float x,float y,float xf, float yf); //Este es el constructor para las plataformas de mov simple
    void posicion();
    void posicion(int newX,int newY);
private:
    QTimer *movi_timer=new QTimer();
    float posx;
    float posy;
    float iy;
    float ix;
    float fy;
    float fx;
    bool dir=0;
public slots:
    void mov(); //movimiento de un lado a otro
    //void pew(); //disparar semilla
};

#endif // PAJARO_H
