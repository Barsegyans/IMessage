#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "updsocket.h"
#include <QList>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    UpdSocket *updsocket;
    QList<QString> onlinelist;
public:
    explicit Dialog(int port1,QString name,QWidget *parent = 0);
    ~Dialog();
    QString nick;
    int port;
private slots:
    void setText(QString nickname,QString text);
    void on_lineEdit_returnPressed();
    void setList(QString name);
    void updateList(QString name);
    void deletePerson(QString name);
    void drawList();
    void closeEvent(QCloseEvent *e);
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
