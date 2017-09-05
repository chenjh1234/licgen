#include <iostream>
#include "licapp.h"
#include "licdoc.h"
#include "mainwindow.h"
using namespace std;

int main (int argc, char *argv[])
{
    cout << "hello world" << endl;       
    QString qstr;
    LicApp  app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);
 
    LicDoc doc;
    app.m_doc =&doc;
     
    MainWindow mainWin;
 
    app.m_win = &mainWin;
    
    mainWin.show();
    return app.exec();
}

