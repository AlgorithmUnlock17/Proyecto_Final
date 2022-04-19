#include "mainwindow.h"
#include "game.h"
#include "dialog.h"
#include <QApplication>
Game *game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog users= new dialog();
    game = new Game();
    users.exec();
    game->show(); //se muesta la escena creada
    game->menu(); //se llama el metodo para que empiece el juego
    return a.exec();
}
