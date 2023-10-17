#include "test.h"
#include "travelagency.h"

void Test::test1()
{
    TravelAgency travelagency;
    travelagency.readFile("C:\\_Uni\\Semester2\\Programmiern2\\Praktikum\\Praktikum4\\bookingsPraktikum4.json", true);

    QCOMPARE(travelagency.test1(), 7);
}

void Test::test2()
{
    TravelAgency travelagency;
    travelagency.readFile("C:\\_Uni\\Semester2\\Programmiern2\\Praktikum\\Praktikum4\\bookingsPraktikum4.json", true);

    QCOMPARE(travelagency.test2(), 4);
}

void Test::test3()
{
    TravelAgency travelagency;
    travelagency.readFile("C:\\_Uni\\Semester2\\Programmiern2\\Praktikum\\Praktikum4\\bookingsPraktikum4.json", true);

    QCOMPARE(travelagency.test3(), 14);
}
//google unittest
