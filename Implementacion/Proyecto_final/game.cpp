#include "game.h"
#include <QTimer>
#include <QBrush>
#include <QImage>
#include <QDir>
#include <iostream>
#include <fstream>
#include <string>
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
    /*
    QFile file(":/save.txt"); //Se le da la ubicación a una variable qfile
    qDebug()<<file.isWritable();
    if (!file.exists()) { //parte del debug, cuando tenia problemas, revisa si existe el archivo donde se declara
        qDebug() <<"no ex";
    }
    QString errMsg; //parte del debug
    QFileDevice::FileError err = QFileDevice::NoError; //parte del debug
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        errMsg = file.errorString(); //muestra el tipo de error que está pasando, solo cuando no abre
        err = file.error();
        qDebug() << "could not open it" << err << errMsg; //muestra en la consola lo que pasa
        return; // con esta parte, si no se puede abrir, no se genera un error ni problemas de continuidad
    }
    QTextStream lvl(&file); //Se vincula un escritor de stream (string) con save, que es el archivo
    lvl<<level; //se le indica a lvl escribir el nivel
    qDebug() <<level; //debug para ver que este escribiendo bien lo que es
    file.close(); //se cierra el archivo
    */
    std::ofstream file;
    file.open("save.txt");
    file<<level;
    file.close();
}
void Game::load_game()
{
    /*
    qDebug()<<level; //para revisar el nivel que se tiene desde antes, suele ser un 0
    QFile file(":/save.txt"); //Se le pone una variable Qfile al archivo
    if (!file.exists()) { //parte del debug, para revisar si esta el archivo en la ubicacion puesta
        qDebug() <<"no ex";
    }
    QString errMsg; //parte de un debug
    QFileDevice::FileError err = QFileDevice::NoError; //parte de un debug
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){ //se abre el archivo como read only, si no se puede abrir se sigue el siguiente debug
        errMsg = file.errorString(); //se guarda el tipo de error generado
        err = file.error();
        qDebug() << "could not open it" << err << errMsg; //se muestra el error en la consola
        return;
    }
    QTextStream lvl(&file); //se guarda la informacion del archivo en lvl
    lvl>>level; //se le asigna a level lo que aparece en lvl
    qDebug()<<level; //se muestra en la consola para validar que esté funcionando bien
    file.close(); //se cierra el archivo
    */
    std::string line;
    std::ifstream file ("save.txt");
    getline (file,line);
    level=std::stoi(line);
    file.close();
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
    Vplataformas.clear();
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
    //se crea una label del nivel
    QFont levelText("Times New Roman",20);
    level_display=scene->addText("Nivel: ",levelText);
    level_display->setPos(5,0);
    number=scene->addText(QString::number(level+1),levelText);
    number->setPos(56,0);
    switch(level){ //Aqui se agregan los niveles
    case 0:
        lev1();
        break;
    case 1:
        lev2();
        break;
    }
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
    level=1; //para reiniciar el juego
    start();
}
void Game::close() //slot para salir
{
    delete titleText;
    delete playButton;
    delete quitButton;
    delete saveButton;
    clearscene(scene);
    save_game();
    exit(0);
}
void Game::backMenu() //volver al menu pricipal
{
    save_game();
    menu();
}
void Game::lev1()
{
    tico->posicion(50,650);
    /*platform *uno= new platform(20,550);
    platform *uno0= new platform(400,570);
    platform *uno1= new platform(220,450);
    platform *uno2= new platform(420,350);
    platform *uno3= new platform(200,230);
    platform *uno4= new platform(30,130);
    platform *base1=new platform(0,700);
    platform *base2=new platform(100,700);
    platform *base3=new platform(200,700);
    platform *base4=new platform(300,700);
    platform *base5=new platform(400,700);
    platform *base6=new platform(500,700);

    scene->addItem(uno);
    scene->addItem(uno0);
    scene->addItem(uno1);
    scene->addItem(uno2);
    scene->addItem(uno3);
    scene->addItem(uno4);
    scene->addItem(base1);
    scene->addItem(base2);
    scene->addItem(base3);
    scene->addItem(base4);
    scene->addItem(base5);
    scene->addItem(base6);*/
    int Py=0;
    for(int i=0;i<15;i++){
        int Px=0;
    for(int j=0;j<12;j++){
    if(MapLevel1[i][j]==1){
        Vplataformas.push_back(new platform(Px,Py));
        Px+=50;}
    else Px+=50;
    }
    Py+=50;
    }

    int VPsize=Vplataformas.size();
    for(int k=0;k<VPsize;k++)scene->addItem(Vplataformas[k]);
}
void Game::lev2()
{
    tico->posicion(220,525);
    //platform *uno0= new platform(200,570);
    //platform *dos=new platform(30,600,30,300);
    //platform *tres=new platform(300,570,false);
    Bacteria *enemy=new Bacteria(300,300,100);
    int Py=0;
    for(int i=0;i<15;i++){
        int Px=0;
    for(int j=0;j<12;j++){
    if(MapLevel2[i][j]==1){
        Vplataformas.push_back(new platform(Px,Py));
        Px+=50;}
    if(MapLevel2[i][j]==2){
        Vplataformas.push_back(new platform(Px,Py,Px,Py-300));
        Px+=50;}
    if(MapLevel2[i][j]==3){
        Vplataformas.push_back(new platform(Px,Py,false));
        Px+=50;}
    else Px+=50;
    }
    Py+=50;
    }
    int VPsize=Vplataformas.size();
    for(int k=0;k<VPsize;k++)scene->addItem(Vplataformas[k]);
    //scene->addItem(uno0);
    //scene->addItem(dos);
    //scene->addItem(tres);
    scene->addItem(enemy);
}
