// lab4_upg2.cpp
// Program för att beräkna samtalstaxa för RingPling2 004 AB
// Thomas Nordenmark 2013-12-08
// Ver 0.1
//------------------------------------------------------------------------------
#include <iostream> // cin, cout
#include <sstream> // stringstream
#include <iomanip> // setw, setprecision
#include <string> // string, getline
using namespace std;

// ==================
// Globala konstanter
// ==================
const double MOMS = 1.25; // Momssats 25%
const double TAXA = 4.00; // Ordinare fullpristaxa
const double TID_RABATT = 0.35; // Kvällspris 65% rabatt
const double LANGD_RABATT = 0.85; // Samtal längre än 30 min, 15% rabatt
const string START_TID = "08:00"; // Starttid för fulltaxa
const string STOPP_TID = "18:30"; // Stopptid för fulltaxa

// ======================
// Funktionsdeklarationer
// ======================
bool kollaTid(string tid); // Kontrollera tidsformat
char menyVal(); // Hantera valet att köra programmet igen eller avsluta
double totalKostnad(string start, string stopp); // Beräkna toltalkostnad för samtal
int antalMinuter(string tid); // Konvertera tider till minuter

// ============
// Huvudprogram
// ============
int main()
{
    string start, stopp; // Användarens tidsangivelser
    bool giltigt_format; // Lagra om det inmatade tidsformatet är true (ok) eller false (ej ok)
    char menyval; // char för valet att avsluta eller köra programmet igen
    double totalkostnad = 0; // Lagra totalkostnaden
    double allasamtal = 0;

    // Huvudloop, upprepa så länge menyval är j
    do
    {        
        // Upprepa så länge formatet på angiven starttid är felaktigt
        do
        {
            cout << "Starttid (HH:MM eller H:MM): ";
            getline(cin, start);
            giltigt_format = kollaTid(start);
        }while(giltigt_format != true);

        // Upprepa så länge formatet på angiven stopptid är felaktigt
        do
        {
            cout << "Stopptid (HH:MM eller H:MM): ";
            getline(cin, stopp);
            giltigt_format = kollaTid(stopp);
        }while(giltigt_format != true);

        // Anropa funktionen som beräknar totalkostnad med parametrarna starttid och stopptid
        totalkostnad = totalKostnad(start, stopp);

        // Addera alla samtalskostnader till en totalsumma
        allasamtal += totalkostnad;

        // Kontrollera decimalutskrift beroende på hur stort talet är
        if(totalkostnad <= 9.99)
            cout << endl << "Totalkostnaden är: " << setprecision(3) << totalkostnad << endl;
        else if(totalkostnad <= 99.99)
            cout << endl << "Totalkostnaden är: " << setprecision(4) << totalkostnad << endl;
        else if(totalkostnad <= 999.99)
            cout << endl << "Totalkostnaden är: " << setprecision(5) << totalkostnad << endl;
        else if(totalkostnad <= 9999.99)
            cout << endl << "Totalkostnaden är: " << setprecision(6) << totalkostnad << endl;
        else
            // Vad tokigt det kan bli va?
            cout << "Dags att lägga på, du har ringt för länge..." << endl;

        // Skriv ut totalkostnaden för samtliga samtal denna programkörning
        cout << "Totalkostnad alla samtal: " << allasamtal << endl;

        // Upprepa så länge menyvalet inte är j eller n
        do
        {
            menyval = menyVal();
        }while(!(menyval == 'J' || menyval == 'N'));
    }while(menyval == 'J');

    return 0;
}

// =====================
// Funktionsdefinitioner
// =====================

// Kontrollera att inmatat tidformat är korrekt
bool kollaTid(string tid)
{
    int timme = 0, minut = 0; // Variabler att lagra stringstreams utdata i
    int separator = tid.find(":"); // Hitta kolonets plats i strängen

    // Om strängen är 4 tecken lång med kolon på plats 2 ELLER om strängen är 5 tecken
    // lång med kolon på plats 3 (som människor räknar)
    if((tid.length() == 4 && separator == 1) || (tid.length() == 5 && separator == 2))
    {
        tid[separator] = ' '; // Ersätt kolon med mellanslag för stringstream

        istringstream iss(tid); // Skapa strängström av strängen
        iss >> timme >> minut; // Slå isär strängen till timmar och minuter

        // Kolla så att timmar ligger mellan 0 och 23
        if(timme < 0 || timme > 23)
        {
            cout << "Formatet för timmar är felaktigt." << endl;

            return false;
        }

        // Kolla så att minuter ligger mellan 0 och 59
        if(minut < 0 || minut > 59)
        {
            cout << "Formatet för minuter är felaktigt." << endl;

            return false;
        }
        return true;
    }
    // Om kolonet är på helt fel plats eller strängen är för lång eller kort, skriv ut felmeddelande
    else
        cout << "Angivet tidsformat är felaktigt, ange HH:MM eller H:MM" << endl;
        return false;
}

// Hantera valet att köra programmet igen eller avsluta
char menyVal()
{
    char menyval; // char för att lagra menyvalet

    cout << endl << "Vill du köra programmet igen (j/n)? ";
    cin.get(menyval); // Läs ett tecken (j eller n)
    menyval = toupper(menyval); // Konvertera valet till versal
    cin.get(); // Läs bort retur

    return menyval;
}

// Beräkna antalet minuter
int antalMinuter(string tid)
{
    int antalmin = 0; // Variabel för att lagra antalet minuter
    int timme = 0, minut = 0; // Variabler att lagra stringstreams utdata i
    int separator = tid.find(":"); // Hittade kolonets plats i strängen

    tid[separator] = ' '; // Ersätt kolon med mellanslag för stringstream

    istringstream iss(tid); // Skapa strängström av strängen
    iss >> timme >> minut; // Slå isär strängen till timmar och minuter

    antalmin = (timme * 60) + minut; // Varje timme är 60 min

    return antalmin;
}

// Beräkna totalkostnaden för ett samtal
double totalKostnad(string start, string stopp)
{
    // Fuskar lite med en kontroll här eftersom jag missade instruktionen om att man skulle
    // kontrollera att starttid är mindre än stopptid. Skulle behöva skicka båda strängarna
    // start och stopp till kontrollfunktionen och skriva om den helt och hållet för att få
    // det att fungera.
    if(start < stopp)
    {
        // Antal minuter från midnatt som är starttid för samtalet
        int startmin = antalMinuter(start);

        // Antal minuter från midnatt som är sluttid för samtalet
        int slutmin = antalMinuter(stopp);

        // Antal minuter från midnatt fulltaxetid börjar
        int startfull = antalMinuter(START_TID);

        // Antal minuter från midnatt fulltaxetid slutar
        int stoppfull = antalMinuter(STOPP_TID);

        // Variabler för att lagra de uträknade minuterna med fulltaxa samt rabatterad taxa
        int total_min_full = 0;
        int total_min_rabatt = 0;

        // Loop för att iterera över samtalets minuter
        for (int i = startmin; i < slutmin; i++)
        {
            // Om i är större än eller lika med fulltaxestarttiden
            if(i >= startfull && i < stoppfull)
                // Lägg till en minut till fulltaxeräknaren
                total_min_full++;
            // Om inte
            else
                // Lägg till en minut till rabatträknaren
                total_min_rabatt++;
        }

        //Beräknar det totala priset
        double totalpris = total_min_full * TAXA + total_min_rabatt * TAXA * TID_RABATT;

        // Beräknar momsen
        totalpris = totalpris * MOMS;

        // Om samtalet är längre än 30 min, dra av rabattsatsen
        if(total_min_full + total_min_rabatt > 30)
            totalpris = totalpris * LANGD_RABATT;

        return totalpris;
    }
    else
    {
        // Om starttid är större än stopptid
        cout << "Ogiltig inmatning, starttid är mindre är stopptid." << endl;
        return 0;
    }
}
