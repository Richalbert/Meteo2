#pragma once
#include <string>
#include <vector>

class Tendance {
public:
	Tendance(std::string fichier);
	void ajoutValeur(double val);
	int8_t getTendance();
private:
	std::vector<double> hist;
};

