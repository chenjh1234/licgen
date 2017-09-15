 
#include <QtWidgets>
#include <QMessageBox>
#include "mainwindow.h"
#define stringList csVector<std::string>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QPixmap>
#include <QVBoxLayout>
 
 
MainWindow::MainWindow():QMainWindow()
{
    //left dock: up:modules,down:moduleHelp:
//dock
    m_w=  1500;
    m_h = 800;
    
    venderDockWidget = new QDockWidget("venderView",this );
    addDockWidget(Qt::LeftDockWidgetArea, venderDockWidget);
    //venderDockWidget->setFixedWidth(300);
     
//venderView:
    
    venderManager = new  QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(venderManager);
    venderWin = new VenderWin(venderManager);

    vlayout->setSpacing(1);
    vlayout->addWidget(venderWin);

    venderDockWidget->setWidget(venderManager);
 
 // main: 
   
    packageWin  = new PackageWin(this);
    setCentralWidget(packageWin);
// connect:
   // connect(editFilter,SIGNAL(textChanged(QString )),modListView,SLOT(slotFilter(QString)));
   // connect(buttonModAll,SIGNAL(clicked ()),modListView,SLOT(slotFilterAll()));

 
 
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    setWindowModified(false);//init
    resize(m_w,m_h);
    venderDockWidget->resize(m_w/2,m_h);
  
    setTitle();
    setFile(LICFILE_DEFAULT);

  //  venderWin->getData();
 //   packageWin->getData();
   
    return; 
  
}
void MainWindow::setTitle()
{
  
    QString str;
    str = "";
    str = str + APP_NAME + "-"+APP_VERSION +"-"+ __DATE__ ;
    
    setWindowTitle(str);
    qDebug() << "title = " << str;

}
  

     
void MainWindow::closeEvent(QCloseEvent *event)

{
    qDebug() << " main win downo";

 
        writeSettings();
        event->accept();
        qDebug() << " main win down";
    
}
 
void MainWindow::newFile()
{
    setFile(LICFILE_DEFAULT);
}

void MainWindow::open()
{
     
    int i;
    QString strt,strd,strf,str;
    strf = "Lic file (*.lic );; All file (*.*)";
    
    strt = "Open lic file";
    strd = theApp->m_doc->m_licHome;
    
   
    QString fileName = QFileDialog::getOpenFileName(this,strt,strd,strf);
    if (fileName.isEmpty()) return;
            
    QFileInfo fi(fileName);
    i = fileName.lastIndexOf("/");
    str = fileName.left(i+1);
    theApp->m_doc->m_licHome = str;// remember the last set

    setFile(fileName);         
}
 
int  MainWindow::setFile(QString file)
{
    int i;
    DOC->m_filename = file;

    i = DOC->setFile(file);
    qDebug() << "i = " << i;
    if (i <=0) 
    {
        ST(file + " file open Error");
        return i;
    }
    else
        ST(file + " file open OK");
  
    venderWin->setData();
    packageWin->setData();

    return i;
}

bool MainWindow::save()
{
    bool b;
    
    if (DOC->m_fileOut.isEmpty()) 
    {
        b = saveAs();
    } 
    else 
    {
        b =  saveFile(DOC->m_fileOut);
    }
    qDebug() << "save =" << b;
    return b;
}

bool MainWindow::saveAs()
{
    bool b;
    QString strt,strd,strf,str;
    strf = "*.lic";
    strt = "save license file";
    strd = theApp->m_doc->m_licHome;
  
    QString fileName = QFileDialog::getSaveFileName(this,strt,strd,strf);
    if (fileName.isEmpty())
    {
        ST("No File spcified");
        return false;
    }
    QFileInfo fi(fileName);

    QString ext = "lic";
    if (fi.suffix() != ext) 
    {
        fileName = fileName +"."+ext;
    }
    DOC->m_fileOut = fileName;
    b =  saveFile(fileName);
    qDebug() << "save =" << b;
    return b;
}
 
void MainWindow::about()
//! [13] //! [14]
{
    QString title,str,str1;
    title = ORG_NAME;
    str1 = __DATE__;
    str = QString("   App name : ") +QString(APP_NAME) + "\n" +
          QString("App version : ") +QString(APP_VERSION) + "\n" +
          QString("       Date : ") +str1;
   QMessageBox::about(this, title,str);
}
 
void MainWindow::createActions()
{
    //new
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
 
    openOutAct = new QAction(QIcon(":/images/openout.png"), tr("&OpenOut..."), this);
    //openOutAct->setShortcuts(QKeySequence::Open);
    openOutAct->setStatusTip(tr("Open output"));
    connect(openOutAct, SIGNAL(triggered()), this, SLOT(openOut()));
 

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
 
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
 
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    // edit:
    addRowAct = new QAction(QIcon(":/images/addrow.png"), tr("&AddRow"), this);
    //addRowAct->setShortcuts(QKeySequence::Save);
    addRowAct->setStatusTip(tr("append a row"));
    connect(addRowAct, SIGNAL(triggered()), this, SLOT(addRow()));

    rmRowAct = new QAction(QIcon(":/images/rmrow.png"), tr("&RmRow"), this);
    //addRowAct->setShortcuts(QKeySequence::Save);
    rmRowAct->setStatusTip(tr("remove the last row "));
    connect(rmRowAct, SIGNAL(triggered()), this, SLOT(rmRow()));

     copyRowAct = new QAction(QIcon(":/images/copyrow.png"), tr("&CopyRow"), this);
    //addRowAct->setShortcuts(QKeySequence::Save);
    copyRowAct->setStatusTip(tr("copy the selected row"));
    connect(copyRowAct, SIGNAL(triggered()), this, SLOT(copyRow()));


    pasteRowAct = new QAction(QIcon(":/images/pasterow.png"), tr("&PasteRow"), this);
   //addRowAct->setShortcuts(QKeySequence::Save);
   pasteRowAct->setStatusTip(tr("paste the selected row "));
   connect(pasteRowAct, SIGNAL(triggered()), this, SLOT(pasteRow()));

 
//help

    helpAct = new QAction(QIcon(":/images/help.png"), tr("&Help"), this);
    helpAct->setStatusTip(tr("User manual of flowPad"));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(slotHelp()));
    //qDebug() << "create action OK";


//about

    aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    //qDebug() << "create action OK";
    return;
   
}
 void MainWindow::createMenus()
{
   // open
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(openOutAct);
    fileMenu->addSeparator();
    
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addRowAct);
    editMenu->addAction(rmRowAct);
    editMenu->addAction(copyRowAct);
    editMenu->addAction(pasteRowAct);
  
 
 
//help
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    qDebug() << "create menu OK";
    return;
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
     fileToolBar->addAction(openOutAct);
    //fileToolBar->addAction(textFlowAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(addRowAct);
    editToolBar->addAction(rmRowAct);
    editToolBar->addAction(copyRowAct);
    editToolBar->addAction(pasteRowAct);

     helpToolBar = addToolBar(tr("Help"));
      helpToolBar->addAction(helpAct);
     helpToolBar->addAction(aboutAct);
 
    qDebug() << "create toolbar OK";
    return;
}

void MainWindow::createStatusBar()

{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    //QSettings settings(ORG_NAME, APP_NAME);
    //QString str = settings.value("flow").toString();
    //theApp->m_doc->m_filename =str; 
 
}
void MainWindow::writeSettings()
{
    #if 0
    QString str;
    QSettings settings(ORG_NAME,APP_NAME);
    str = QString("\"") + theApp->m_doc->m_filename + QString("\"");
    settings.setValue("flow", theApp->m_doc->m_filename);
    #endif
}

bool MainWindow::maybeSave()
{ 
    #if 0
    if ( isWindowModified ()) 
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("You will New your flow"),
                     tr("The current flow has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    } 
    #endif
    return true;
}
 

bool MainWindow::saveFile(const QString &fileName)
{

    //return true;
    int i;
    LLicFile *lfile;
    venderWin->getData();
    packageWin->getData();

    lfile = &(DOC->licFile);
    LLicEncrypt lic;
    lic.setLicFile(lfile);
    i = lic.createKey();
    if(i <0)
    {
        msg(lic._err);
        return false;
    }
    else
    {
        DOC->licFile.writeFile(DOC->m_fileOut);
        fileText(DOC->m_fileOut);
    }    
    return true;
}
void MainWindow::openOut()
{
    fileText(DOC->m_fileOut,DOC->m_fileOut);
}
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
  
        
void MainWindow::resizeEvent ( QResizeEvent * event )
{
    //int w,h;
    m_w = event->size().width();
    m_h = event->size().height();
    //flowMode();
}
void MainWindow::slotHelp()
{
    QString cmd,str;
    char *ch;
    cmd = CMD_SHOWPDF;
    cmd = cmd+  DOC->docPath()+ "/" + APP_NAME+".pdf";
        //cmd = "ls";
    qDebug() << "cmd=" <<cmd;
    hrun.start(cmd);

}
void MainWindow::addRow()
{
    qDebug() <<" addRow";
    int i;
    i = packageWin->addRow();
  
}
void MainWindow::rmRow()
{
   // qDebug() <<" rmRow";
        int i;
     if(! ask("this will remove the last row of the table , are you sure???")) return;
    i = packageWin->rmRow();
    QString str;
     if (i == -1 ) str = "Error: only one row left";
     else str ="OK";
     ST(str);

}
void MainWindow::copyRow()
{
   // qDebug() <<" copyRow";
        int i;
    i = packageWin->copyRow();
     QString str;
     if (i <0 ) str = "Error: No selected row";
     else str ="OK";
     ST(str);
}
void MainWindow::pasteRow()
{
    //qDebug() <<" pasteRow";
     int i;
     if(! ask("this will replace the cantains of selected row, are you sure???")) return;
    i = packageWin->pasteRow();
     QString str;
     if (i == -1 ) str = "Error: No copyed row";
     else if (i <0 ) str = "Error: No selected row";
     else str ="OK";
     ST(str);
}
bool MainWindow::ask(QString str,QString title)
{
    int id;
    id = QMessageBox::question(this,title,str);
    if (id ==QMessageBox::Yes) 
        return true;
    return false;
}

void MainWindow::msg(QString str,QString title)
{
     QMessageBox::information(this,title,str);
}
void MainWindow::fileText(QString file,QString title)
{
    LFileDate fd;
    QString str;
    str = fd.getText(file);
     QMessageBox::information(this,title,str);
}
