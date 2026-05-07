# Izvještaj

## Različiti režimi mirovanja
#### Light sleep
Pauzira se rad CPU-a, no RAM i periferija ostaju aktivni. To omogućuje vrlo brzo buđenje te nema potrebe za ponovnim postavljanjem, spremanjem varijabli itd. što ga čini odličnim za česte i kratke pauze u radu.

#### Deep sleep
Dolazi do potpunog gašenja CPU-a, jedini dio koji ostane raditi je RTC. Dolazi do potpunog "reset-a" sustava, odnosno nakon buđenja je potrebno ponovno postavljanje (pokreće se setup()). Buđenje traje dulje nego kod light sleep-a.

#### Hibernation
Gasi se gotovo čitavi mikroupravljač što omogućuje minimalnu potrošnju energije. Prilikom paljenje se ponaša skoro potpuno isto kao i prvobitno paljenje, glavna je razlika mogućnost konfiguracije paljenja timerom ili GPIO pinom, no i to je vrlo ograničeno. Vrijeme paljenja je puno dulje nego kod deep sleep-a.

## Opis izrađenog sustava
Za izradu sustava korišten je deep sleep način rada ESP32 mikroupravljača.
Kod izrade osnovne funkcionalnosti korišteno je periodičko buđenje koje je probudilo mikroupravljač svakih 10 sekundi, dok je za izradu podzadatka varijante A korišteno buđenje eksternim prekidom, točnije pritiskom na tipkalo.
Zadatak je implementiran tako da se prilikom paljenja mikroupravljača prvo postavljaju osnovne postavke, te se potom izvršava kod "aktivne faze". Potom mikroupravljač odlazi u stanje mirovanja te se proces ponavlja svakim buđenjem uređaja koje može biti izazvano timerom ili vanjskim prekidom, ovisno o potreba zadatka.
Najveće je ograničenje simulacije bilo što nije moguće pratiti stvarnu potrošnju energije.

## Debouncing
Bouncing je fenomen do kojega dolazi kod korištenja fizičkih tipkala koja spajaju dva kontakt a pritiskom na njih. Prilikom pritiska tipkala dolazi do vibracije zbog koje se u jako kratkom vremenu više puta spoje i odspoje kontakti. Ako ne koristimo debouncing može doći do detekcije jednog pritiska kao niza pritisaka tipkala zbog čega bi u ovom konkretno slučaju došlo do izvođenja nekoliko ciklusa spavanja i buđenja. 
Kako bi to riješili radimo debouncing, odnosno dodajemo mali delay unutar handleWakeup koda kako bi dali tipkalu vremena da se  smiri i tako onemogućili slučajne ponovne aktivacije radi "bouncing-a".

## Teorijsko trajanje baterije
Ako pretpostavimo da uređaj troši oko 50mA struje dok je aktivan i 0.01mA u deep sleep-u te uzmemo da je u sleep modu 10 sekundi a aktivan 4 sekunde (3 za LED delay + nekoliko kraćih delay-eva zbog debouncinga, čekanja da se upali serial monitor, itd.) dobijemo računicu da je prosječna potrošnja struje oko 14.3mA. Iz toga dobivamo da bi baterija trebala potrajati oko 175 sati, što je oko tjedan dana rada.

## Tablica

| Stavka   | Odgovor  |
|----------|----------|
| Platforma | ESP32 |
|Varijanta|A|
|Sleep mode|Deep sleep|
|Buđenje|Periodičko|
|Čuvanje stanja|Ne|
|Debouncing| Da|
|Wokwi link - osnovni|https://wokwi.com/projects/463306097144963073|
|Wokwi link - A|https://wokwi.com/projects/463306105546158081|


## Dijagrami stanja
#### Osnovni kod
![Signals](https://github.com/GvidoMas/RUS--Maskalan/blob/main/Lab2/docs/basicc.png)


#### Podzadatak - A
![Signals](https://github.com/GvidoMas/RUS--Maskalan/blob/main/Lab2/docs/a.png)
