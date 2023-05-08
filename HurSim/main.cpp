#include <QCoreApplication>
#include <QTcpSocket>
#include "hursimtcpsocket.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HurSimTcpSocket s;
    s.doConnect();
    return a.exec();
}
