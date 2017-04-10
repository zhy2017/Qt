#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocketRx = new QUdpSocket(this);
    udpSocketTx = new QUdpSocket(this);

    connect(ui->clearReceiveButton, SIGNAL(clicked()), this, SLOT(OnClearReceive()));
    connect(ui->clearSendButton, SIGNAL(clicked()), this, SLOT(OnclearSend()));
    connect(ui->listenButton, SIGNAL(clicked()), this, SLOT(OnListen()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(OnSend()));
    connect(ui->sendButton1, SIGNAL(clicked()), this, SLOT(OnSend1()));
    connect(ui->sendButton2, SIGNAL(clicked()), this, SLOT(OnSend2()));
    connect(ui->sendButton3, SIGNAL(clicked()), this, SLOT(OnSend3()));

    connect(ui->sendlineEdit1, SIGNAL(textChanged(QString)), this, SLOT(setButton1()));
    connect(ui->sendlineEdit2, SIGNAL(textChanged(QString)), this, SLOT(setButton2()));
    connect(ui->sendlineEdit3, SIGNAL(textChanged(QString)), this, SLOT(setButton3()));

    buttonStatus = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnClearReceive()
{
    ui->receivePlainTextEdit->clear();
}

void MainWindow::OnclearSend()
{
    ui->sendPlainTextEdit->clear();
}

void MainWindow::OnListen()
{
    bool ok;
    int portRx;

    ipTx = QHostAddress(ui->remoteAddress->text());
    portTx = ui->remotePort->text().toInt(&ok);

    portRx = ui->localPort->text().toInt(&ok);
    udpSocketRx->bind(QHostAddress::Any, portRx);

    connect(udpSocketRx, SIGNAL(readyRead()), this, SLOT(receiveDatagram()));
    ui->sendButton->setEnabled(ok);

    if(buttonStatus)
    {
        ui->listenButton->setIcon(QIcon(":/images/stop.png"));
        buttonStatus = 0;
    }
    else
    {
        ui->listenButton->setIcon(QIcon(":/images/run.png"));
        buttonStatus = 1;
    }
}

void MainWindow::OnSend()
{
    QByteArray datagram = ui->sendPlainTextEdit->toPlainText().toAscii();
//    qDebug() << datagram.size();
    udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
}

void MainWindow::OnSend1()
{
    if(buttonStatus)
        return;

    QByteArray datagram;
    bool state = ui->checkBox1->isChecked();

    if(state)
    {
        datagram = HexStrToByteArray(ui->sendlineEdit1->text());
        udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
    }
    else
    {
        datagram = ui->sendlineEdit1->text().toAscii();
        udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
    }
}

void MainWindow::OnSend2()
{
    if(buttonStatus)
        return;

    QByteArray datagram;
    bool state = ui->checkBox2->isChecked();

    if(state)
    {
        datagram = HexStrToByteArray(ui->sendlineEdit2->text());
        udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
    }
    else
    {
        datagram = ui->sendlineEdit2->text().toAscii();
        udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
    }
}

void MainWindow::OnSend3()
{
    if(buttonStatus)
        return;

    QByteArray datagram;
    bool state = ui->checkBox3->isChecked();

    if(state)
    {
        datagram = HexStrToByteArray(ui->sendlineEdit3->text());
        udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
    }
    else
    {
        datagram = ui->sendlineEdit3->text().toAscii();
        udpSocketTx->writeDatagram(datagram, datagram.size(), ipTx, portTx);
    }
}

void MainWindow::receiveDatagram()
{
    while(udpSocketRx->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocketRx->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketRx->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        ui->receivePlainTextEdit->appendPlainText(datagram);
    }
}

void MainWindow::setButton1()
{
    QString str = ui->sendlineEdit1->text();
    if(str == NULL)
        ui->sendButton1->setEnabled(false);
    else
        ui->sendButton1->setEnabled(true);
}

void MainWindow::setButton2()
{
    QString str = ui->sendlineEdit2->text();
    if(str == NULL)
        ui->sendButton2->setEnabled(false);
    else
        ui->sendButton2->setEnabled(true);
}

void MainWindow::setButton3()
{
    QString str = ui->sendlineEdit3->text();
    if(str == NULL)
        ui->sendButton3->setEnabled(false);
    else
        ui->sendButton3->setEnabled(true);
}
