#ifndef TICO_H
#define TICO_H
#define G 5
#define DT 0.1 //cada cuantos milisegundos se actualiza
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QList>

class Tico: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tico(float x, float y);

    void keyPressEvent(QKeyEvent *event);
    /*// Es probable que estos métodos no se necesiten porque se trabaja el movimiento en la misma clase, se dejan por si acaso
    float getPosX() const;
    void setPosX(float newPosX);
    float getPosY() const;
    void setPosY(float newPosY);
    float getVelX() const;
    void setVelX(float newVelX);
    float getVelY() const;
    void setVelY(float newVelY);
    int getVidas() const;
    void setVidas(int newVidas);
    int getTamanoX() const;
    int getTamanoY() const;*/
    void posicion();
    void posicion(int newX,int newY);

public slots:
    void movY(); //En este se hace lo del movimiento parabolico
private:
    //Cambiar tamano cuando se cambie el sprite
    const int tamanoX=50;
    const int tamanoY=50;
    float posX;
    float posY;
    float velX=10;
    float velY=100;
    int vidas=5;
    QTimer *movY_timer;
    bool encima=false;
    bool salto;
};

#endif // TICO_H
