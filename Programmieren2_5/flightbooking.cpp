#include "flightbooking.h"
#include <sstream>

using namespace std;

FlightBooking::FlightBooking()
{

}

FlightBooking::FlightBooking(string pID, double pPrice, string pFromDate, string pToDate, string pFromDestination, string pToDestination,
                             string pAirline, char pBookingClass, string pFromDestLat, string pFromDestLong, string pToDestLat, string pToDestLong, long pTravelID)
    :fromDestination(pFromDestination), toDestination(pToDestination), airline(pAirline), bookingClass(pBookingClass), fromDestLat(pFromDestLat),
     fromDestLong(pFromDestLong), toDestLat(pToDestLat), toDestLong(pToDestLong)
{
    id = pID;
    price = pPrice;
    fromDate = pFromDate;
    toDate = pToDate;
    travelID = pTravelID;

    string year{}, month{}, day{};
    int intYear{}, intMonth{}, intDay{};

    year = fromDate.substr(0,4);
    month = fromDate.substr(4,2);
    day = fromDate.substr(6,2);

    intYear = stoi(year);
    intMonth = stoi(month);
    intDay = stoi(day);

    qFromDate.setDate(intYear,intMonth,intDay);

    year = toDate.substr(0,4);
    month = toDate.substr(4,2);
    day = toDate.substr(6,2);

    intYear = stoi(year);
    intMonth = stoi(month);
    intDay = stoi(day);

    qToDate.setDate(intYear,intMonth,intDay);
}

FlightBooking::~FlightBooking()
{

}

std::string FlightBooking::showDetails()
{
    ostringstream strs;
    strs << price;
    string str = strs.str();
    return "Flugbuchung von " + fromDestination + " nach " + toDestination + " mit " + airline + " (" + getFullBookingClass() + ") am " + fromDate + ". Preis: " + str + " Euro";

}

std::string FlightBooking::getFullBookingClass()
{
    std::string fullBookingClass{};

    switch(bookingClass) {
    case 'Y' : fullBookingClass = "Economy Class";
        break;
    case 'W' : fullBookingClass = "Premium Economy Class";
        break;
    case 'J' : fullBookingClass = "Business Class";
        break;
    case 'F' : fullBookingClass = "First Class";
    }
    return fullBookingClass;
}

const std::string &FlightBooking::getFromDestination() const
{
    return fromDestination;
}

const std::string &FlightBooking::getToDestination() const
{
    return toDestination;
}

const std::string &FlightBooking::getAirline() const
{
    return airline;
}

void FlightBooking::setFromDestination(const std::string &newFromDestination)
{
    fromDestination = newFromDestination;
}

void FlightBooking::setToDestination(const std::string &newToDestination)
{
    toDestination = newToDestination;
}

void FlightBooking::setAirline(const std::string &newAirline)
{
    airline = newAirline;
}

void FlightBooking::setBookingClass(char newBookingClass)
{
    bookingClass = newBookingClass;
}

const std::string &FlightBooking::getFromDestLat() const
{
    return fromDestLat;
}

const std::string &FlightBooking::getFromDestLong() const
{
    return fromDestLong;
}

const std::string &FlightBooking::getToDestLat() const
{
    return toDestLat;
}

const std::string &FlightBooking::getToDestLong() const
{
    return toDestLong;
}

char FlightBooking::getBookingClass() const
{
    return bookingClass;
}

