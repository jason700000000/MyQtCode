#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcp_server.h"
#include "tcp_client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onCreateTcpServer();
    void onCreateTcpClient();

private:
    Ui::MainWindow *ui;
    Tcp_Server *tcpserver;
    Tcp_Client *tcpclient;
};
#endif // MAINWINDOW_H
