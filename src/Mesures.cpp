/*
 * 	Meteo/src/Mesures.cpp
 */

#include "Mesures.h"
#include <QDebug>

#include <iostream>

#include "Horodata.h"
#include "Zambretti.h"

#include <QString>

#define TEMP_EXT 25.0
#define ALTITUDE 146.0

//constructor
Mesures::Mesures() {

	// ouverture du fichier meteo.data, et
	// calcul d une tendance par defaut, et 
	// affichage correspondant
	// initTendance -> a travers la creation de l objet Tendance
	// certainement une instance d un objet static
	// static Tendance tendance;

	initSensor(&dev);
    comp_data.temperature = 16.4;
    
    //init des valeurs meteo par defaut via un fichier de valeurs 
	this->tend = new Tendance("/var/meteo/meteo.data");	//ouvre et stocke les valeurs dans vecteur
}

void Mesures::refresh() {
	//qDebug() << "Called the C++ slot";
	struct bme280_data *data = &comp_data;

	// prise de mesure
    	refreshSensor(&dev, &comp_data);

	// correction de la pression
	Zambretti zambretti; 
 	data->pressure = zambretti.p_to_p0(data->pressure,data->temperature,ALTITUDE);	
	zambretti.setPression(data->pressure);
	

	// sauvegarde dans fichier
	Horodata bme280(data->pressure,data->temperature,data->humidity);
	bme280.write_data_to_file(3600);

	this->tend->ajoutValeur(data->pressure);		//ajout dans les vecteurs de taille constante
																//  et mise a jour de la pente=tendance

	//zambretti_algo
	
	int8_t l_tend = this->tend->getTendance();
	char lettre = zambretti.zambretti_algo(l_tend*45.0,SUMMER);
	m_icone = QString::fromStdString(zambretti.getIcon(lettre,l_tend));
	m_description = QString::fromStdString(zambretti.getDescription(lettre,l_tend));


	
	//this->tend->CalculPente()
	//this->tendance = this->tend->getTrend();					//calcule la tendance et affichage

	// ajout de la nouvelle donne dans le vecteur
	// suppression de la plus ancienne
	// calcule de la nouvelle tendance
	// affichage correspondant
}



//getter
float  Mesures::temp() const {		
	return comp_data.temperature;
}

float Mesures::pression() const{
    	return comp_data.pressure;
}

float Mesures::humidite() const {
    	return comp_data.humidity;
}

double Mesures::pente() const {
	return 45.0 * this->tend->getTendance();
}

QString Mesures::icone() const {
    	return m_icone;
}

QString Mesures::description() const {
    	return m_description;
}
