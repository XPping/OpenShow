#include "server.h"

Server::Server(QString server_type, QObject *parent) : QObject(parent),
    m_server_type(server_type),
    m_tcpSocket(0)
{
    m_tcpSocket = new QTcpSocket(this);
    m_receive_data = "";
}

bool Server::connectToServer(QString host, int port)
{
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host, port);
    if(!m_tcpSocket->waitForConnected(100)){
        return false;
    }
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    m_receive_data = "";
    return true;
}

void Server::sendMessage(QByteArray &byte)
{
    //byte.insert(0, m_server_type+";");
    quint32 write_len = m_tcpSocket->write(byte);
    //m_tcpSocket->write("Send End");
}

void Server::receiveMessage()
{
    QByteArray end = "END";
    QByteArray byte = m_tcpSocket->readAll();
    m_receive_data.append(byte);
    //qDebug()<<m_receive_data.length();
    if(m_receive_data.contains(end)){
        //qDebug()<<m_receive_data.length()<<end.length()<<m_receive_data.indexOf(end, m_receive_data.length()-4);
        m_receive_data = m_receive_data.mid(0, m_receive_data.lastIndexOf(end));
        emit readyReceive(m_receive_data);
        //qDebug()<<"split"<<m_receive_data.length();
        m_receive_data = "";
    }
}
