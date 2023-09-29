#include <stdio.h>

struct Store {
    char product[100];
    unsigned int price;
};

struct Store products[100];
unsigned int productCount = 0, totalSpend;

void printCommands() {
    printf("\nList of available commands:\n"
           "'h' - outputs this help information\n"
           "'a' - adds new product to database\n"
           "'l' - lists all products in database\n"
           "'p' - enters purchase mode\n"
           "'t' - outputs total money spent by user\n"
           "'q' - quits program\n\n");
}

void addProduct() {
    printf("Product name:");
    scanf("%s", products[productCount].product);
    printf("Product's unit price:");
    scanf("%u", &products[productCount].price);
    printf("Product added successfully\n");
    productCount++;
}

void listProducts() {
    printf("\n");
    for (int i = 0; i < productCount; i++) {
        printf("Product %d\n"
               "\tName: %s\n"
               "\tPrice: %u USD\n", i, products[i].product, products[i].price);
    }
}

void purchaseProducts() {
    unsigned int index, quantity, spend;
    printf("Enter product index:");
    scanf("%u", &index);

    if (index >= 0 && index <= productCount-1 && 0 != productCount) {
        printf("You are going to purchase %s which costs %d USD. What is the quantity you are looking for?",
               products[index].product, products[index].price);
        scanf("%u", &quantity);
        spend = quantity * products[index].price;
        totalSpend += spend;
        printf("\nProduct purchased successfully. You spent %d USD on it\n", spend);
    } else {
        printf("Product with given index does not exist\n");
    }
}

int main() {

    char command = '_';
    printf("Type 'h' to list available commands\n");

    while (command != 'q') {
        scanf("%c", &command);

        switch (command) {
            case 'h':
                printCommands();
                break;
            case 'a':
                addProduct();
                break;
            case 'l':
                listProducts();
                break;
            case 'p':
                purchaseProducts();
                break;
            case 't':
                printf("Total money spend is %d\n", totalSpend);
                break;
            default:
                continue;
        }

    }

    return 0;
}
