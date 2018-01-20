#ifndef UPDSOCKET_H
#define UPDSOCKET_H

#include <QObject>
#include <QUdpSocket>
#include <QDataStream>
class UpdSocket : public QObject
{
    Q_OBJECT
private:
    QString nickname;
    QUdpSocket *socket;
    int _port;

public:
     UpdSocket(QString nick, int port);
     void send(QString str, qint8 type);
signals:
     void textChanged(QString nickname,QString text);
     void listChanged(QString nickname);
     void updateList(QString nickname);
     void deletePerson(QString nickname);
public slots:
    void read();
};

#endif // UPDSOCKET_H
