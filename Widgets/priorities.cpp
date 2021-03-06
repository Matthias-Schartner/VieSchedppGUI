#include "priorities.h"
#include "ui_priorities.h"

Priorities::Priorities(QStandardItemModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Priorities),
    model_{model}
{
    ui->setupUi(this);
    setup();

}

Priorities::~Priorities()
{
    delete ui;
}

boost::property_tree::ptree Priorities::toXML()
{
    auto *t = ui->treeWidget_params;

    boost::property_tree::ptree tree;
    int v = ui->horizontalSlider_recom->value();
    tree.add("priorities.fraction", v*10);
    tree.add("priorities.percentile",ui->doubleSpinBox_quantile->value());


    QTreeWidgetItem *itm_nobs = t->topLevelItem(0);
    auto *dsp_nobs = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_nobs,1));
    boost::property_tree::ptree t_nobs;
    t_nobs.add("variable", dsp_nobs->value());
    t_nobs.add("variable.<xmlattr>.name", itm_nobs->text(0).toStdString());
    tree.add_child("priorities.variable",t_nobs.get_child("variable"));



    QTreeWidgetItem *itm_eop = t->topLevelItem(1);
    for( int i = 0; i<itm_eop->childCount(); ++i){
        QTreeWidgetItem *itm = itm_eop->child(i);
        auto *dsp = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm,1));
        boost::property_tree::ptree t2;

        t2.add("variable", dsp->value());
        t2.add("variable.<xmlattr>.name", itm->text(0).toStdString());
        tree.add_child("priorities.variable",t2.get_child("variable"));
    }

    QTreeWidgetItem *itm_sta = t->topLevelItem(2);
    for( int i = 0; i<itm_sta->childCount(); ++i){
        QTreeWidgetItem *itm = itm_sta->child(i);
        auto *dsp = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm,1));
        boost::property_tree::ptree t2;

        t2.add("variable", dsp->value());
        t2.add("variable.<xmlattr>.name", itm->text(0).toStdString());
        tree.add_child("priorities.variable",t2.get_child("variable"));
    }

    return tree;
}

void Priorities::fromXML(const boost::property_tree::ptree &tree)
{
    int v = tree.get("priorities.fraction", 70);
    ui->horizontalSlider_recom->setValue(v/10);

    ui->doubleSpinBox_quantile->setValue(tree.get("priorities.percentile",0.75));


    auto *t = ui->treeWidget_params;

    for( const auto &any : tree){
        if(any.first != "variable"){
            continue;
        }
        QString name = QString::fromStdString(any.second.get("<xmlattr>.name",""));
        double val = QString::fromStdString(any.second.data()).toDouble();


        for(int tli = 0; tli<t->topLevelItemCount(); ++tli){
            QTreeWidgetItem *itm_tl = t->topLevelItem(tli);
            QDoubleSpinBox *dsp_tl = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_tl, 1));
            if(itm_tl->text(0) == name){
                dsp_tl->setValue(val);
                break;
            }else{
                for(int c = 0; c<itm_tl->childCount(); ++c){
                    QTreeWidgetItem *itm_c = itm_tl->child(c);
                    QDoubleSpinBox *dsp_c = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c, 1));
                    QString itm_name = itm_c->text(0);
                    if( itm_name == name){
                        dsp_c->setValue(val);
                        break;
                    }
                }
            }
        }
    }
    paintBars();

}

void Priorities::addStations(QStandardItem *)
{
    setup();
}

void Priorities::setup()
{
    ui->treeWidget_params->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    auto *t = ui->treeWidget_params;

    auto *sta = t->topLevelItem(2);
    qDeleteAll(sta->takeChildren());

    for( int i = 0; i<model_->rowCount(); ++i){
        QString name = model_->item(i,0)->text();
        QTreeWidgetItem *itm = new QTreeWidgetItem(QStringList() << name);
        itm->setIcon(0, QIcon(":/icons/icons/station.png"));
        sta->addChild(itm);
        sta->setIcon(0, QIcon(":/icons/icons/station_group.png"));
    }

    for(int tli = 0; tli<t->topLevelItemCount(); ++tli){
        QTreeWidgetItem *itm_tl = t->topLevelItem(tli);
        QDoubleSpinBox *a = new QDoubleSpinBox();
        a->setValue(1);
        a->setRange(0,100);
        a->setSingleStep(.25);
        t->setItemWidget(itm_tl, 1, a);
        if(tli == 0){
            connect(a, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Priorities::paintBars);
        }
        if(tli == 1){
            connect(a, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Priorities::averageEOP);
        }
        if(tli == 2){
            connect(a, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Priorities::averageSta);
        }

        QProgressBar *b = new QProgressBar();
        b->setOrientation(Qt::Horizontal);
        b->setRange(0,100);
        b->setTextVisible(true);
        t->setItemWidget(itm_tl, 2, b);

        for(int c=0; c<itm_tl->childCount(); ++c){
            QTreeWidgetItem *itm_c = itm_tl->child(c);
            QDoubleSpinBox *a = new QDoubleSpinBox();
            if(tli == 1){
                a->setValue(1./5.);
            }
            if(tli == 2){
                a->setValue(1./model_->rowCount());
            }
            a->setRange(0,100);
            a->setSingleStep(.25);
            t->setItemWidget(itm_c, 1, a);
            connect(a, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Priorities::paintBars);

            QProgressBar *b = new QProgressBar();
            b->setOrientation(Qt::Horizontal);
            b->setRange(0,100);
            b->setTextVisible(true);
            t->setItemWidget(itm_c, 2, b);
        }
    }
    t->expandAll();
    paintBars();
}

void Priorities::averageEOP()
{
    blockPaint = true;
    auto *t = ui->treeWidget_params;
    QTreeWidgetItem *itm = t->topLevelItem(1);
    double v = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm,1))->value();

    double total = 0;
    for(int i = 0; i<itm->childCount(); ++i){
        QTreeWidgetItem *itm_c = itm->child(i);
        total += qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1))->value();
    }

    for(int i = 0; i<itm->childCount(); ++i){
        QTreeWidgetItem *itm_c = itm->child(i);
        auto dsp = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1));
        if( total == 0){
            dsp->setValue(v/itm->childCount());
        } else{
            double v_c = dsp->value();
            v_c = v_c/total;
            dsp->setValue(v*v_c);
        }
    }
    blockPaint = false;
    paintBars();
}

void Priorities::averageSta()
{
    blockPaint = true;
    auto *t = ui->treeWidget_params;
    QTreeWidgetItem *itm = t->topLevelItem(2);
    double v = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm,1))->value();

    double total = 0;
    for(int i = 0; i<itm->childCount(); ++i){
        QTreeWidgetItem *itm_c = itm->child(i);
        total += qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1))->value();
    }

    for(int i = 0; i<itm->childCount(); ++i){
        QTreeWidgetItem *itm_c = itm->child(i);
        auto dsp = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1));
        if( total == 0){
            dsp->setValue(v/itm->childCount());
        } else{
            double v_c = dsp->value();
            v_c = v_c/total;
            dsp->setValue(v*v_c);
        }
    }
    blockPaint = false;
    paintBars();
}

void Priorities::paintBars()
{
    if(blockPaint){
        return;
    }

    auto *t = ui->treeWidget_params;
    double total = 0;

    QTreeWidgetItem *itm_nobs = t->topLevelItem(0);
    auto *dsp_nobs = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_nobs,1));
    double v_nobs = dsp_nobs->value();
    total += v_nobs;


    QTreeWidgetItem *itm_eop = t->topLevelItem(1);
    auto *dsp_eop = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_eop,1));
    double v_eop = 0;
    for(int c=0; c<itm_eop->childCount(); ++c){
        QTreeWidgetItem *itm_c = itm_eop->child(c);
        auto *itm2 = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1));
        double v = itm2->value();
        total+=v;
        v_eop+=v;
    }
    dsp_eop->setValue(v_eop);


    QTreeWidgetItem *itm_sta = t->topLevelItem(2);
    auto *dsp_sta = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_sta,1));
    double v_sta = 0;
    for(int c=0; c<itm_sta->childCount(); ++c){
        QTreeWidgetItem *itm_c = itm_sta->child(c);
        auto *itm2 = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1));
        double v = itm2->value();
        total+=v;
        v_sta+=v;
    }
    dsp_sta->setValue(v_sta);



    for(int i = 0; i<t->topLevelItemCount(); ++i){
        QTreeWidgetItem *itm_tli = t->topLevelItem(i);
        auto *dsp_tli = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_tli,1));
        double v = dsp_tli->value();

        double p = 0;
        if(total > 0){
            p = v/total*100;
        }
        qobject_cast<QProgressBar *>(t->itemWidget(itm_tli,2))->setValue(std::lround(p));
        qobject_cast<QProgressBar *>(t->itemWidget(itm_tli,2))->setFormat(QString("%1%").arg(p,0,'f',2));


        for(int j = 0; j<itm_tli->childCount(); ++j){
            QTreeWidgetItem *itm_c = itm_tli->child(j);
            auto *dsp_c = qobject_cast<QDoubleSpinBox *>(t->itemWidget(itm_c,1));
            double v_c = dsp_c->value();

            double p = 0;
            if(total > 0){
                p = v_c/total*100;
            }
            qobject_cast<QProgressBar *>(t->itemWidget(itm_c,2))->setValue(std::lround(p));
            qobject_cast<QProgressBar *>(t->itemWidget(itm_c,2))->setFormat(QString("%1%").arg(p,0,'f',2));
        }
    }

}
