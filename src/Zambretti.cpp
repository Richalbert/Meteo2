/*
 *	Meteo/src/Zambretti.cpp
 *	
 *	definition de la classe
 */

#include "Zambretti.h"
#include <string>
#include <math.h>
#include <iostream>


struct Forecast {
    char letter;
    std::string description;
};

struct Barometer {
    int number;
    char letter;
    std::string text;
    int pressure;
    std::string icon;
};

//struct Forecast forecast[26]={
//		{'A',"Settled Fine"},
//       		{'B',"Fine Weather"},
//        	{'C',"Becoming Fine"},
//	        {'D',"Fine Becoming Less Settled"},
//	        {'E',"Fine, Possibly showers"},
//	        {'F',"Fairly Fine, Improving"},
//	        {'G',"Fairly Fine, Possibly showers, early"},
//	        {'H',"Fairly Fine Showery Later"},
//	        {'I',"Showery Early, Improving"},
//	        {'J',"Changeable Mending"},
//	        {'K',"Fairly Fine , Showers likely"},
//	        {'L',"Rather Unsettled Clearing Later"},
//	        {'M',"Unsettled, Probably Improving"},
//	        {'N',"Showery Bright Intervals"},
//	        {'O',"Showery Becoming more unsettled"},
//	        {'P',"Changeable some rain"},
//	        {'Q',"Unsettled, short fine Intervals"},
//	        {'R',"Unsettled, Rain later"},
//	        {'S',"Unsettled, rain at times"},
//	        {'T',"Very Unsettled, Finer at times"},
//	        {'U',"Rain at times, worse later."},
//		{'V',"Rain at times, becoming very unsettled"},
//		{'W',"Rain at Frequent Intervals"},
//		{'X',"Very Unsettled, Rain"},
//		{'Y',"Stormy, possibly improving"},
//		{'Z',"Stormy, much rain"}
//};

struct Barometer falling[10] = { // tableau des previsions pour les pressions en baisse
        {0, '\0', "",                                       0,    ""}, // start at 1
        {1, 'A',  "Settled Fine",                           1050, "001-cloud"},
        {2, 'B',  "Fine Weather",                           1040, "001-cloud"},
        {3, 'D',  "Fine Becoming Less Settled",             1024, "001-cloud"},
        {4, 'H',  "Fairly Fine Showery Later",              1018, "001-cloud"},
        {5, 'O',  "Showery Becoming more unsettled",        1010, "001-cloud"},
        {6, 'R',  "Unsettled, Rain later",                  1004, "001-cloud"},
        {7, 'U',  "Rain at times, worse later.",            998, "001-cloud"},
        {8, 'V',  "Rain at times, becoming very unsettled", 991, "001-cloud"},
        {9, 'X',  "Very Unsettled, Rain",                   985, "001-cloud"}
};

struct Barometer steady[11] = { //tableau des previsions pour les pressions stable
        {0,  '\0', "",                             0, ""}, // start at 1
        {1,  'A',  "Settled Fine",                 1033, "001-cloud"},
        {2,  'B',  "Fine Weather",                 1023, "001-cloud"},
        {3,  'E',  "Fine, Possibly showers",       1014, "001-cloud"},
        {4,  'K',  "Fairly Fine , Showers likely", 1008, "001-cloud"},
        {5,  'N',  "Showery Bright Intervals",     1000, "001-cloud"},
        {6,  'P',  "Changeable some rain",         994, "001-cloud"},
        {7,  'S',  "Unsettled, rain at times",     989, "001-cloud"},
        {8,  'W',  "Rain at Frequent Intervals",   981, "001-cloud"},
        {9,  'X',  "Very Unsettled, Rain",         974, "001-cloud"},
        {10, 'Z',  "Stormy, much rain",            960, "001-cloud"}
};

struct Barometer rising[14] = { // tableau de previsions pour les pressions en hause
        {0,  '\0', "",                                     0, ""}, // start at 1
        {1,  'A',  "Settled Fine",                         1030, "039-sun"},
        {2,  'B',  "Fine Weather",                         1022, "038-cloudy-3"},
        {3,  'C',  "Becoming Fine",                        1012, "038-cloudy-3"},
        {4,  'F',  "Fairly Fine, Improving",               1007, "038-cloudy-3"},
        {5,  'G',  "Fairly Fine, Possibly showers, early", 1000, "034-cloudy-1"},
        {6,  'I',  "Showery Early, Improving",             995, "003-rainy"},
        {7,  'J',  "Changeable Mending",                   990, "001-cloud"},
        {8,  'L',  "Rather Unsettled Clearing Later",      984, "001-cloud"},
        {9,  'M',  "Unsettled, Probably Improving",        978, "011-cloudy"},
        {10, 'Q',  "Unsettled, short fine Intervals",      970, "013-storm-2"},
        {11, 'T',  "Very Unsettled, Finer at times",       965, "009-storm-1"},
        {12, 'Y',  "Stormy, possibly improving",           959, "008-storm"},
        {13, 'Z',  "Stormy, much rain",                    947, "013-storm"}
};


char Zambretti::zambretti_algo(double laPente, LaSeasonEst laSeasonEst) {

//    LaSeasonEst laSeasonEst = SUMMER;
    double seuilDePente = 0.5;
LaTendanceEst laTendanceEst = A_LA_HAUSSE;

    if (laPente > seuilDePente) {
        laTendanceEst = A_LA_HAUSSE;
    } else {
        if (laPente < -1 * seuilDePente) {
            laTendanceEst = A_LA_BAISSE;
        } else {
            laTendanceEst = STABLE;
        }
    }


    /*
     * A Winter falling generally results in a Z value lower by 1 unit compared with a Summer falling pressure.
     * Similarly a Summer rising, improves the prospects by 1 unit over a Winter rising.
     *
     */


    double p = Zambretti::getPression();

    char letter = '\0';


    switch (laTendanceEst) {

        case A_LA_HAUSSE:
            letter = p_to_letter_in_rising(p);
            //std::cout << "p_to_letter_in_rising(" << p << ") -> " << letter << std::endl;
            if (laSeasonEst == SUMMER) {
                // letter++ dans le tableau rising
                letter = correction_ete(letter);
                //std::cout << "correction_ete --> " << letter << std::endl;
            }
            break;

        case STABLE:
            letter = p_to_letter_in_steady(p);
            break;

        case A_LA_BAISSE:
            letter = p_to_letter_in_falling(p);
            if (laSeasonEst == WINTER) {
                // letter-- dans le tableau falling
                letter = correction_hiver(letter);
            }
            break;
    }

    //std::cout << "pression = " << p << "   -> lettre : " << letter << std::endl;

    return letter;
}


//entree: la lettre
//sortie: la lettre+1 dans le tableau rising
//-------------------------------------------
char Zambretti::correction_ete(char letter) {
    char z = '\0';

    // on trouve l'index de la lettre dans le tableau
    int j = 0;
    for (int i = 1; i < RISING_SIZE; i++) {
        j = i;
        if (letter == rising[i].letter) { break; }
    }

    // on applique la correction
    if (j < RISING_SIZE - 1) {
        z = rising[j + 1].letter;
    } else {
        z = rising[j].letter;
    }

    return z;
}


//entree: la lettre
//sortie: la lettre-1 dans le tableau falling
//-------------------------------------------
char Zambretti::correction_hiver(char letter) {
    char z = '\0';

    // on trouve la lettre dans le tableau
    int j = 0;
    for (int i = 1; i < RISING_SIZE; i++) {
        j = i;
        if (letter == falling[i].letter) { break; }
    }

    // on applique la correction
    if (j > 0) {
        z = rising[j - 1].letter;
    } else {
        z = rising[j].letter;
    }

    return z;
}


//entree: la pression
//sortie: la lettre correspondant dans le tableau rising
//-------------------------------------------------------
char Zambretti::p_to_letter_in_rising(double p) {
    char z = '\0';

    for (int i = 1; i < RISING_SIZE; i++) {
        z = rising[i].letter;
        if (p >= rising[i].pressure) { break; }
    }

    return z;
}


//entree: la pression
//sortie: la lettre correspondant dans le tableau steady
//-------------------------------------------------------
char Zambretti::p_to_letter_in_steady(double p) {
    char z = '\0';

    for (int i = 1; i < STEADY_SIZE; i++) {
        z = steady[i].letter;
        if (p >= steady[i].pressure) { break; }
    }

    return z;
}


//entree: la pression 
//sortie: la lettre correspondant dans le tableau falling
//-------------------------------------------------------
char Zambretti::p_to_letter_in_falling(double p) {
    char z = '\0';

    for (int i = 1; i < FALLING_SIZE; i++) {
        z = falling[i].letter;
        if (p >= falling[i].pressure) { break; }
    }

    return z;
}

std::string Zambretti::getDescription(char lettre, int8_t tend) {
	int i;
	switch(tend) {
		case -1:
			for(i=1;i<FALLING_SIZE;i++) {
				if (falling[i].letter == lettre)
					return falling[i].text;
			}
			break;
		case 1:
			for(i=1;i<RISING_SIZE;i++) {
				if (rising[i].letter == lettre)
					return rising[i].text;
			}
			break;
		default:
			for(i=1;i<STEADY_SIZE;i++) {
				if (steady[i].letter == lettre)
					return steady[i].text;
			}
			break;
	}
	return "";
}

std::string Zambretti::getIcon(char lettre, int8_t tend) {
	int i;
	switch(tend) {
		case -1:
			for(i=1;i<FALLING_SIZE;i++) {
				if (falling[i].letter == lettre)
					return falling[i].icon;
			}
			break;
		case 1:
			for( i=1;i<RISING_SIZE;i++) {
				if (rising[i].letter == lettre)
					return rising[i].icon;
			}
			break;
		default:
			for(i=1;i<STEADY_SIZE;i++) {
				if (steady[i].letter == lettre)
					return steady[i].icon;
			}
			break;
	}
	return "";
}

//-----------------------------------------------------
//entree: la pression 
//	  la temperature exterieure (pas celle du capteur) 
//	  l altitude (146 m) 
//sortie: la pression au niveau de la mer
//-----------------------------------------------------
//TEST: https://keisan.casio.com/exec/system/1224575267
//	H=1000m, P=980hPa, T=15°C => P0=1101.93hPa
//-----------------------------------------------------
double Zambretti::p_to_p0(double p, double t, double h) {

    double p0 = 0.0;

    p0 = p * pow(1 - ((0.0065 * h) / (t + 0.0065 * h + 273.15)), -5.257);

    return p0;
}




