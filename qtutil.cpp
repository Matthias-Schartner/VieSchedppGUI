#include "qtutil.h"


QList<std::tuple<int, double, double, int>> qtUtil::pointingVectors2Lists(const std::vector<VieVS::PointingVector> &pvs)
{
    QList<std::tuple<int, double, double, int>> l;

    for(const VieVS::PointingVector &p : pvs){
        l.append({p.getTime(), p.getAz(), p.getEl(), p.getSrcid()});
    }

    return l;
}

QList<qtUtil::ObsData> qtUtil::getObsData(unsigned long staid, const std::vector<VieVS::Scan> &scans)
{
    QList<ObsData> list;
    for(const VieVS::Scan &scan: scans){
        auto oidx = scan.findIdxOfStationId(staid);
        if(oidx.is_initialized()){
            int idx = oidx.get();
            ObsData obs;
            obs.srcid = scan.getSourceId();
            obs.az = scan.getPointingVector(idx).getAz();
            obs.el = scan.getPointingVector(idx).getEl();
            obs.startTime = scan.getPointingVector(idx).getTime();
            obs.endTime = scan.getPointingVector(idx,VieVS::Timestamp::end).getTime();
            obs.nsta = scan.getNSta();
            list.append(obs);
        }
    }
    return list;
}

void qtUtil::worldMap(ChartView *worldmap)
{
    QChart *worldChart = new QChart();
    worldChart->setAcceptHoverEvents(true);

    QFile coastF(":/plotting/coast.txt");
    if (coastF.open(QIODevice::ReadOnly)){
        QTextStream in(&coastF);

        int c = 0;
        while (!in.atEnd()){

            QLineSeries *coast = new QLineSeries(worldChart);
            coast->setColor(Qt::gray);
            coast->setName("coast");

            while(!in.atEnd()){
                QString line = in.readLine();

                if(line == "NaN,NaN"){
                    ++c;
                    worldChart->addSeries(coast);
                    break;
                }
                QStringList split = line.split(",",QString::SplitBehavior::SkipEmptyParts);
                QString lat = split[0];
                QString lon = split[1];
                coast->append(lon.toDouble(),lat.toDouble());
            }
        }
        coastF.close();
    }

    worldChart->createDefaultAxes();
    worldChart->setAcceptHoverEvents(true);
    worldChart->legend()->hide();
    worldChart->axisX()->setRange(-180,180);
    worldChart->axisY()->setRange(-90,90);
    worldChart->setAnimationOptions(QChart::NoAnimation);

    worldmap->setChart(worldChart);
    worldmap->setMinMax(-180,180,-90,90);
    worldmap->setRenderHint(QPainter::Antialiasing);
    worldmap->setFrameStyle(QFrame::Raised | QFrame::StyledPanel);
    worldmap->setBackgroundBrush(QBrush(Qt::white));
    worldmap->setMouseTracking(true);

}

std::pair<double, double> qtUtil::radec2xy(double ra, double de)
{
    ra -= pi;
    double hn = qSqrt( 1 + qCos(de)*qCos(ra/2) );

    double x = (2 * qSqrt(2) *qCos(de) *qSin(ra/2) ) / hn;
    double y = (qSqrt(2) *qSin(de) ) / hn;

    return {x,y};
}

void qtUtil::skyMap(ChartView *skymap)
{
    QChart *skyChart = new QChart();

    for(int ra = 0; ra<=360; ra+=60){
        QLineSeries *ral = new QLineSeries(skyChart);
        ral->setColor(Qt::gray);
        double lambda = ra * deg2rad;

        for(int de = -90; de<=90; de+=5){
            double phi = de * deg2rad;

            auto xy = qtUtil::radec2xy(lambda, phi);

            ral->append(xy.first, xy.second);
        }
        skyChart->addSeries(ral);
    }

    for(int de = -60; de<=60; de+=30){
        QLineSeries *del = new QLineSeries(skyChart);
        del->setColor(Qt::gray);
        double phi = de * deg2rad;

        for(int ra = 0; ra<=360; ra+=5){
            double lambda = ra * deg2rad;
            auto xy = qtUtil::radec2xy(lambda, phi);

            del->append(xy.first, xy.second);
        }
        skyChart->addSeries(del);
    }

    QLineSeries *ecliptic = new QLineSeries(skyChart);
    ecliptic->setPen(QPen(QBrush(Qt::darkGreen),3,Qt::DashLine));
    double e = qDegreesToRadians(23.4);
    for(int i=-180; i<=180; i+=5){
        double l = qDegreesToRadians((double)i);
        double b = 0;
        double lambda = qAtan2(qSin(l)*qCos(e) - qTan(b)*qSin(e),qCos(l)) + pi;
//        lambda-=M_PI;
        double phi = qAsin(qSin(b)*qCos(e) + qCos(b)*qSin(e)*qSin(l));

        auto xy = qtUtil::radec2xy(lambda,phi);

        ecliptic->append(xy.first,xy.second);
    }

    skyChart->addSeries(ecliptic);

    skyChart->createDefaultAxes();
    skyChart->setAcceptHoverEvents(true);
    skyChart->legend()->hide();
    skyChart->axisX()->setRange(-2.85,2.85);
    skyChart->axisY()->setRange(-1.45,1.45);
    skyChart->axisX()->hide();
    skyChart->axisY()->hide();
    skyChart->setAnimationOptions(QChart::NoAnimation);

    skymap->setChart(skyChart);
    skymap->setMinMax(-2.85,2.85,-1.45,1.45);
    skymap->setRenderHint(QPainter::Antialiasing);
    skymap->setFrameStyle(QFrame::Raised | QFrame::StyledPanel);
    skymap->setBackgroundBrush(QBrush(Qt::white));
    skymap->setMouseTracking(true);

}
