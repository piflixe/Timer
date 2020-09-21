for English, please see [README.md](README.md)

# Timer
Zeitschaltuhr für Photo-Vergrößerer u.a. mit einem Drehknopf und [Solid-State-Relay](http://www.segor.de/#Q=SSR2A(Modul)&M=1). Das Projekt wurde mit einem
[Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) umgesetzt, aber mit einem anderen Arduino oder Arduino-kompatiblem Board funktioniert es wahrscheinlich genauso.

Die Zeitschaltuhr verwendet ein handels-übliches 7-Segment Display mit insgesamt 8 Ziffern. Ich habe damit zwei getrennte Timer programmiert, mit jeweils 4 Ziffern je Timer. 
Ich finde dies beim Vergrößern sehr praktisch da man sich zum Beispiel auf den einen Timer 2 Sekunden für die Teststreifen legen kann, dann den Teststreifen mehrfach belichten 
und dann auf dem anderen Timer die gewünschte Zeit, z.B. 4 x 2 Sekunden = 8 Sekunden legen. So muss man sich nicht merken, wie lange die einzelnen Tests-Segmente belichtet wurden 
und sieht gleichzeitig noch die Belichtung des letzten Bildes.

Ich freue mich über Mitarbeit an diesem Projekt! Ich bin kein professionieller Programmierer und freue mich über input jeder Art.

# Verwendung
* Knopf drücken: Starte / Stoppe Timer
* Doppelklick: Lampe dauerhaft anschalten (z.B. zum einrichten / einstellen)
* lange Drücken: Wechsel zwischen den zwei Timern
* Knopf drehen: Zeit einstellen

# Bilder
![Zusammenbau](/doc/IMG_20200921_235534.jpg)

![Steuerungselektronik](/doc/IMG_20200922_000312.jpg)

![230V Elektronik](/doc/IMG_20200922_000351.jpg)
