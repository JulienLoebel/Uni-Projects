#include "hotelbooking.h"
#include <sstream>

using namespace std;

HotelBooking::HotelBooking()
{

}

HotelBooking::HotelBooking(string pID, double pPrice, string pFromDate, string pToDate, string pHotel, string pTown, string pRoomType,
                           string pHotelLat, string pHotelLong, long pTravelID)
    :hotel(pHotel), town(pTown), roomType(pRoomType), hotelLat(pHotelLat), hotelLong(pHotelLong)
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

HotelBooking::~HotelBooking()
{

}

std::string HotelBooking::showDetails()
{
    ostringstream strs;
    strs << price;
    string str = strs.str();
    return "Hotelbuchung (" +getFullRoomType() + ") im " + hotel + " in " + town + " vom " + fromDate + " bis zum " + toDate + ". Preis: " + str + " Euro";
}

std::string HotelBooking::getFullRoomType()
{
    string fullRoomType{};

    if (roomType == "EZ") {
        fullRoomType = "Einzelzimmer";
    } else if (roomType == "DZ") {
        fullRoomType = "Doppelzimmer";
    } else if (roomType == "AP") {
        fullRoomType = "Appartment";
    } else if (roomType == "SU") {
        fullRoomType = "Suite";
    }
    return fullRoomType;
}

const std::string &HotelBooking::getHotel() const
{
    return hotel;
}

const std::string &HotelBooking::getTown() const
{
    return town;
}

void HotelBooking::setHotel(const std::string &newHotel)
{
    hotel = newHotel;
}

void HotelBooking::setTown(const std::string &newTown)
{
    town = newTown;
}

void HotelBooking::setRoomType(const std::string &newRoomType)
{
    roomType = newRoomType;
}

const std::string &HotelBooking::getHotelLat() const
{
    return hotelLat;
}

const std::string &HotelBooking::getHotelLong() const
{
    return hotelLong;
}

const std::string &HotelBooking::getRoomType() const
{
    return roomType;
}
