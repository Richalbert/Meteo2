/*
 *	Meteo/src/Zambretti.h
 *
 *	declaration de la classe 
 */


#include <string>
#include "Zambretti_defs.h"

class Zambretti {

	private:
		
		double m_pression;
		char m_lettre;
		double m_tendance;


	public:
	
		//constructor
		Zambretti() {
		}
		//destructor
		~Zambretti() {
		}

		//getter
		double getPression() const { return this->m_pression; }
		char   getLettre() const   { return this->m_lettre;   }
		double getTendance() const { return this->m_tendance; }

		//setter
		void setPression(double pression) { this->m_pression = pression; }
		void setLettre(char lettre) 	  { this->m_lettre = lettre;     }
		void setTendance(double tendance) { this->m_tendance = tendance; }


		char correction_ete(char letter);
		char correction_hiver(char letter);

		char p_to_letter_in_rising(double p);
		char p_to_letter_in_steady(double p);
		char p_to_letter_in_falling(double p);

		double p_to_p0(double p, double t, double h);
		char zambretti_algo(double laPente, LaSeasonEst laSeasonEst);
		std::string getDescription(char lettre, int8_t tend);
		std::string getIcon(char lettre, int8_t tend);
};
