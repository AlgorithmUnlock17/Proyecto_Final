#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,580,680);//define tamaño escena, hay que arreglarlo, aparece un scrol
    ui->graphicsView->setScene(scene); // Llamado escena
    scene->addRect(scene->sceneRect());
    tico=new Tico(50,630); //Instanciamiento personaje
    scene->addItem(tico); //Añado el personaje a la escena
    movY_timer=new QTimer(this); //Timer para salto
    connect(movY_timer,SIGNAL(timeout()),this,SLOT(tico_actualizar())); //conexion del timer con la funcion tico_actualizar
   }

MainWindow::~MainWindow()
{
    delete ui;
    delete tico;
    delete scene;
}
/*void MainWindow::keyPressEvent(QKeyEvent *event) //Teclas
{
    if (event->key()==Qt::Key_Space && !movY_timer->isActive()){
        tico->setVelY(50);
        movY_timer->stop();
        movY_timer->start(10);
    }
    if (event->key()==Qt::Key_D){
        if (tico->getPosX()<(580-tico->getTamanoX())){
            tico->setPosX(tico->getPosX()+tico->getVelX());
        }
        else tico->posicion(580-tico->getTamanoX(),tico->getPosY());
    }
    if (event->key()==Qt::Key_A){
        if (tico->getPosX()>(0)){
            tico->setPosX(tico->getPosX()-tico->getVelX());
        }
        else tico->posicion(0,tico->getPosY());
    }
    tico->posicion();
}*/

void MainWindow::tico_actualizar()
{
    tico->movY();
    if (tico->getPosY()>=680-tico->getTamanoY()){
        movY_timer->stop();
    }
}
