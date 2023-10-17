#include "travelagency.h"
#include <fstream>
#include <cstdlib>
#include "flightbooking.h"
#include "rentalcarreservation.h"
#include "hotelbooking.h"
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include "graph.h"

using json = nlohmann::json;

using namespace std;

TravelAgency::TravelAgency()
{

}

TravelAgency::~TravelAgency()
{
    clearBookings();
    clearCustomers();
    clearTravels();
}

void TravelAgency::clearBookings()
{
    allBookings.clear();
}

void TravelAgency::clearCustomers()
{
    allCustomers.clear();
}

void TravelAgency::clearTravels()
{
    allTravels.clear();
}

std::shared_ptr<Booking> TravelAgency::findBooking(string id)
{
    std::shared_ptr<Booking> booking(NULL);
    for (std::shared_ptr<Booking> b : allBookings) {
        if (id == b->getId()) {
            booking = b;
        }
    }
    return booking;
}

std::shared_ptr<Travel> TravelAgency::findTravel(long id) {
    std::shared_ptr<Travel> travel(NULL);
    for (std::shared_ptr<Travel> t : allTravels) {
        if (t->getId() == id) {
            travel = t;
        }
    }
    return travel;
}

std::shared_ptr<Customer> TravelAgency::findCustomer(long id)
{
    std::shared_ptr<Customer> customer(NULL);
    for (std::shared_ptr<Customer> c : allCustomers) {
        if (c->getId() == id) {
            customer = c;
        }
    }
    return customer;
}

const std::vector<std::shared_ptr<Booking>> &TravelAgency::getBookings() const
{
    return allBookings;
}

const std::vector<std::shared_ptr<Customer> > &TravelAgency::getAllCustomers() const
{
    return allCustomers;
}

const std::vector<std::shared_ptr<Travel> > &TravelAgency::getAllTravels() const
{
    return allTravels;
}

void TravelAgency::addBooking(shared_ptr<Booking> booking)
{
    allBookings.push_back(booking);
}

void TravelAgency::addTravel(shared_ptr<Travel> travel)
{
    allTravels.push_back(travel);
}

void TravelAgency::addCustomer(long id, string name)
{
    allCustomers.push_back(make_shared<Customer>(id, name));
}

void TravelAgency::readFile(string pFileName, bool testing)
{
    clearBookings();
    clearCustomers();
    clearTravels();

    ifstream source(pFileName, ifstream::in);

   if (!source) {
       throw invalid_argument("Datei kann nicht geoeffnet werden!");
   }

   json bookingList;

   source >> bookingList;   //Inhalt der json-Datei wird in das json-Objekt bookingList geschrieben

   source.close();

   double jsonPrice{};
   long travelId{}, customerId{};
   string customerName{};
   string jsonID{}, jsonToDate{}, jsonFromDate{};
   string jsonToDest{}, jsonFromDest{}, jsonAirline{}, jsonBookingClass{};
   string jsonToDestLat{}, jsonToDestLong{}, jsonFromDestLat{}, jsonFromDestLong{};
   string jsonPickupLocation{}, jsonReturnLocation{}, jsonCompany{}, jsonVehicleClass{};
   string jsonPickupLocationLat{}, jsonPickupLocationLong{}, jsonReturnLocationLat{}, jsonReturnLocationLong{};
   string jsonHotel{}, jsonTown{}, jsonRoomType{};
   string jsonHotelLat{}, jsonHotelLong{};

   int jsonCounterFlight{0}, jsonCounterRentalCar{0}, jsonCounterHotel{0}; //Zähler der einzelnen Klassen
   double jsonSumFlight{0}, jsonSumRentalCar{0}, jsonSumHotel{0};          //Summe der Preise der einzelnen Klassen

   for(unsigned int i = 0; i < bookingList.size(); i++) { //bookingList ist ein Array mit Objekten diese werden nacheinander initailisiert

       if (bookingList[i].at("type") == "Flight") { //Fallunterscheidung für jede Unterklasse von Booking


           if (bookingList[i].at("id") == "") {
               throw invalid_argument("Ungeultige id in Objekt: " + to_string(i));
           }

           jsonID = bookingList[i].at("id");

           if (!bookingList[i].at("price").is_number()) {
               throw invalid_argument("Ungueltiger Preis in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("fromDate") == "") {
               throw invalid_argument("Ungueltiges Startdatum in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("toDate") == "") {
               throw invalid_argument("Ungueltiges Enddatum in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("fromDest") == "") {
               throw invalid_argument("Ungueltiger Startflughafen in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("toDest") == "") {
               throw invalid_argument("Ungueltiger Endflughafen in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("airline") == "") {
               throw invalid_argument("Ungueltige Airline in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("bookingClass") == "") {
               throw invalid_argument("Ungueltige Buchungsklasse in Buchung ID: " + jsonID);
           }

           jsonToDest = bookingList[i].at("toDest");
           jsonFromDest = bookingList[i].at("fromDest");

           if (jsonToDest.size() != 3 || jsonFromDest.size() != 3) {
               throw invalid_argument("Flughafenkuerzel duerfen nur aus drei Zeichen bestehen ID: " + jsonID);
           }

           jsonPrice = bookingList[i].at("price");
           jsonFromDate = bookingList[i].at("fromDate");
           jsonToDate = bookingList[i].at("toDate");
           jsonAirline = bookingList[i].at("airline");
           jsonBookingClass = bookingList[i].at("bookingClass");
           char charBookingClass = jsonBookingClass[0];
           jsonFromDestLat = bookingList[i].at("fromDestLatitude");
           jsonFromDestLong = bookingList[i].at("fromDestLongitude");
           jsonToDestLat = bookingList[i].at("toDestLatitude");
           jsonToDestLong = bookingList[i].at("toDestLongitude");
           travelId = bookingList[i].at("travelId");

           std::shared_ptr<FlightBooking> jsonFlightPointer(new FlightBooking(jsonID, jsonPrice, jsonFromDate, jsonToDate, jsonFromDest, jsonToDest, jsonAirline,
                                                                              charBookingClass, jsonFromDestLat, jsonFromDestLong, jsonToDestLat, jsonToDestLong, travelId));
           allBookings.push_back(jsonFlightPointer);

           jsonCounterFlight++;
           jsonSumFlight = jsonSumFlight + jsonPrice;

           customerId = bookingList[i].at("customerId");
           customerName = bookingList[i].at("customerName");

           std::shared_ptr<Travel> travel = findTravel(travelId);

           if (travel) {
               travel->addBooking(jsonFlightPointer);
           } else {
                travel = std::shared_ptr<Travel>(new Travel(travelId, customerId));
                travel->addBooking(jsonFlightPointer);
                allTravels.push_back(travel);
           }

           std::shared_ptr<Customer> customer = findCustomer(customerId);

           if (customer) {
               if (customer->checkTravelList(travelId) == NULL) {
                   customer->addTravel(travel);
               }
           } else {
               customer = std::shared_ptr<Customer>(new Customer(customerId, customerName));
               customer->addTravel(travel);
               allCustomers.push_back(customer);
           }

       } else if (bookingList[i].at("type") == "RentalCar") {

           if (bookingList[i].at("id") == "") {
               throw invalid_argument("Ungeultige id in Objekt: " + to_string(i));
           }

           jsonID = bookingList[i].at("id");

           if (!bookingList[i].at("price").is_number()) {
               throw invalid_argument("Ungueltiger Preis in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("fromDate") == "") {
               throw invalid_argument("Ungueltiges Startdatum in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("toDate") == "") {
               throw invalid_argument("Ungueltiges Enddatum in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("pickupLocation") == "") {
               throw invalid_argument("Ungueltiger Abholort in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("returnLocation") == "") {
               throw invalid_argument("Ungueltiger Rueckgabeort in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("company") == "") {
               throw invalid_argument("Ungueltige Firma in Buchung ID: " + jsonID);
           }

           jsonPrice = bookingList[i].at("price");
           jsonFromDate = bookingList[i].at("fromDate");
           jsonToDate = bookingList[i].at("toDate");
           jsonPickupLocation = bookingList[i].at("pickupLocation");
           jsonReturnLocation = bookingList[i].at("returnLocation");
           jsonCompany = bookingList[i].at("company");
           jsonVehicleClass = bookingList[i].at("vehicleClass");
           jsonPickupLocationLat = bookingList[i].at("pickupLatitude");
           jsonPickupLocationLong = bookingList[i].at("pickupLongitude");
           jsonReturnLocationLat = bookingList[i].at("returnLatitude");
           jsonReturnLocationLong = bookingList[i].at("returnLongitude");
           travelId = bookingList[i].at("travelId");

          std::shared_ptr<RentalCarReservation> jsonCarPointer(new RentalCarReservation(jsonID, jsonPrice, jsonFromDate, jsonToDate, jsonPickupLocation,
                                                                                        jsonReturnLocation, jsonCompany, jsonVehicleClass, jsonPickupLocationLat,
                                                                                        jsonPickupLocationLong, jsonReturnLocationLat, jsonReturnLocationLong, travelId));
           allBookings.push_back(jsonCarPointer);

           jsonCounterRentalCar++;
           jsonSumRentalCar = jsonSumRentalCar + jsonPrice;

           customerId = bookingList[i].at("customerId");
           customerName = bookingList[i].at("customerName");

           std::shared_ptr<Travel> travel = findTravel(travelId);

           if (travel) {
               travel->addBooking(jsonCarPointer);
           } else {
                travel = std::shared_ptr<Travel>(new Travel(travelId, customerId));
                travel->addBooking(jsonCarPointer);
                allTravels.push_back(travel);
           }

           std::shared_ptr<Customer> customer = findCustomer(customerId);

           if (customer) {
               if (customer->checkTravelList(travelId) == NULL) {
                   customer->addTravel(travel);
               }
           } else {
               customer = std::shared_ptr<Customer>(new Customer(customerId, customerName));
               customer->addTravel(travel);
               allCustomers.push_back(customer);
           }

       } else if (bookingList[i].at("type") == "Hotel") {

           if (bookingList[i].at("id") == "") {
               throw invalid_argument("Ungeultige id in Objekt: " + to_string(i));
           }

           jsonID = bookingList[i].at("id");

           if (!bookingList[i].at("price").is_number()) {
               throw invalid_argument("Ungueltiger Preis in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("fromDate") == "") {
               throw invalid_argument("Ungueltiges Startdatum in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("toDate") == "") {
               throw invalid_argument("Ungueltiges Enddatum in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("hotel") == "") {
               throw invalid_argument("Ungueltiges Hotel in Buchung ID: " + jsonID);
           }
           if (bookingList[i].at("town") == "") {
               throw invalid_argument("Ungueltige Stadt in Buchung ID: " + jsonID);
           }

           jsonPrice = bookingList[i].at("price");
           jsonFromDate = bookingList[i].at("fromDate");
           jsonToDate = bookingList[i].at("toDate");
           jsonHotel = bookingList[i].at("hotel");
           jsonTown = bookingList[i].at("town");
           jsonRoomType = bookingList[i].at("roomType");
           jsonHotelLat = bookingList[i].at("hotelLatitude");
           jsonHotelLong = bookingList[i].at("hotelLongitude");
           travelId = bookingList[i].at("travelId");

           std::shared_ptr<HotelBooking> jsonHotelPointer(new HotelBooking(jsonID, jsonPrice, jsonFromDate, jsonToDate, jsonHotel, jsonTown, jsonRoomType,
                                                                           jsonHotelLat, jsonHotelLong, travelId));
           allBookings.push_back(jsonHotelPointer);

           jsonCounterHotel++;
           jsonSumHotel = jsonSumHotel + jsonPrice;

           customerId = bookingList[i].at("customerId");
           customerName = bookingList[i].at("customerName");

           std::shared_ptr<Travel> travel = findTravel(travelId);

           if (travel) {
               travel->addBooking(jsonHotelPointer);
           } else {
                travel = std::shared_ptr<Travel>(new Travel(travelId, customerId));
                travel->addBooking(jsonHotelPointer);
                allTravels.push_back(travel);
           }

           std::shared_ptr<Customer> customer = findCustomer(customerId);

           if (customer) {
               if (customer->checkTravelList(travelId) == NULL) {
                   customer->addTravel(travel);
               }
           } else {
               customer = std::shared_ptr<Customer>(new Customer(customerId, customerName));
               customer->addTravel(travel);
               allCustomers.push_back(customer);
           }
       }

   }

  if (!testing) {
      QString allBookingsMessage = QString("Es wurden %1 Flugbuchungen im Wert von %2 Euro,\n%3 Mietwagenbuchungen im Wert von %4 Euro\nund %5 Hotelreservierungen im Wert von %7 Euro eingelesen.\n")
              .arg(jsonCounterFlight).arg(jsonSumFlight).arg(jsonCounterRentalCar).arg(jsonSumRentalCar).arg(jsonCounterHotel).arg(jsonSumHotel);
      QString travelsAndCustomers = QString("Es wurden %1 Reisen und %2 Kunden angeleget.\n")
              .arg(allTravels.size()).arg(allCustomers.size());
      QString customerInfo = QString("Der Kunde mit der ID 1 hat %1 Reisen gebucht.\nZur Reise mit der ID 17 gehoeren %2 Buchungen.")
              .arg(findCustomer(1)->getTravelList().size()).arg(findTravel(17)->getTravelBookings().size());

      QMessageBox::information(nullptr,"Datei erfolgreich eingelesen", allBookingsMessage+travelsAndCustomers+customerInfo);

      readAirports();
      createTravelGraphs(bookingList);
  }
}

void TravelAgency::readAirports()
{
    allAirports.clear();

    QString fileName = "C:\\Users\\Julien\\Downloads\\iatacodes(1).json";

    QFile source(fileName);

   if (!source.open(QIODevice::ReadOnly)) {
       throw invalid_argument("Datei kann nicht geoeffnet werden!");
   }

   QString sourceString = source.readAll();

   source.close();

   QJsonDocument jsonDocument = QJsonDocument::fromJson(sourceString.toUtf8());

   QJsonArray airportList = jsonDocument.array();
   QJsonObject airport{};
   QJsonValue name{}, iso_country{}, municipality{}, iata_code{};
   string sName{}, sIso_country{}, sMunicipality{}, sIata_code{};

   for (unsigned int i = 0; i < airportList.size(); i++) {
       airport = airportList[i].toObject();

       name = airport.value("name");
       iso_country = airport.value("iso_country");
       municipality = airport.value("municipality");
       iata_code = airport.value("iata_code");

       sName = name.toString().toStdString();
       sIso_country = iso_country.toString().toStdString();
       sMunicipality = municipality.toString().toStdString();
       sIata_code = iata_code.toString().toStdString();

       allAirports.push_back(make_shared<Airport>(sName, sIso_country, sMunicipality, sIata_code));
   }
}

string TravelAgency::findAirport(string iata)
{
    string airport = "Ungueltiger Iata-Code";

    for (unsigned int i = 0; i < allAirports.size(); i++) {
        if (allAirports[i]->getIata_code() == iata) {
            airport = allAirports[i]->getName();
            break;
        }
    }
    return airport;
}

void TravelAgency::saveToJSON(SortFunktor::SortierParameter parameter)
{

    SortFunktor sortFunktor = SortFunktor(parameter);

    sort(allBookings.begin(), allBookings.end(), sortFunktor);

    json bookingList;
    json bookingElement;

    for (shared_ptr<Booking> booking : allBookings) {

        if (typeid(FlightBooking) == typeid(*booking)) {
            bookingElement["id"] = booking->getId();
            bookingElement["price"] = booking->getPrice();
            bookingElement["fromDate"] = booking->getFromDate();
            bookingElement["toDate"] = booking->getToDate();

            bookingElement["travelId"] = booking->getTravelID();

            std::shared_ptr<Travel> travel = findTravel(booking->getTravelID());

            bookingElement["customerId"] = travel->getCustomerId();

            std::shared_ptr<Customer> customer = findCustomer(travel->getCustomerId());

            bookingElement["customerName"] = customer->getName();

            shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);

            bookingElement["fromDest"] = flight->getFromDestination();
            bookingElement["toDest"] = flight->getToDestination();
            bookingElement["airline"] = flight->getAirline();
            std::string bookingClass(1, flight->getBookingClass());
            bookingElement["bookingClass"] = bookingClass;
            bookingElement["fromDestLatitude"] = flight->getFromDestLat();
            bookingElement["fromDestLongitude"] = flight->getFromDestLong();
            bookingElement["toDestLatitude"] = flight->getToDestLat();
            bookingElement["toDestLongitude"] = flight->getToDestLong();

            bookingElement["type"] = "Flight";

        } else if (typeid(RentalCarReservation) == typeid(*booking)) {
            bookingElement["id"] = booking->getId();
            bookingElement["price"] = booking->getPrice();
            bookingElement["fromDate"] = booking->getFromDate();
            bookingElement["toDate"] = booking->getToDate();

            bookingElement["travelId"] = booking->getTravelID();

            std::shared_ptr<Travel> travel = findTravel(booking->getTravelID());

            bookingElement["travelId"] = travel->getId();
            bookingElement["customerId"] = travel->getCustomerId();

            std::shared_ptr<Customer> customer = findCustomer(travel->getCustomerId());

            bookingElement["customerName"] = customer->getName();

            shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);

            bookingElement["pickupLocation"] = car->getPickupLocation();
            bookingElement["returnLocation"] = car->getReturnLocation();
            bookingElement["company"] = car->getCompany();
            bookingElement["vehicleClass"] = car->getVehicleClass();
            bookingElement["pickupLatitude"] = car->getPickupLocationLat();
            bookingElement["pickupLongitude"] = car->getPickupLocationLong();
            bookingElement["returnLatitude"] = car->getReturnLocationLat();
            bookingElement["returnLongitude"] = car->getReturnLocationLong();

            bookingElement["type"] = "RentalCar";


        } else if (typeid(HotelBooking) == typeid(*booking)) {
            bookingElement["id"] = booking->getId();
            bookingElement["price"] = booking->getPrice();
            bookingElement["fromDate"] = booking->getFromDate();
            bookingElement["toDate"] = booking->getToDate();

            bookingElement["travelId"] = booking->getTravelID();

            std::shared_ptr<Travel> travel = findTravel(booking->getTravelID());

            bookingElement["travelId"] = travel->getId();
            bookingElement["customerId"] = travel->getCustomerId();

            std::shared_ptr<Customer> customer = findCustomer(travel->getCustomerId());

            bookingElement["customerName"] = customer->getName();

            shared_ptr<HotelBooking> hotel = static_pointer_cast<HotelBooking>(booking);

            bookingElement["hotel"] = hotel->getHotel();
            bookingElement["town"] = hotel->getTown();
            bookingElement["roomType"] = hotel->getRoomType();
            bookingElement["hotelLatitude"] = hotel->getHotelLat();
            bookingElement["hotelLongitude"] = hotel->getHotelLong();

            bookingElement["type"] = "Hotel";
        }
        bookingList.push_back(bookingElement);
        bookingElement.clear();
    }
    ofstream outputStream("savedBookingsPraktikum4.json");
    if (!outputStream) {
        throw runtime_error("JSON Datei konnte nicht erzeugt werden");
    }
    outputStream << bookingList.dump(4);
    outputStream.close();
}

int TravelAgency::test1() {
    int counter = 0;

    for (shared_ptr<Booking> booking : allBookings) {
        shared_ptr<RentalCarReservation> car = static_pointer_cast<RentalCarReservation>(booking);
        if (car) {
            if (car->getCompany() == "Europcar") {
                counter++;
            }
        }
    }
    return counter;
}

int TravelAgency::test2() {
    int counter = 0;

    for (shared_ptr<Booking> booking : allBookings) {
        shared_ptr<FlightBooking> flight = static_pointer_cast<FlightBooking>(booking);
        if (flight) {
            if (flight->getAirline() == "Air France") {
                counter++;
            }
        }
    }
    return counter;
}

int TravelAgency::test3() {
    int counter = 0;

    for (shared_ptr<Booking> booking : allBookings) {
        shared_ptr<HotelBooking> hotel = static_pointer_cast<HotelBooking>(booking);
        if (hotel) {
            if (hotel->getFullRoomType() == "Suite" || hotel->getFullRoomType() == "Appartment") {
                counter++;
            }
        }
    }
    return counter;
}

void TravelAgency::createTravelGraphs(json bookingList) {

    string id{}, pre1ID{}, pre2ID{};
    long travelID{};
    int posSelf{}, posPre1{}, posPre2{};

    for (unsigned int t = 0; t < allTravels.size(); t++) {

        shared_ptr<Graph<shared_ptr<Booking>, 15>> graph(new Graph<shared_ptr<Booking>, 15>);
        int vertexCounter = 0;
        string help[15];
        fill_n(help, 15, "");

        for (unsigned int i = 0; i < bookingList.size(); i++) {

            travelID = bookingList[i].at("travelId");

            if (allTravels[t]->getId() == travelID) {
                id = bookingList[i].at("id");
                vertexCounter++;
                graph->insertVertex(vertexCounter, findBooking(id));
                help[vertexCounter] = id;
            }
        }

        for (unsigned int j = 0; j < bookingList.size(); j++) {

            travelID = bookingList[j].at("travelId");

            if (allTravels[t]->getId() == travelID) {
                id = bookingList[j].at("id");

                for(int h = 0; h < 15; h++) {
                    if (help[h] == id) {
                        posSelf = h;
                    }
                }

                if (bookingList[j].contains("predecessor1")) {
                    pre1ID = bookingList[j].at("predecessor1");

                    for(int h = 0; h < 15; h++) {
                        if (help[h] == pre1ID) {
                            posPre1 = h;
                        }
                    }

                    graph->insertEdge(posPre1, posSelf);
                }

                if (bookingList[j].contains("predecessor2")) {
                    pre2ID = bookingList[j].at("predecessor2");

                    for(int h = 0; h < 15; h++) {
                        if (help[h] == pre2ID) {
                            posPre2 = h;
                        }
                    }

                    graph->insertEdge(posPre2, posSelf);
                }
            }
        }

        allTravels[t]->setGraph(graph);
    }
/*
    for (shared_ptr<Travel> travel : allTravels) {
        cout << travel->getId() << endl;
        travel->checkEnoughHotels();

    }
*/


}

double TravelAgency::getTotalPrice()
{
    double totalPrice = 0;

    for (unsigned int i = 0; i < allBookings.size(); i++) {
        totalPrice = totalPrice + allBookings[i]->getPrice();
    }

    return totalPrice;
}

void TravelAgency::abcAnalyse()
{
    sort(allCustomers.begin(), allCustomers.end(),[](shared_ptr<Customer> c1, shared_ptr<Customer> c2) {return c1->getTotalCustomerPrice() > c2->getTotalCustomerPrice();});
}
