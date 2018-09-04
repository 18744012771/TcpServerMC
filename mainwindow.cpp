#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcp_server_private.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    tcp_server_ = new TcpServer(this);

    if(!tcp_server_->listen(QHostAddress::Any, 1000))
    {
        qDebug()<<tcp_server_->errorString();    //错误信息
        return;
    }

    connect(tcp_server_,&TcpServer::ClientConnected,this,&MainWindow::ClientConnected);//连接监听
    connect(tcp_server_,&TcpServer::ClientDisconnected,this,&MainWindow::ClientDisconnected);//断开连接监听
    connect(this, &MainWindow::ServerRecved, this, &MainWindow::ServerRecvedSlot);//有数据到达，接收数据
    connect(this,&MainWindow::destroyed,this,&MainWindow::dealCloseWindow);
}

MainWindow::~MainWindow() {
    tcp_server_->close();
    delete ui;

}

void MainWindow::ClientConnected(qintptr handle, QTcpSocket* socket)
{
    QString IP_Port = QString("%1 %2 %3").
            arg(socket->peerAddress().toString()).
            arg(socket->peerPort()).
            arg("connect success");

    QString IP_PortInMap = QString("%1 %2").
            arg(socket->peerAddress().toString()).
            arg(socket->peerPort());

    ui->textEdit->append(IP_Port);
    clientAll.insert(handle,IP_PortInMap);


    connect(socket, &QTcpSocket::readyRead,
            [=]() {
        emit ServerRecved(handle, socket, socket->readAll());
    });
}

void MainWindow::ClientDisconnected(qintptr handle)
{
    Q_UNUSED(handle);
    QMap<int, QString>::Iterator mi;

    mi=clientAll.find(handle);
    QString val=mi.value();
    qDebug() << val;
   QString IP_PortDis = QString("%1 %2").
            arg(val).
            arg("disconnect ");
    ui->textEdit->append(IP_PortDis);

    clientAll.remove(handle);

}

void MainWindow::ServerRecvedSlot(qintptr handle, QTcpSocket *socket,const QByteArray &data) {
    Q_UNUSED(handle);
    qDebug()<<socket->peerAddress().toString()<<socket->peerPort()<<data;
    QString IP =socket->peerAddress().toString();
    if(IP=="::ffff:192.168.0.155")
    {
         socket->write(ui->lineSend1->text().toUtf8().data());
    }

    if(IP=="::ffff:192.168.0.125")
    {
         socket->write(ui->lineSend2->text().toUtf8().data());
    }



}


void MainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text()=="监控")
    {
        if(tcp_server_->isListening())
            return;
        if(!tcp_server_->listen(QHostAddress::Any, ui->linePort->text().toInt()))
        {
            qDebug()<<ui->linePort->text();
            qDebug()<<tcp_server_->errorString();    //错误信息
            return;
        }
        ui->pushButton_2->setText("断开");
    }
    else
    {
        if(!tcp_server_->isListening())
            return;
        tcp_server_->handDisConnect();
        tcp_server_->close();
        ui->pushButton_2->setText("监控");

    }
}



void MainWindow::on_pushButton_3_clicked()
{
    tcp_server_->handDisConnect();
    tcp_server_->close();
    this->close();
}
void MainWindow::dealCloseWindow()
{
    tcp_server_->handDisConnect();
    tcp_server_->close();
}
