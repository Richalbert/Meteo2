/*
 *    Meteo/src/Horodata.cpp
 *
 *    definition de classe
 */

#include <iostream>
#include <fstream>
#include <sstream>    //stringstream
#include <cstring>    //strcpy
#include <ctime>
#include <iomanip>      // std::put_time
#include "Horodata.h"

time_t Horodata::m_last_file_creation = 0;

//constructor
Horodata::Horodata(double pressure, double temperature, double humidity) {
    this->m_now = time(NULL);        //get current date
    this->m_bme.pressure = pressure;
    this->m_bme.temperature = temperature;
    this->m_bme.humidity = humidity;
}


//destructor
Horodata::~Horodata() {}


//getter
time_t Horodata::getTime() {
    return this->m_now;
}


//setter
void Horodata::setNow (time_t now) {
    this->m_now = now;
}

void Horodata::setPressure(double pression){
    this->m_bme.pressure = pression;
}

void Horodata::setTemperature(double temperature){
    this->m_bme.temperature = temperature;
}

void Horodata::setHumidity(double humidite) {
    this->m_bme.humidity = humidite;
}

void Horodata::display() const {
    struct tm *ltm = localtime(&m_now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    int min = ltm->tm_min;
    int sec = ltm->tm_sec;

    std::cout<<year<<"-"<<month<<"-"<<day<<"-"<<hour<<"-"<<min<<"-"<<sec<<" "<<std::endl;
    std::cout<<m_bme.pressure<<" "<<m_bme.temperature<<" "<<m_bme.humidity<<" "<<std::endl;
}


/**
 *
 * @param delay in seconds
 */
void Horodata::write_data_to_file(double delay) {

    // moment ou on doit créer un autre fichier de stockage    
    if ( difftime(this->m_now, this->m_last_file_creation) > delay ) {
        this->m_last_file_creation = this->m_now;
    }

    struct tm *ltm = localtime(&(this->m_last_file_creation));

    // conversion de la date en string
    std::stringstream ss;
    //ss << std::put_time(ltm,"%Y%m%d-%H%M%S");
    ss << std::put_time(ltm,"%Y%m%d-%H%M");
    
    
    // creation du nom de fichier
    std::string path_str("/var/meteo/");
    path_str += ss.str();
    path_str += ".data";


    // écriture dans le fichier
    std::ofstream ofs(path_str, std::ios::app);

    
    // debug print
    // std::cout << "fichier : " << path_str << std::endl;
    
    
    if (ofs.is_open()) {  
        ofs << m_now << " "
            << m_bme.pressure << " " 
            << m_bme.temperature << " "  
            << m_bme.humidity << std::endl
            ;

        ofs.close();
    } else {
         std::cout <<"File opening is fail.";
    }
}

