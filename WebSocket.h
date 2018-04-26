#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QtWebSockets>

class WebSocket : public QWebSocket
{
    Q_OBJECT

public:
    WebSocket(QString url="");
    ~WebSocket();

public slots:
    void isConnected();
    void logError(QAbstractSocket::SocketError err);
    void logSslError(QList<QSslError> errs);
    void stateHasChanged(QAbstractSocket::SocketState newState);
    void newTextFrame(QString msg, bool isLast);
    void newMessage(QString msg);

    void reconnect();

private:
    QString hostUrl;
};

#endif // WEBSOCKET_H
