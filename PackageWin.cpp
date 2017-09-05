#include "packagewin.h"
#include "licapp.h"
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMessageBox>
#include <math.h>
PackageWin::PackageWin(QWidget *p):QGraphicsView(p)
{
    init();
}
//=======================
PackageWin::~PackageWin()
{
    
}
void PackageWin::init()
{
    // table:
        gridLayout = new QGridLayout(this);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(this);
        tableView->setObjectName(QStringLiteral("tableView"));
        gridLayout->addWidget(tableView, 0, 0, 1,1);
   // table:
        QString str;
        QStringList liststr;
        model = new QStandardItemModel(4,3);
        liststr << "type" << "name" << "value";
        model->setHorizontalHeaderLabels(liststr);
        //horizontalHeader()->setStretchLastSection(true);
        dlg = new TableDlg();
        tableView->setItemDelegateForColumn(0,dlg);
       // str = "&table";
        #define MAX_DEFINES 6

        for (int row = 0; row < MAX_DEFINES; ++row) 
        {
            for (int column = 0; column < 1; ++column) 
            {
                 if(row == 3 ) str = "&define";
                 else str= "&table";
                 QModelIndex index = model->index(row, column, QModelIndex());
                 model->setData(index, QVariant(str));
            }
        }

        tableView->setModel(model);


       // connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelect(QModelIndex)));
        //connect(ui.tableView, SIGNAL(clicked(QModelIndex )),  this, SLOT(accept()));
       // connect(ui.tableView, SIGNAL(clicked(QModelIndex )),(flowDefine *) this, SLOT(slotSelect( QModelIndex )));
      //  connect(buttonBox, SIGNAL(accepted()),this, SLOT(accept()));


}
