#include "licapp.h"
LicApp *theApp;

LicApp::LicApp( int & argc, char ** argv ):QApplication(argc,argv)
{
    init();
}
LicApp::~LicApp()
{

}
void  LicApp::init()
{
    theApp = this;

}
