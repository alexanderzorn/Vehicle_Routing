//
//  vrpintroduction.cpp
//  
//
//  Created by Alexander Zorn on 07.03.17.
//
//

#include "vrpintroduction.hpp"


int main (int argc, char* argv[]){
    /*
        Überprüfung ob genau ein Parameter mit übergeben wurde
     */
    if(argc!=2){
        std::cerr << "invalid parameter count" << std::endl;
        throw;
    }
    
    /*
        Initialisierung des Graphen:
        Auslesen der mit übergebenen Datei + Einpflegen der Informationen in den Graphen
     */
    
    Graph graph;
    graph.initializegraph(argv[1]);

    graph.simpletour();
    //std::cout<<std::endl<<"Länge Gesamttour"<<graph.tourdistance()<<std::endl;
    
    /*
        Wendet twoopt() auf den Graphen an.
     */
    graph.twoopt();
    //std::cout<<std::endl<<"Länge verbessterte Tour"<<graph.tourdistance()<<std::endl;//zeigt die Länge der Simpletour mit Verbesserung durch twoopt() auf
    
    /*
        Aufteilen der durch twoopt() verbesserten Tour in die einzelnen Fahrzeittouren
     */
    graph.tourpartition();
    
    //graph.print();
    //graph.printtours();
    //graph.worstdist();
    
    
    /*
        Programmausgabe mit printalltours() welche alle zu fahrenden Routen auf der Konsole ausgibt
     */
    std::cout<<std::endl<<"OBJECTIVE:"<<graph.totaldistance()<<std::endl;
    graph.printalltours();

    graph.visualprint();
    
    return 0;
}
