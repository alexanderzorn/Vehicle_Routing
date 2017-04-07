//
//  customerclass.hpp
//  
//
//  Created by Alexander Zorn on 08.03.17.
//
//

#ifndef customerclass_hpp
#define customerclass_hpp

#include <stdio.h>
/*
    Definition der Klasse Customer
 */
class Customer {
private:
    int xpos, ypos, demand, neighbora, neighborb;//X-Postion , Y-Position , previuos Neighbor, next Neighbor
public:
    void set (int,int, int);//initialiere einen Kunden
    void setdemand(int);//Setze die Nachfrage des Kunden
    void setneighbora(int neighboranumber){neighbora=neighboranumber;};//Setze einen Vorgänger (identifiziert anhand der Nummer im Vektor
    void setneighborb(int neighborbnumber){neighborb=neighborbnumber;};//Setze einen Nachfolger "-"
    void print();//gebe den Kunden mit seinen Daten auf der Konsole aus
    inline int getxpos() const {return xpos;};//gebe die X-Position zurück
    int getypos() const {return ypos;};//gebe Y-Position zurück
    int getdemand() const {return demand;};//gebe Nachfrage zurück
    int getneighbora() const {return neighbora;};//gebe den Vorgänger zurück
    int getneighborb() const {return neighborb;};//gebe den Nachfolger zurück
};

#endif /* customerclass_hpp */
