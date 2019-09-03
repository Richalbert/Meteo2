#include "Tendance.h"
#include <fstream>
#include <iostream>

Tendance::Tendance(std::string fichier) {
	std::ifstream ifs(fichier);
	std::string str;
	if (ifs.is_open()) {
		//std::cout << "------ Init de Tendance" << std::endl;
		while(getline(ifs,str)) {
			std::string::size_type sz;
			long temps = std::stol(str,&sz);
			long press = std::stol(str.substr(sz));
			this->ajoutValeur((double)press);
		}
		//std::cout << "------ fin d'init de Tendance" << std::endl;
		ifs.close();
	}
}

void Tendance::ajoutValeur(double val) {
	//std::cout << "Ajout de : " << val << std::endl;
	this->hist.push_back(val);
	if (this->hist.size()>1800)
		this->hist.erase(this->hist.begin());
}

int8_t Tendance::getTendance() {
	double diff = this->hist.end() - this->hist.begin();
	if (diff < -25) return -1;
	if (diff > 25)  return 1;
	return 0;
}
