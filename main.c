#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>


#include "main.h"
#include "GeneralFunctions.h"
#include "Filefunctions.h"
#include "BinaryFunctions.h"
#include "Shop.h"
#include "Inventory.h"
#include "Beer.h"
#include "Wine.h"
#include "Sales.h"
#include "Customer.h"
#include "list.h"
#include "Reservation.h"
#include "Date.h"
#include "BinaryFunctions.h"
#include "BringThemHome.h"





int main()
{
    printf("HELLO AND WELLCOME TO THE LIQUOR STORE:\n");
    Shop theShop;
    Inventory inventory;
    Sales sales;

    initSystemFromFiles(&theShop, &sales, &inventory);


   
    double totalRevenue = 0.0;
    int option;
    int stop = 0;

    do
    {
        option = menu();
        switch (option)
        {
        case ePrintInventory:
            printInventory(&inventory);
            break;
        case ePrintReservations:
            printReservationsArr(theShop.salesDepartment->reservationArray, theShop.salesDepartment->reservationCount);
            break;
        case ePrintCustomers:
            printAllCustomers(theShop.salesDepartment);
            break;
        case eAddBeveragesToInventory:
            if (!addBeveragesToInventory(&inventory))
                printf("Error adding beverages to inventory\n");
            break;
            case eRefillInventory:
                if (!handleRefillInventory(&inventory)) {
                    printf("Error refilling inventory\n");
                }
               
                break;
        case eAddClient:
            if (!addNewCustomer(theShop.salesDepartment))
                printf("Error adding client\n");
            break;
        case eMakeReservation:
            if (!addNewReservationToArray2(theShop.salesDepartment, theShop.inventory,getCustomerForReservation(theShop.salesDepartment)))//not good template
                    printf("Error making reservation\n");
            break;
        case eSortReservationArray:
            sortReservations(&sales);
            break;
        case eFindReservation:
            findReservation(&sales);
            break;
        case ecalculateTotalRevenue:          
            printTotalRevenue(&theShop, SHOP_BASE_BUDGET);
            break;
        case eTopNCustomers:
            findTopCustomers(theShop.salesDepartment, FIND_TOP_N_CLIENTS);
            break;
            case eBringThemHome:
                BringThemHomeNow(&inventory);
                break;
        case EXIT:
            printf("Bye bye\n");
            stop = 1;
            break;
        default:
            printf("Wrong option\n");
            break;
        }
    } while (!stop);

    saveShopToTextFile(&theShop,(FILE*) INVENTORY_FILE_NAME, (FILE*)CUSTOMER_LIST_TEXT_FILE_SAVE_NAME, (FILE*)RESERVATIONS_ARR_TEXT_FILE_SAVE_NAME);
    saveShopToBianryFile(&theShop, (FILE*)INVENTORY_BINARY_FILE_NAME, (FILE*)CUSTOMER_LIST_BINARY_FILE_SAVE_NAME, (FILE*)RESERVATIONS_ARR_BINARY_FILE_SAVE_NAME);//(FILE*)CUSTOMER_LIST_BINARY_FILE_LOAD_NAME, (FILE*)RESERVATIONS_ARR_BINARY_FILE_LOAD_NAME//

    freeShop(&theShop);
   
   
    _CrtDumpMemoryLeaks();
    return 1;
}




void initSystemFromFiles(Shop* pShop, Sales* pSales, Inventory* pInventory)
{
    int choice;
    int validChoice = 0;

    while (!validChoice)
    {
        printf("Select the file format to load from:\n");
        printf("1. Text files\n");
        printf("2. Binary files\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Load from text files
            if (!initCustomerListFromTextFile(pSales, "customer_list_saveTo.txt"))
            {
                printf("Failed to load customers from text file.\n");
                return;
            }
            if (!initInventoryFromTextFile(pInventory, "Inventory.txt"))
            {
                printf("Failed to load inventory from text file.\n");
                return;
            }
            if (!loadReservationsArrayFromTextFile(pSales, "reservation_arr_saveTo.txt"))
            {
                printf("Failed to load reservations from text file.\n");
                return;
            }
            printf("System loaded successfully from text files.\n");
            validChoice = 1;
            break;

        case 2:
            // Load from binary files
            if (!readCustomerListFromBFile(pSales, "BinaryCustomerSaveTo.bin"))
            {
                printf("Failed to load customers from binary file.\n");
                return;
            }
            if (!initInventoryFromBinaryFile(pInventory, "Inventory.bin"))
            {
                printf("Failed to load inventory from binary file.\n");
                return;
            }
            if (!loadReservationsArrayFromBinaryFile(pSales, "BinaryReservationSaveTo.bin"))
            {
                printf("Failed to load reservations from binary file.\n");
                return;
            }
            printf("System loaded successfully from binary files.\n");
            validChoice = 1;
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    initShop(pShop, pInventory, pSales, SHOP_BASE_BUDGET);
}







int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit (And Save System To Text & Binary Files) \n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

