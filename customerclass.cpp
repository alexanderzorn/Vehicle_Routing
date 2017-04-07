//
//  customerclass.cpp
//  
//
//  Created by Alexander Zorn on 08.03.17.
//
//

#include "customerclass.hpp"
#include <iostream>

/*
    Initialisierung eines neuen Kunden
 */
void Customer::set(int x, int y, int z){
    xpos=x;//Position in X-Richtung
    ypos=y;//"- "  in Y-Richtung
    demand=z;//Nachfragemenge
}
/*
    Setzen der Nachfrage eines Kunden
 */
void Customer::setdemand(int x){
    demand = x;
}

/*
    Ausgabe aller Daten eines Kunden auf der Konsole
 */
void Customer::print(){
    std::cout <<getxpos()<<" "<<getypos()<<" "<<getdemand()<<" "<<getneighbora()<<" "<<getneighborb()<<std::endl;
    
}
