#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QString server_type, QObject *parent = nullptr);

    bool connectToServer(QString host="127.0.0.1", int port=6666);

    void sendMessage(QByteArray &byte);

signals:
    void readyReceive(QByteArray &byte);

public slots:
    void receiveMessage();

private:
    QString m_server_type;
    QTcpSocket *m_tcpSocket;
    QByteArray m_receive_data;
};

#endif // SERVER_H
