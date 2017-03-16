#include "mysqlview.h"
#include <QApplication>
#include <QtGui>
#include <QtSql>
#include <QtDebug>
#include <QSqlDatabase>


bool createConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("zhy");
    db.setUserName("root");
    db.setPassword("zhy");

    if(!db.open())
    {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int result;
    result = createConnect();
    //qDebug() << result;
    if(!result)
    {
        return 1;
    }

    MysqlView w;
    w.show();

    return a.exec();
}
