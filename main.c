#include <stdio.h>
#include <string.h>


typedef struct{
int id;
char name[100];
int quantity;
float price;
}item;

item inventory[100];
item sold[100];

int itemCount=0;
int saleCount=0;

int login();
int isUnique(int id);
int findIndex(int id);
int calculate(float price,int quantity);
int choose(int quantity);
void add();
void update();
void display();
void stockUpdate();


void inventoryManagment();
void customerBilling();
void dailySalesUpdates();

int main() {


 return 0;
}

int login() {
    char user[100];
    printf("Enter user name: ");
    scanf("%s",&user);
    int pin;
    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (strcmp(user, "admin") == 0 && pin == 1234) {
        return 1;
    } else {
        return 0;
    }
}


int isUnique(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id)
            return 0;
    }
    return 1;
}

int findIndex(int id)
{
    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == id)
            return i;
    }
    return -1;
}

void add()
{
  int temp;
  printf("Enter product's ID: ");
  scanf("%d",&temp);

  if(isUnique(temp)){
      inventory[itemCount].id = temp;
      printf("Enter Products name, price and quantity : ");
      scanf("%s %f %d",&inventory[itemCount].name,&inventory[itemCount].price,&inventory[itemCount].quantity);
      itemCount++;
  }
  else{
    printf("Duplicate Product ID, Please enter an unique ID");
  }
}

void update()
{
    int temp,i;
    printf("Enter The product ID to update: ");
    scanf("%d",&temp);

    i=findIndex(temp);

    if(i>-1){
        printf("Enter the new quantity and price of %s: ",inventory[i].name);
        scanf("%d %.2f",&inventory[i].quantity,&inventory[i].price);

    }
    else{
        printf("Product does not exist with that ID");
    }
}
void display() {
    printf("\nID\tName\t\tPrice\t\tQuantity\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-15s\t%.2f\t\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    printf("-----------------------------------------------\n");
}
void inventoryManagment()
{
    int pick;
    if(login()){
        printf("-----Inventory Management-----\n \t 1.Add Item\n \t 2.Update Item\n \t 3.Display Item\n");
        printf("Enter your choice: ");
        scanf("%d",&pick);

        switch(pick){
            case 1: add();
                      break;
            case 2: update();
                      break;
            case 3: display();
                      break;
            default: printf("Invalid choice.\n");
        }
    }
    else{
        printf("Wrong User name or PIN");
    }
}


