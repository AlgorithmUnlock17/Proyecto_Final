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
    if(first==true){
        scene->clear();
        first=false;
    }
    else{
      scene->clear();
      /*QList<QGraphicsItem*> itemsList = scene->items();
      QList<QGraphicsItem*>::iterator iter = itemsList.begin();
      QList<QGraphicsItem*>::iterator end = itemsList.end();
      while(iter != end){
         QGraphicsItem* item = (*iter); scene->removeItem(item);
         iter++;
      }*/
      Vplataformas.clear();
    }
}
void Game::menu()
{    
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
    std::ofstream file;
    file.open("save.txt");
    file<<level;
    file.close();
}
void Game::load_game()
{
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
    //se crea una label del nivel
    QFont levelText("Times New Roman",20);
    level_display=scene->addText("Nivel: ",levelText);
    level_display->setPos(4,0);
    //se crea label de vida
    QFont LivesText("Times New Roman",20);
    level_display=scene->addText("Vidas: ",LivesText);
    level_display->setPos(4,40);
     //number=scene->addText(QString::number(level+1),levelText);
     //number->setPos(56,0);
     //Display para mostrar nivel
     levelnumber=new QLCDNumber(1,this);
     levelnumber->display(level+1);
     levelnumber->move(72,10);
     levelnumber->resize(20,20);
     levelnumber->setPalette(Qt::green);
     levelnumber->setFrameStyle(0);
     levelnumber->setVisible(true);

     // Display para mostrar vidas
     livesnumber= new QLCDNumber(1,this);
     livesnumber->display(tico->getVidas());
     livesnumber->move(75,50);
     livesnumber->resize(20,20);
     livesnumber->setPalette(Qt::green);
     livesnumber->setFrameStyle(0);
     livesnumber->setVisible(true);
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
    level=0; //para reiniciar el juego
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
    delete Bmenu;
    delete levelnumber;
    delete livesnumber;
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
        Px+=50;
    }
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
