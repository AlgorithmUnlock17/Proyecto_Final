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
    Bacteria(float x,float y,float xf, float yf); //Este es el constructor para las plataformas de mov simple
    void posicion();
    void posicion(int newX,int newY);
private:
    QTimer *movi_timer=new QTimer();
    QTimer *movi2_timer=new QTimer();
    float cx; //centro en x
    float cy; //centro en y
    float posx;
    float posy;
    float rad;
    float angulo;
    float iy;
    float ix;
    float fy;
    float fx;
    bool dir=0;
    const float w=0.1; //velocidad angular
public slots:
    void mov(); //movimiento circular
    void mov2(); //movimiento de un lado a otro

};

#endif // BACTERIA_H
