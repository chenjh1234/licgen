 
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
    m_w= m_h = 800;
    
    venderDockWidget = new QDockWidget("venderView",this );
    addDockWidget(Qt::LeftDockWidgetArea, venderDockWidget);
     
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

  
    setTitle();
    return; 
  
}
void MainWindow::setTitle()
{
  
    QString str;
    str = "";
    str = str + APP_NAME + "-"+APP_VERSION +"-"+ __DATE__+"-";
    
    setWindowTitle(str);
    qDebug() << "title = " << str;

}
  

void MainWindow::slotTextFlow()
{
  
}
    
void MainWindow::closeEvent(QCloseEvent *event)

{
 
        writeSettings();
        event->accept();
    
}
 
void MainWindow::newFile()
{
    if (maybeSave()) 
    {
        // do somthing:
        setWindowModified(false);//new
        //setCurrentFile("");
    }
}

void MainWindow::open()
{
    #if 0
    int i;
    QString strt,strd,strf,str;
    strf = "*.flow";
    strt = "Open flow file";
    strd = theApp->m_doc->m_flowHome;
    if (strd.isEmpty()) 
    {
        strd = flowpath;
    }
    //qDebug() << "flowpath=" <<flowpath;
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,strt,strd,strf);
        if (!fileName.isEmpty())
            loadFile(fileName);

        QFileInfo fi(fileName);
        i = fileName.lastIndexOf(SLASH);
        str = fileName.left(i+1);
        flowpath = str;// remember the last set
        qDebug() << "flowpath=" <<flowpath << str;
    }
    setTitle();
    #endif
}

bool MainWindow::save()
{
    
    //return true;
    if (theApp->m_doc->m_filename.isEmpty()) 
    {
        return saveAs();
    } else 
    {
        return saveFile(theApp->m_doc->m_filename);
    }
}

bool MainWindow::saveAs()
{
    #if 0
    QString strt,strd,strf,str;
    strf = "*.flow";
    strt = "save flow file";
    strd = theApp->m_doc->m_flowHome;
    //qDebug() << "flowHome = " << strd;
    if (strd.isEmpty()) 
    {
        strd = flowpath;
    }

    QString fileName = QFileDialog::getSaveFileName(this,strt,strd,strf);
    if (fileName.isEmpty())
        return false;
    QFileInfo fi(fileName);

    QString ext = "flow";
    if (fi.suffix() != ext) 
    {
        fileName = fileName +"."+ext;
    }
    return saveFile(fileName);
    #endif
    return true;
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
    //open
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
 
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
 

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
    fileMenu->addAction(exitAct);
  
 
 
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
    //fileToolBar->addAction(textFlowAct);
 
    qDebug() << "create toolbar OK";
    return;
}

void MainWindow::createStatusBar()

{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(ORG_NAME, APP_NAME);
    QString str = settings.value("flow").toString();
    theApp->m_doc->m_filename =str; 
 
}
void MainWindow::writeSettings()
{
    QString str;
    QSettings settings(ORG_NAME,APP_NAME);
    str = QString("\"") + theApp->m_doc->m_filename + QString("\"");
    settings.setValue("flow", theApp->m_doc->m_filename);
}

bool MainWindow::maybeSave()
{ 
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
    return true;
}
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    // start:
  
    
}
 

bool MainWindow::saveFile(const QString &fileName)
{
     
    return true;
}
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
  
        
void MainWindow::resizeEvent ( QResizeEvent * event )
{
    int w,h;
    m_w = event->size().width();
    m_h = event->size().height();
    //flowMode();
}
void MainWindow::slotHelp()
{
    QString cmd,str;
    char *ch;
    cmd = "showpdf ";
    //cmd = cmd+ getDocDir()+ SLASH + "flowpad.pdf";
        //cmd = "ls";
    qDebug() << "cmd=" <<cmd;
    //hrun.start(cmd);

}
