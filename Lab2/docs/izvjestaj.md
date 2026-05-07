# Izvještaj

## Različiti režimi mirovanja
#### Light sleep
Pauzira se rad CPU-a, no RAM i periferija ostaju aktivni. To omogućuje vrlo brzo buđenje te nema potrebe za ponovnim postavljanjem, spremanjem varijabli itd. što ga čini odličnim za česte i kratke pauze u radu.

#### Deep sleep
Dolazi do potpunog gašenja CPU-a, jedini dio koji ostane raditi je RTC. Dolazi do potpunog "reset-a" sustava, odnosno nakon buđenja je potrebno ponovno postavljanje (pokreće se setup()). Buđenje traje dulje nego kod light sleep-a.

#### Hibernation
Gasi se gotovo čitavi mmikorupravljač što omogućuje minimalnu potrošnju energije. Prilikom paljenje se ponaša skoro potpuno isto kao i prvobitno paljenje, glavna je razlika mmogućnost konfiguracije paljenja timerom ili GPIO pinom, no i to je vrlo ograničeno. Vrijeme paljenja je puno dulje nego kod deep sleep-a.

## Opis izrađenog sustava
Za izradu sustava koriššten je deep sleep način rada ESP32 mikroupravljača.
Kod izrade osnovne funkcionlnosti korišteno je periodičko buđenje koje je probudilo mikroupravljač svakih 10 sekundi, dok je za izradu podzadatka varijante A korišteno buđenje eksternim prekidom, točnije pritiskom na tipkalo.
Zadatak je implementiran tako da se prilikom paljenja mmikroupravljača prvo postavljaju osnovne postavke, te se potom izvršava kod "aktivne faze". Potom mikroupravljač odlazi u stanje mirovanja te se proces ponavlja svakim buđenjem uređaja koje momže biti izazvano timerom ili vanjskim prekidom, ovisno o potrebaa zadatka.
Najveće je ograničenje simulacije bilo što nije moguće pratiti stvarnu potrošnju energije.

## Debouncing
Bouncing je fenommen do kojega dolazi kod korišštenja fizičkih tipkala koja spajaju dva kontakt apritiskom na njih. Prilikom pritiska tipkalka dolazi do vibracije zbog koje se u jako kratkom vremmeneu višše puta spoje i odpoje kontakti. Ako ne koristimo debouncing može doći do detekcije jednog pritiska kao niza pritisaka tipklala zbog ćega bi u ovom konkretno slučaju došlo do izvođenja nekoliko ciklusa spavanja i buđenja. 
Kako bi to riješili radimo debouncing, odnosno dodajemo mali delay unutar handleWakeup koda kako bi dali tipkalu vremena da se  smiri i tako onemogućili slučajne ponovne aktivacije radi "bouncing-a".

## Teorijsko trajanje baterije


| Stavka   | Odgovor  |
|----------|----------|
| Platforma | ESP32 |
|Varijanta|A|
|Sleep mode|Deep sleep|
|Buđenje|Periodičko|
|Čuvanje stanja|Ne|
|Debouncing| Da|
|Wokwi link||


## Diajgrammi stanja
![Signals](https://github.com/GvidoMas/RUS--Maskalan/blob/main/Lab2/docs/basic.png)
![Signals](https://github.com/GvidoMas/RUS--Maskalan/blob/main/Lab2/doccs/a.png)
