/* 
 *  VieSched++ Very Long Baseline Interferometry (VLBI) Scheduling Software
 *  Copyright (C) 2018  Matthias Schartner
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "unknown"
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QListWidget>
#include <QWhatsThis>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDesktopServices>
#include <QDockWidget>
//#include <QTextBrowser>
#include <Utility/mytextbrowser.h>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QInputDialog>

#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QPolarChart>
#include <QtCharts/QAreaSeries>

#include "Utility/chartview.h"
#include "secondaryGUIs/multischededitdialogint.h"
#include "secondaryGUIs/multischededitdialogdouble.h"
#include "secondaryGUIs/multischededitdialogdatetime.h"
#include "Utility/callout.h"
#include "secondaryGUIs/addgroupdialog.h"
#include "Parameters/baselineparametersdialog.h"
#include "Parameters/stationparametersdialog.h"
#include "Parameters/sourceparametersdialog.h"
#include "secondaryGUIs/addbanddialog.h"
#include "secondaryGUIs/savetosettingsdialog.h"
#include "../VieSchedpp/VieSchedpp.h"
#include "secondaryGUIs/textfileviewer.h"
#include "secondaryGUIs/vieschedpp_analyser.h"
#include "../VieSchedpp/Input/SkdParser.h"
#include "Utility/qtutil.h"
#include "secondaryGUIs/skedcataloginfo.h"
#include "Utility/multicolumnsortfilterproxymodel.h"
#include "secondaryGUIs/obsmodedialog.h"
#include "Utility/statistics.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:    
    void closeEvent(QCloseEvent *event);

    QString writeXML();

    void loadXML(QString path);

    void readSettings();

    void on_actionMode_triggered();

    void on_actionWelcome_triggered();

    void on_actionGeneral_triggered();

    void on_actionStation_triggered();

    void on_actionSource_triggered();

    void on_actionBaseline_triggered();

    void on_actionRules_triggered();

    void on_actionMulti_Scheduling_triggered();

    void on_actionOutput_triggered();

    void on_actionSettings_triggered();

    void on_actionWeight_factors_triggered();

    void on_pushButton_browseAntenna_clicked();

    void on_pushButton_browseEquip_clicked();

    void on_pushButton_browsePosition_clicked();

    void on_pushButton_browseMask_clicked();

    void on_pushButton_browseSource_clicked();

    void on_pushButton_browseFlux_clicked();

    void on_pushButton_browsModes_clicked();

    void on_pushButton_browseFreq_clicked();

    void on_pushButton_browseTracks_clicked();

    void on_pushButton_browseLoif_clicked();

    void on_pushButton_browseRec_clicked();

    void on_pushButton_browseRx_clicked();

    void on_pushButton_browseHdpos_clicked();

    void on_treeView_allSelectedStations_clicked(const QModelIndex &index);

    void on_groupBox_modeSked_toggled(bool arg1);

    void on_groupBox_modeCustom_toggled(bool arg1);

    void on_lineEdit_allStationsFilter_textChanged(const QString &arg1);

    void on_treeView_allAvailabeStations_clicked(const QModelIndex &index);

    void on_actionInput_triggered();

    void on_doubleSpinBox_weightLowDecStart_valueChanged(double arg1);

    void on_doubleSpinBox_weightLowDecEnd_valueChanged(double arg1);

    void on_doubleSpinBox_weightLowElStart_valueChanged(double arg1);

    void on_doubleSpinBox_weightLowElEnd_valueChanged(double arg1);

    void on_spinBox_scanSequenceCadence_valueChanged(int arg1);

    void on_doubleSpinBox_calibratorLowElStart_valueChanged(double arg1);

    void on_doubleSpinBox_calibratorLowElEnd_valueChanged(double arg1);

    void on_doubleSpinBox_calibratorHighElStart_valueChanged(double arg1);

    void on_doubleSpinBox_calibratorHighElEnd_valueChanged(double arg1);

    void createMultiSchedTable();

    void createModesPolicyTable();

    void addModesPolicyTable(QString name);

    void createModesCustonBandTable();

    void addModesCustomTable(QString name, double freq, int nChannel);

    void deleteModesCustomLine(QString name);

    void on_actionWhat_is_this_triggered();

    void on_spinBox_fontSize_valueChanged(int arg1);

    void on_fontComboBox_font_currentFontChanged(const QFont &f);

    void on_treeView_allAvailabeStations_entered(const QModelIndex &index);

    void worldmap_hovered(QPointF point, bool state);

    void skymap_hovered(QPointF point, bool state);

    void on_pushButton_modeCustomAddBand_clicked();

    void on_treeView_allSelectedStations_entered(const QModelIndex &index);

    void on_actionSky_Coverage_triggered();

    void on_actionExit_triggered();

    void on_iconSizeSpinBox_valueChanged(int arg1);

    void on_treeWidget_2_itemChanged(QTreeWidgetItem *item, int column);

    void addGroupStation();

    void addGroupSource();

    void addGroupBaseline();

    void on_pushButton_stationParameter_clicked();

    void on_dateTimeEdit_sessionStart_dateTimeChanged(const QDateTime &dateTime);

    void on_doubleSpinBox_sessionDuration_valueChanged(double arg1);

    void on_DateTimeEdit_startParameterStation_dateTimeChanged(const QDateTime &dateTime);

    void on_DateTimeEdit_endParameterStation_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_3_clicked();

    void addSetup(QTreeWidget *targetTreeWidget, QDateTimeEdit *paraStart, QDateTimeEdit *paraEnd,
                  QComboBox *transition, QComboBox *member, QComboBox *parameter, VieVS::ParameterSetup &paraSetup,
                  QChartView *setupChartView, QComboBox *targetStationPlot);

    void on_pushButton_4_clicked();

    void deleteSetupSelection(VieVS::ParameterSetup &setup, QChartView *setupChartView, QComboBox *setupCB, QTreeWidget *setupTW);

    void on_treeWidget_setupStation_itemEntered(QTreeWidgetItem *item, int column);

    void prepareSetupPlot(QChartView *figure, QVBoxLayout *container);

    void drawSetupPlot(QChartView *cv, QComboBox *cb, QTreeWidget *tw);

    void setBackgroundColorOfChildrenWhite(QTreeWidgetItem *item);

    void on_comboBox_stationSettingMember_currentTextChanged(const QString &arg1);

    void on_ComboBox_parameterStation_currentTextChanged(const QString &arg1);

    void displayStationSetupParameterFromPlot(QPointF,bool);

    void displaySourceSetupParameterFromPlot(QPointF,bool);

    void displayBaselineSetupParameterFromPlot(QPointF,bool);

    void on_comboBox_setupStation_currentTextChanged(const QString &arg1);

    void on_pushButton_sourceParameter_clicked();

    void on_comboBox_setupSource_currentTextChanged(const QString &arg1);

    void on_treeWidget_setupSource_itemEntered(QTreeWidgetItem *item, int column);

    void on_pushButton_removeSetupSource_clicked();

    void on_pushButton_addSetupSource_clicked();

    void on_DateTimeEdit_startParameterSource_dateTimeChanged(const QDateTime &dateTime);

    void on_DateTimeEdit_endParameterSource_dateTimeChanged(const QDateTime &dateTime);

    void createBaselineModel();

    void on_pushButton__baselineParameter_clicked();

    void on_DateTimeEdit_startParameterBaseline_dateTimeChanged(const QDateTime &dateTime);

    void on_DateTimeEdit_endParameterBaseline_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_addSetupBaseline_clicked();

    void on_pushButton_removeSetupBaseline_clicked();

    void on_treeWidget_setupBaseline_itemEntered(QTreeWidgetItem *item, int column);

    void on_comboBox_setupBaseline_currentTextChanged(const QString &arg1);

    void setupStationWaitAddRow();

    void setupStationAxisBufferAddRow();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_treeView_allAvailabeSources_clicked(const QModelIndex &index);

    void on_treeView_allSelectedSources_clicked(const QModelIndex &index);

    void on_pushButton_13_clicked();

    void on_pushButton_15_clicked();

    void on_treeView_allAvailabeSources_entered(const QModelIndex &index);

    void on_treeView_allSelectedSources_entered(const QModelIndex &index);

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_actionNew_triggered();

    void on_comboBox_sourceSettingMember_currentTextChanged(const QString &arg1);

    void on_comboBox_baselineSettingMember_currentTextChanged(const QString &arg1);

    void on_ComboBox_parameterSource_currentTextChanged(const QString &arg1);

    void on_ComboBox_parameterBaseline_currentTextChanged(const QString &arg1);

    void on_pushButton_multiSchedAddSelected_clicked();

    void on_pushButton_25_clicked();

    QString on_actionSave_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_saveCatalogPathes_clicked();

    void on_pushButton_26_clicked();

    void changeDefaultSettings(QStringList path, QStringList value, QString name);

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void createDefaultParameterSettings();

    void on_pushButton_saveNetwork_clicked();

    void on_pushButton_loadNetwork_clicked();

    void on_pushButton_saveSourceList_clicked();

    void on_pushButton_loadSourceList_clicked();

    void on_pushButton_saveMode_clicked();

    void on_pushButton_loadMode_clicked();

    void clearGroup(bool sta, bool src, bool bl, QString name);

    void clearSetup(bool sta, bool src, bool bl);

    void splitterMoved();

    void on_pushButton_faqSearch_clicked();

    void on_actionFAQ_triggered();

    void on_actionRun_triggered();

    void processFinished();

    void networkSizeChanged();

    void sourceListChanged();

    void baselineListChanged();

    void on_comboBox_nThreads_currentTextChanged(const QString &arg1);

    void on_comboBox_jobSchedule_currentTextChanged(const QString &arg1);

    void on_actionsummary_triggered();

    void setupSkyCoverageTemplatePlot();

    void skyCoverageTemplate();

    void on_pushButton_skyCoverageTemplateRandom_clicked();

    void on_influenceTimeSpinBox_valueChanged(int arg1);

    void on_actionConditions_triggered();

    void on_pushButton_addCondition_clicked();

    void on_pushButton_removeCondition_clicked();

    void on_lineEdit_allStationsFilter_3_textChanged(const QString &arg1);

    void on_actionNetwork_triggered();

    void on_actionSource_List_triggered();

    void on_dateTimeEdit_sessionStart_dateChanged(const QDate &date);

    void on_spinBox_doy_valueChanged(int arg1);

    void on_pushButton_clicked();

    void markerWorldmap();

    void markerSkymap();

    void on_radioButton_imageSkymap_toggled(bool checked);

    void on_radioButton_imageWorldmap_toggled(bool checked);

    void on_checkBox_showEcliptic_clicked(bool checked);

    void baselineHovered(QPointF point ,bool flag);

    void on_treeView_allSelectedBaselines_entered(const QModelIndex &index);

    void on_checkBox_showBaselines_clicked(bool checked);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_parameterStation_edit_clicked();

    void on_pushButton_parameterSource_edit_clicked();

    void on_pushButton_parameterBaseline_edit_clicked();

    void on_spinBox_maxNumberOfIterations_valueChanged(int arg1);

    void on_pushButton_31_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_30_clicked();

    void on_experimentNameLineEdit_textChanged(const QString &arg1);

    void on_pushButton_41_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_addHighImpactAzEl_clicked();

    void on_pushButton_removeHighImpactAzEl_clicked();

    void on_actionFix_High_Impact_Scans_triggered();

    void on_pushButton_readLogFile_read_clicked();

    void on_pushButton_readSkdFile_read_clicked();

    void on_actionLog_parser_triggered();

    void on_actionSkd_Parser_triggered();

    void on_actionAbout_Qt_triggered();

    void on_comboBox_multiSched_maxNumber_currentIndexChanged(const QString &arg1);

    void on_comboBox_multiSched_seed_currentIndexChanged(const QString &arg1);

    void multi_sched_count_nsched();

    void on_pushButton_save_multiCore_clicked();

    void on_pushButton_sessionBrowse_clicked();

    void on_pushButton_sessionAnalyser_clicked();

    void on_comboBox_log_file_currentIndexChanged(const QString &arg1);

    void on_comboBox_log_console_currentIndexChanged(const QString &arg1);

    void on_pushButton_browseSource2_clicked();

    void on_pushButton_stations_clicked();

    void on_pushButton_reloadsources_clicked();

    void on_pushButton_reloadcatalogs_clicked();

    void on_actionOpen_triggered();

    void addSetup(QTreeWidget *tree, const boost::property_tree::ptree &ptree, QComboBox *cmember,
                  QComboBox *cpara, QDateTimeEdit *dte_start, QDateTimeEdit *dte_end, QComboBox *trans,
                  QPushButton *add);
    void gbps();

    void on_pushButton_modeCustomAddBAnd_clicked();

    void on_pushButton_browseExecutable_clicked();

    void on_pushButton_howAreSkedCatalogsLinked_clicked();

    void on_actionCurrent_Release_triggered();

    void on_actionAbout_triggered();

    void on_pushButton_2_clicked();

    void on_groupBox_modeAdvanced_toggled(bool arg1);

    void on_pushButton_startAdvancedMode_clicked();

    void changeObservingModeSelection(int idx);

    void on_pushButton_loadAdvancedMode_clicked();

    void on_pushButton_saveAdvancedMode_clicked();

    void on_pushButton_changeCurrentAdvancedMode_clicked();

    void on_pushButton_20_clicked();

    void on_checkBox_outputNGSFile_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString mainPath;
    boost::property_tree::ptree settings_;

    boost::optional<VieVS::ObservingMode> advancedObservingMode_;

    VieVS::ParameterSettings para;

    QStandardItemModel *allStationModel;
    QStandardItemModel *allSourceModel;
    MultiColumnSortFilterProxyModel *allStationProxyModel;
    MultiColumnSortFilterProxyModel *allSourceProxyModel;

    QStandardItemModel *selectedStationModel;
    QStandardItemModel *selectedSourceModel;
    QStandardItemModel *selectedBaselineModel;
    bool createBaselines;

    QStandardItemModel *allSourcePlusGroupModel;
    QStandardItemModel *allStationPlusGroupModel;
    QStandardItemModel *allBaselinePlusGroupModel;

    QStringListModel *allSkedModesModel;

    VieVS::SkdCatalogReader skdCatalogReader;

    ChartView *worldmap;
    ChartView *skymap;
    QChartView *setupStation;
    QChartView *setupSource;
    QChartView *setupBaseline;
    QChartView *skyCoverageTemplateView;
    bool plotSkyCoverageTemplate;

    QScatterSeries *availableStations;
    QScatterSeries *selectedStations;
    QScatterSeries *availableSources;
    QScatterSeries *selectedSources;

    Callout *worldMapCallout;
    Callout *skyMapCallout;
    Callout *stationSetupCallout;
    Callout *sourceSetupCallout;
    Callout *baselineSetupCallout;

    QVector<double> obsAz;
    QVector<double> obsEl;
    QVector<int> obsTime;

    QSignalMapper *deleteModeMapper;

    bool setupChanged;
    boost::property_tree::ptree setupStation_;
    boost::property_tree::ptree setupSource_;
    boost::property_tree::ptree setupBaseline_;
    VieVS::ParameterSetup setupStationTree;
    VieVS::ParameterSetup setupSourceTree;
    VieVS::ParameterSetup setupBaselineTree;

    std::map<std::string, std::vector<std::string>> groupSta;
    std::map<std::string, std::vector<std::string>> groupSrc;
    std::map<std::string, std::vector<std::string>> groupBl;

    std::map<std::string, VieVS::ParameterSettings::ParametersStations> paraSta;
    std::map<std::string, VieVS::ParameterSettings::ParametersSources> paraSrc;
    std::map<std::string, VieVS::ParameterSettings::ParametersBaselines> paraBl;

    Statistics *statistics;

    void readSkedCatalogs();

    void readStations();

    void readSources();

    void readAllSkedObsModes();

    void plotWorldMap();

    void plotSkyMap();

    void defaultParameters();

    bool eventFilter(QObject *watched, QEvent *event);

    void displayStationSetupMember(QString name);

    void displaySourceSetupMember(QString name);

    void displayBaselineSetupMember(QString name);

    void displayStationSetupParameter(QString name);

    void displaySourceSetupParameter(QString name);

    void displayBaselineSetupParameter(QString name);

    void displaySetupCallout(QPointF,bool);

    int plotParameter(QChart* targetChart, QTreeWidgetItem *item, int level, int plot, QString target, const std::map<std::string, std::vector<std::string> > &map);

    double interpolate( QVector<double> &xData, QVector<double> &yData, double x, bool extrapolate=false );

    void updateAdvancedObservingMode();

};

#endif // MAINWINDOW_H
