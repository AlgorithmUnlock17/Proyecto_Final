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
Bacteria::Bacteria(float x,float y,float xf,float yf): //plataforma de mov simple
posx(x),posy(y),ix(x),iy(y),fx(xf),fy(yf) // Inicialización de variables heredadas con el constructor de la clase base
{
    setPixmap(QPixmap(":/Sprites/Tico.png")); // Lectura de sprite
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    connect(movi2_timer,SIGNAL(timeout()),this,SLOT(mov3())); // esta no se conecta porque es estática
    movi2_timer->start(10);
}
void Bacteria::mov() //me esta funcionando jeje
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
void Bacteria::mov2()
{
    int finalx;
    int finaly;
    if (dir==0){
        finalx=fx;
        finaly=fy;
        if(posx<finalx)
            posx++;
        if (posx>finalx)
            posx--;
        if(posy<finaly)
            posy++;
        if(posy>finaly)
            posy--;
        if (posx==finalx && posy==finaly){
            dir=1;
        }
    }
    if (dir==1){
        finalx=ix;
        finaly=iy;
        if(posx<finalx)
            posx++;
        if (posx>finalx)
            posx--;
        if(posy<finaly)
            posy++;
        if(posy>finaly)
            posy--;
        if (posx==finalx && posy==finaly){
            dir=0;
        }
    }

    QList<QGraphicsItem *> list = collidingItems() ;
    foreach(QGraphicsItem * i , list) //es probable que tenga que mover esto a la parte de las plataformas, para que el mov de tico varie por plataforma
    {
        Tico * item= dynamic_cast<Tico *>(i); //Con esto se hace la colision con cada plataforma
        if (item)
        {
            game->start();
        }
    }
    posicion();
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
