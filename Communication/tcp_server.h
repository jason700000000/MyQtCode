#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Tcp_Server;
}

class Tcp_Server : public QWidget
{
    Q_OBJECT

public:
    explicit Tcp_Server(QWidget *parent = nullptr);
    ~Tcp_Server();

private slots:
    void onServer_New_Connect();

    void onServer_ReadData();

    void onServer_Disconnected();

    void on_btn_Listen_clicked();

    void on_btn_Send_clicked();

private:
    Ui::Tcp_Server *ui;
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif // TCP_SERVER_H
