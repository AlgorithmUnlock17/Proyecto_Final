#ifndef DIALOG_H
#define DIALOG_H
#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include  <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <list>
class dialog : public QDialog
{
    Q_OBJECT
public:
    dialog(QWidget *parent = nullptr);
    void lectura();

public slots:
    void finalizar();
    void uno();
    void dos();
    bool revisar();

private:
    QLabel *agregar;
    QComboBox *lista;
    QCheckBox *agregarCheck;
    QCheckBox *listaCheck;
    QLineEdit *agregarLine;
    QPushButton *sendButton;
    QDialogButtonBox *grupoAgregar;
    QDialogButtonBox *grupoSend;
    QDialogButtonBox *todo;
    std::list <std::pair<std::string,int>> usuarios; //se crea una lista de users, nivel
    std::string player;
    };

#endif // DIALOG_H
