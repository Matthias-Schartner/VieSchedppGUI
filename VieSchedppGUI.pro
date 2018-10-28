 # 
 #  VieSched++ Very Long Baseline Interferometry (VLBI) Scheduling Software
 #  Copyright (C) 2018  Matthias Schartner
 #
 #  This program is free software: you can redistribute it and/or modify
 #  it under the terms of the GNU General Public License as published by
 #  the Free Software Foundation, either version 3 of the License, or
 #  (at your option) any later version.
 #
 #  This program is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU General Public License for more details.
 #  
 #  You should have received a copy of the GNU General Public License
 #  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #

#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T11:36:13
#
#-------------------------------------------------
CONFIG += c++14

QMAKE_CXXFLAGS+= -fopenmp
LIBS += -fopenmp

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VieSchedppGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH += /home/mschartn/boost_1_64_0/
#LIBS += "-LC:/home/mschartn/boost_1_64_0//stage/lib/"
INCLUDEPATH += C:/MinGW/include
LIBS += ../IAU_SOFA/Release/libsofa_c.a

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        chartview.cpp \
        callout.cpp \
        multischededitdialogint.cpp \
        multischededitdialogdouble.cpp \
        multischededitdialogdatetime.cpp \
        addgroupdialog.cpp \
        stationparametersdialog.cpp \
        sourceparametersdialog.cpp \
        baselineparametersdialog.cpp \
        settingsloadwindow.cpp \
        addbanddialog.cpp \
        savetosettingsdialog.cpp \
        mytextbrowser.cpp \
        ../VieSchedpp/AbstractAntenna.cpp \
        ../VieSchedpp/Antenna_AzEl.cpp \
        ../VieSchedpp/Antenna_HaDc.cpp \
        ../VieSchedpp/Antenna_XYew.cpp \
        ../VieSchedpp/AstronomicalParameters.cpp \
        ../VieSchedpp/Baseline.cpp \
        ../VieSchedpp/AbstractCableWrap.cpp \
        ../VieSchedpp/CableWrap_AzEl.cpp \
        ../VieSchedpp/CableWrap_HaDc.cpp \
        ../VieSchedpp/CableWrap_XYew.cpp \
        ../VieSchedpp/CalibratorBlock.cpp \
        ../VieSchedpp/Equipment.cpp \
        ../VieSchedpp/Equipment_elDependent.cpp \
        ../VieSchedpp/AbstractFlux.cpp \
        ../VieSchedpp/Flux_B.cpp \
        ../VieSchedpp/Flux_M.cpp \
        ../VieSchedpp/HighImpactScanDescriptor.cpp \
        ../VieSchedpp/AbstractHorizonMask.cpp \
        ../VieSchedpp/HorizonMask_line.cpp \
        ../VieSchedpp/HorizonMask_step.cpp \
        ../VieSchedpp/Initializer.cpp \
        ../VieSchedpp/LogParser.cpp \
        ../VieSchedpp/LookupTable.cpp \
        ../VieSchedpp/MultiScheduling.cpp \
        ../VieSchedpp/Network.cpp \
        ../VieSchedpp/Observation.cpp \
        ../VieSchedpp/ObservationMode.cpp \
        ../VieSchedpp/Output.cpp \
        ../VieSchedpp/ParameterGroup.cpp \
        ../VieSchedpp/ParameterSettings.cpp \
        ../VieSchedpp/ParameterSetup.cpp \
        ../VieSchedpp/PointingVector.cpp \
        ../VieSchedpp/Position.cpp \
        ../VieSchedpp/Scan.cpp \
        ../VieSchedpp/ScanTimes.cpp \
        ../VieSchedpp/Scheduler.cpp \
        ../VieSchedpp/Skd.cpp \
        ../VieSchedpp/SkdCatalogReader.cpp \
        ../VieSchedpp/SkdParser.cpp \
        ../VieSchedpp/SkyCoverage.cpp \
        ../VieSchedpp/Source.cpp \
        ../VieSchedpp/Station.cpp \
        ../VieSchedpp/StationEndposition.cpp \
        ../VieSchedpp/Subcon.cpp \
        ../VieSchedpp/TimeSystem.cpp \
        ../VieSchedpp/Vex.cpp \
        ../VieSchedpp/VieVS_NamedObject.cpp \
        ../VieSchedpp/VieVS_Object.cpp \
        ../VieSchedpp/WeightFactors.cpp \
        ../VieSchedpp/util.cpp \
        ../VieSchedpp/Flags.cpp \
        textfileviewer.cpp \
        vieschedpp_analyser.cpp \
        qtutil.cpp \
        skedcataloginfo.cpp \
    multicolumnsortfilterproxymodel.cpp \
    obsmodedialog.cpp

HEADERS += \
        mainwindow.h \
        chartview.h \
        callout.h \
        multischededitdialogint.h \
        multischededitdialogdouble.h \
        multischededitdialogdatetime.h \
        addgroupdialog.h \
        stationparametersdialog.h \
        sourceparametersdialog.h \
        baselineparametersdialog.h \
        settingsloadwindow.h \
        addbanddialog.h \
        savetosettingsdialog.h \
        mytextbrowser.h \
        ../VieSchedpp/AbstractAntenna.h \
        ../VieSchedpp/Antenna_AzEl.h \
        ../VieSchedpp/Antenna_HaDc.h \
        ../VieSchedpp/Antenna_XYew.h \
        ../VieSchedpp/AstronomicalParameters.h \
        ../VieSchedpp/Baseline.h \
        ../VieSchedpp/AbstractCableWrap.h \
        ../VieSchedpp/CableWrap_AzEl.h \
        ../VieSchedpp/CableWrap_HaDc.h \
        ../VieSchedpp/CableWrap_XYew.h \
        ../VieSchedpp/CalibratorBlock.h \
        ../VieSchedpp/Constants.h \
        ../VieSchedpp/Equipment.h \
        ../VieSchedpp/Equipment_elDependent.h \
        ../VieSchedpp/AbstractFlux.h \
        ../VieSchedpp/Flux_B.h \
        ../VieSchedpp/Flux_M.h \
        ../VieSchedpp/HighImpactScanDescriptor.h \
        ../VieSchedpp/AbstractHorizonMask.h \
        ../VieSchedpp/HorizonMask_line.h \
        ../VieSchedpp/HorizonMask_step.h \
        ../VieSchedpp/Initializer.h \
        ../VieSchedpp/LogParser.h \
        ../VieSchedpp/LookupTable.h \
        ../VieSchedpp/MultiScheduling.h \
        ../VieSchedpp/Network.h \
        ../VieSchedpp/Observation.h \
        ../VieSchedpp/ObservationMode.h \
        ../VieSchedpp/Output.h \
        ../VieSchedpp/ParameterGroup.h \
        ../VieSchedpp/ParameterSettings.h \
        ../VieSchedpp/ParameterSetup.h \
        ../VieSchedpp/PointingVector.h \
        ../VieSchedpp/Position.h \
        ../VieSchedpp/Scan.h \
        ../VieSchedpp/ScanTimes.h \
        ../VieSchedpp/Scheduler.h \
        ../VieSchedpp/Skd.h \
        ../VieSchedpp/SkdCatalogReader.h \
        ../VieSchedpp/SkdParser.h \
        ../VieSchedpp/SkyCoverage.h \
        ../VieSchedpp/Source.h \
        ../VieSchedpp/Station.h \
        ../VieSchedpp/StationEndposition.h \
        ../VieSchedpp/Subcon.h \
        ../VieSchedpp/Subnetting.h \
        ../VieSchedpp/TimeSystem.h \
        ../VieSchedpp/Vex.h \
        ../VieSchedpp/VieVS_NamedObject.h \
        ../VieSchedpp/VieVS_Object.h \
        ../VieSchedpp/WeightFactors.h \
        ../VieSchedpp/sofa.h \
        ../VieSchedpp/sofam.h \
        ../VieSchedpp/util.h \
        ../VieSchedpp/Flags.h \
        textfileviewer.h \
        vieschedpp_analyser.h \
        qtutil.h \
        skedcataloginfo.h \
    multicolumnsortfilterproxymodel.h \
    obsmodedialog.h

FORMS += \
        mainwindow.ui \
        multischededitdialogint.ui \
        multischededitdialogdouble.ui \
        multischededitdialogdatetime.ui \
        addgroupdialog.ui \
        stationparametersdialog.ui \
        sourceparametersdialog.ui \
        baselineparametersdialog.ui \
        settingsloadwindow.ui \
        addbanddialog.ui \
        savetosettingsdialog.ui \
        textfileviewer.ui \
        vieschedpp_analyser.ui \
        skedcataloginfo.ui \
    obsmodedialog.ui

RESOURCES += \
        myresources.qrc

DISTFILES += \
        VLBI_Scheduler/libsofa_c.a \
        VLBI_Scheduler/CMakeLists.txt

#exists( $$PWD/.git) {
exists( .git) {
    GIT_COMMIT_HASH = $$system(git log -1 --format=%H)
}else{
    GIT_COMMIT_HASH = "unknown"
}

exists( ../VieSchedpp/.git){
    GIT_SCHEDULER_COMMIT_HASH = $$system(cd ../VieSchedpp; git log -1 --format=%H)
}else{
    GIT_SCHEDULER_COMMIT_HASH = "unknown"
}

message(VieSched++ GUI version $$GIT_COMMIT_HASH)
message(VieSched++ version $$GIT_SCHEDULER_COMMIT_HASH)

DEFINES += GIT_COMMIT_HASH=\\\"$$GIT_COMMIT_HASH\\\"
DEFINES += GIT_SCHEDULER_COMMIT_HASH=\\\"$$GIT_SCHEDULER_COMMIT_HASH\\\"
