#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char name[100];
    int quantity;
    float price;
} item;

typedef struct
{
    int id;
    int quantity;
} cart;

item inventory[100];
item sold[100];

int itemCount = 0;
int saleCount = 0;
float totalSales = 0;

int login();
int loggedIn = 0;
int isUnique(int id);
int findIndex(int id);
int calculate(float price, int quantity);
void add();
void update();
void display();
void inventoryManagment();
void customerBilling();

int login()
{
    char user[100];
    printf("Enter username: ");
    scanf("%s", user);
    int pin;
    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (strcmp(user, "admin") == 0 && pin == 1234)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isUnique(int id)
{
    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == id)
        {
            return 0;
        }
    }
    return 1;
}

int findIndex(int id)
{
    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void add()
{
    int temp;
    printf("Enter product's ID: ");
    scanf("%d", &temp);

    if (isUnique(temp))
    {
        inventory[itemCount].id = temp;
        printf("Enter Product's name, price, and quantity: ");
        scanf("%s %f %d", inventory[itemCount].name, &inventory[itemCount].price, &inventory[itemCount].quantity);
        itemCount++;
    }
    else
    {
        printf("Duplicate Product ID. Please enter a unique ID\n");
    }
}

void update()
{
    int temp, i;
    printf("Enter the product ID to update: ");
    scanf("%d", &temp);

    i = findIndex(temp);

    if (i > -1)
    {
        printf("Enter the new quantity and price for %s: ", inventory[i].name);
        scanf("%d %.2f", &inventory[i].quantity, &inventory[i].price);
    }
    else
    {
        printf("Product does not exist with that ID\n");
    }
}

void display()
{
    printf("\nID\tName\t\tPrice\t\tQuantity\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < itemCount; i++)
    {
        printf("%d\t%-15s\t%.2f\t\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    printf("-----------------------------------------------\n");
}

void inventoryManagment()
{
    int pick;
    if (!loggedIn)
    {
        if (login())
        {
            loggedIn = 1;
            printf("Login successful\n");
        }
        else
        {
            printf("Wrong username or PIN. Exiting.\n");
            return;
        }
    }

    printf("-----Inventory Management-----\n \t 1. Add Item\n \t 2. Update Item\n \t 3. Display Items\n \t 4. Customer Billing\n\t 5. Show Sold Items\n\t 0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &pick);

    switch (pick)
    {
    case 1:
        add();
        break;
    case 2:
        update();
        break;
    case 3:
        display();
        break;
    case 4:
        customerBilling();
        break;
    case 5:
        showSoldItems();
        break;
    case 0:
        exit(0);
    default:
        printf("Invalid choice.\n");
    }
}

void customerBilling()
{
    float VAT_RATE = 0.10;
    int n, id, qty, index;
    cart data[800];
    float total = 0;

    printf("Enter number of items to buy: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Item ID and Quantity: ");
        scanf("%d %d", &id, &qty);

        index = findIndex(id);

        if (index == -1)
        {
            printf("Item ID %d not found.\n", id);
            i--;
            continue;
        }

        if (qty > inventory[index].quantity)
        {
            printf("Insufficient stock for %s.\n", inventory[index].name);
            i--;
            continue;
        }

        inventory[index].quantity -= qty;
        data[i].id = id;
        data[i].quantity = qty;

        sold[saleCount].id = id;
        strcpy(sold[saleCount].name, inventory[index].name);
        sold[saleCount].price = inventory[index].price;
        sold[saleCount].quantity = qty;

        total += inventory[index].price * qty;
        saleCount += qty;
    }

    float vat = total * VAT_RATE;
    float finalTotal = total + vat;

    totalSales += finalTotal;

    printf("\n--- Bill Summary ---\n");
    for (int i = 0; i < n; i++)
    {
        index = findIndex(data[i].id);
        printf("%s x %d = %.2f\n", inventory[index].name, data[i].quantity, inventory[index].price * data[i].quantity);
    }

    printf("Subtotal: %.2f\nVAT (10%%): %.2f\nTotal: %.2f\n", total, vat, finalTotal);
}
void showSoldItems()
{
    if (saleCount == 0)
    {
        printf("No items sold yet.\n");
        return;
    }
    printf("\n--- Sold Items ---\n");
    printf("ID\tName\t\tPrice\t\tQuantity\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < saleCount; i++)
    {
        printf("%d\t%-15s\t%.2f\t\t%d\n", sold[i].id, sold[i].name, sold[i].price, sold[i].quantity);
    }
    printf("-----------------------------------------------\n");
}
int main()
{
    while (1)
    {
        inventoryManagment();
    }
    return 0;
}
