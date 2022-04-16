#include "pajaro.h"
#include <QDebug>


extern Game * game;
pajaro::pajaro(float x,float y,float xf,float yf): //plataforma de mov simple
posx(x),posy(y),ix(x),iy(y),fx(xf),fy(yf) // Inicialización de variables heredadas con el constructor de la clase base
{
    setPixmap(QPixmap(":/Sprites/pajaro.png"));
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    connect(movi_timer,SIGNAL(timeout()),this,SLOT(mov())); // esta no se conecta porque es estática
    movi_timer->start(10);
}
void pajaro::mov()
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
void pajaro::posicion() //metodo (sobrecargado) llamado en el constructor para posicionar personaje
{
    setPos(posx,posy);
}
void pajaro::posicion(int newX,int newY) // Actualizar posición con parametros
{
    posx=newX;
    posy=newY;
    setPos(posx,posy);
}
