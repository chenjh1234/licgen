#ifndef PACKAGE_WIN_H
#define PACKAGE_WIN_H
 
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QHeaderView>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include "tableitem.h"
#include "tableview.h"
 

class PackageWin :public QGraphicsView
{
Q_OBJECT

public:
    PackageWin(QWidget *p);
    ~PackageWin();
    void init();
    void setData();
    void  setData(int x, int y,QString v);

    void getData();
    QString getData(int x,int y);
    void clear();

    int addRow();
    int rmRow();
    int copyRow();
    int pasteRow();

    TableView *tableView;
    QGridLayout *gridLayout;

    QStandardItemModel *model;
    TableDlg *dlg;
    QStringList rowList;




 
};
#endif



