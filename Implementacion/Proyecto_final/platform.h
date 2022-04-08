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
    //platform(int x,int y,int xf, int yf); //Este es el contructor para las plataformas de mov simple
    void posicion();
    void posicion(int newX,int newY);
    float getPosx() const;

    float getPosy() const;

    int getSizex() const;

    int getSizey() const;

private:
    QTimer *mov_timer;
    int sizex=100;
    int sizey=20 ;
    float posx;
    float posy;
    float velx;
    float vely;
    int duracion;
public slots:
    //void mov(int ipox,int ipoy,int fpox,int fpoy); //inicial y final, mov lineal
};

#endif // PLATFORM_H
