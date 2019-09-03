/*
 *	Meteo/src/Horodata.h
 *
 * 	declaration de la classe
 *
 * 	modif : rajout de l'attribut m_last_file_cretaion pour le calcul
 * 	de l intervalle de temps etcreer un nouveau fichier
 *
 */

//#pragma once

#include "bme280_defs.h"
#include <ctime>


class Horodata {

	private :

		struct bme280_data m_bme;
		time_t m_now;
		static time_t m_last_file_creation;

	public:
		//constructor
		Horodata(double p,double t,double h);
		//destructor
		~Horodata();

		//setter
		void setNow(time_t now);
		void setPressure(double p);
		void setTemperature(double t);
		void setHumidity(double h);
			
		//getter 
		time_t getTime();

		void display() const ;
		void write_data_to_file(double delay);		// en secondes

};
	

