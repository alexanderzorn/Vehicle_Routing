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
    
    /*
        Aufteilen der durch twoopt() verbesserten Tour in die einzelnen Fahrzeittouren
     */
    graph.tourpartition();
    
    //graph.print();
   // graph.printtours();
    
    
    /*
        Programmausgabe mit printalltours() welche alle zu fahrenden Routen auf der Konsole ausgibt
     */
    std::cout<<std::endl<<"OBJECTIVE:"<<graph.totaldistance()<<std::endl;
    graph.printalltours();
    //std::cout<<graph.size;//Used for the timeanalysis. for this feature this line has to be the only output of the algorithm
    graph.visualprint();//Nicht Teil des Eigentlichen Algorithmus. Nur für die Ausgabe in eine svg Datei zuständig.
    
    return 0;
}
