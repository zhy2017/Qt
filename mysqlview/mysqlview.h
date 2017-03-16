#ifndef MYSQLVIEW_H
#define MYSQLVIEW_H

#include <QDialog>

namespace Ui {
class MysqlView;
}

class QSqlTableModel;

class MysqlView : public QDialog
{
    Q_OBJECT

public:
    explicit MysqlView(QWidget *parent = 0);
    ~MysqlView();

private slots:
    void commitChange();
    void undo();
    void addRecord();
    void delRecord();
    void ascending();
    void descending();
    void select();
    void refresh();
    void returnAll();

private:
    Ui::MysqlView *ui;

private:
    QSqlTableModel *m_model;
};

#endif // MYSQLVIEW_H
