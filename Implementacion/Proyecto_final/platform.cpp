#include "platform.h"
#include <QBrush>

platform::platform(int x, int y):
posx(x),posy(y) // Inicialización de variables heredadas con el constructor de la clase base
{
    setRect(0,0,sizex,sizey);
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);
    //connect(mov_timer,SIGNAL(timeout()),this,SLOT(movY())); // esta no se conecta porque es estática
}

void platform::posicion() //metodo (sobrecargado) llamado en el constructor para posicionar personaje
{
    setPos(posx,posy);
}
void platform::posicion(int newX,int newY) // Actualizar posición con parametros
{
    posx=newX;
    posy=newY;
    setPos(posx,posy);
}

float platform::getPosx() const
{
    return posx;
}
float platform::getPosy() const
{
    return posy;
}
int platform::getSizex() const
{
    return sizex;
}
int platform::getSizey() const
{
    return sizey;
}
