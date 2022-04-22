#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPainter>
#include <QImage>
#include "tico.h"
#include "game.h"

class platform: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    platform(float x,float y); //plataforma sin movimiento
    platform(float x,float y,float xf, float yf); //Este es el constructor para las plataformas de mov simple
    platform(float x,float y, bool flag); //plataforma sin movimiento
    void posicion();
    void posicion(float newX,float newY);
    float getPosx() const;
    float getPosy() const;
    int getSizex() const;
    int getSizey() const;

private:
    QTimer *mov_timer1=new QTimer();
    QTimer *mov_timer2=new QTimer();
    const int sizex=100;
    const int sizey=20 ;
    float posx;
    float posy;
    float iy;
    float ix;
    float fy;
    float fx;
    float velx;
    float vely;
    bool dir=0;
    int duracion;
public slots:
    void mov();
    void mov2();
    void mov3();
};

#endif // PLATFORM_H
