#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "tico.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QString>
#include <vector>
#include <list>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *newScene);
private slots:
        void tico_actualizar();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Tico *tico;
    QTimer *movY_timer;
};
#endif // MAINWINDOW_H
