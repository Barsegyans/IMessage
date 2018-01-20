#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
#include <QTime>
#include <QTextCursor>
#include <QCloseEvent>
Dialog::Dialog(int port1,QString name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    nick=name;
    port=port1;
    QString k=QString::number(port1);
    this->setWindowTitle("IMessage ["+nick+"@"+k+"]");
    updsocket=new UpdSocket(nick,port1);
    updsocket->send(nick,3);

    connect(updsocket, SIGNAL(textChanged(QString,QString)),this, SLOT(setText(QString,QString)));
    connect(updsocket, SIGNAL(listChanged(QString)),this, SLOT(setList(QString)));
    connect(updsocket, SIGNAL(updateList(QString)), this, SLOT(updateList(QString)));
    connect(updsocket, SIGNAL(deletePerson(QString)), this, SLOT(deletePerson(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_lineEdit_returnPressed()
{
    QString text;
    text =ui->lineEdit->text();
    if(!text.isEmpty()){
        ui->lineEdit->clear();
        updsocket->send(nick+" "+text,2);
    }
}
void Dialog::setText(QString nickname,QString text){
    QTime time=QTime::currentTime();
    QString st=time.toString();
    st="["+st+"]";
    text=": "+text;
    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    if (nickname==nick){
        ui->textEdit->insertHtml("<div><font color=\"red\">"+st+nickname+"</font></div>");
        ui->textEdit->insertHtml("<div><font color=\"black\">"+text+"</font></div>");
        ui->textEdit->append("");
    }else {
        ui->textEdit->insertHtml("<div><font color=\"blue\">"+st+nickname+"</font></div>");
        ui->textEdit->insertHtml("<div><font color=\"black\">"+text+"</font></div>");
        ui->textEdit->append("");

    }

}
void Dialog::setList(QString name)
{
    updsocket->send(nick,4);
    if(onlinelist.contains(name) || nick==name)
        return;
    onlinelist.append(name);
    drawList();
}

void Dialog::updateList(QString name)
{
    if(onlinelist.contains(name) || nick==name)
        return;
    onlinelist.append(name);
    drawList();
}

void Dialog::deletePerson(QString name)
{
    if(onlinelist.contains(name))
        onlinelist.removeOne(name);
    drawList();
}

void Dialog::drawList()
{
    ui->listWidget->clear();
    for(QString n: onlinelist)
    {
        ui->listWidget->addItem(n);
    }
    ui->listWidget->sortItems();
}

void Dialog::closeEvent(QCloseEvent *e)
{
    updsocket->send(nick,5);
    e->accept();
}

void Dialog::on_pushButton_clicked()
{
    on_lineEdit_returnPressed();
}
