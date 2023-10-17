#include "upandaway.h"
#include "travelagency.h"

#include <QApplication>

#include "test.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<TravelAgency> travelagency(new TravelAgency());

    UpAndAway w(travelagency);
    w.show();

    //Test test;
    //QTest::qExec(&test);


    return a.exec();
}
