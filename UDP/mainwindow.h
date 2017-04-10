#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static QString ByteArrayToHexStr(QByteArray data)
    {
        QString temp = "";
        QString hex = data.toHex();
        for (int i = 0; i < hex.length(); i = i + 2)
        {
            temp += hex.mid(i, 2) + " ";
        }
        return temp.trimmed().toUpper();
    }

    static char ConvertHexChar(char ch)
    {
        if((ch >= '0') && (ch <= '9'))
            return ch - 0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch - 'A' +10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch - 'a' + 10;
        else return (-1);
    }

    static QByteArray HexStrToByteArray(QString str)
    {
        QByteArray senddata;
        int hexdata,lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len/2);
        char lstr,hstr;
        for(int i = 0; i < len; )
        {
            hstr = str[i].toAscii();
            if(hstr == ' ')
            {
                i++;
                continue;
            }
            i++;
            if(i >= len)
                break;
            lstr = str[i].toAscii();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
                break;
            else
                hexdata = hexdata*16 + lowhexdata;
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }

private slots:
    void OnClearReceive();
    void OnclearSend();
    void OnListen();
    void OnSend();
    void OnSend1();
    void OnSend2();
    void OnSend3();

    void receiveDatagram();

    void setButton1();
    void setButton2();
    void setButton3();

private:
    Ui::MainWindow *ui;

    QUdpSocket *udpSocketRx;
    QUdpSocket *udpSocketTx;
    QHostAddress ipTx;
    int portTx;
    bool buttonStatus;

};

#endif // MAINWINDOW_H
