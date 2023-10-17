#include "booking.h"

Booking::Booking()
{

}

Booking::Booking(std::string pID, double pPrice, std::string pFromDate, std::string pToDate, long pTravelID)
    :id(pID), price(pPrice), fromDate(pFromDate), toDate(pToDate), travelID(pTravelID)
{

}

Booking::~Booking()
{

}

const std::string &Booking::getId() const
{
    return id;
}

double Booking::getPrice() const
{
    return price;
}

const std::string &Booking::getFromDate() const
{
    return fromDate;
}

const std::string &Booking::getToDate() const
{
    return toDate;
}

const QDate &Booking::getQFromDate() const
{
    return qFromDate;
}

void Booking::setQFromDate(const QDate &newQFromDate)
{
    qFromDate = newQFromDate;
}

const QDate &Booking::getQToDate() const
{
    return qToDate;
}

void Booking::setQToDate(const QDate &newQToDate)
{
    qToDate = newQToDate;
}

void Booking::setPrice(double newPrice)
{
    price = newPrice;
}

long Booking::getTravelID() const
{
    return travelID;
}
