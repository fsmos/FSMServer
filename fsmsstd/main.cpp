#include <QCoreApplication>
#include <QtNetwork>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc!=3) return 0;
    QLocalSocket* sock = new QLocalSocket();
    sock->connectToServer(argv[1]);
    int data[1];
    data[0]=QString(argv[2]).toInt();
    sock->write((char*)data,sizeof(int));
    sock->close();
    return 0;
}

