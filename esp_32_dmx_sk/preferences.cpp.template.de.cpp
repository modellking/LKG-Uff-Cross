#ifndef PRE_CPP
#define PRE_CPP 1

// SECTION SETUP
// Standard Adresse des ersten Kanals (1 indiciert) (Wenn die Addresse im Einsatz geändert werden soll, kann hier ein beliebiger Wert verwendet werden) (Standartwert: 1)
#define DMX_START_ADDRESS 1
// Erlaube Adressänderung im Einsatz? 1 Erlaubt die Änderung durch eine DMX Prozedur, 2 Erlaubt die Änderung durch 2 Knöpfe, 3 durch eine Reihe DIP Schalter (siehe Handbuch) (Standartwert: 0)
#define USE_INFIELD_ADDRESSING 1
// Wie viele LEDs hat der Streifen insgesamt?
#define LED_COUNT 324
// Auf welchem Pin sollen die Daten für den LED Streifen ausgegeben werden? (Standartwert: 4)
#define LED_PIN 4
// Der DMX Input Pin ist auf Pin 16 festgelegt (um das zu ändern nutze einen anderen UART2 RX fähigen Pin und bearbeite dmx.cpp:3)

// Wie groß soll die Deadzone beim Zeit-Fader sein? (Standartwert: 5)
#define T_DEADZONE_SIZE (10 / 2)

// SECTION FORM
// Geht davon aus, dass der Start des Streifens irgendwo auf der linken Seite des unteren Arms und läuft gegen Uhrzeigersinn um das Kreuz (von Vorne gesehen)
// Wie viele LEDs sind in jeweils einem Abschnitt entlang des unteren Arms links bzw. rechts?
#define SHds 73
// Wie viele LEDs sind in jeweils einem Abschnitt entlang des linken Arms unten bzw. oben?
#define SHls 25
// Wie viele LEDs sind in jeweils einem Abschnitt entlang des oberen Arms links bzw. rechts?
#define SHts 25
// Wie viele LEDs sind in jeweils einem Abschnitt entlang des rechten Arms unten bzw. oben?
#define SHrs 25
// Wie viele LEDs sind in jeweils einem Abschnitt entlang der Außenseiten der Arme?
#define SHos  7
// Wie viele LEDs ist der Anfang des Streifens von der inneren Ecke am Kreuz entfernt?
#define SH_off 17

// SECTION FORTGESCHRITTEN
// Wie lange soll zwischen DMX Aktualisierungsversuchen gewartet werden? in ms (Standartwert: 30)
#define POLLRATE 30
// Wie lange soll zwischen Aktualisierungen des LED-Streifens gewartet werden? in ms (Standartwert: 10)
#define UPDATETIME 10
// SKIP todo set multiplier only
#define T_MAX (LED_COUNT * 64)
// SKIP How many color slot do you want to support? todo support anything aside from 4
#define COLOR_SLOT_COUNT 4

// SKIP Debug mode?
#define DEBUG 1

#endif
