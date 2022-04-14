#include "button.h"
#include <QBrush>
#include <QGraphicsTextItem>

Button::Button(QString name, QGraphicsItem *parent)
{
 // dibujar boton
    setRect(0,0,200,50); //modificar para cambiar el tamano de los botones y el estilo
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);

    // dibujar el texto

    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 -text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // habilitamos evento hover

    setAcceptHoverEvents(true);
}
Button::Button(int sizex,int sizey,QString name, QGraphicsItem *parent)
{
 // dibujar boton
    setRect(0,0,sizex,sizey); //modificar para cambiar el tamano de los botones y el estilo
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
    // dibujar el texto
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 -text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    // habilitamos evento hover
    setAcceptHoverEvents(true);
}
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
}
