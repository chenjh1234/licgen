
include (../../licInclude.config)
TEMPLATE = app
QT += widgets
QT += testlib
  
DESTDIR =$${LIC_BIN}
TARGET = licgen


#INCLUDEPATH += $${INCLUDE_BUS}

INCLUDEPATH +=./  \
	../../property\
	../../property/include\
	../../licbase

#LIBS +=  $${LIBS_BUS}

LIBS += \
	-L $${LIC_ROOT_PATH}/lib\
	-llicbase   -lproperty

 
# Input

RESOURCES  += \
	licgen.qrc
SOURCES += \
                licgen.cpp\
		tableview.cpp\
                tableitem.cpp\
                licapp.cpp\
                licdoc.cpp\
                venderwin.cpp\
                packagewin.cpp\
		mainwindow.cpp	

HEADERS +=  \
                tableitem.h\
		tableview.h\
                licapp.h\
                licdoc.h\
                venderwin.h\
                packagewin.h\
		mainwindow.h
		


