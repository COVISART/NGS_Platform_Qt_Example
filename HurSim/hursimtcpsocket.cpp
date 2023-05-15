#include "hursimtcpsocket.h"

HurSimTcpSocket::HurSimTcpSocket(QObject *parent) : QObject(parent)
{

}
void HurSimTcpSocket::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("localhost", 9091);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }


    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    int i = 0;
    for (int i=0; i<1000; i++) {

        const char* byte_x = reinterpret_cast<const char*>(&x);
        const char* byte_y = reinterpret_cast<const char*>(&y);
        const char* byte_z = reinterpret_cast<const char*>(&z);

        QByteArray payload = QByteArray::fromRawData(byte_x, sizeof (byte_x));
        payload.append(QByteArray::fromRawData(byte_y, sizeof (byte_y)));
        payload.append(QByteArray::fromRawData(byte_z, sizeof (byte_z)));

        socket->write(payload, payload.length());
        socket->flush();
        x+=0.01;
        y+=0.01;
        z+=0.01;

        QThread::msleep(10);
    }
    socket->disconnectFromHost();

}
void HurSimTcpSocket::connected()
{
    qDebug() << "connected...";

}

void HurSimTcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void HurSimTcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void HurSimTcpSocket::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}
