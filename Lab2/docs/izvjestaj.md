#Izvještaj

#Različiti režimi mmimrovanja


#Opis izrađenog sustava
Za izradu sustava koriššten je deep sleep način rada ESP32 mikroupravljača.
Kod izrade osnovne funkcionlnosti korišteno je periodičko buđenje koje je probudilo mikroupravljač svakih 10 sekundi, dok je za izradu podzadatka varijante A korišteno buđenje eksternim prekidom, točnije pritiskom na tipkalo.
Zadatak je implementiran tako da se prilikom paljenja mmikroupravljača prvo postavljaju osnovne postavke, te se potom izvršava kod "aktivne faze". Potom mikroupravljač odlazi u stanje mirovanja te se proces ponavlja svakim buđenjem uređaja koje momže biti izazvano timerom ili vanjskim prekidom, ovisno o potrebaa zadatka.
Najveće je ograničenje simulacije bilo što nije moguće pratiti stvarnu potrošnju energije.

#Debouncing


#Teorijsko trajanje baterije


| Stavka   | Odgovor  |
|----------|----------|
| Platforma | ESP32 |
|Varijanta|A|
|Sleep mode|Deep sleep|
|Buđenje|Periodičko|
|Čuvanje stanja|Ne|
|Debouncing| Da|
|Wokwi link||
