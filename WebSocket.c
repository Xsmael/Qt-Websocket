#include "WebSocket.h"

WebSocket::WebSocket(QString url) : QWebSocket()
{

    connect(this, SIGNAL(connected()), this, SLOT(isConnected()));
    connect(this, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(logSslError(QList<QSslError>)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(logError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateHasChanged(QAbstractSocket::SocketState)));
    connect(this, SIGNAL(textMessageReceived(QString)), this, SLOT(newMessage(QString)));
    //connect(this, SIGNAL(textFrameReceived(QString,bool)), this, SLOT(newTextFrame(QString,bool)));

    if(!url.isEmpty()) this->open(QUrl(url));
    hostUrl=url;

}

WebSocket::~WebSocket()
{

}

void WebSocket::isConnected()
{
    this->sendTextMessage("Hello From Qt!!!");
}

void WebSocket::logError(QAbstractSocket::SocketError err)
{
    qDebug() << "Error: ";
    qDebug() << err;
}

void WebSocket::logSslError(QList<QSslError> errs)
{
    qDebug() << "SSLError: ";
    qDebug() << errs;
}

void WebSocket::stateHasChanged(QAbstractSocket::SocketState newState)
{
    qDebug() << "\n\nState Changed! ";
    qDebug() << newState;

    if(newState == QAbstractSocket::UnconnectedState)
         QTimer::singleShot(5000,this,SLOT(reconnect()));
}

void WebSocket::reconnect()
{
      this->open(hostUrl);
}

void WebSocket::newMessage(QString msg)
{
    qDebug() << msg;
}

void WebSocket::newTextFrame(QString msg, bool isLast)
{
    qDebug() <<" TextFrame received: "+msg;
    qDebug() << isLast;
}
