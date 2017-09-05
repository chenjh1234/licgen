#ifndef PACKAGE_WIN_H
#define PACKAGE_WIN_H
 
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QHeaderView>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include "tabledlg.h"
class PackageWin :public QGraphicsView
{
Q_OBJECT

public:
    PackageWin(QWidget *p);
    ~PackageWin();
    void init();
    QTableView *tableView;
    QGridLayout *gridLayout;

    QStandardItemModel *model;
    TableDlg *dlg;


 
};
#endif



