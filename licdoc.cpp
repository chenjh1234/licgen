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
 QString LicDoc::rootDir()
{
   QString s;
   s = getenv(LIC_ROOT_PATH);
   if (s == "")  s = ".";
   return s;
}
 
QString LicDoc::docPath()
{
   QString s;
   s = rootDir() + "/" + LIC_FILE_PATH;
   return s;
}
