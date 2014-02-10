TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/mai.cpp \
    ../src/Data/Vrp_Paths.cpp \
    ../src/Data/File_tsp.cpp \
    ../src/Data/InterfaceEnum/Type.cpp \
    ../src/Data/InterfaceEnum/Node_coord_type.cpp \
    ../src/Data/InterfaceEnum/Edge_weight_type.cpp \
    ../src/Data/InterfaceEnum/Edge_weight_format.cpp \
    ../src/Data/InterfaceEnum/Edge_data_format.cpp \
    ../src/Data/InterfaceEnum/Display_data_type.cpp \
    ../src/Data/Edge/Matrix.cpp \
    ../src/Data/Edge/full_matrix.cpp \
    ../src/Data/Node/Node_coord_two_coords.cpp \
    ../src/Data/Node/Node_coord_factory.cpp

HEADERS += \
    ../src/Data/Wraper_read.h \
    ../src/Data/Vrp_Paths.h \
    ../src/Data/Result.h \
    ../src/Data/File_tsp.h \
    ../src/Data/Display_Data.h \
    ../src/Data/Adapter.h \
    ../src/cost.h \
    ../src/Data/InterfaceEnum/Type.h \
    ../src/Data/InterfaceEnum/Node_coord_type.h \
    ../src/Data/InterfaceEnum/Edge_weight_type.h \
    ../src/Data/InterfaceEnum/Edge_weight_format.h \
    ../src/Data/InterfaceEnum/Edge_data_format.h \
    ../src/Data/InterfaceEnum/Display_data_type.h \
    ../src/Data/Edge/upper_row.h \
    ../src/Data/Edge/Matrix.h \
    ../src/Data/Edge/lower_row.h \
    ../src/Data/Edge/lower_diag_row.h \
    ../src/Data/Edge/full_matrix.h \
    ../src/Data/Edge/Edge_read_headers.h \
    ../src/Data/Node/Node_coord_two_coords.h \
    ../src/Data/Node/Node_coord_factory.h \
    ../src/Data/Node/Node_coor_base.h


CONFIG += boost

CONFIG   += c++11


LIBS += -lboost_system -lboost_filesystem
