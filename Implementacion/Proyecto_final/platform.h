#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QObject>
//#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include "tico.h"

class platform: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    platform(int x,int y); //plataforma sin movimiento
    platform(int x,int y,int xf, int yf); //Este es el constructor para las plataformas de mov simple
    void posicion();
    void posicion(int newX,int newY);
    float getPosx() const;
    float getPosy() const;
    int getSizex() const;
    int getSizey() const;
    void mov(int fpox,int fpoy, int ix,int iy);

private:
    QTimer *mov_timer1=new QTimer();
    QTimer *mov_timer2=new QTimer();
    const int sizex=100;
    const int sizey=20 ;
    float posx;
    float posy;
    int iy;
    int ix;
    int fy;
    int fx;
    float velx;
    float vely;
    bool dir=0;
    int duracion;
public slots:
    void mov();
    void conectlin(); //pos final, mov lineal
};

#endif // PLATFORM_H
