#include "rentalcarreservation.h"
#include <sstream>

using namespace std;

RentalCarReservation::RentalCarReservation()
{

}

RentalCarReservation::RentalCarReservation(string pID, double pPrice, string pFromDate, string pToDate, string pPickupLocation, string pReturnLocation,
                                           string pCompany, string pVehicleClass, string pPickupLocationLat, string pPickupLocationLong,
                                           string pReturnLocationLat, string pReturnLocationLong, long pTravelID)
    :pickupLocation(pPickupLocation), returnLocation(pReturnLocation), company(pCompany), vehicleClass(pVehicleClass),
     pickupLocationLat(pPickupLocationLat), pickupLocationLong(pPickupLocationLong), returnLocationLat(pReturnLocationLat), returnLocationLong(pReturnLocationLong)
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

RentalCarReservation::~RentalCarReservation()
{

}

const std::string &RentalCarReservation::getPickupLocation() const
{
    return pickupLocation;
}

const std::string &RentalCarReservation::getReturnLocation() const
{
    return returnLocation;
}

const std::string &RentalCarReservation::getCompany() const
{
    return company;
}

const std::string &RentalCarReservation::getVehicleClass() const
{
    return vehicleClass;
}

void RentalCarReservation::setPickupLocation(const std::string &newPickupLocation)
{
    pickupLocation = newPickupLocation;
}

void RentalCarReservation::setReturnLocation(const std::string &newReturnLocation)
{
    returnLocation = newReturnLocation;
}

void RentalCarReservation::setCompany(const std::string &newCompany)
{
    company = newCompany;
}

void RentalCarReservation::setVehicleClass(const std::string &newVehicleClass)
{
    vehicleClass = newVehicleClass;
}

const std::string &RentalCarReservation::getPickupLocationLat() const
{
    return pickupLocationLat;
}

const std::string &RentalCarReservation::getPickupLocationLong() const
{
    return pickupLocationLong;
}

const std::string &RentalCarReservation::getReturnLocationLat() const
{
    return returnLocationLat;
}

const std::string &RentalCarReservation::getReturnLocationLong() const
{
    return returnLocationLong;
}

string RentalCarReservation::showDetails()
{
    ostringstream strs;
    strs << price;
    string str = strs.str();
    return "Mietwagenreservierung mit " + company +" (" + vehicleClass + "). Abholung am " + fromDate + " in " + pickupLocation + ". Rueckgabe am " + toDate + " in " + returnLocation + ". Preis: " + str + " Euro";
}
