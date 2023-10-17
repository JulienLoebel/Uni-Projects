#ifndef TRAVEL_H
#define TRAVEL_H
#include "booking.h"
#include <vector>
#include <memory>
#include "graph.h"

struct VertexData {
    int endtime;
    std::shared_ptr<Booking> booking;
};


class Travel
{
public:
    Travel(long pID, long pCustomerid);
    ~Travel();

    void addBooking(std::shared_ptr<Booking> booking);
    void addGraphelement(std::shared_ptr<Booking> self, std::shared_ptr<Booking> pre1, std::shared_ptr<Booking> pre2);
    void sortGraph(std::vector<VertexData> &data);
    bool checkRoundtrip();
    bool checkEnoughHotels();
    bool checkNoUselessHotel();
    bool checkNoUselessRentalCar();
    double getTotalTravelPrice();

    long getId() const;

    QDate getFirstDate();
    QDate getLastDate();

    const std::vector<std::shared_ptr<Booking> > &getTravelBookings() const;

    long getCustomerId() const;


    const std::shared_ptr<Graph<std::shared_ptr<Booking>, 15> > &getGraph() const;
    void setGraph(const std::shared_ptr<Graph<std::shared_ptr<Booking>, 15> > &newGraph);

private:
    long id;
    long customerId;
    std::vector<std::shared_ptr<Booking>> travelBookings;

    std::shared_ptr<Graph<std::shared_ptr<Booking>, 15>> graph;

};

#endif // TRAVEL_H
