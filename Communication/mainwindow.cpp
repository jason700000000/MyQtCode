#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tcp_server.h"
#include "tcp_client.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "app.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //绑定菜单单击事件
    connect(ui->actionServer,&QAction::triggered,this,&MainWindow::onCreateTcpServer);
    connect(ui->actionClient,&QAction::triggered,this,&MainWindow::onCreateTcpClient);

    App::writeConfig();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateTcpServer()
{
    tcpserver=new Tcp_Server();
    tcpserver->show();
}

void MainWindow::onCreateTcpClient()
{
    tcpclient=new Tcp_Client();
    tcpclient->show();
}

