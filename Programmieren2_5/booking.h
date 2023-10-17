#ifndef BOOKING_H
#define BOOKING_H
#include <iostream>
#include <QDate>

class Booking
{
public:
    Booking();
    Booking(std::string pID, double pPrice, std::string pFromDate, std::string pToDate, long pTravelID);
    virtual ~Booking();

    virtual std::string showDetails() = 0;

    const std::string &getId() const;

    double getPrice() const;

    const std::string &getFromDate() const;

    const std::string &getToDate() const;

    const QDate &getQFromDate() const;
    void setQFromDate(const QDate &newQFromDate);

    const QDate &getQToDate() const;
    void setQToDate(const QDate &newQToDate);

    void setPrice(double newPrice);

    long getTravelID() const;

protected:
    std::string id;
    double price;
    std::string fromDate;
    std::string toDate;
    long travelID;

    QDate qFromDate;
    QDate qToDate;
};

#endif // BOOKING_H
