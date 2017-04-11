Kompilieren:
Folgenden Befehl habe ich zum Kompilieren des Programms benutzt:
 g++ -Wall -pedantic -std=c++11 *.cpp

Daraufhin lässt sich das Programm starten mit ./a.out DATEINAME

In diesem Ordner befindet sich ein Dokument namens Laufzeitanalyse.pdf und ein Ordner ProjektAnalysisKit (mit dessen Dateien ich die PDF erstellt habe). Das PDF Dokument soll einen Eindruck der Laufzeit bei den gegebenen Beispieldateien vermitteln.
Des Weiteren befinden sich im Ordner ProjektAnalyseKit der Ordner A-VRP mit einem Grossteil der Testdateien.

Des Weiteren schreibt das Programm (mithilfe der Funktion visualprint()) die Datei visualprint.svg welche die errechneten Touren grafisch sichtbar macht.

Alle Ergebnisse aus dem Ordner ProjektAnalysisKit/A-VRP befinden sich (mit Zeiten) in Ergebnisse.txt (erstellt mithilfe von testall.sh)
