//
//  graphclass.cpp
//  
//
//  Created by Alexander Zorn on 08.03.17.
//
//
#include "graphclass.hpp"

/*
    Befülle den Graphen mit Informationen wie den Customer vektor und dem disttype. Quelle: Kommandozeilenparameter
 */
void Graph::initializegraph(std::string const filename){
    Customer newone;
    int number, xpos, ypos, demandval, securitycounter=0;
    std::fstream file;
    std::string type, fillera=" ", fillerb;
    
    file.open(filename, std::ios::in);
    /* 
        Gehe den ersten Teil der Datei durch und lese die Variablen wie CAPACITY oder DISTTYPE aus bis zur Zeile NODE_COORD_SECTION
        Falls nach 1000 Zeilen (securitycounter) immer noch nicht die NODE_COORD_SECTION gefunden wurde muss es sich um eine Fehlerhafte Datei handeln.
     */
    while(fillera.compare(0,18,"NODE_COORD_SECTION")!=0 && securitycounter<1000){
        file>>fillera>>fillerb;
        securitycounter++;
        if (fillerb.compare(0,1,":")==0){
            file>>fillerb;
        }
        //Falls durch die  COMMENT Section die Reihenfolge von fillera und fillerb vertauscht wurde wird das durch folgende if Abfrage abgefangen (nach der COMMENT Section kommt immer die Type Section)
        if(fillerb.compare(0,5,"TYPE:")==0){
            file>>fillerb;
        }
        
        if(fillera.compare(0,16,"EDGE_WEIGHT_TYPE")==0)//Überprüfung ob die aktuelle Zeile den Distanz type enthält(wenn ja lese ihn aus )
        {   
           
            if(fillerb.compare("EUC_2D")==0)disttype= EUC_2D;
            else if(fillerb.compare("CEIL_2D")==0)disttype= CEIL_2D;
            else if(fillerb.compare("MAN_2D")==0)disttype= MAN_2D;
            else {
                std::cout <<"Check the EDGE_WEIGHT_TYPE please."<< std::endl;//Überprüfen ob ein gültiger Distanztyp angegeben wurde
                std::terminate();
            }
        }
        else if(fillera.compare(0,8,"CAPACITY")==0)//Überprüfung ob die aktuelle Zeile die Kapazität des Paketwagens enthält enthält(wenn ja lese ihn aus )
        {
            capacity = stoi(fillerb, nullptr);
            if (capacity<=0){
                std::cout<<"Please check the Capacity.";//Überprüfen ob ein gültige Kapazität eingegeben wurde angegeben wurde
                std::terminate();
            }
        }
            
        else if(fillera.compare(0,9,"DIMENSION")==0)//Überprüfung ob die aktuelle Zeile die Anzahl der Kunden enthält enthält enthält(wenn ja lese sie aus )
        {
            size = stoi(fillerb, nullptr);
            if (size<=0){
                std::cout<<"Please check the Dimension";//Überprüfen ob eine gültige Dimension angegeben wurde
                std::terminate();
            }
        else if (file.eof()){

            std::cout<<"Please look for the file Format"<<std::endl;
            std::terminate();
        }
            /*
             
             //Hier lässt sich das Programm bei Bedarf unterbrechen wenn der Graph mehr als 10000 Knoten enthält da die sehr lange zum rechnen bräuchte
            if(size>10000)//terminates when there are more then 10000nodes.
            {
                std::cout<<"too large Dimension. Not computable in valuable time";
                std::terminate();
            }
             */
        }
    }
    if (securitycounter==1000){
        std::cout<<"Please look for the file Format";
        std::terminate();
    }
    number= stoi(fillerb);
    file>>xpos>>ypos;
    bool demand  = false;//Gibt an ob das Programm sich bereits in der DEMAND_SECTION des files befindet und liest die Datei demenstprechend aus
    while(!file.eof()){
        if(fillera.compare(0,14,"DEMAND_SECTION")==0)//Überprufen der aktuellen Zeile auf den String DEMAND_SECTION
        {
            demand = true;
            number=xpos;
            demandval=ypos;
	    fillera=std::to_string(number);
        }
        else if(fillera.compare(0,13,"DEPOT_SECTION")==0){
            break;
        }
        if (!demand)//Falls sich das Programm noch in der NODE_COORD_SECTION befindet so liest es die X-position und Y-Position aus
        {
            newone.set(xpos,ypos,0);
            nodes.push_back(newone);
            if(number<0||number>size||xpos<0||ypos<0)//Abfangen von Fehlern beim auslesen
            {
                std::cout<<"Please check node Number "<<number<<"in DEPOT_SECTION.";
                std::terminate();
            }
        }
        else//sonst müssen wir uns bereits in DEMAND_SECTION befinden also wird die Nachfrage des Kunden ausgelesen und gespeichert
        {
            number =stoi(fillera,nullptr);
            nodes[number-1].setdemand(demandval);
            if (number<0||number>size||demandval<0||demandval>capacity){//Abfangen von Fehlern beim auslesen
                std::cout<<"Please check node Number "<<number<<"in DEMAND_SECTION.";
                std::terminate();
            }
        }
        if(!demand) file>>fillera>>xpos>>ypos;
        else file>>fillera>>demandval;
    }
    file.close();
    size_t sizeinsizetype = size;
    if (nodes.size()!=sizeinsizetype)//Falls die angegebene DIMENSION und die tatsächliche Vektorlänge von nodes nicht übereinstimmen beendet sich das Programm
    {
        std::cout<<"Please check the number list. It size does not match with the listed DIMENSION.";
        std::terminate();
    }
}

void Graph::simplehelp(int i)//Dient simpletour als Funktion die von jedem Thread mit einem bestimmten i ausgeführt wird.
{
    nodes[i].setneighbora(i-1);
    nodes[i].setneighborb(i+1);
}

void Graph::simpletour()//Erstellt eine einfache Tour auf den Knoten der Form 1,2,3,...,n,1
{
    static const int number_of_threads = size-2;
    std::vector <std::thread> t;
    nodes[0].setneighbora(size-1);
    nodes[0].setneighborb(1);
    nodes[size-1].setneighbora(size-2);
    nodes[size-1].setneighborb(0);

    //Starte die verschiedenen Theards, in jedem Thread werden die Nachbarn für einen Knoten festgelegt
    for (int i = 0; i < number_of_threads; ++i) { 
        t.push_back(std::thread(&Graph::simplehelp, this, i+1)); 
    }

    //Warte bis alle fertig sind.
    for (int i = 0; i < number_of_threads; i++) {
        t[i].join();
    }
}
double Graph::distance(int n,int m)//gibt den Abstand zwischen zwei Kunden zurück (abhängug von der ausgelesenen disttype)
{
    double distx = abs(nodes[n].getxpos()-nodes[m].getxpos());
    double disty = abs(nodes[n].getypos()-nodes[m].getypos());
    if(disttype==EUC_2D)return sqrt(distx*distx+disty*disty);
    else if(disttype==CEIL_2D) return ceil(sqrt(distx*distx+disty*disty));
    else return distx+disty;
}

bool disjunkt(int a, int x, int y, int z)//entscheidet ob die vier int Werte (Räpresentanten für Knoten) disjunkt sind. Die wird bei der folgenden Funktion twoopt() benutzt um zu entscheiden ob sich 
{
    if(a!=x && a!=y && a!=z && x!=y && x!=z && y!=z)return true;

    else return false;
}
/*
    Verbessert die aktuelle Tour anhand der 2-OPT Methode. Sind werden immer zwei Knoten k und i betrachtet und ihre Nachfolger in der aktuellen Tour l, m . z und p sind zwischenspeicher und dienen dazu die gesamte Tour zu verändern wenn zwei Kanten ausgetauscht werden müssen. Wenn Zwei Kanten ausgetausch werden wird durch i=size , k=-1 das gesamte Prozedere wieder von vorne begangen, bis einmal jedes Knotenpaar überprüft wurde und bei dieser Prüfung nicht ein Tausch von nöten war.
 */
 
void Graph::twoopt(){
    int l,m,z,p;
    bool changed = false;
    for (int k=0; k<size; k++){
        changed=false;
        for(int i=k; i<size; i++){
            l=nodes[k].getneighborb();
            m=nodes[i].getneighborb();
            if(disjunkt(k,l,i,m) && (distance(k,i)+distance(l,m))<(distance(k,l)+distance(i,m))){//Abfrage ob die vier betrachteten Knoten vier verschiedene Knoten sind und die Tour durch tauschen der Kanten verbessert werden kann.
                nodes[k].setneighborb(i);
                nodes[i].setneighborb(nodes[i].getneighbora());
                nodes[i].setneighbora(k);
                z=nodes[i].getneighborb();
                while(z!=l){
                    p=nodes[z].getneighbora();
                    nodes[z].setneighbora(nodes[z].getneighborb());
                    nodes[z].setneighborb(p);
                    z=p;
                }
                nodes[z].setneighbora(nodes[z].getneighborb());
                nodes[z].setneighborb(m);
                nodes[m].setneighbora(l);
                changed =true;
            }//Wenn ja wird hier s.o der Austausch und die Anpassung aller anderen Knoten durchgeführt
        }
         if(changed)k=-1;
    }
}

/*
    Die folgende Funktion gib die Länge der Tour als double zurück gibt es mehrere Touren in dem Graphen so wir die gewhält die als ersten Knoten den Nachfolger des Depots benutzt
 */
double Graph::tourdistance(){
    int n=nodes[0].getneighborb();
    int m;
    double sum=distance(0, n);
    while(n!=0){
        m=nodes[n].getneighborb();
        sum+=distance(n,m);
        n=m;
    }
    return sum;
}
/*
    Aufteilen der Tour in mehrere kleine durch durchgehen der gesamt Tour Aufaddierung der Kunden Nachfrage. kurz vor der überschreitung des Fassungsvermögen CAPACITY der ZUstellwagens wird eine neue Tour erstellt und der Graph angepasst
 */
void Graph::tourpartition(){
    int k=nodes[0].getneighborb();//Number of node
    int z, nextdmnd = nodes[nodes[0].getneighborb()].getdemand();//Demand from the next node
    int capsum=0;
    tours.push_back(nodes[0].getneighborb());
    while (k!=0){
        while(capsum+nextdmnd<=capacity&&k!=0){
            capsum+=nextdmnd;
            k= nodes[k].getneighborb();
            nextdmnd= nodes[k].getdemand();
        }
        capsum=0;
        z=nodes[k].getneighbora();
        nodes[z].setneighborb(0);
        nodes[k].setneighbora(0);
        tours.push_back(z);
        tours.push_back(k);
    }
}
/*
    Die Funltion lässt sich mit der oben definierten tourdistance() die Länge jeder Tour zurückgeben und addiert diese Werte auf, welche dann OBJECTIVE ergeben
 */
double Graph::totaldistance(){
    double sum=0;
    for(size_t n=0; 2*n+1<tours.size(); n++){
        nodes[0].setneighborb(tours[2*n]);
        nodes[0].setneighbora(tours[2*n+1]);
        sum+=tourdistance();
    }
    return sum;
}
