#include "udplistener.hpp"
UDPListener::UDPListener(QObject *parent) : QObject(parent)
{
    _udpSocket = new QUdpSocket(this);

    connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

UDPListener::~UDPListener()
{
    _udpSocket->close();
    _udpSocket->deleteLater();
}

bool UDPListener::bind(const QHostAddress &iAddress, quint16 iPort)
{
    return _udpSocket->bind(iAddress, iPort);
}

void UDPListener::unBind()
{
    _udpSocket->close();
}

void UDPListener::onReadyRead()
{
    // when data comes in
    QByteArray mBuffer;
    mBuffer.resize(static_cast<int>(_udpSocket->pendingDatagramSize()));

    QHostAddress mSender;
    quint16 mSenderPort;

    _udpSocket->readDatagram(mBuffer.data(), mBuffer.size(), &mSender, &mSenderPort);

    qDebug() << "Message from: " << mSender.toString();
    qDebug() << "Message port: " << mSenderPort;
    qDebug() << "Message: " << mBuffer;

    emit keyReceived(mBuffer);
}
