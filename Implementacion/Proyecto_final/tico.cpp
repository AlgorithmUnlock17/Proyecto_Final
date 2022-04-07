#include "tico.h"
#include <QKeyEvent>
#include <QDebug>
#include "game.h"
extern Game * game;
Tico::Tico(float posX_, float posY_):
    posX(posX_),posY(posY_) // Inicialización de variables heredadas con el constructor de la clase base
{
    setPixmap(QPixmap(":/Sprites/Tico.png")); // Lectura de sprite
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    movY_timer=new QTimer(this); //Timer para salto
    connect(movY_timer,SIGNAL(timeout()),this,SLOT(movY()));
}
void Tico::keyPressEvent(QKeyEvent *event) //Teclas
{
    if (event->key()==Qt::Key_Space && !movY_timer->isActive()){
        velY=50;
        movY_timer->stop();
        movY_timer->start(10);
    }
    if (event->key()==Qt::Key_D){
        if (posX<(600-tamanoX)){
            posX=posX+velX;
        }
        else posicion(600-tamanoX,posY);
    }
    if (event->key()==Qt::Key_A){
        if (posX>(0)){
            posX=posX-velX;
        }
        else posicion(0,posY);
    }
    if (event->key()==Qt::Key_E){ //vuelve al menu con e, muy inestable, revisar estabilidad, tal vez sirva crear una funcion de limpiar escena
        movY_timer->stop();
        game->menu();
    }
    posicion();
}
void Tico::movY() // salto con gravedad
{
    velY = velY+(DT*(-G));
    posY +=-velY*DT+(-G)*DT*DT*0.5;
    posicion();
    if (posY>700-tamanoY){
        posicion(posX,700-tamanoY);
        velY=0;
        movY_timer->stop();
    }
}
void Tico::posicion() //metodo (sobrecargado) llamado en el constructor para posicionar personaje
{
    setPos(posX,posY);
}
void Tico::posicion(int newX,int newY) // Actualizar posición con parametros
{
    posX=newX;
    posY=newY;
    setPos(posX,posY);
}
/*
float Tico::getPosX() const //metodo para retornar el valor de posX
{
    return posX;
}
void Tico::setPosX(float newPosX) //metodo para actualizar valos de posX
{
    posX = newPosX;
}
float Tico::getPosY() const //metodo para retornar valor de posY
{
    return posY;
}
void Tico::setPosY(float newPosY) //metodo para actualizar valos de posY
{
    posY = newPosY;
}
float Tico::getVelX() const //Retornar VelX
{
    return velX;
}
void Tico::setVelX(float newVelX) //ActualizarVelX
{
    velX = newVelX;
}
float Tico::getVelY() const
{
    return velY;
}
void Tico::setVelY(float newVelY)
{
    velY = newVelY;
}
int Tico::getVidas() const
{
    return vidas;
}
void Tico::setVidas(int newVidas)
{
    vidas = newVidas;
}
int Tico::getTamanoX() const //Tamaño personaje en x(width)
{
    return tamanoX;
}
int Tico::getTamanoY() const // Tamaño personaje en y (high)
{
    return tamanoY;
}*/
