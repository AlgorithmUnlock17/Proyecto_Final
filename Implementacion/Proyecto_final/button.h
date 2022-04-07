#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
//Este código viene directamente de VideoGame, del ejemplo de classroom, puede tener modificaciones
class Button: public QObject, public QGraphicsRectItem{

    Q_OBJECT

public:
    Button(QString name, QGraphicsItem * parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
signals:
    void clicked();
private:
    QGraphicsTextItem *text ;
};
#endif // BUTTON_H
