#include "venderwin.h"
#include <QMessageBox>
#include <QtGlobal>
VenderWin::VenderWin(QWidget *p):QtTreePropertyBrowser(p)//QWidget(p)
{
    init();
}
//=======================
VenderWin::~VenderWin()
{
    qDebug() << " vender win down";
}

//=======================
void VenderWin::init()
{  
 

    m_mngE = new QtEnumPropertyManager();
    m_mng = new QtVariantPropertyManager();
    
    m_fct = new QtVariantEditorFactory();
    m_fctE = new QtEnumEditorFactory();
  //  m_fctPop = new QtPopupEditorFactory();

    setFactoryForManager(m_mng, m_fct); 
    setFactoryForManager(m_mngE, m_fctE);
    setSplitterPosition(150);

    //m_name = "";
    //m_node =NULL;
    createProperty();
 
}
 
void VenderWin::getData()
{
    int sz,i;
    LInfo * vender;
    QList<QtProperty *> listp,listsp;
    QtProperty *pt;
    QString str,key,v;
    bool bNew = false;
    qDebug() << "getdata";
    listp =  properties ();
    sz = listp.size();
     if (DOC->licFile.size() == 0)  
     {
        vender = DOC->licFile.vender();
        if (vender== NULL) 
        {
            vender = new  LInfo();
            bNew = true;
        }
    }
     else
         vender = DOC->licFile.vender();


    qDebug() << "get data params = " <<sz <<vender;
    //qDebug() << " vender = " << vender->getText();
    for (i = 0; i <sz;i++) 
    {
        pt = listp[i];
        key =  pt->propertyName();
        v =  pt->valueText();
        qDebug()<< key << v;
        vender->set(key,v);
        //qDebug() << i;
    }
    if (bNew)  
        DOC->licFile.addVender(vender); 
}
void VenderWin::setData()
{
     int sz,idx,i;
    QList<QtProperty *> listp,listsp;
    QtProperty *pt;
    QtVariantProperty *vpt;
    QString str,key,v,vv;
    LInfo * vender;
    qDebug() << "vender setdata";
    listp =  properties ();  
 
    if (DOC->licFile.size() == 0)  return;
    vender = DOC->licFile.vender();
    if (vender == NULL)  return;
  
    sz = listp.size();
    qDebug() << "set data params = " <<sz<<vender;
    //qDebug() << vender->getText();
    for (i = 0; i <sz;i++) 
    {
        pt = listp[i];
        key =  pt->propertyName();
        //v =  pt->valueText();
        if (vender->isKey(key)) 
        {
            v = vender->get(key).toString();
            vpt = (QtVariantProperty *)pt;
            //qDebug() << "setdata =" << i << pt  << key << v;
            if (key == VENDERKEY) 
            {
                vv = "";
        
                for (int m = 0; m<v.length(); m=m+100) 
                {
            
                    vv = vv+v.mid(m ,100)+ "\n";
                }
                pt->setToolTip(vv); 
            }
            if (key == BORROW) 
            {
                if (v.toLower() == "yes")  idx = 0;
                else idx = 1;
                //vpt->setValue(idx); 
                 m_mngE->setValue(vpt,idx);
            }
            else
                vpt->setValue(v); 
            //qDebug() << "setok";
        }
    }
}

int VenderWin::createProperty()
{
    QString str,key,tip,v;
    QStringList slist;
    pathConnect = true;
    qDebug() << "create property";
 
// vneder message:
    key = VENDERNAME;
    tip = key;
    v = "GeoEast";
    tip = "vender name";
    addStr(VENDERNAME,tip,v);
    tip = "vender seed string ,please keep it security";
    v= "0123456789";
    addStr(VENDERSEED,tip,"");
     tip = "venderprivate key file name ,please keep it security,use createkey commandline to get it ";
     v = "vender.pri";
     
    addFile(VENDERPRI,tip,v);
     #if 0
     tip = "vender public key file name ,please keep it security";
     v = "vender.pub";
    addFile(VENDERPUB,tip,v);
      #endif
 //client name:
    tip = "client  name";
    addStr(CLIENTNAME,tip,"");
// server:
    tip = "server hostname";
    addStr(SERVERNAME,tip,"");
     tip = "server id: use  commandline mid to get it";
    addStr(SERVERID,tip,"");
// borrow:
     tip = "if allow borrow mechanical :  yes/no";
     slist.clear();
     slist <<"yes" << "no";
    addOption(BORROW,tip,slist);
 // uuid:
     tip = "uuid : each license file give a different uuid";
    addStr(UUID,tip,"");
// venderkey:
     tip = "vender key  :  is the vender signed message";
    addStr(VENDERKEY,tip,"");
 

    connect(m_mng,SIGNAL(propertyChanged( QtProperty *)),
                         this,SLOT(slotModify(QtProperty *)));
    connect(m_mngE,SIGNAL(propertyChanged( QtProperty *)),
                         this,SLOT(slotModify(QtProperty *)));
  
    return  0;
}
 void VenderWin::addStr(QString key,QString tip,QString v)
{
    QtProperty *pt0;
      qDebug() << " addStr tip" << key << tip << v;
    //pathId = m_mng->pathTypeId();
    pt0 = m_mng->addProperty( QVariant::String, key);
    //pt0->setStatusTip(tip);
     pt0-> setToolTip(tip);
    m_mng->setValue(pt0,v);
    if (key == VENDERKEY || key == UUID) 
    {
        pt0->setEnabled(false);
    }
    addProperty(pt0);   
}

 void VenderWin::addOption(QString key,QString tip,QStringList slist)
{
    QtProperty *pt0;
    int idx;
      qDebug() << " addoption";
    pt0 = m_mngE->addProperty( key); 
    m_mngE->setEnumNames(pt0, slist);
    idx = 0;
    m_mngE->setValue(pt0,idx);
    pt0-> setToolTip(tip);
    addProperty(pt0);   
}
void VenderWin::addFile(QString key,QString tip,QString v)
{

    QtProperty *pt0;
    qDebug() << " addfile";
    int pathId;
    pathId = m_mng->pathTypeId();
    pt0 = m_mng->addProperty(pathId, key);
    if (pathConnect) //ensure connect   one time
    {
          connect(m_mng, SIGNAL(openPathTriggered(QtVariantProperty * , QtVariantPropertyManager * )), 
                 this, SLOT(slotOpenFile(QtVariantProperty* , QtVariantPropertyManager * )));
          pathConnect = false;
    }
    pt0-> setToolTip(tip);
    m_mng->setValue(pt0,v);
    addProperty(pt0);   
}

 
void VenderWin::slotModify(QtProperty *pro  )
{
    #if 0
    //qDebug() << "modifyed enter " ;
    if(theApp->m_doc->m_loadFile) return;
    theApp->m_win->setWindowModified(true);//modify
    qDebug() << "modifyed = " << pro->propertyName() ;
    #endif
}
void VenderWin::slotOpenFile(QtVariantProperty *property, QtVariantPropertyManager *thisManager)
{

    QString fileName,str,path;
    int i;
    path = DOC->m_licHome;
    fileName = QFileDialog::getOpenFileName(this, 
             tr("Open File"), path, tr("data Files (*.*)"));
    if (fileName.isEmpty()) return;

    QFileInfo fi(fileName);
    i = fileName.lastIndexOf("/");
    str = fileName.left(i+1);
    DOC->m_licHome = str;// remember the last set;
    property->setValue(fileName); 
}

 

