/*
 *      Meteo/src/Mesures.h
 */

#pragma once
#include <QObject>
#include <QString>
#include "capteurs.h"
#include "Tendance.h"

class Mesures : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float   temp     READ temp     NOTIFY tempChanged)
    Q_PROPERTY(float   pression READ pression NOTIFY pressionChanged)
    Q_PROPERTY(float   humidite READ humidite NOTIFY humiditeChanged)
    Q_PROPERTY(double  pente    READ pente    NOTIFY penteChanged)
    Q_PROPERTY(QString icone    READ icone    NOTIFY iconeChanged)
    Q_PROPERTY(QString description    READ description NOTIFY descriptionChanged)
    
private:
    struct bme280_dev  dev;            /*le device*/
    struct bme280_data comp_data;        /*les metriques */
    Tendance *tend;                /*envoi des metriques pour calcul de la tendance*/
    QString m_tendance;
    QString m_icone;
    QString m_description;
    
signals:
    void tempChanged();
    void pressionChanged();
    void humiditeChanged();
    void penteChanged();
    void descriptionChanged();
    void iconeChanged();
    
public slots:
    void refresh();
    
public:
    Mesures();
    float temp() const;
    float pression() const;
    float humidite() const;
    double pente() const;
    QString icone() const;
    QString description() const;
};
