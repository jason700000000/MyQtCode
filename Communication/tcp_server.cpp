#include "tcp_server.h"
#include "ui_tcp_server.h"

Tcp_Server::Tcp_Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tcp_Server)
{
    ui->setupUi(this);

    server=new QTcpServer();

    ui->btn_Send->setEnabled(false);
    ui->txt_Port->setText("8888");

    //绑定信号
    connect(server,&QTcpServer::newConnection,this,&Tcp_Server::onServer_New_Connect);
}

Tcp_Server::~Tcp_Server()
{
    server->close();
    server->deleteLater();
    delete ui;
}

void Tcp_Server::onServer_New_Connect()
{
    //获取客户端链接
    socket=server->nextPendingConnection();

    //获取ip并添加到socket队列中
    QString ip=socket->peerAddress().toString();

    //队列中是否存在该ip socket
    if(!map_socket.contains(ip))
    {
            map_socket.insert(ip,socket);

            //设置socket信号，用来读取数据
            connect(socket,&QTcpSocket::readyRead,this,&Tcp_Server::onServer_ReadData);
            connect(socket,&QTcpSocket::disconnected,this,&Tcp_Server::onServer_Disconnected);
    }

    //启动发送按钮
    ui->btn_Send->setEnabled(true);
    qDebug()<<"A Client connect!";
}

void Tcp_Server::onServer_ReadData()
{
    //读取缓存区内容
    QByteArray buffer;
    buffer=socket->readAll();

    if(!buffer.isEmpty())
    {
        QString str=ui->textEdit_Rev->toPlainText();
        str+=buffer;
        //刷新接收区文本框
        ui->textEdit_Rev->setText(str);
    }
}

void Tcp_Server::onServer_Disconnected()
{
    //禁用发送按钮
    ui->btn_Send->setEnabled(false);
    ui->btn_Listen->setText(tr("侦听"));
    qDebug()<<"Disconnected!";
}

void Tcp_Server::on_btn_Listen_clicked()
{
    if(ui->btn_Listen->text()==tr("侦听"))
    {
        //获取端口
        unsigned short port=ui->txt_Port->text().toUShort();

        //侦听指定端口
        if(!server->listen(QHostAddress::Any,port))
        {
            qDebug()<<server->errorString();
            return;
        }

        //修改按钮文字
        ui->btn_Listen->setText("停止");
        qDebug()<<"Listen successfully!";

    }
    else
    {

        //        //如果正在连接（点击侦听后立即取消侦听，若socket没有指定对象会有异常，应修正——2017.9.30）
        //        if(socket->state() == QAbstractSocket::ConnectedState)
        //        {
        //            //关闭连接
        //            socket->disconnectFromHost();
        //        }

        //关闭SOCKET
        socket->abort();

        //取消侦听
        server->close();

        //修改按钮
        ui->btn_Listen->setText(tr("侦听"));

        //发送消息按钮
        ui->btn_Send->setEnabled(false);

    }
}

void Tcp_Server::on_btn_Send_clicked()
{
    qDebug()<<"Send: "<<ui->textEdit_Send->toPlainText();
    //获取发送文本，以ASCII码形式发送
    socket->write(ui->textEdit_Send->toPlainText().toLatin1());
    socket->flush();
}
