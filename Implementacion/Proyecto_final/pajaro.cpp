#include "pajaro.h"
#include "semilla.h"
#include <QDebug>

extern Game * game;
pajaro::pajaro(float x,float y,float xf,float yf): //plataforma de mov simple
posx(x),posy(y),ix(x),iy(y),fx(xf),fy(yf) // Inicialización de variables heredadas con el constructor de la clase base
{
    posicion(); // con posX y posY definidas en el constructor posiciono el personaje
    connect(movi_timer,SIGNAL(timeout()),this,SLOT(mov())); // esta no se conecta porque es estática
    movi_timer->start(10);
    connect(pew_timer,SIGNAL(timeout()),this,SLOT(pew()));
    pew_timer->start(50);
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
            game->setTico_vidas(game->getTico_vidas()-1);
            if (game->getTico_vidas()<=0){
                game->setLevel(0);
                game->setTico_vidas(5);
                game->menu();
            }
            else
                game->start();
        }
        semilla * item2= dynamic_cast<semilla *>(i); //Con esto se hace la colision con cada plataforma
        if (item2)
        {
            vidas--;
            game->scene->removeItem(item2);
            delete item2;
        }
    }
    if (vidas<=0){
        //eliminar el pajaro
        game->scene->removeItem(this);
        delete (this);
    }
    posicion();
}
void pajaro::pew()
{
    semilla* pew=new semilla(posx,posy+70,0); //la pos en y se debe cambiar dependiendo del sprite
    game->scene->addItem(pew);
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
