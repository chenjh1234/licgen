#include "packagewin.h"
#include "licapp.h"
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMessageBox>
#include <math.h>
PackageWin::PackageWin(QWidget *p) : QGraphicsView(p)
{
   init();
}
//=======================
PackageWin::~PackageWin()
{
    qDebug() << " package win down";

}
void PackageWin::init()
{
   // table:
   gridLayout = new QGridLayout(this);
   gridLayout->setObjectName(QStringLiteral("gridLayout"));
   tableView = new TableView(this);
   tableView->setObjectName(QStringLiteral("tableView"));
   gridLayout->addWidget(tableView, 0, 0, 1, 1);
   // table:
   QString str;
   QStringList slist;
   model = new QStandardItemModel(MAX_PACKAGES, PACKAGE_KEYS);
   char *key[] = PACKAGE_DEFINE;
   int i;
   i = 0;
   for (i = 0; i < PACKAGE_KEYS; i++)
   {
      slist << key[i];
      qDebug() << slist;
   }
   model->setHorizontalHeaderLabels(slist);
   //horizontalHeader()->setStretchLastSection(true);
   dlg = new TableDlg();

   int column = 2;
   tableView->setItemDelegateForColumn(column, dlg);
   clear();
#if 1
   //str = "task";
   QStandardItem *item;
   for (int row = 0; row < MAX_PACKAGES; ++row)
   {
       
       item = model->item(row,PKEY_ITEM_IDX);
       item->setEnabled(false);

   }
#endif
   tableView->setModel(model);
   //connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelect(QModelIndex)));
   //  connect(buttonBox, SIGNAL(accepted()),this, SLOT(accept()));
}
void PackageWin::clear()
{
    int rows,cols,i,j;
    QString str,str1;
    rows = model->rowCount(QModelIndex());
    cols = model->columnCount(QModelIndex());
    str = "";
    str1 = "task";
    for (i = 0; i < rows;i++) 
    {
        for (j =0; j< cols;j++) 
        {
            if (j == 2)  
                setData(i, j, str1); 
            else
                setData(i, j, str); 
        }    
    }
}
QString  PackageWin::getData(int x, int y)
{
    QModelIndex index = model->index(x, y, QModelIndex());
    return  model->data(index).toString();

}
void PackageWin::setData(int x, int y,QString v)
{
      QModelIndex index = model->index(x, y, QModelIndex());
      model->setData(index, QVariant(v));
}
void PackageWin::setData()
{
    int rows,cols,i,j;
    char *key[] = PACKAGE_DEFINE;
    QString str,str1,k;
    LInfo *package;
    int sz;
    sz = DOC->licFile.size();
    if ( sz<= 0)  return;

  
    rows = model->rowCount(QModelIndex());
    cols = model->columnCount(QModelIndex());

    if (rows !=sz)  
        model->setRowCount(sz);

    clear();
    rows = sz;

    str = ""; 
    str1 = "task";
    for (i = 0; i < rows;i++) 
    {
        package  = DOC->licFile.package(i);
        if (package == NULL) continue; // it  should not NULL
                                    
        for (j =0; j< cols;j++) 
        {
            k = key[j];
            str = package->get(k).toString();
            setData(i,j,str);
            qDebug() << "pack setdata = "<< i << j << str;
        }    
    }

}
void PackageWin::getData()
{
    int rows,cols,i,j;
    char *key[] = PACKAGE_DEFINE;
    QString str,k;
    LInfo *package;
    bool bNew;
    int sz;
    sz = DOC->licFile.size();
     

    rows = model->rowCount(QModelIndex());
    cols = model->columnCount(QModelIndex());
    str = "";
    bNew = false;
    for (i = 0; i < rows;i++) 
    {
        str = getData(i, 0); 
        if (str.length() == 0)  break;// apckagename = "";
        // get packge or new
        if (i < sz) 
        {
            package =  DOC->licFile.package(i);
            bNew = false;
        }
        else
        {
             package =  DOC->licFile.package(i);
             bNew = true;
        }
        // end of package
        //getdata:
        for (j = 0; j < cols; j++) 
        {      
               str = getData(i, j);   
               k = key[j];
               if(package !=NULL)
               {
                   package->set(k,str);
               }
               qDebug() << "pack getdata = "<< i << j << str;
        }    
    }
#if 0
  void flowDefine::setText(int row,QString &t,QString &n, QString &v)
{
    model->setData(model->index(row,0,QModelIndex()),t);
    model->setData(model->index(row,1,QModelIndex()),n);
    model->setData(model->index(row,2,QModelIndex()),v);
}
void flowDefine::getText(int row,QString &t,QString &n ,QString &v)
{
    QVariant vq;
    vq  = model->data(model->index(row,0,QModelIndex()));
    t = vq.toString();
    vq  = model->data(model->index(row,1,QModelIndex()));
    n = vq.toString();
    vq = model->data(model->index(row,2,QModelIndex()));
    v = vq.toString();

} 
   #endif

}
int  PackageWin::addRow()
{
    int sz;
    sz = model->rowCount();
    model->setRowCount(sz+1);
    setData(sz, 2, "task"); 
    return sz+1;
}
int PackageWin::rmRow()
{
    int sz;
    sz = model->rowCount();
    if (sz <=1)  return -1;
    model->setRowCount(sz - 1); 
    return sz -1;
}

int PackageWin::copyRow()
{
    int sz,row,i;
    QModelIndexList  mlist;
    QModelIndex idx;
    mlist  = tableView->selected() ;
    sz = mlist.size();
    row = -1;
    rowList.clear();

    if (sz == 0)  return -1;// no thing selected
    for (i = 0; i <sz;i++) 
    {
        idx = mlist[i];
        if (idx.column() == 0)  
        {
            row = idx.row();
            break;
        }
    }
    qDebug() << "copyRow = " << row;
    if (row <0)  return -2;// column 0 not selected;
    // get data:
    
    for (i = 0;i < model->columnCount();i++) 
    {
        rowList << getData(row,i);
    }
    return row; 
}
int PackageWin::pasteRow()
{
    int sz,row,i;
    QModelIndexList  mlist;
    QModelIndex idx;
    QString s;
    if (rowList.size() == 0 )  return -1;// no copy contains:

    mlist  = tableView->selected();
    sz = mlist.size();
    row = -1;
    if (sz == 0)  return -2;// nothing selected

    for (i = 0; i <sz;i++) 
    {
        idx = mlist[i];
        if (idx.column() == 0)  
        {
            row = idx.row();
            break;
        }
    }
    qDebug() << "pasteRow = " << row;
    if (row <0)  return -3;// column 0 not selected;

    // set data:
    for (i = 0;i < model->columnCount();i++) 
    {
         s = rowList[i];
         setData(row,i,s);
    }
    return row; 
}

