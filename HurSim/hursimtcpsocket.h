#ifndef HURSIMTCPSOCKET_H
#define HURSIMTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QByteArray>
#include <QThread>

class HurSimTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit HurSimTcpSocket(QObject *parent = nullptr);
    void doConnect();
signals:
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
};

#endif // HURSIMTCPSOCKET_H
