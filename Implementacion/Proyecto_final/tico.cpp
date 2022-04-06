#include "tico.h"

Tico::Tico(float posX_, float posY_):
    posX(posX_),posY(posY_)
{
    setPixmap(QPixmap(":/Sprites/OPEN.png"));
    posicion();
}
float Tico::getPosX() const
{
    return posX;
}
void Tico::setPosX(float newPosX)
{
    posX = newPosX;
}
float Tico::getPosY() const
{
    return posY;
}
void Tico::setPosY(float newPosY)
{
    posY = newPosY;
}
float Tico::getVelX() const
{
    return velX;
}
void Tico::setVelX(float newVelX)
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
void Tico::posicion()
{
    setPos(posX,posY);
}
void Tico::posicion(int newX,int newY)
{
    posX=newX;
    posY=newY;
    setPos(posX,posY);
}
int Tico::getTamanoX() const
{
    return tamanoX;
}
int Tico::getTamanoY() const
{
    return tamanoY;
}
void Tico::movY()
{
    velY = velY+(DT*(-G));
    posY +=-velY*DT+(-G)*DT*DT*0.5;
    if (posY>800-tamanoY){
        posicion(posX,800-tamanoY);
        velY=0;
    }
    posicion();
}
