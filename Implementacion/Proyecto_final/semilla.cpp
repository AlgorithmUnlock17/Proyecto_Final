#include "semilla.h"
extern Game * game;

semilla::semilla(float x, float y, bool dir):
posx(x),posy(y),dir(dir) // Inicialización de variables heredadas con el constructor de la clase base
{
    setPixmap(QPixmap(":/Sprites/semilla.png")); // Lectura de sprite
    posicion(); // con posX y posY definidas en el constructor, posiciono el personaje
    connect(mov_timer,SIGNAL(timeout()),this,SLOT(mov())); // esta no se conecta porque es estática
    mov_timer->stop();
    mov_timer->start(5);
}
void semilla::mov()
{
    if (dir==0){ //esto es para que baje
        posy++;
    }
    if (dir==1){
        posy--;
    }
    posicion();
    if(verificador==1)game->backMenu();

    if (posy>700 || posy<0){
        game->scene->removeItem(this);
        delete (this);
        mov_timer->stop();
    }
    QList<QGraphicsItem *> list = collidingItems() ;
    foreach(QGraphicsItem * i , list){
        Tico * item3= dynamic_cast<Tico *>(i);
        if (item3)
        {
            game->setTico_vidas(game->getTico_vidas()-1);
            game->scene->removeItem(this);
            game->livesnumber->display(game->getTico_vidas()); // muestro las vidas restantes
            if (game->getTico_vidas()<=0){
                game->setLevel(0);
                game->setTico_vidas(3);
                mov_timer->stop();
                delete (this);
                game->backMenu();
            }
            else {
                mov_timer->stop();
                delete (this);
                //game->start();
            }
    }
    }

    //tener en cuenta que las colisiones con los objetos se hacen desde los otros objetos, para facilitar el proceso de pérdida de vidas
}
void semilla::posicion() //metodo (sobrecargado) llamado en el constructor para posicionar personaje
{
    setPos(posx,posy);
}
void semilla::posicion(int newX,int newY) // Actualizar posición con parametros
{
    posx=newX;
    posy=newY;
    setPos(posx,posy);
}
int semilla::getVerificador() const
{
    return verificador;
}
void semilla::setVerificador(int newVerificador)
{
    verificador = newVerificador;
}
