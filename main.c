#include <stdio.h>
#include <string.h>

typedef struct
{
    char date[11];
    char category[10];
    float amount;
} expenses;

void add_expense(expenses expense, FILE *file);
void view_expense(FILE *file, expenses expense);
void search_expense(FILE *file, expenses expense);
float total_expenses(FILE *file, expenses expense);

int main(void)
{

    expenses expense;
    int choose;
    FILE *file = fopen("page_expenses.csv", "a+");
    if (file == NULL)
    {
        printf("The file didn't open.");
        return 1;
    }
    printf("Expense Tracker.\n");
    printf("1. Add Expence\n");
    printf("2. View Expence\n");
    printf("3. Search Expenses by Date\n");
    printf("4. Show total Expenses\n");
    printf("5. Exit\n");
    printf("\n");
    do
    {
        printf("Choose an option: ");
        scanf("%i", &choose);

        switch (choose)
        {
        case 1:
            add_expense(expense, file);
            printf("\n");
            break;

        case 2:
            view_expense(file, expense);
            printf("\n");
            break;
        case 3:
            search_expense(file, expense);
            printf("\n");
            break;
        case 4:
            float total_price = total_expenses(file, expense);
            printf("TOtal price: %.2f\n", total_price);
            printf("\n");
            break;
        }
    } while (choose != 5);
    fclose(file);
}
void add_expense(expenses expense, FILE *file)
{

    char save_information;
    char choose[10];
    printf("Enter date. like 2026/06/08\n");
    scanf("%10s", expense.date);
    printf("Enter category: ");
    scanf("%9s", expense.category);
    printf("Enter the price: ");
    scanf("%f", &expense.amount);
    printf("Date: %s\n", expense.date);
    printf("Category: %s\n", expense.category);
    printf("Price: %f\n", expense.amount);
    fwrite(&expense, sizeof(expenses), 1, file);
}

void view_expense(FILE *file, expenses expense)
{
    rewind(file);
    while (fread(&expense, sizeof(expenses), 1, file) == 1)
    {
        printf("%s, %s, %.2f\n", expense.date, expense.category, expense.amount);
    }
}

void search_expense(FILE *file, expenses expense)
{
    char date[11];
    printf("Date: ");
    scanf("%s", date);
    int check = 0;
    rewind(file);
    while (fread(&expense, sizeof(expenses), 1, file) == 1)
    {

        if (strcmp(date, expense.date) == 0)
        {
            printf("Date: %s, Categry: %s, Price: %.2f\n", expense.date, expense.category, expense.amount);
            check++;
        }
    }
    if (check == 0)
    {
        printf("There is no expense in this day: %s\n", date);
    }
}

float total_expenses(FILE *file, expenses expense)
{
    char string[30];
    float total_price = 0;
    rewind(file);
    while (fread(&expense, sizeof(expenses), 1, file) == 1)
    {
        total_price = total_price + expense.amount;
    }
    return total_price;
}
