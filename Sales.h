#pragma once



#include "Customer.h"
#include "Reservation.h"
#include "Inventory.h"



typedef enum { eNone, eResCode, eCustomerName, eDate, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];



typedef struct
{
    LIST                    customersList;
    struct Reservation**    reservationArray;
    int                     reservationCount;
    eSortOption	            ReservationSortOpt;


    
    //Inventory* inventory;
   
  

}Sales;



void        initSales(Sales* pSales);
void        freeSales(Sales* pSales);


/// <summary>
/// Client funcs
int         addNewCustomer(Sales* pSales);
Customer*   initCustomer(Sales* pSales);
Customer*   findCustomerByName(const Sales* pSales, const char* name);
int         uniqeNameCheck(const char* name, const Sales* pSales);
int         customerCompare(const void* data1, const void* data2);//name comperator
//int         pickCustomerFromList(const Sales* pSales);//print all clients 

void        printAllCustomers(const Sales* pSales);



/// <summary>
/// /Res funcs
 

//int        makeNewReservationForCustomer(Sales* pSales, Customer* pCustomer);

int         addNewReservationToArray(Sales* pSales, Customer* pCustomer, char* itemsList, int itemsPrice);

void        printReservationsArr(Reservation** array ,int size);

void        freeReservationsArr(Reservation** array, int size);



eSortOption showSortMenu();
void        findReservation(const Sales* pSales); //bsearch- 1)ResCode  2)clientName   3)date?
void        sortReservations(Sales* pSales);
