#ifndef LIC_DOC_H
#define LIC_DOC_H

 
#include <iostream>
#include <QString>
#define ORG_NAME "LICGEN"
#define APP_NAME "licgen"
#define APP_VERSION "1.001"
#define APP_DATE " 2017.10.1 "
using namespace std;
 
class LicDoc 
{
public:
    LicDoc();
    ~LicDoc();
    void init();
    QString m_filename;
   
};
#endif

