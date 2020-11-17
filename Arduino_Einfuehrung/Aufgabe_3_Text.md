# Arduino Einführung Aufgaben

## [Aufgaben-Datei](https://moodle.hsnr.de/pluginfile.php/640276/mod_resource/content/1/Anleitung_Kennenlernprojekte_WS2021_V3.pdf)

## Aufgabe 1

[Source-Code](https://git.ide3.de/universumgames/esp/-/tags/First-Task)

## Aufgabe 2

[Source-Code](https://git.ide3.de/universumgames/esp/-/tags/Second-Task)

## Aufgabe 3

### 3 d) GEschwindigkeit von (Ultra-)Schall
    Geschwindigkeit von Untraschall in Luft
    Mach 1 = 1234,8 km/h = 343 m/s

### 3 e)
    Grafik muss noch erstellt werden, sowie der Rest der Fragen beantwortet werden

### 3 f) Ablauf einer Entfernungsmessung
Um die Entferung mittels Ultraschall messen zu können, wird im Prinzip ein kleiner Ultraschalllautsprecher und ein dazugehöriges Mikrofon verwendet. Der Mikrokontroller auf dem Entfernungsmesser sendet bei Eingang eines Signals über den `Trigger`-Pin Ultraschallwellen aus und empfängt ein Echo. Mithilfe der SChallgeschwindigkeit (343 m/s) und der vergangenen Zeit seitdem der Schall ausgesendet worden ist, kann die Entfernung zum Objekt unmittelbar (2-300cm) vor dem Ultraschallsensor errechnet werden. Das Ergebnis dieser Rechnung wird letztendlich über den `Echo`-Pin an den Arduino gesendet. Die `PulseIn()` Funktion des Arduinos wird beim Empfang des Signals verwendet, da die Daten nur über ein Kabel (`Echo`) gesendet werden und speziell "encodiert" sind. Der HC-SR04, so wie der Chip des Ultraschallsensors heißt, stellt den Pin `Echo` proportional (um den Wert 0.017) zur Entfernung auf HIGH (5V). Mithilfe der `PulseIn()` Methode des Arduinos kann die Dauert dieses Wertes gemessen werden und wird letzendlich von der Methode zurückgegeben.
