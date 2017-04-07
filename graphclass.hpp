//
//  graphclass.hpp
//  
//
//  Created by Alexander Zorn on 08.03.17.
//
//

#ifndef graphclass_hpp
#define graphclass_hpp
#include "customerclass.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <math.h>
enum Disttype{
    EUC_2D,
    CEIL_2D,
    MAN_2D
};

class Graph {
private:
    std::vector<Customer> nodes;//Kundenliste (doppeltverkettet)
    std::vector<int> tours;//Speicherung der Anfangs- und Endknoten der Fahrzeugtouren
    Disttype disttype;//Art der Distanzrechnung
    int capacity;//Kapazität des Fahrzeuges
public:
    void initializegraph(std::string);//Befüllt den Graphen mit den nötigen Daten, welche er aus einer Datei bezieht deren Namen beim Programmaufruf mitgegeben wird.
    void simpletour();//Bildet eine Tour durch alle Kunden der Form 1,2,3,....,n,1
    double distance(int, int);//gibt die Distanz zwischen zwei Kunden zurück
    double tourdistance();//gibt die Länge einer einzelnen Fahrzeugtour zurück
    void tourpartition();//teilt die Gesamttour anhand der CAPACITY in einzelne Fahrzeutouren auf
    double totaldistance();//Errechnet OBJEVTIVE und gibt es in einem double zurück
    void twoopt();//verbessert die Simpletour mit der 2-OPT Methode
    void print();//Gibt den gesamten Graphen auf der Konsole aus
    void printtours();//gibt den Vektor tours auf der Konsole aus
    void printalltours();//Schreibt alle Fahrzeug Routen mit deren beinhaltenden Knoten auf die Konsole
    void visualprint();//Erzeut eine graohische Darstellung des Graphen in einer svg Datei
    inline Customer getcustomer(int n) {return nodes[n];};//gibt einen Kunden anhand seiner Nummer zurück wird bei print() Funktion genutzt um die einzelnen Kunden auf die Konsole zu schreiben
    int size;//Anzahl der Knoten/Kunden in nodes
};


#endif /* graphclass_hpp */
