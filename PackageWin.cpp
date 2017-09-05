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
        model = new QStandardItemModel(4,8);
        liststr << "name" << "version" << "type"<<"number" <<"start" << "end" << "key" << "pborrow";
        model->setHorizontalHeaderLabels(liststr);
        //horizontalHeader()->setStretchLastSection(true);
        dlg = new TableDlg();
        tableView->setItemDelegateForColumn(2,dlg);
        #if 1
        str = "task";
        #define MAX_DEFINES 10

        for (int row = 0; row < MAX_DEFINES; ++row) 
        {
            int column = 2;  
               
                 QModelIndex index = model->index(row, column, QModelIndex());
                 model->setData(index, QVariant(str));
 
        }
#endif
        tableView->setModel(model);


       // connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelect(QModelIndex)));
        //connect(ui.tableView, SIGNAL(clicked(QModelIndex )),  this, SLOT(accept()));
       // connect(ui.tableView, SIGNAL(clicked(QModelIndex )),(flowDefine *) this, SLOT(slotSelect( QModelIndex )));
      //  connect(buttonBox, SIGNAL(accepted()),this, SLOT(accept()));


}
