Tema este reprezentata de o serie de taskuri cu lucru asupra imaginilor. Aceste operatii sunt folosite pentru a manipula imaginea in diverse moduri, cum ar fi: inversarea pe orizontala, rotirea la stanga, decuparea ei, extinderea ei, copierea si lipire, aplicarea filtrelor. Pentru a implementa aceste operatii, am folosit structuri de date, cum ar fi matricea pixelilor si structuri pentru pastrarea informatiilor despre imagine.
De asemenea tema contine un procesor de imagini interactiv, care permite utilizatorului sa execute operatii de procesare a imaginilor direct din interfata grafica a programului. Aceste comenzi sunt : 
    ->"e": asigura o inchidere curata si fara pierderi de memorie a programului dupa ce utilizatorul a terminat de folosit aplicatia;
    ->"l": citeste o imagine dintr-un fisier BMP specificat de utilizator si o salveaza intr-o structura de date pentru imagini;
    ->"s": salveaza o imagine specificata de utilizator intr-un fisier BMP si citeste indicele imaginii de salvat idx si calea catre fisierul BMP, ulterior utilizand functia write_to_bmp pentru a scrie datele imaginii in fisierul specificat;
    ->"ah": inverseaza imaginea pe orizontala;
    ->"ar": roteste imaginea la stanga;
    ->"ac": decupeaza o imagine;
    ->"ae": extinde o imagine adaugand o margine colorata;
    ->"ap": lipseste o imagine pe alta;
    ->"cf": creeaza un filtru prin citestirea dimensiunea acestuia "flt_size" si matricea de valori pentru filtru, apoi il adauga in vectorul de filtre.
    ->"af": aplica un filtru unei imagini.
    ->"df": citeste indicele filtrului de sters "idx_flt" si il elimina folosind functia "delete_filter", astfel rolul ei este de a sterge un filtru;
    ->"di": sterge o imagine.
La final am uitilzat Valgrind pentru a gasi și remedia erorile de memorie si scurgerile de memorie din Heap pe care le-am avut. 