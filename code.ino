const int mainRed = 2;    // Hauptampel Rot LED Pin
const int mainYellow = 3; // Hauptampel Gelb LED Pin
const int mainGreen = 4;  // Hauptampel Grün LED Pin

#define mainRedS A3    // Spezielle Hauptampel Rot LED Pin
#define mainYellowS A4 // Spezielle Hauptampel Gelb LED Pin
#define mainGreenS A5  // Spezielle Hauptampel Gelb LED Pin

const int mainRedLeft = 10;    // Pfeilampel Hauptstraße (Linksabbieger) Rot LED Pin
const int mainYellowLeft = 11; // Pfeilampel Hauptstraße (Linksabbieger) Gelb LED Pin
const int mainGreenLeft = 12;  // Pfeilampel Hauptstraße (Linksabbieger) Grün LED Pin

#define mainRedRight A0    // Pfeilampel Hauptstraße (Rechtsabbieger) Rot LED Pin
#define mainYellowRight A1 // Pfeilampel Hauptstraße (Rechtsabbieger) Gelb LED Pin
#define mainGreenRight A2  // Pfeilampel Hauptstraße (Rechtsabbieger) Grün LED Pin

const int pedRed = 5;   // Fussgängerampel Rot LED Pin
const int pedGreen = 6; // Fussgängerampel Grün LED Pin

const int onewayRed = 7;    // SeitenStraße Rot LED Pin
const int onewayYellow = 8; // SeitenStraße Gelb LED Pin
const int onewayGreen = 9;  // SeitenStraße Grün LED Pin

const int button = 13;      // Fussgängerampel-Knopf Pin
int state = 1;              // Variable zum Abfragen des Tasterstatus
bool cache = false;         // Variable zum Speichern des Tasterstatus während Ampelphase noch läuft
bool serialcache = true;    // Variable um zu verhindern, dass "Knopf betätigt" mehrmals ausgegeben wird
char input = 'platzhalter'; // Variable um Eingaben zu lesen

const int crossTime = 6000; // Variable zum Festlegen der Fussgängerüberquerzeit

void setup()
{
    pinMode(mainRed, OUTPUT);
    pinMode(mainYellow, OUTPUT);
    pinMode(mainGreen, OUTPUT);

    pinMode(pedRed, OUTPUT);
    pinMode(pedGreen, OUTPUT);

    pinMode(onewayRed, OUTPUT);
    pinMode(onewayYellow, OUTPUT);
    pinMode(onewayGreen, OUTPUT);

    pinMode(mainRedLeft, OUTPUT);
    pinMode(mainYellowLeft, OUTPUT);
    pinMode(mainGreenLeft, OUTPUT);

    pinMode(mainRedRight, OUTPUT);
    pinMode(mainYellowRight, OUTPUT);
    pinMode(mainGreenRight, OUTPUT);

    digitalWrite(pedRed, HIGH); // Alle Ampeln auf Rot stellen
    digitalWrite(mainRed, HIGH);
    digitalWrite(mainRedS, HIGH);
    digitalWrite(onewayRed, HIGH);
    digitalWrite(mainRedLeft, HIGH);
    digitalWrite(mainRedRight, HIGH);

    pinMode(button, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("");
    Serial.println("--- Neustart ---");
}

void loop()
{
    frameMainLeft();
    if (cache == true)
    {
        framePed();
        cache = false;
    }

    frameSec();
    if (cache == true)
    {
        framePed();
        cache = false;
    }

    frameMainRight();
    if (cache == true)
    {
        framePed();
        cache = false;
    }

    frameSec();
    if (cache == true)
    {
        framePed();
        cache = false;
    }
}

void frameMainLeft()
{
    Serial.println("Hauptstraße und Pfeilampel Links");
    digitalWrite(mainYellow, HIGH);     // Autoampel Gelb & Rot an
    digitalWrite(mainYellowLeft, HIGH); // Pfeilampel Links Gelb & Rot an

    for (int x = 0; x <= 83; x++)
    {
        delay(9);
        get();
    }

    digitalWrite(mainGreen, HIGH);     // Autoampel Grün an
    digitalWrite(mainGreenLeft, HIGH); // Pfeilampel Links Grün An
    digitalWrite(mainRed, LOW);        // Autoampel Rot aus
    digitalWrite(mainYellow, LOW);     // Autoampel Gelb aus
    digitalWrite(mainRedLeft, LOW);    // Pfeilampel Links Rot Aus
    digitalWrite(mainYellowLeft, LOW); // Pfeilampel Links Gelb Aus

    for (int x = 0; x <= 100; x++) // 6000ms
    {
        delay(60);
        get();
    }

    digitalWrite(mainYellow, HIGH);     // Autoampel Gelb an
    digitalWrite(mainYellowLeft, HIGH); // Pfeilampel Links Gelb an
    digitalWrite(mainGreen, LOW);       // Autoampel Grün aus
    digitalWrite(mainGreenLeft, LOW);   // Pfeilampel Links Grün aus

    for (int x = 0; x <= 83; x++) // 750ms
    {
        delay(9);
        get();
    }

    digitalWrite(mainRed, HIGH);       // Autoampel Rot an
    digitalWrite(mainRedLeft, HIGH);   // Pfeilampel Links Rot an
    digitalWrite(mainYellow, LOW);     // Autoampel Gelb aus
    digitalWrite(mainYellowLeft, LOW); // Pfeilampel Links Gelb aus

    for (int x = 0; x <= 83; x++) // 750ms
    {
        delay(9);
        get();
    }
}
void frameMainRight()
{
    Serial.println("Hauptstraße und Pfeilampel Rechts");
    digitalWrite(mainYellow, HIGH);      // Autoampel Gelb & Rot an
    digitalWrite(mainYellowS, HIGH);     // sp. Autoampel Gelb & Rot an
    digitalWrite(mainYellowRight, HIGH); // Pfeilampel Rechts Gelb & Rot an

    for (int x = 0; x <= 83; x++)
    {
        delay(9);
        get();
    }

    digitalWrite(mainGreen, HIGH);      // Autoampel Grün an
    digitalWrite(mainGreenS, HIGH);     // sp. Autoampel Grün an
    digitalWrite(mainGreenRight, HIGH); // Pfeilampel Rechts Grün An
    digitalWrite(mainRed, LOW);         // Autoampel Rot aus
    digitalWrite(mainRedS, LOW);        // sp. Autoampel Rot aus
    digitalWrite(mainYellow, LOW);      // Autoampel Gelb aus
    digitalWrite(mainYellowS, LOW);     // sp. Autoampel Gelb aus
    digitalWrite(mainRedRight, LOW);    // Pfeilampel Rechts Rot Aus
    digitalWrite(mainYellowRight, LOW); // Pfeilampel Rechts Gelb Aus

    for (int x = 0; x <= 100; x++) // 6000ms
    {
        delay(60);
        get();
    }

    digitalWrite(mainYellow, HIGH);      // Autoampel Gelb an
    digitalWrite(mainYellowS, HIGH);     // sp. Autoampel Gelb an
    digitalWrite(mainYellowRight, HIGH); // Pfeilampel Rechts Gelb an
    digitalWrite(mainGreen, LOW);        // Autoampel Grün aus
    digitalWrite(mainGreenS, LOW);       // sp. Autoampel grün aus
    digitalWrite(mainGreenRight, LOW);   // Pfeilampel Rechts Grün aus

    for (int x = 0; x <= 83; x++) // 750ms
    {
        delay(9);
        get();
    }

    digitalWrite(mainRed, HIGH);        // Autoampel Rot an
    digitalWrite(mainRedS, HIGH);       // sp. Autoampel Rot an
    digitalWrite(mainRedRight, HIGH);   // Pfeilampel Rechts Rot an
    digitalWrite(mainYellow, LOW);      // Autoampel Gelb aus
    digitalWrite(mainYellowS, LOW);     // sp. Autoampel Gelb aus
    digitalWrite(mainYellowRight, LOW); // Pfeilampel Rechts Gelb aus

    for (int x = 0; x <= 83; x++) // 750ms
    {
        delay(9);
        get();
    }
}
void frameSec()
{
    Serial.println("Seitenstraße");
    digitalWrite(onewayYellow, HIGH); // Einbahnampel Gelb & Rot an

    for (int x = 0; x <= 83; x++)
    {
        delay(9);
        get();
    }

    digitalWrite(onewayGreen, HIGH); // Einbahnampel Grün an
    digitalWrite(onewayRed, LOW);    // Einbahnampel Rot aus
    digitalWrite(onewayYellow, LOW); // Einbahnampel Gelb aus

    for (int x = 0; x <= 100; x++)
    {
        delay(60);
        get();
    }

    digitalWrite(onewayYellow, HIGH); // Einbahnampel Gelb an
    digitalWrite(onewayGreen, LOW);   // Einbahnampel Grün

    for (int x = 0; x <= 83; x++)
    {
        delay(9);
        get();
    }

    digitalWrite(onewayRed, HIGH);   // Einbahnampel Rot an
    digitalWrite(onewayYellow, LOW); // Einbahnampel Gelb aus

    for (int x = 0; x <= 83; x++)
    {
        delay(9);
        get();
    }
}
void framePed()
{
    Serial.println("Fussgänger");
    // digitalWrite(mainYellow, HIGH); // Autoampel Gelb & Rot an
    delay(750);

    // digitalWrite(mainGreen, HIGH); // Autoampel Grün an
    // digitalWrite(mainRed, LOW);    // Autoampel Rot aus

    digitalWrite(pedGreen, HIGH); // FG Ampel Grün an
    digitalWrite(pedRed, LOW);    // FG Ampel Rot aus
    delay(crossTime);

    for (int x = 0; x <= 10; x++) // FG Ampel blinkt gegen Ende der Überquerzeit
    {
        digitalWrite(pedGreen, HIGH);
        delay(250);
        digitalWrite(pedGreen, LOW);
        delay(250);
    }

    digitalWrite(pedRed, HIGH);  // FG Ampel Rot an
    digitalWrite(pedGreen, LOW); // FG Ampel Grün aus

    // digitalWrite(mainYellow, HIGH); // Autoampel Gelb an
    // digitalWrite(mainGreen, LOW);   // Autoampel Gelb aus
    delay(750);

    // digitalWrite(mainRed, HIGH);   // Autoampel Rot an
    // digitalWrite(mainYellow, LOW); // Autoampel Gelb aus
    delay(750);
    serialcache = true;
}

void get()
{
    state = digitalRead(button);
    if (state == 0)
    {
        if (serialcache == true)
        {
            Serial.println("Knopf betätigt");
            serialcache = false;
        }
        cache = true;
    }
}
