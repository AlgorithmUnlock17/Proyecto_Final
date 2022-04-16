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
    movY_timer->start(10);
    //movY_timer->start(10);
}
void Tico::keyPressEvent(QKeyEvent *event) //Teclas
{
    salto=false;
    if (event->key()==Qt::Key_Space && encima){
        salto=true;
        velY=40;
    }
    if (event->key()==Qt::Key_D){
        setPixmap(QPixmap(":/Sprites/Tico.png")); //Mirando a la derecha
        if (posX<(600-tamanoX)){
            posX=posX+velX;
        }
        else posicion(600-tamanoX,posY);
    }
    if (event->key()==Qt::Key_A){
        setPixmap(QPixmap(":/Sprites/Tico2.png")); // mirando a la izquierda
        if (posX>(0)){
            posX=posX-velX;
        }
        else posicion(0,posY);
    }    
    posicion();
}
void Tico::movY() // salto con gravedad
{
    setFocus();
    velY = velY+(DT*(-G));
    posY +=-velY*DT+(-G)*DT*DT*0.5;
    if (posY>710-tamanoY){ //Esto se va a tener que cambiar cuando se haga lo del piso
        game->start();
        //movY_timer->stop();
    }
    if (posY<0){
        //game->scene->clear(); // diferenciar que ya supere el primer nivel
        game->setLevel(game->getLevel()+1); // si el salto supera el escenario pasa de nivel
        game->start();
    }    
    QList<QGraphicsItem *> list = collidingItems() ;
    if (list.size()==0){
        salto=false;
        encima=false;
    }
    posicion();
}
bool Tico::getSalto() const
{
    return salto;
}
void Tico::setSalto(bool newSalto)
{
    salto = newSalto;
}
bool Tico::getEncima() const
{
    return encima;
}
void Tico::setEncima(bool newEncima)
{
    encima = newEncima;
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
}
