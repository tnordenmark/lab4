// lab4_upg1.cpp
// Program för att kasta ett givet nummer tärningar och beräkna statistik
// Thomas Nordenmark 2013-12-07
// Ver 0.1
//------------------------------------------------------------------------------
#include <iostream> // cin, cout
#include <random> // default_random_engine
#include <iomanip> // setw
#include <functional> // bind
using namespace std;

// ======================
// Funktionsdeklarationer
// ======================
int rollDice(); // Returnera ett slumptal

// ============
// Huvudprogram
// ============
int main()
{
    // Initiera slumpdistributörsobjektet generator
    default_random_engine generator(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> random(1, 6); // Slumpa i itervallet 1-6
    // Slå ihop slumpgeneratorn till en funktion för enklare användning
    auto rollDice = bind(random, generator);

    int rolls; // Antal tärningar som ska kastas
    // Variabler för att lagra de olika tärningarnas förekomst
    int ones = 0, twoes = 0, threes = 0, fours = 0, fives = 0, sixes = 0;
    int result; // Variabel för att lagra slumptalet från funktionen rollDice()
    int numberofrolls = 0; // Räknare för att lagra antalet tärningskast

    // Ledtext är kul, hämta antalet kast samt rensa buffern utan radbrytning
    cout << "Hur många gånger vill du kasta tärningen? " << flush;
    cin >> rolls;

    // Loop för att kasta tärningen angivet antal gånger
    for(int i = 0; i < rolls; i++)
    {
        // Anropa funktionen och lagra resultatet i result
        result = rollDice();
        // Skriv ut resultat för tärningsnummer
        cout << "Tärning " << setw(2) << numberofrolls + 1 << ": " << result << endl;

        // Uppdatera räknaren för antalet tärningskast
        numberofrolls++;

        // Uppdatera räknare för varje enskild tärning
        if(result == 1)
            ones++;
        else if(result == 2)
            twoes++;
        else if(result == 3)
            threes++;
        else if(result == 4)
            fours++;
        else if(result == 5)
            fives++;
        else if(result == 6)
            sixes++;
    }

    // Vänsterjustering gäller tills annat anges
    cout << left;

    // Massor med ledtext, kul!
    cout << endl << "===================" << endl;
    cout << "Antal tärningskast: " << numberofrolls << endl;
    cout << "===================" << endl;

    cout << endl << "Tärningarnas resultat" << endl;
    cout << "=====================" << endl;

    // De enskilda tärningarnas resultat
    cout << endl << setw(8) << "Ettor: " << ones << endl
         << setw(9) << "Tvåor: " << twoes << endl // setw(9) för att å inte räknas
         << setw(8) << "Treor: " << threes << endl
         << setw(8) << "Fyror: " << fours << endl
         << setw(8) << "Femmor: " << fives << endl
         << setw(8) << "Sexor: " << sixes << endl;

    // Ledtext igen, kul kul!
    cout << endl << "Relativ frekvens i %" << endl;
    cout << "====================" << endl;

    // Tärningarnas relativa frekvens
    cout << endl << setw(10) << "Ettor %: " << (double)ones / (double)numberofrolls * 100 << endl
         << setw(11) << "Tvåor %: " << (double)twoes / (double)numberofrolls * 100 << endl
         << setw(10) << "Treor %: " << (double)threes / (double)numberofrolls * 100 << endl
         << setw(10) << "Fyror %: " << (double)fours / (double)numberofrolls * 100 << endl
         << setw(10) << "Femmor %: " << (double)fives / (double)numberofrolls * 100 << endl
         << setw(10) << "Sexor %: " << (double)sixes / (double)numberofrolls * 100 << endl;

    return 0;
}
