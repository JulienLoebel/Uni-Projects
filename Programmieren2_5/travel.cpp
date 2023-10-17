#include "travel.h"
#include "flightbooking.h"
#include <iomanip>
#include "search.h"
#include "rentalcarreservation.h"
#include "hotelbooking.h"


Travel::Travel(long pID, long pCustomerid)
    :id(pID), customerId(pCustomerid)
{

}

Travel::~Travel()
{

}

void Travel::addBooking(std::shared_ptr<Booking> booking)
{
    travelBookings.push_back(booking);
}

long Travel::getId() const
{
    return id;
}


QDate Travel::getFirstDate()
{
    QDate firstDate = travelBookings[0]->getQFromDate();

    for (std::shared_ptr<Booking> b : travelBookings) {
        if (b->getQFromDate() < firstDate) {
            firstDate = b->getQFromDate();
        }
    }
    return firstDate;
}

QDate Travel::getLastDate()
{
    QDate lastDate = travelBookings[0]->getQToDate();

    for (std::shared_ptr<Booking> b : travelBookings) {
        if (b->getQToDate() > lastDate) {
            lastDate = b->getQToDate();
        }
    }
    return lastDate;
}

const std::vector<std::shared_ptr<Booking> > &Travel::getTravelBookings() const
{
    return travelBookings;
}

long Travel::getCustomerId() const
{
    return customerId;
}

const std::shared_ptr<Graph<std::shared_ptr<Booking>, 15> > &Travel::getGraph() const
{
    return graph;
}

void Travel::setGraph(const std::shared_ptr<Graph<std::shared_ptr<Booking>, 15> > &newGraph)
{
    graph = newGraph;
}

void Travel::sortGraph(std::vector<VertexData> &data)
{
    DepthFirstSearch(*graph);

    VertexData vertexData;
    int n = 0;
    while (graph->nextVertex(n) >= 0) {

        int pos = graph->nextVertex(n);

        vertexData.booking = graph->getVertexValue(pos);
        vertexData.endtime = graph->getEnd(pos);

        data.push_back(vertexData);
        n++;
    }

    for (unsigned int step = 0; step < data.size() - 1; step++) {
        int max = step;
        for (unsigned int i = step + 1; i < data.size(); i++) {

            if(data[i].endtime > data[max].endtime)
                max = i;
        }
        VertexData temp = data[max];
        data[max] = data[step];
        data[step] = temp;
    }
/*
    for (VertexData v : data) {
        cout << v.booking->getId() << " " << v.endtime << endl;
    }
*/
}

bool Travel::checkRoundtrip()
{
    bool isRoundtrip = false;

    std::vector<VertexData> data;

    sortGraph(data);

    int i = 0;

    while(typeid(FlightBooking) != typeid(*data[i].booking)) {
        i++;
        if(i >= data.size()){
            return false;
        }
    }

    std::shared_ptr<FlightBooking> firstFlight = static_pointer_cast<FlightBooking>(data[i].booking);


    i = data.size() - 1;

    while(typeid(FlightBooking) != typeid(*data[i].booking)) {
        i--;
        if(i < 0){
            return false;
        }
    }

    std::shared_ptr<FlightBooking> lastFlight = static_pointer_cast<FlightBooking>(data[i].booking);

    if (firstFlight->getFromDestination() == lastFlight->getToDestination())
        isRoundtrip = true;


    return isRoundtrip;
}

bool Travel::checkEnoughHotels()
{
    bool enoughHotels = true;

    std::vector<VertexData> data;

    sortGraph(data);

   for (unsigned int i = 0; i < data.size() - 1; i++) {
       if (typeid(RentalCarReservation) != typeid(*data[i].booking)) {

           for (unsigned int j = i +1; j < data.size(); j++) {
               if (typeid(RentalCarReservation) != typeid(*data[j].booking)) {

                   if(data[i].booking->getQToDate() < data[j].booking->getQFromDate()) {
                       enoughHotels = false;
                   }
                   break;
               }
           }
       }
   }
    return enoughHotels;
}

bool Travel::checkNoUselessHotel()
{
    bool noUselessHotel = true;

    std::vector<VertexData> data;

    sortGraph(data);

    for (unsigned int i = 0; i < data.size() - 1; i++) {
        if (typeid(RentalCarReservation) != typeid(*data[i].booking)) {

            for (unsigned int j = i +1; j < data.size(); j++) {
                if (typeid(RentalCarReservation) != typeid(*data[j].booking)) {

                    if(data[i].booking->getQToDate() > data[j].booking->getQFromDate()) {
                        noUselessHotel = false;
                    }
                    break;
                }
            }
        }
    }

    return noUselessHotel;
}

bool Travel::checkNoUselessRentalCar()
{
    bool noUselessRentalCar = true;

    std::vector<VertexData> data;

    sortGraph(data);

    for (unsigned int i = 0; i < data.size() - 1; i++) {
        if (typeid(HotelBooking) != typeid(*data[i].booking)) {

            for (unsigned int j = i +1; j < data.size(); j++) {
                if (typeid(HotelBooking) != typeid(*data[j].booking)) {

                    if(data[i].booking->getQToDate() > data[j].booking->getQFromDate()) {
                        noUselessRentalCar = false;
                    }
                    break;
                }
            }
        }
    }

    return noUselessRentalCar;
}

double Travel::getTotalTravelPrice()
{
    double totalTravelPrice = 0;

    for (unsigned int i = 0; i < travelBookings.size(); i++) {
        totalTravelPrice = totalTravelPrice + travelBookings[i]->getPrice();
    }
    return totalTravelPrice;
}
