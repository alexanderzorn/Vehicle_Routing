//
//  graphprinting.cpp
//  
//
//  Created by Alexander Zorn on 10.03.17.
//
//
#include <stdio.h>
#include <fstream>
#include "graphclass.hpp"

/*
    Ausgabe des gesamten Graphen in der Konsole
 */
void Graph::print(){
    for(int n=0;n<size;n++){
        std::cout<<n<<": ";
        getcustomer(n).print();
    }
}

/*
    Ausgabe des Vektors tours in dem die Anfangs und Endknoten der jeweiligen zu fahrenden Touren verzeichnet sind.
 */
void Graph::printtours(){
    for(size_t n=0; 2*n+1<tours.size(); n++){
        std::cout<<tours[2*n]<<"  "<<tours[2*n+1]<<std::endl;//Ausgabe den Anfangs und Endknoten jeweils in einer Zeile.
    }
}

/*
    Ausgabe aller Touren/Routen mit den jeweiligen Knoten auf dem Weg auf der Konsole
 */
void Graph::printalltours(){
    int actualcustomer=-1;
    for(size_t n=0; 2*n+1<tours.size(); n++){
        std::cout<<"ROUTE "<<n+1<<" "<<tours[2*n]+1;
        actualcustomer= nodes[tours[2*n]].getneighborb();
        while(actualcustomer!=0){
            std::cout<<" "<<actualcustomer+1;
            actualcustomer= nodes[actualcustomer].getneighborb();
        }//Jede Tour beginnt bei dem in tours verzeichneten ersten Knoten und gibt solange die nachbarn dieser Knoten aus bis der nächste Nachbar (actualcustomer) wieder das Depot ist. 
        std::cout<<std::endl;
    }
}

/*
    Graphische Visualisierung des Graphen in einer SVG Datei visualprint.svg im aktuellen Ordner.
 */

void Graph::visualprint(){
    std::fstream f;
    int maximumsize=100;
    for(int n=0;n<size; n++ ){
        if(maximumsize<nodes[n].getxpos())maximumsize=nodes[n].getxpos();
        if(maximumsize<nodes[n].getypos())maximumsize=nodes[n].getypos();
    }
    f.open("visualprint.svg", std::ios_base::out | std::ios_base::trunc );
    f <<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<std::endl;
    f<<"<svg xmlns=\"http://www.w3.org/2000/svg\""<<std::endl;
    f<<"xmlns:xlink=\"http://www.w3.org/1999/xlink\""<<std::endl;
    f<<"version=\"1.1\" baseProfile=\"full\""<<std::endl;
    f<<"width=\""<<maximumsize+100<<"px\" height=\""<<maximumsize+100<<"px\""<<std::endl;
    f<<"viewBox=\"-10 -10 "<<maximumsize+100<<" "<<maximumsize+100<<"\">"<<std::endl;
    f<<"<title>Titel der Datei</title>"<<std::endl;
    f<<"<desc>Visualprint</desc>"<<std::endl;
    for(int nodecounter=0; nodecounter<size; nodecounter++ ){
        f<<"<circle cx=\""<<nodes[nodecounter].getxpos()<<"\" cy=\""<<nodes[nodecounter].getypos()<<"\" r=\"1\" />"<<std::endl;
        f<<"<text x=\""<<nodes[nodecounter].getxpos()<<"\" y=\""<<nodes[nodecounter].getypos()<<"\" fill=\"red\" style=\"font-size:5px\">"<<nodecounter+1<<"</text>"<<std::endl;
    }
    for (int nodecounter=1; nodecounter<size;nodecounter++){
        f<<"<line x1=\""<<nodes[nodecounter].getxpos()<<"\" y1=\""<<nodes[nodecounter].getypos()<<"\" x2=\""<<nodes[nodes[nodecounter].getneighborb()].getxpos()<<"\" y2=\""<<nodes[nodes[nodecounter].getneighborb()].getypos()<<"\" style=\"stroke:rgb(0,0,0);stroke-width=1\"  />"<<std::endl;
    }
    for (size_t tourcounter=0;tourcounter<tours.size();tourcounter+=2){
        f<<"<line x1=\""<<nodes[tours[tourcounter]].getxpos()<<"\" y1=\""<<nodes[tours[tourcounter]].getypos()<<"\" x2=\""<<nodes[0].getxpos()<<"\" y2=\""<<nodes[0].getypos()<<"\" style=\"stroke:rgb(0,0,0);stroke-width=1\"  />"<<std::endl;
    }
    f<<"</svg>";
    f.close();

}
