#include "tcp_client.h"
#include "ui_tcp_client.h"

#include <QTextCodec>

Tcp_Client::Tcp_Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tcp_Client)
{
    ui->setupUi(this);

    //实例化QTcpsocket
    socket=new QTcpSocket();

    //连接信号槽
    connect(socket,&QTcpSocket::readyRead,this,&Tcp_Client::onSocket_ReadData);
    connect(socket,&QTcpSocket::disconnected,this,&Tcp_Client::onDisconneted);

    ui->btn_Send->setEnabled(false);
    ui->txtIP->setText("127.0.0.1");
    ui->txtPort->setText("8888");
}

Tcp_Client::~Tcp_Client()
{
    //释放socket指针
    delete this->socket;
    delete ui;
}

bool Tcp_Client::onClient_Connect(QString IP,unsigned short port)
{
    //取消已有连接
    socket->abort();

    //连接服务器
    socket->connectToHost(IP,port);

    //等待连接成功
    if(!socket->waitForConnected(30000))
    {
        return false;
    }

    return  true;
}

void Tcp_Client::onSocket_ReadData()
{
    QByteArray buffer;

    //读取缓冲区数据
    buffer=socket->readAll();

    if(!buffer.isEmpty())
    {
        QString str=ui->textEdit_Rev->toPlainText();
        str+=buffer;

        //刷新显示
        ui->textEdit_Rev->setText(str);
    }
}

void Tcp_Client::onDisconneted()
{
    //发送按钮失效
    ui->btn_Send->setEnabled(false);

    //修改按钮文字
    ui->btn_Connection->setText("连接");
    qDebug()<<"Disconnected!";
}

void Tcp_Client::on_btn_Connection_clicked()
{
    if(ui->btn_Connection->text()=="连接")
    {
        QString IP=ui->txtIP->text();
        unsigned short port=ui->txtPort->text().toUShort();

        //连接服务器
        if(onClient_Connect(IP,port))
        {
            ui->textEdit_Rev->setText("链接成功!");

            //设置按钮文字
            ui->btn_Connection->setText("断开");
            ui->btn_Send->setEnabled(true);
        }
        else
        {
            ui->textEdit_Rev->setText("链接失败!");
        }
    }
    else
    {
        //断开连接
        socket->disconnectFromHost();

        //设置按钮文字
        ui->btn_Connection->setText("连接");
        ui->btn_Send->setEnabled(false);
    }
}

void Tcp_Client::on_btn_Send_clicked()
{
    qDebug()<<"Send: "<<ui->textEdit_Send->toPlainText().toLatin1();
    //发送数据
    socket->write(ui->textEdit_Send->toPlainText().toLatin1());
    socket->flush();
}
