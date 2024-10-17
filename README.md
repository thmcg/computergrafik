# Computergrafik

Dieses Repository enthält den Code zur Vorlesung "Computergrafik" an der Technischen Hochschule Mittelhessen.

## Inhalt

- /cgm_01/ - Code von Kapitel 1
- /cgm_02/ - Code von Kapitel 2
- /cgm_03/ - ...
- /libraries/ - Bibliotheken, die zum Kompilieren benötigt werden


## Projekt starten

Öffnen Sie den Ordner in Visual Studio Code. In der **Run and Debug** Ansicht lässt sich das passende Kapitel auswählen und starten.

Die einzelnen Tasks zum bauen der Kapitel und auch zum Aufräumen sind über das Menü **Terminal** ➔ **Run Build Task...** verfügbar.

Über die Kommandozeile lassen sich die einzelnen Kapitel wie folgt bauen, starten und aufräumen:

```
$ make cgm_01

$ bin/cgm_01

$ make clean
```


## Aufgabenstellung

Die Beschreibung der einzelnen Kapitel finden Sie auf [meiner Website](https://www.tobias-reimann.com/thm/computergrafik/).


## Copyright Hinweise

Die Bibliotheken in `/libraries/` wurden von den jeweiligen Autoren unter einer freien Lizenz veröffentlicht. Die genauen Lizenzbedingungen finden Sie in den jeweiligen Verzeichnissen.

Die Texturen der Erde wurden erzeugt aus Bildmaterial der NASA. Credits: NASA Goddard Space Flight Center Image by Reto Stöckli (land surface, shallow water, clouds). Enhancements by Robert Simmon (ocean color, compositing, 3D globes, animation). Data and technical support: MODIS Land Group; MODIS Science Data Support Team; MODIS Atmosphere Group; MODIS Ocean Group Additional data: USGS EROS Data Center (topography); USGS Terrestrial Remote Sensing Flagstaff Field Center (Antarctica); Defense Meteorological Satellite Program (city lights).

Die Sternentextur wurde erzeugt aus dem Bildmeterial von [Deep Star Maps 2020](https://svs.gsfc.nasa.gov/4851) des NASA/Goddard Space Flight Center Scientific Visualization Studio vom 9. September 2020.

Das THM Logo ist Eigentum der Technischen Hochschule Mittelhessen.