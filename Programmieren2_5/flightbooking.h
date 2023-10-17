#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H
#include "booking.h"

class FlightBooking : public Booking
{
public:
    FlightBooking();
    FlightBooking(std::string pID, double pPrice, std::string pFromDate, std::string pToDate, std::string pFromDestination, std::string pToDestination,
                  std::string pAirline, char pBookingClass, std::string pFromDestLat, std::string pFromDestLong, std::string pToDestLat, std::string pToDestLong, long pTravelID);
    ~FlightBooking();

    std::string showDetails();
    std::string getFullBookingClass();

    const std::string &getFromDestination() const;

    const std::string &getToDestination() const;

    const std::string &getAirline() const;


    void setFromDestination(const std::string &newFromDestination);

    void setToDestination(const std::string &newToDestination);

    void setAirline(const std::string &newAirline);

    void setBookingClass(char newBookingClass);

    const std::string &getFromDestLat() const;

    const std::string &getFromDestLong() const;

    const std::string &getToDestLat() const;

    const std::string &getToDestLong() const;

    char getBookingClass() const;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string airline;
    char bookingClass;
    std::string fromDestLat;
    std::string fromDestLong;
    std::string toDestLat;
    std::string toDestLong;

};

#endif // FLIGHTBOOKING_H
