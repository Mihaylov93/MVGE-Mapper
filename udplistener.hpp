#pragma once

#include <QObject>
#include <QUdpSocket>
class UDPListener : public QObject {
    Q_OBJECT
public:
    explicit UDPListener(QObject *parent = nullptr);
    ~UDPListener();
    bool bind(const QHostAddress &address, quint16 port = 0);
    void unBind();
signals:
    void keyReceived(const QString &key);
public slots:
    void onReadyRead();

private:
    QUdpSocket *_udpSocket;
};
