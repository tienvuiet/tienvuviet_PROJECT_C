
//kieu du lieu
#include <stdbool.h>
typedef struct {
    char email[100];
    char password[100];
} Admin;
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    int categoryId; 
} Product;
typedef struct {
	int id;
	char name[50];
} Category;

