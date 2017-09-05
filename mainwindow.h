#ifndef FLOWMAINWINDOW_H
#define FLOWMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
//class QPlainTextEdit;
QT_END_NAMESPACE
#include <QSplitter>
#include <QTabWidget>
#include <QDockWidget>
#include <QTextBrowser>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include "licapp.h"

#include "iostream"
//#include <QtTreePropertyBrowser>
//#include "flowapplication.h"
#include "venderwin.h"
#include "packagewin.h"

using namespace std;
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
public: 
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
   
private: 

 
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
 
    QString strippedName(const QString &fullFileName);
    void setTitle();

   // QPlainTextEdit *textEdit;
   // QSplitter *split;
   // QTabWidget *tabWidget;
    QDockWidget *venderDockWidget;
    
    QWidget *venderManager,*packageManager;
 
  
    VenderWin *venderWin;
    PackageWin *packageWin;
  
    QMenu *fileMenu;   
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;   
    QAction *exitAct;
 
  
    QAction *aboutAct;
    QAction *helpAct;
public:
    QProcess hrun;
  

public slots:
   
   // void slotTextFlow();
    void  slotHelp();
    void  slotTextFlow();
  
    void resizeEvent ( QResizeEvent * event );
public:
     
private:
    
    int m_w,m_h;
    //bool isflowMode();
 
};
//! [0]

#endif
