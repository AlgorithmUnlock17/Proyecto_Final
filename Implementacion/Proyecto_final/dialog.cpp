#include "dialog.h"
#include "game.h"
#include <QDebug>
#include <QVBoxLayout>
#include <iterator>
#include <algorithm>
extern Game *game;
dialog::dialog(QWidget *parent)
    :QDialog(parent)
{
    lectura();
    //esto es para agregar un usuario
    agregar = new QLabel(tr("Agregar usuario: "));
    agregarLine = new QLineEdit;
    agregar->setBuddy(agregarLine);
    agregarCheck = new QCheckBox(); // se pueden quitar los nombres y poner al lado de los otros
    agregarCheck->setChecked(true);
    connect(agregarCheck,SIGNAL(toggled(bool)),this,SLOT(uno()));

    //esto es para hacer todo de lo de lectura de lo que hay en el dialog, falta todo lo de lectura y escritura
    sendButton = new QPushButton(tr("Enviar"));
    sendButton->setDefault(true);
    connect(sendButton,SIGNAL(clicked()),this,SLOT(finalizar()));

    //con esto se pueden ver los usuarios (falta hacer lo de lectura)
    listaCheck = new QCheckBox(tr("Ver lista de usuarios"));
    connect(listaCheck,SIGNAL(toggled(bool)),this,SLOT(dos()));
    lista=new QComboBox();
    std::list<std::pair<std::string,int>>::iterator it;
    for (it =usuarios.begin(); it !=usuarios.end(); ++it){
        lista->addItem(QString::fromStdString((*it).first));
    }
    //El resto es organizacion del layout
    //layout de agregar
    QHBoxLayout *agregarLayout = new QHBoxLayout;
    agregarLayout->addWidget(agregarCheck);
    agregarLayout->addWidget(agregar);
    agregarLayout->addWidget(agregarLine);

    //layout de lista
    QHBoxLayout *listLayout = new QHBoxLayout;
    listLayout->addWidget(listaCheck);
    listLayout->addWidget(lista);

    //layout general
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(agregarLayout, 0, 0);
    mainLayout->addLayout(listLayout, 1, 0);
    mainLayout->addWidget(sendButton, 2, 0);
    mainLayout->setRowStretch(3, 1);
    setLayout(mainLayout);
    setWindowTitle(tr("Usuarios"));

}
void dialog::lectura()
{
    std::string line;
    std::ifstream file ("save.txt");
    std::string mot="";
    std::string user;
    int level;
    while (std::getline(file, line)){
    for (char i:line){
        if (i!=',')  mot=mot+i;
        if (i==','){
           user=mot;
           mot="";
        }
    }
    level=stoi(mot);
    mot="";
    usuarios.push_back({user,level});
    }
    file.close();
}
void dialog::finalizar()
{
    if (agregarCheck->isChecked()){
        QString r=agregarLine->text();
        player=r.toStdString();
        usuarios.push_back({player,0});
    }
    if (listaCheck->isChecked()){
        QString r=lista->itemData(lista->currentIndex()).toString();
        player=r.toStdString();
        std::list<std::pair<std::string,int>>::iterator it = std::find_if(usuarios.begin(),
                                                                          usuarios.end(),
                                                                          [&]( const std::pair<std::string,int> v ){ return 0 == ( v.first==player); });
        game->setLevel((*it).second);
        //qDebug()<<(*it).second;
    }
    game->setUsuarios(usuarios);
    game->setPlayer(player);
    close();
}
void dialog::dos()
{
    if (listaCheck->isChecked()){
        agregarCheck->setChecked(false);
    }
    if (!listaCheck->isChecked()){
        agregarCheck->setChecked(true);
    }
}
void dialog::uno()
{
    if (agregarCheck->isChecked()){
        listaCheck->setChecked(false);
    }
    if (!agregarCheck->isChecked()){
        listaCheck->setChecked(true);
    }
}
