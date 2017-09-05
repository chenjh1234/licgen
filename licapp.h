#ifndef LIC_APP_H
#define LIC_APP_H

#include <QApplication>
#include "mainwindow.h"
#include "licdoc.h"
class LicApp;
class MainWindow;
#include <iostream>

#define DOC theApp->m_doc

using namespace std;
extern LicApp *theApp;
 
class LicApp :public QApplication  
{
public:
    LicApp( int & argc, char ** argv );
    ~LicApp();
    LicDoc *m_doc;
    MainWindow *m_win;


private:

    void init();

};
#endif
