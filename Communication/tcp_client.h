#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

namespace Ui {
class Tcp_Client;
}

class Tcp_Client : public QWidget
{
    Q_OBJECT

public:
    explicit Tcp_Client(QWidget *parent = nullptr);
    ~Tcp_Client();

public slots:

    //链接服务器
    bool onClient_Connect(QString IP,unsigned short port);

    //获取数据
    void onSocket_ReadData();

    //断开连接
    void onDisconneted();

private slots:

    void on_btn_Connection_clicked();

    void on_btn_Send_clicked();

private:
    Ui::Tcp_Client *ui;
    QTcpSocket *socket;
};

#endif // TCP_CLIENT_H
