#include "platform.h"
#include <QBrush>

platform::platform(float x, float y):
posx(x),posy(y) // Inicialización de variables heredadas con el constructor de la clase base
{
    setRect(0,0,sizex,sizey);
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);
    connect(mov_timer1,SIGNAL(timeout()),this,SLOT(mov())); // esta no se conecta porque es estática
    mov_timer1->start(1);
}
platform::platform(float x,float y,float xf,float yf): //plataforma de mov simple
posx(x),posy(y),ix(x),iy(y),fx(xf),fy(yf) // Inicialización de variables heredadas con el constructor de la clase base
{
    setRect(0,0,sizex,sizey);
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
    connect(mov_timer2,SIGNAL(timeout()),this,SLOT(mov3())); // esta no se conecta porque es estática
    mov_timer2->start(10);
}
platform::platform(float x, float y,bool flag): //plataforma de mov simple
posx(x),posy(y) // Inicialización de variables heredadas con el constructor de la clase base
{
    setRect(0,0,sizex,sizey);
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
    connect(mov_timer2,SIGNAL(timeout()),this,SLOT(mov2())); // esta no se conecta porque es estática
    mov_timer2->start(10);
}
void platform::posicion() //metodo (sobrecargado) llamado en el constructor para posicionar personaje
{
    setPos(posx,posy);
}
void platform::posicion(float newX,float newY) // Actualizar posición con parametros
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
void platform::mov()
{
    QList<QGraphicsItem *> list = collidingItems();
    foreach(QGraphicsItem * i , list) //es probable que tenga que mover esto a la parte de las plataformas, para que el mov de tico varie por plataforma
    {
        Tico * item= dynamic_cast<Tico *>(i); //Con esto se hace la colision con cada plataforma
        if (item)
        {
            if (item->getPosY()<posy+sizey/2){
                item->setEncima(true);
                if (!item->getSalto()){
                item->setPosY(posy-item->getTamanoY()+5);
                item->setVelY(0);
                }
            }
            if (item->getPosY()>posy+sizey-5){
                item->setPosY(posy+sizey);
                item->setVelY(0);
            }
        }
    }
}
void platform::mov2() //movimiento de resortes, la verdad, no tengo ni idea como hacerlo
{
    //F=ma
    //F=-kx
    //x=const creo (NO)
    //k=conste, estoy segura

    QList<QGraphicsItem *> list = collidingItems() ;
    foreach(QGraphicsItem * i , list) //es probable que tenga que mover esto a la parte de las plataformas, para que el mov de tico varie por plataforma
    {
        Tico * item= dynamic_cast<Tico *>(i); //Con esto se hace la colision con cada plataforma
        if (item)
        {
            if (item->getPosY()<posy+sizey/2){
                if (!item->getSalto()){
                item->setPosY(posy-item->getTamanoY()+5);
                item->setVelY(0);
                }
            }
            if (item->getPosY()>posy+sizey-5){
                item->setPosY(posy+sizey);
                item->setVelY(0);
            }
        }
    }
    setPos(posx,posy);
}
void platform::mov3()
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
            if (item->getPosY()<posy+sizey/2){
                item->setEncima(true);
                if (!item->getSalto()){
                item->setPosY(posy-item->getTamanoY()+5);
                item->setVelY(0);
                }
            }
            if (item->getPosY()>posy+sizey-5){
                item->setPosY(posy+sizey);
                item->setVelY(0);
            }
        }
    }
    setPos(posx,posy);
}
