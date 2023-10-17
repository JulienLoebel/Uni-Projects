#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H
#include "booking.h"
#include "travel.h"
#include "customer.h"
#include "airport.h"
#include <vector>
#include <memory>
#include "sortfunktor.h"

#include "json.hpp"

class TravelAgency
{
public:
    TravelAgency();
    ~TravelAgency();

    void readFile(std::string pFileName, bool testing);
    void clearBookings();
    void clearCustomers();
    void clearTravels();
    std::shared_ptr<Booking> findBooking(std::string id);
    std::shared_ptr<Travel> findTravel(long id);
    std::shared_ptr<Customer> findCustomer(long id);
    void readAirports();
    std::string findAirport(std::string iata);
    void addCustomer(long id, std::string name);
    void addBooking(std::shared_ptr<Booking> booking);
    void addTravel(std::shared_ptr<Travel> travel);
    void saveToJSON(SortFunktor::SortierParameter parameter);
    void createTravelGraphs(nlohmann::json bookingList);
    void abcAnalyse();
    double getTotalPrice();

    const std::vector<std::shared_ptr<Booking>> &getBookings() const;

    const std::vector<std::shared_ptr<Customer> > &getAllCustomers() const;

    const std::vector<std::shared_ptr<Travel> > &getAllTravels() const;

    int test1();
    int test2();
    int test3();

private:
    std::vector<std::shared_ptr<Booking>> allBookings;
    std::vector<std::shared_ptr<Customer>> allCustomers;
    std::vector<std::shared_ptr<Travel>> allTravels;
    std::vector<std::shared_ptr<Airport>> allAirports;
};

#endif // TRAVELAGENCY_H
