/****************************************************
*	Author: Kacper Domański
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology 
*	Faculty of Electronics and Information Technology
****************************************************/

Problem - t7 - Segments groups


Program input
 - -h | --help : Prints useful information about program.
 - -u | --usage : Prints message with possible input parameters.
 - -f | --file[filename] : Input file with information about segments.
 - -o | --output[filename]  : Output file to be created with program results.
 - --generate-tests [numberOfSegments] : Forces program to generate its own tests in given number.
 - --algorithm [WS | DS]" << " : Specifies which arrange algorithm to use (default WS).
 - --arrangment [NO | SH]" << " : Specifies which sorting heuristic to use (default NO).


Dane pliku wejściowego 
 - Każda linia zentuje jeden ocinek z 4 parametrami, które odpowiadają współrzędnym 2 punktów: startPoint.x, startPoint.y, endPoint.x, endPoint.y
 - Wartości są liczbami całkowitymi z przedziału 0-1000 i są rozdzielone spacją
 - Linia zaczynająca się od znaku '#' będzie traktowana jak komentarz


Rozwiązanie problemu

W programie zastosowano dwa algorytmy wyszukiwania - Deep Search [DS] i Wide(Broad) Search [WS] oraz metodę porządkowania segmentów - Spatial Hash [SH]. Dla porównania program można uruchomić też bez wcześniejszego porządkowania [NO].
Po podaniu parametrów początkowych programu następuje wczytanie danych z pliku/wygenerowanie danych losowych. Następnie w wypadku wybrania przyporządkowania [SH] obszar roboczy dzielony jest na 100 podobszarów w postaci kratki. 
Każdy odcinek zostaje przyporządkowany do obszaru przez który przechodzi lub w nim się znajduje, w przypadku wybrania braku przyporządkowania [NO] wszystkie segmenty zostają wrzucone do jednego kontenera. Następnie w zależności od 
wybranego algorytmu zostaje wykonane wyszukiwanie [DS] lub [WS]. W pierwszym przypadku funkcja wyszukująca działa rekurencyjnie dla każdego segmentu sprawdza wszystkie z którymi znajduje się w tym samym kontenerze, jeżeli ocinek 
nie ma koloru (nie należy do żadnej grupy przecinających się odcinków) zostaje pokolorowany i zostaje wykonana rekurencyjna funkcja dla tego odcinka. W przeciwnym przypadku jeżeli kolor odcinków jest inny to dodajemy parę kolorów do listy 
pasujących do siebie kolorów formatując parę w sposób <mniejszyKolor, większyKolor> co pozwoli nam potem na szybkie jej "rozczytanie". W przypadku [WS] procedura jest niemalże identyczna z tą tylko różnicą, że funkcja nie jest wywoływana rekurencyjnie. 

