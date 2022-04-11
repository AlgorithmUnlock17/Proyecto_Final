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
    connect(mov_timer,SIGNAL(timeout()),this,SLOT(mov())); // esta no se conecta porque es estática
    mov_timer->start(1);
}
platform::platform(int x, int y, int xf, int yf): //plataforma de mov simple
posx(x),posy(y),ix(x),iy(y),fx(xf),fy(yf) // Inicialización de variables heredadas con el constructor de la clase base
{
    setRect(0,0,sizex,sizey);
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
    connect(mov_timer2,SIGNAL(timeout()),this,SLOT(conectlin())); // esta no se conecta porque es estática
    mov_timer2->start(10);
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
void platform::mov()
{
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
}
void platform::conectlin()
{
    mov(fx,fy,ix,iy);
}
void platform::mov(int fpox, int fpoy,int ix,int iy)
{
    int finalx;
    int finaly;
    if (dir==0){
        finalx=fpox;
        finaly=fpoy;
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
