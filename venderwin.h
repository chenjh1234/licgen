#ifndef VENDER_WIN_H 
#define VENDER_WIN_H  
 
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "qteditorfactory.h"
 
#include "licapp.h"
using namespace std;

class VenderWin :public QtTreePropertyBrowser //QWidget
{
    Q_OBJECT

public:
    VenderWin(QWidget *p);
    ~VenderWin();
     
    int createProperty();

    void getData();
    void setData();
  

private:
    void init();
    QtEnumPropertyManager *m_mngE;
    QtVariantPropertyManager * m_mng;  

    QtVariantEditorFactory * m_fct;
    QtEnumEditorFactory *m_fctE;
    //QtPopupEditorFactory *m_fctPop;

    void addStr(QString key,QString tip,QString v);
    void addFile(QString key,QString tip,QString v);
    void addOption(QString key,QString tip,QStringList v);

     bool pathConnect;
    
 
protected:
    //gdata *data;
public slots:
   // void slotParam(QString s);
   // void slotShowParam(QString s);
    void slotOpenFile(QtVariantProperty *property, QtVariantPropertyManager *thisManager); 
    //void slotOpenConstant(QtVariantProperty *property, QtVariantPropertyManager *thisManager);
    void slotModify(QtProperty *  );

   // virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
};


#endif

