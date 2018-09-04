#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "tcp_server.h"
#include "tcp_server_private.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMap<int, QString> clientAll;
    void dealCloseWindow();

signals:
    void ServerRecved(qintptr, QTcpSocket*, const QByteArray &);
private slots:
    void ClientConnected(qintptr handle, QTcpSocket *socket);
    void ClientDisconnected(qintptr handle);
    void ServerRecvedSlot(qintptr handle, QTcpSocket *socket, const QByteArray &data);



    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    TcpServer *tcp_server_;

};

#endif // MAINWINDOW_H
