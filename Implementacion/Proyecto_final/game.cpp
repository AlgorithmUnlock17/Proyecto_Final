#include "game.h"
#include <QTimer>
#include <QBrush>
#include <QImage>
#include "button.h"

Game::Game(QWidget *parent)
{
    // crear la scena
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,700);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,700); //Estoy medianamente segura que esto es lo que hace que quede todo perfecto sin scroll,

}
void Game::clearscene(QGraphicsScene *scene)
{
    scene->clear();
}
void Game::menu()
{
    //scene->clear();
    clearscene(scene);
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Tico's Adventure"));
    QFont titleFont("Times New Roman",50);
    titleText->setFont(titleFont);

    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // crear boton play

    Button *playButton = new Button(QString("Jugar de cero"));
    int bxPos = this->width()/2 -playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(decero()));
    scene->addItem(playButton);

    // crear boton reanudar desde carga

    Button *saveButton = new Button(QString("Reanudar"));
    int sxPos = this->width()/2-saveButton->boundingRect().width()/2;
    int syPos = 350;
    saveButton->setPos(sxPos,syPos);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(reanudar()));
    scene->addItem(saveButton);

    // crear boton salir

    Button *quitButton = new Button(QString("Salir"));
    int qxPos = this->width()/2 -quitButton->boundingRect().width()/2;
    int qyPos = 425;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

}
void Game::save_game()
{
    QFile save("./save.txt"); //Se le da la ubicación a una variable qfile
    if (!save.exists()) { //parte del debug, cuando tenia problemas, revisa si existe el archivo donde se declara
        qDebug() <<"no ex";
    }
    QString errMsg; //parte del debug
    QFileDevice::FileError err = QFileDevice::NoError; //parte del debug
    if (!save.open(QIODevice::WriteOnly | QIODevice::Text)){ //aqui se abre el archivo como write only y forma parte de un debug en caso de no poder abrir el archivo
        errMsg = save.errorString(); //muestra el tipo de error que está pasando, solo cuando no abre
        err = save.error();
        qDebug() << "could not open it" << err << errMsg; //muestra en la consola lo que pasa
        return; // con esta parte, si no se puede abrir, no se genera un error ni problemas de continuidad
    }
    QTextStream lvl(&save); //Se vincula un escritor de stream (string) con save, que es el archivo
    lvl<<level; //se le indica a lvl escribir el nivel
    qDebug() <<level; //debug para ver que este escribiendo bien lo que es
    save.close(); //se cierra el archivo
}
void Game::load_game()
{
    qDebug()<<level; //para revisar el nivel que se tiene desde antes, suele ser un 0
    QFile save("./save.txt"); //Se le pone una variable Qfile al archivo
    if (!save.exists()) { //parte del debug, para revisar si esta el archivo en la ubicacion puesta
        qDebug() <<"no ex";
    }
    QString errMsg; //parte de un debug
    QFileDevice::FileError err = QFileDevice::NoError; //parte de un debug
    if (!save.open(QIODevice::ReadOnly | QIODevice::Text)){ //se abre el archivo como read only, si no se puede abrir se sigue el siguiente debug
        errMsg = save.errorString(); //se guarda el tipo de error generado
        err = save.error();
        qDebug() << "could not open it" << err << errMsg; //se muestra el error en la consola
        return;
    }
    QTextStream lvl(&save); //se guarda la informacion del archivo en lvl
    lvl>>level; //se le asigna a level lo que aparece en lvl
    qDebug()<<level; //se muestra en la consola para validar que esté funcionando bien
    save.close(); //se cierra el archivo
}
void Game::start()
{

    //scene->clear();
    clearscene(scene);
    Button *Bmenu = new Button(40,40,QString("Menu"));
    int mxPos=560;
    int myPos=0;
    Bmenu->setPos(mxPos,myPos);
    connect(Bmenu,SIGNAL(clicked()),this,SLOT(backMenu()));
    scene->addItem(Bmenu);
    //Se hace puede hacer un switch case para cada escenario: tipo 1,2,3...
    //Cada escenario tiene una funcion/metodo aparte en el juego, al final se vuelve a llamar esta funcion para que se decida
    //A donde va a ir despues, asi se vuelve mas facil volver a ingresar al nivel porque ya de por si hay un valor para
    //El switch case

    // crear el jugador
    tico = new Tico(50,650);
    tico->setFlag(QGraphicsItem::ItemIsFocusable); //esto es para que el key press event se lea desde la misma clase (porque tiene focus)
    tico->setFocus(); //Estos dos de focus son muy importantes porque sin ellos no lee el teclado
    scene->addItem(tico);

    platform *uno=new platform(30,600,30,300);
    scene->addItem(uno);
    switch(level){ //Aqui se agregan los niveles
    case 0:
        break;
    case 1:
        break;
    }
    /* Lo siguente viene del otro código pero nos puede informar como llamar enemigos y demás
    // crear puntaje

    score = new Score();
    scene->addItem(score);
    // creamos la vida

    health =new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    //mostrar enemigos
    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);*/

}
void Game::reanudar()
{
    load_game(); //Se carga que level sea lo que se leyo en el archivo
    start();
}
void Game::decero()
{
    level=0; //para reiniciar el juego
    start();
}
// slot para salir
void Game::close()
{
    clearscene(scene);
    save_game();
    exit(0);
}
// volver al menu principal
void Game::backMenu()
{
    //scene->clear();
    clearscene(scene);
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Tico's Adventure"));
    QFont titleFont("Times New Roman",50);
    titleText->setFont(titleFont);

    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // crear boton play

    Button *playButton = new Button(QString("Jugar de cero"));
    int bxPos = this->width()/2 -playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(decero()));
    scene->addItem(playButton);

    // crear boton reanudar desde carga

    Button *saveButton = new Button(QString("Reanudar"));
    int sxPos = this->width()/2-saveButton->boundingRect().width()/2;
    int syPos = 350;
    saveButton->setPos(sxPos,syPos);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(reanudar()));
    scene->addItem(saveButton);

    // crear boton salir

    Button *quitButton = new Button(QString("Salir"));
    int qxPos = this->width()/2 -quitButton->boundingRect().width()/2;
    int qyPos = 425;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

