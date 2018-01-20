#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QStringList>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString name="",buff="";
    bool f1=false, f2=false;
    int port;
    for (int i=1;i<argc;i++){
        buff=argv[i];
        if (buff == "-n"){
            name.append(argv[i+1]);
            f1=!f1;
        }
        if (buff == "-p"){
            buff=argv[i+1];
            port=buff.toInt();
            f2=!f2;
        }
    }
    if (!f1){
        name="username";
    }
    if (!f2){
        port=12222;
    }
    Dialog w1(port,name);
    w1.show();
    return a.exec();
}
