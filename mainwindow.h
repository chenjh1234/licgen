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

#define ST(x) statusBar()->showMessage(x);

#include "licapp.h"
#include "iostream"
#include "venderwin.h"
#include "packagewin.h"

using namespace std;
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
public: 
    MainWindow();
    bool ask(QString str,QString title="Please conform:");
    void msg(QString str,QString title="Information:");
    void fileText(QString str,QString title="Information:");


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    void openOut();
    bool save();
    bool saveAs();
    void about();

    void addRow();
    void rmRow();
    void copyRow();
    void pasteRow();
   
private: 
    int  setFile(QString file);

 
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
 
    bool saveFile(const QString &fileName);
 
    QString strippedName(const QString &fullFileName);
    void setTitle();

    QDockWidget *venderDockWidget;
    QWidget *venderManager,*packageManager;
    PackageWin *packageWin;
    VenderWin *venderWin;
  
    QMenu *fileMenu;   
    QMenu *helpMenu;
    QMenu *editMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *helpToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *openOutAct;
    QAction *saveAct;
    QAction *saveAsAct;   
    QAction *exitAct;

      QAction *addRowAct;
      QAction *rmRowAct;
      QAction *copyRowAct;
      QAction *pasteRowAct;
 
  
    QAction *aboutAct;
    QAction *helpAct;
public:
    QProcess hrun;
  

public slots:
   
   // void slotTextFlow();
    void  slotHelp();
  
    void resizeEvent ( QResizeEvent * event );
public:
     
private:
    
    int m_w,m_h;
    //bool isflowMode();
 
};
//! [0]

#endif
