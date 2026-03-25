# Lab1: Prekidi u ugradbenim sustavima

## Opis programa

Cilj programa je prikazati rad s prekidima različitih prioriteta.
Za to je korišten timer kao prekid najvišeg prioriteta, 3 tipkala od kojih svaki ima svoj prioritet te senzora udaljenosti najnižeg prioriteta.


### Glavna petlja loop()

U glavnoj loop() petlji se konstantno redom provjerava da li se dogodio prekid timera, potom da li su pritisnuta neka tipkala te na poslijetku mjeri udaljenost senzorom i aktivira led lampice prema potrebi.


### onTimer()

Prekidna funkcija koja se poziva timerom. Mjenja timerFlag u TRUE što govori programu u loop() petlji da pozove handleTimer() funkciju


### handleTimer()

Poziva se iz loop() petlje ako je timerFlag TRUE.
Pali ledTimer lampicu na 500ms te resetira timerFlag u FALSE.


### INT1()

Funkcija koja se poziva prekidom izazvanim pritiskom gumba 1.
Poziva funkciju handleBtnPress() i prosljeđuje indeks lampice 1.


### INT2()

Funkcija koja se poziva prekidom izazvanim pritiskom gumba 2.
Poziva funkciju handleBtnPress() i prosljeđuje indeks lampice 2.


### INT3()

Funkcija koja se poziva prekidom izazvanim pritiskom gumba 3.
Poziva funkciju handleBtnPress() i prosljeđuje indeks lampice 3.


### handleBtnPress()

Funkcija koja se poziva iz prekida povezanih sa gumbima.
Radi debounce gumba te postavlja btnFlag pritisnutog gumba u TRUE kako bi se lapica tog gumba upalila.
Kao parametar prima indeks gumba za koji treba upaliti lampicu.


### handleButtons()

Funkcija koja se poziva u loop() funkciji te pali lampice sa postavljenim flagom.
Prolazi kroz btnFlags niz i mjenja stanje lapice ako je flag postavljen u TRUE.


### distance()

Funkcija koja očitava udaljenost korištenjem senzora za udaljenost.
Poziva se u loop() funkciji te očitava udaljenost do prepreke.
Vraća vrijednost udaljenosti.


## Rezultati logičkog analizatora

![Signals](https://github.com/GvidoMas/RUS--Maskalan/blob/main/Lab1/img/signals.png)

D0 - Tipkalo 1;
D1 - Tipkalo 2;
D2 - Tipkalo 3;
D3 - ledTimer;
D4 - ledBtn1;
D5 - ledBtn2;
D6 - ledBtn3;
D7 - distanceLed

Iz logičkog analizatora možeo vidjeti da se timerLed pali svakih 500ms što ukazuje na to da timer imma najviši prioritet jer se izvršava bez obzira na ostale prekide.
Također možemo vidjeti da se led lampice povezane sa tipkalimma pale nakon što završi izvršavanje handleTimer() funkcije jer imaju mmanji proritet.
Možemo vidjeti i da su prioriteti tipkala postojani jer ako pritisneo tipkalo 2 pa tipkalo 1 nakon, upaliti će se prvo ledBtn1 a nakon nje ledBtn2.


## UML dijagram

![UL](https://github.com/GvidoMas/RUS--Maskalan/blob/main/Lab1/img/UML.png)


