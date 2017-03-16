#include "mysqlview.h"
#include "ui_mysqlview.h"
#include <QtGui>
#include <QtSql>
#include <QMessageBox>
#include <QSqlError>
#include "GBK.h"

MysqlView::MysqlView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MysqlView)
{
    ui->setupUi(this);

    m_model = new QSqlTableModel(this);
    m_model->setTable("students");
    m_model->setSort(0, Qt::AscendingOrder);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setHeaderData(1, Qt::Horizontal, tr("Number"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Name"));

    m_model->select();

    ui->tableView->setModel(m_model);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
   // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setStretchLastSection(true);

    connect(ui->commitChangeButton, SIGNAL(clicked()), this, SLOT(commitChange()));
    connect(ui->undoButton, SIGNAL(clicked()), this, SLOT(undo()));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(select()));
    connect(ui->returnAllButton, SIGNAL(clicked()), this, SLOT(returnAll()));
    connect(ui->ascendingButton, SIGNAL(clicked()), this, SLOT(ascending()));
    connect(ui->descendingButton, SIGNAL(clicked()), this, SLOT(descending()));
    connect(ui->addRecordButton, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(ui->delRecordButton, SIGNAL(clicked()), this, SLOT(delRecord()));

    setWindowTitle(tr("Mysql View"));
}

void MysqlView::commitChange()
{
    m_model->database().transaction();//start things
    if(m_model->submitAll())
    {
        m_model->database().commit();
    }
    else
    {
        m_model->database().rollback();
        QMessageBox::warning(this, tr("table Model"), GBK::ToUnicode("数据库错误：%1")
                .arg(m_model->lastError().text()));
    }

}

void MysqlView::undo()
{
    m_model->revertAll();
}

void MysqlView::addRecord()
{
    int rowNum = m_model->rowCount();

    int id = rowNum + 1;
    m_model->insertRow(rowNum);
    m_model->setData(m_model->index(rowNum, 0), id);
}

void MysqlView::delRecord()
{
    int curRow = ui->tableView->currentIndex().row();
    m_model->removeRow(curRow);

    int ok;
    ok = QMessageBox::warning(this,
                              GBK::ToUnicode("删除当行"),
                              GBK::ToUnicode("你确定要删除当行吗？"),
                              QMessageBox::Yes,
                              QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        m_model->submitAll();
    }
    else
    {
        m_model->revertAll();
    }
}

void MysqlView::ascending()
{
    m_model->setSort(1, Qt::AscendingOrder);
    m_model->select();
}

void MysqlView::descending()
{
    m_model->setSort(0, Qt::DescendingOrder);
    m_model->select();
}

void MysqlView::select()
{
    QString name = ui->nameLineEdit->text();
    m_model->setFilter(QObject::tr("name = '%1'").arg(name));
    m_model->select();
}

void MysqlView::refresh()
{
    m_model->select();
    QMessageBox::information(NULL, "Table View", GBK::ToUnicode("刷新成功"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MysqlView::returnAll()
{
   // m_model->setTable("students");
    m_model->setFilter(QObject::tr("id != -1"));
    m_model->select();
}

MysqlView::~MysqlView()
{
    delete ui;
}
