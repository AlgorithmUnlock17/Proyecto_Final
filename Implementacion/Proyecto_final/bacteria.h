#ifndef BACTERIA_H
#define BACTERIA_H
#define DT 0.1 //cada cuantos milisegundos se actualiza
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QMainWindow>
#include <math.h>

class Bacteria: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bacteria(float x, float y,float rad);
private:
    QTimer *movi_timer=new QTimer();
    void posicion();
    void posicion(int newX,int newY);
    float cx; //centro en x
    float cy; //centro en y
    float posx;
    float posy;
    float rad;
    float angulo;
    const float w=0.1; //velocidad angular
public slots:
    void mov();
};

#endif // BACTERIA_H
