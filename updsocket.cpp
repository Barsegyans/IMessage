#include "updsocket.h"
#include <QDebug>
UpdSocket::UpdSocket(QString nick, int port) {
    nickname = nick;
    socket = new QUdpSocket(this);
    _port = port;
    socket->bind(QHostAddress::Any, port,QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);

    connect(socket, SIGNAL(readyRead()),this, SLOT(read()));

}
void UpdSocket::send(QString str, qint8 type) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint64(0);
    out << qint8(type);
    out << str;
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    socket->writeDatagram(data, QHostAddress::Broadcast, _port);
}

void UpdSocket::read() {
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64)) {
        in >> size;
    } else return;
    if (in.device()->size() - sizeof(qint64) < size) return;

    qint8 type = 0;
    in >> type;

    if (type == 2)
    { //USUAL_MESSAGE
        QString str;
        in >> str;
        int end=str.indexOf(" ");
        QString nick=str.mid(0,end);
        str.remove(0,end);
        emit textChanged(nick,str);
    }
    else if (type == 3)
    {   //PERSON_ONLINE
        QString str;
        in >> str;
        emit listChanged(str);
    }
    else if (type == 4 )
    {   //WHO_IS_ONLINE
        QString str;
        in >> str;
        emit updateList(str);
    }
    else if (type == 5)
    {
        QString str;
        in >> str;
        emit deletePerson(str);
    }

}
