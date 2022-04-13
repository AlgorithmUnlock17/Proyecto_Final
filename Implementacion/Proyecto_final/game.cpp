#include "game.h"
#include <QTimer>
#include <QBrush>
#include <QImage>
#include "button.h"

Game::Game(QWidget *parent)
{
    // crear la scena
    QImage fondo(":/Sprites/fondo.png"); // ruta con imagen de fondo
    QBrush Bfondo(fondo); // brush de fondo
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,700);
    setScene(scene);
    scene->setBackgroundBrush(Bfondo); //Coloco fondo a la scene
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
    //delete Bmenu;
    clearscene(scene);
    titleText = new QGraphicsTextItem(QString("Tico's Adventure")); // instancio la clase para poner titulo en el menu principal
    QFont titleFont("Times New Roman",50);
    titleText->setFont(titleFont);    

    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // crear boton play

    //Button *playButton = new Button(QString("Jugar de cero"));
    playButton = new Button(QString("Jugar de cero"));
    int bxPos = this->width()/2 -playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    scene->addItem(playButton);
    connect(playButton,SIGNAL(clicked()),this,SLOT(decero()));

    // crear boton reanudar desde carga
    saveButton = new Button(QString("Reanudar"));
    int sxPos = this->width()/2-saveButton->boundingRect().width()/2;
    int syPos = 350;
    saveButton->setPos(sxPos,syPos);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(reanudar()));
    scene->addItem(saveButton);

    // crear boton salir
    quitButton = new Button(QString("Salir"));
    int qxPos = this->width()/2 -quitButton->boundingRect().width()/2;
    int qyPos = 425;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

}
void Game::save_game()
{
    QFile save(":/save.txt"); //Se le da la ubicación a una variable qfile
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
    QFile load(":/save.txt"); //Se le pone una variable Qfile al archivo
    if (!load.exists()) { //parte del debug, para revisar si esta el archivo en la ubicacion puesta
        qDebug() <<"no ex";
    }
    QString errMsg; //parte de un debug
    QFileDevice::FileError err = QFileDevice::NoError; //parte de un debug
    if (!load.open(QIODevice::ReadOnly | QIODevice::Text)){ //se abre el archivo como read only, si no se puede abrir se sigue el siguiente debug
        errMsg = load.errorString(); //se guarda el tipo de error generado
        err = load.error();
        qDebug() << "could not open it" << err << errMsg; //se muestra el error en la consola
        return;
    }
    QTextStream lvl(&load); //se guarda la informacion del archivo en lvl
    lvl>>level; //se le asigna a level lo que aparece en lvl
    qDebug()<<level; //se muestra en la consola para validar que esté funcionando bien
    load.close(); //se cierra el archivo
}
int Game::getLevel() const
{
    return level;
}
void Game::setLevel(int newLevel)
{
    level = newLevel;
}
void Game::start()
{
    //scene->clear();

    clearscene(scene);
    Bmenu = new Button(40,40,QString("Menu"));
    int mxPos=560;
    int myPos=0;
    Bmenu->setPos(mxPos,myPos);
    connect(Bmenu,SIGNAL(clicked()),this,SLOT(backMenu()));
    scene->addItem(Bmenu);


    // crear el jugador
    tico = new Tico(50,650);
    tico->setFlag(QGraphicsItem::ItemIsFocusable); //esto es para que el key press event se lea desde la misma clase (porque tiene focus)
    tico->setFocus(); //Estos dos de focus son muy importantes porque sin ellos no lee el teclado
    scene->addItem(tico);

    uno= new platform(20,550);
    uno0= new platform(400,570);
    uno1= new platform(220,450);
    uno2= new platform(420,350);
    uno3= new platform(200,230);
    uno4= new platform(30,130);

    platform *dos=new platform(30,600,30,300);


    switch(level){ //Aqui se agregan los niveles
    case 0:        
        scene->addItem(uno);
        scene->addItem(uno0);
        scene->addItem(uno1);
        scene->addItem(uno2);
        scene->addItem(uno3);
        scene->addItem(uno4);
        //for(unsigned int i=0;i<6;i++){
           // scene->addItem(platformlevel1[i]);}
        break;
    case 1:        
        scene->addItem(dos);
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
    delete titleText;
    delete playButton;
    delete quitButton;
    delete saveButton;
    load_game(); //Se carga que level sea lo que se leyo en el archivo
    start();
}
void Game::decero()
{
    delete titleText;
    delete playButton;
    delete quitButton;
    delete saveButton;
    level=0; //para reiniciar el juego
    start();
}
// slot para salir
void Game::close()
{
    delete titleText;
    delete playButton;
    delete quitButton;
    delete saveButton;
    clearscene(scene);
    save_game();
    exit(0);
}
// volver al menu principal
void Game::backMenu()
{
    save_game();
    menu();
}

