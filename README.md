# Meteo

Projet de station météorologique avec:
- **Raspberry Pi**
- Capteur **BME280** (humidité, pression, température)

 
## Fonctions

Création d'une interface Qt avec récupération et affichage des données du capteur puis calcul d'une prévision météorologique à quatre heures.


## Installation

    sudo apt-get install qtbase5-dev qtdeclarative5-dev


## Compilation et execution sur processeur ARM

    cd Meteo 
    mkdir build && cd build && cmake .. && make && ./src/meteo
 
