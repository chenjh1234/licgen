#include "licdoc.h"
 

LicDoc::LicDoc()
{
    init();
}
LicDoc::~LicDoc()
{

}
void  LicDoc::init()
{ 
    m_fileOut = "";
    m_filename = LICFILE_DEFAULT;
}
int  LicDoc::setFile(QString file)
{
    m_filename = file;
    return licFile.readFile(file);
}
QString LicDoc::docPath()
{
    return "./";
}
