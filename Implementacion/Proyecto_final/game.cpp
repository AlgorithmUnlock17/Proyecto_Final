#include "game.h"
#include <iterator>
#include <QTimer>
#include <QBrush>
#include <QImage>
#include <QDir>
#include <iostream>
#include <fstream>
#include <string>
#include "button.h"
#include <QDebug>
Game::Game(QWidget *parent)
{
    // crear la scena
    QImage fondo(":/Sprites/fondo1.png"); // ruta con imagen de fondo
    QBrush Bfondo(fondo); // brush de fondo    
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,700);
    setScene(scene);
    scene->setBackgroundBrush(Bfondo); //Coloco fondo a la scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,700); //Estoy medianamente segura que esto es lo que hace que quede todo perfecto sin scroll,

    //Qlcd para nivel
    levelnumber=new QLCDNumber(1,this);
    levelnumber->move(72,10);
    levelnumber->resize(20,20);
    levelnumber->setPalette(Qt::green);
    levelnumber->setFrameStyle(0);
    levelnumber->setVisible(false);// Con este comando controlo la visibilidad del display

    // Qlcd para vidas
    livesnumber= new QLCDNumber(1,this);
    livesnumber->move(75,50);
    livesnumber->resize(20,20);
    livesnumber->setPalette(Qt::green);
    livesnumber->setFrameStyle(0);
    livesnumber->setVisible(false);

}
void Game::clearscene(QGraphicsScene *scene)
{
    int size=Vplataformas.size();
     for (int i=0;i<size;i++){
         scene->removeItem(Vplataformas[i]);
         delete Vplataformas[i];
         Vplataformas[i]=0;
     }
     Vplataformas.clear();
     size=Vbacterias.size();
     for (int i=0;i<size;i++){
         scene->removeItem(Vbacterias[i]);
         delete Vbacterias[i];
         Vbacterias[i]=0;
     }
     Vbacterias.clear();
     size=Vpajaros.size();
     for (int i=0;i<size;i++){
         if(Vpajaros[i]->scene() != nullptr){
         scene->removeItem(Vpajaros[i]);
         delete Vpajaros[i];
         Vpajaros[i]=0;}
     }
     Vpajaros.clear();
     if(tico->scene() != nullptr) // nullptr from C++ 11, else use NULL
     {
         tico->stop();
         scene->removeItem(tico);
     }
     Vplataformas.clear();
     scene->clear();
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
    //scene->addItem(titleText);

    // crear boton play

    //Button *playButton = new Button(QString("Jugar de cero"));
    playButton = new Button(QString("Jugar de cero"));
    int bxPos = this->width()/2 -playButton->boundingRect().width()/2;
    int byPos = 330;
    playButton->setPos(bxPos,byPos);
    playButton->setBrush(Qt::darkGreen);
    scene->addItem(playButton);
    connect(playButton,SIGNAL(clicked()),this,SLOT(decero()));

    // crear boton reanudar desde carga
    saveButton = new Button(QString("Reanudar"));
    int sxPos = this->width()/2-saveButton->boundingRect().width()/2;
    int syPos = 390;
    saveButton->setPos(sxPos,syPos);
    saveButton->setBrush(Qt::darkGreen);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(reanudar()));
    scene->addItem(saveButton);

    // crear boton salir
    quitButton = new Button(QString("Salir"));
    int qxPos = this->width()/2 -quitButton->boundingRect().width()/2;
    int qyPos = 450;
    quitButton->setPos(qxPos,qyPos);
    quitButton->setBrush(Qt::darkGreen);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}
void Game::save_game()
{
    std::list<std::pair<std::string,int>>::iterator it = std::find_if(usuarios.begin(),
                                                                      usuarios.end(),
                                                                      [&]( const std::pair<std::string,int> v ){ return 0 == ( v.first==player); });
    it->second=level;
    std::ofstream file;
    file.open("save.txt");
    std::list<std::pair<std::string,int>>::iterator it2;
    for (it2 =usuarios.begin(); it2 !=usuarios.end(); it2++){
        file<<(*it2).first<<','<<(*it2).second<<std::endl;
    }
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
    //delete livesnumber;
    //delete levelnumber;
    //scene->clear();
    Bmenu = new Button(40,40,QString("Menu"));
    int mxPos=560;
    int myPos=0;
    Bmenu->setPos(mxPos,myPos);
    Bmenu->setBrush(Qt::darkGreen);
    connect(Bmenu,SIGNAL(clicked()),this,SLOT(backMenu()));
    scene->addItem(Bmenu);
    // crear el jugador    
    scene->addItem(tico);
    tico->start();
    //se crea una label del nivel
    QFont levelText("Times New Roman",20);
    level_display=scene->addText("Nivel: ",levelText);
    level_display->setPos(4,0);
    //se crea label de vida
    QFont LivesText("Times New Roman",20);
    lives_display=scene->addText("Vidas: ",LivesText);
    lives_display->setPos(4,40);

     //Display para mostrar nivel

     levelnumber->display(level+1);
     levelnumber->setVisible(true);

     livesnumber->display(tico_vidas);
     livesnumber->setVisible(true);
    switch(level){ //Aqui se agregan los niveles
    case 0:
        lev1();
        break;
    case 1:
        lev2();
        break;
    case 2:
        lev3();
        break;
    case 3:
        lev4();
        break;
    }
}
void Game::reanudar()
{
    delete titleText;
    delete playButton;
    delete quitButton;
    delete saveButton;
    //load_game(); //Se carga que level sea lo que se leyo en el archivo
    start();
}
void Game::decero()
{
    delete titleText;
    delete playButton;
    delete quitButton;
    delete saveButton;
    tico_vidas=3;
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
    delete level_display;
    delete lives_display;
    levelnumber->setVisible(false);
    livesnumber->setVisible(false);
    QImage fondo(":/Sprites/fondo1.png");
    QBrush Bfondo(fondo);
    scene->setBackgroundBrush(Bfondo);
    //save_game();
    menu();
}
void Game::lev1()
{
    tico->posicion(50,650);   
    QImage fondo2(":/Sprites/fondoL1.png");
    QBrush Bfondo2(fondo2);
    scene->setBackgroundBrush(Bfondo2);
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
    for(int k=0;k<VPsize;k++) scene->addItem(Vplataformas[k]);
}
void Game::lev2()
{
    tico->posicion(160,600);
    QImage fondoL2(":/Sprites/fondo.png");
    QBrush Bfondo2(fondoL2);
    scene->setBackgroundBrush(Bfondo2);
    Vbacterias.push_back(new Bacteria(200,200,100));
    //pajaro *enemybird=new pajaro(100,100,500,100);
    int Py=0;
    for(int i=0;i<15;i++){
        int Px=0;
    for(int j=0;j<12;j++){
    if(MapLevel2[i][j]==1){
        Vplataformas.push_back(new platform(Px,Py));
        Px+=50;}
    if(MapLevel2[i][j]==2){
        Vplataformas.push_back(new platform(Px,Py,Px+300,Py));
        Px+=50;}
    if(MapLevel2[i][j]==3){
        Vplataformas.push_back(new platform(Px,Py,false));
        Px+=50;}
    else Px+=50;
    }
    Py+=50;
    }
    int size=Vplataformas.size();
    for(int k=0;k<size;k++)scene->addItem(Vplataformas[k]);
    size=Vbacterias.size();
    for(int k=0;k<size;k++)scene->addItem(Vbacterias[k]);    //scene->addItem(enemybird);
}
void Game::lev3()
{
    tico->posicion(100,600);
    QImage fondoL3(":/Sprites/fondoL3.png");
    QBrush BfondoL3(fondoL3);
    scene->setBackgroundBrush(BfondoL3);
    Vpajaros.push_back(new pajaro(100,100,500,100));
    int Py=0;
    for(int i=0;i<15;i++){
        int Px=0;
    for(int j=0;j<12;j++){
    if(MapLevel3[i][j]==1){
        Vplataformas.push_back(new platform(Px,Py));
        Px+=50;}
    if(MapLevel3[i][j]==2){
        Vplataformas.push_back(new platform(Px,Py,Px,Py-200));
        Px+=50;}
    if(MapLevel3[i][j]==3){
        Vplataformas.push_back(new platform(Px,Py,false));
        Px+=50;}
    else Px+=50;
    }
    Py+=50;
    }
    int size=Vplataformas.size();
    for(int k=0;k<size;k++) scene->addItem(Vplataformas[k]);
    size=Vpajaros.size();
    for(int k=0;k<size;k++) scene->addItem(Vpajaros[k]);
}
void Game::lev4()
{
    tico->posicion(250,600);
    QImage fondoL3(":/Sprites/fondoL3.png");
    QBrush BfondoL3(fondoL3);
    scene->setBackgroundBrush(BfondoL3);
    Vpajaros.push_back(new pajaro(100,150,500,150));
    int Py=0;
    for(int i=0;i<15;i++){
        int Px=0;
    for(int j=0;j<12;j++){
    if(MapLevel4[i][j]==1){
        Vplataformas.push_back(new platform(Px,Py));
        Px+=50;}
    if(MapLevel4[i][j]==2){
        Vplataformas.push_back(new platform(Px,Py,Px,Py-300));
        Px+=50;}
    if(MapLevel4[i][j]==3){
        Vplataformas.push_back(new platform(Px,Py,false));
        Px+=50;}
    else Px+=50;
    }
    Py+=50;
    }
    int size=Vplataformas.size();
    for(int k=0;k<size;k++) scene->addItem(Vplataformas[k]);
    size=Vpajaros.size();
    for(int k=0;k<size;k++) scene->addItem(Vpajaros[k]);
}
int Game::getTico_vidas() const
{
    return tico_vidas;
}
void Game::setTico_vidas(int newTico_vidas)
{
    tico_vidas = newTico_vidas;
}
void Game::setUsuarios(const std::list<std::pair<std::string, int> > &newUsuarios)
{
    usuarios = newUsuarios;
}
void Game::setPlayer(const std::string &newPlayer)
{
    player = newPlayer;
}
