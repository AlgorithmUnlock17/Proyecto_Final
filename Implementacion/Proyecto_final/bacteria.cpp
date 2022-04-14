#include "bacteria.h"
#include "game.h"
#include <QDebug>
extern Game * game;
Bacteria::Bacteria(float x, float y, float rad):
    cx(x),cy(y),rad(rad)
{
    setPixmap(QPixmap(":/Sprites/Tico.png")); // Lectura de sprite
    posx=rad+cx;
    posy=cy;
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    connect(movi_timer,SIGNAL(timeout()),this,SLOT(mov()));
    movi_timer->start(10);
}

void Bacteria::mov() //no me esta funcionando jeje
{
    angulo=angulo+w*DT;
    posx=cx+rad*cos(angulo);
    posy=cy+rad*sin(angulo);
    //qDebug()<<"x: "<<posx<<", y: "<<posy;
    posicion();
    QList<QGraphicsItem *> list = collidingItems();
    foreach(QGraphicsItem * i , list) //es probable que tenga que mover esto a la parte de las plataformas, para que el mov de tico varie por plataforma
    {
        Tico * item= dynamic_cast<Tico *>(i); //Con esto se hace la colision con cada plataforma
        if (item)
        {
            game->start();
        }
    }
}
void Bacteria::posicion() //metodo (sobrecargado) llamado en el constructor para posicionar personaje
{
    setPos(posx,posy);
}
void Bacteria::posicion(int newX,int newY) // Actualizar posición con parametros
{
    posx=newX;
    posy=newY;
    setPos(posx,posy);
}
