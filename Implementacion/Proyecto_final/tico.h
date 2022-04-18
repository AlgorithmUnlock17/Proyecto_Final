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
    //void keyPressEvent(QKeyEvent *event); // por definición el metodo debe ir protegido
    float getPosX() const;
    void setPosX(float newPosX);
    float getPosY() const;
    void setPosY(float newPosY);
    float getVelX() const;
    void setVelX(float newVelX);
    float getVelY() const;
    void setVelY(float newVelY);
    int getTamanoX() const;
    int getTamanoY() const;
    void posicion();
    void posicion(int newX,int newY);
    bool getEncima() const;
    void setEncima(bool newEncima);
    bool getSalto() const;
    void setSalto(bool newSalto);
    void start();
    void stop();

protected:
     void keyPressEvent(QKeyEvent *event); //Protegido para no generar conflictos

public slots:
    void movY(); //En este se hace lo del movimiento parabolico
private:
    //Cambiar tamano cuando se cambie el sprite
    const int tamanoX=50;
    const int tamanoY=50;
    float posX;
    float posY;
    float velX=14;
    float velY=0;
    QTimer *movY_timer;
    bool encima=true;
    bool salto;
};

#endif // TICO_H
