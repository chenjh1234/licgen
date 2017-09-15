#ifndef LIC_DOC_H
#define LIC_DOC_H

 
#include <iostream>
#include <QString>
#include "LLicFile.h"
#include "LLicEncrypt.h"
using namespace std;
#define ORG_NAME "LICGEN"
#define APP_NAME "licgen"
#define APP_VERSION "1.001"
#define APP_DATE " 2017.10.1 "
//
#define CMD_SHOWPDF "evince "

#define MAX_PACKAGES 10
#define PACKAGE_KEYS 7
#define PKEY_ITEM_IDX 7-1

#define PACKAGE_DEFINE {(char*)PACKAGENAME,(char*)PVERSION,\
                        (char*)PTYPE,(char*)PLIMIT,(char*)PSTARTDATE,\
                        (char*)PENDDATE,(char*)PKEY,\
                        NULL}
class LicDoc 
{
public:
    LicDoc();
    ~LicDoc();
    void init();
    int setFile(QString file);

    QString m_filename;
    QString m_fileOut;
    QString m_licHome;
    QString docPath();

    LLicFile licFile;
    int _numPackage;
   
};
#endif

