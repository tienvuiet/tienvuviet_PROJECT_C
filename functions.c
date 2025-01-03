#include<stdio.h>

#include"functions.h"
//logic ham

void startTheProgram(){
	while(1){
    int choise;
	printf("                      ***Store Management System Using C***\n\n");
	printf("                                CHOOSE YOUR ROLE\n");
	printf("                              =====================\n");
	printf("                              [1] Admin.\n");
	printf("                              [2] Exit the Program.\n");
	printf("                              =====================\n");
	printf("                              Enter The Choise:");
	scanf("%d",&choise);
	fflush(stdin);
	switch (choise){
		case 1:{
			adMin();
			break;
		}
		case 2:{
			endOfTheProgram();
			exit(0);
		}
		default:
        printf("Invalid choice. Please try again.\n");
        break;
	}
	}
}

void adMin(){
	saveAdminCredentials("tienvuviet@gmail.com", "151906");
    inputAdmin();
    system("cls");
    categoryManagement();
}
void endOfTheProgram(){
	printf("                           ***The program has ended***\n\n");
	printf("                                    THANKS A LOT\n");
}
void saveAdminCredentials(const char *email, const char *password) {
    FILE *file = fopen("admin.bin", "wb"); //ghi 
    if (file == NULL) {
        printf("Error: Unable to open file to save credentials.\n");
        return;
    }
    Admin admin; 
    strcpy(admin.email, email); 
    strcpy(admin.password, password); 
    fwrite(&admin, sizeof(Admin), 1, file); // Ghi bien admin vao file
    fclose(file); 
}
int verifyAdminCredentials(const char *email, const char *password) {
    FILE *file = fopen("admin.bin", "rb"); 
    if (file == NULL) { 
        printf("Error: Unable to open file to verify credentials.\n");
        return 0; 
    }
    Admin admin;
    fread(&admin, sizeof(Admin), 1, file); 
    fclose(file); 
    if (strcmp(admin.email, email) == 0 && strcmp(admin.password, password) == 0) {
        return 1; // Neu trung khop tra ve 1 
    }

    return 0; // Neu khong trung tra ve 0 
}
void inputAdmin() {
    char email[100]; 
    char password[100]; 
    printf("\n");
    printf("                                LOGIN\n");
    int loginSuccess = 0; 
    while (!loginSuccess) { 
        printf("                              Enter email: ");
        scanf("%s", email); 
        fflush(stdin); 
        printf("                              Enter password: ");
        scanf("%s", password); 
        fflush(stdin);
        if (verifyAdminCredentials(email, password)) {
            printf("                              Login successful!\n");
            loginSuccess = 1; 
        } else {
            printf("                              Invalid email or password. Please try again.\n");
            printf("                              Note: email:tienvuviet@gmail.com / pass: 151906\n");
        }
    }
}
void categoryManagement(){
    int choises; 
    while(1){
    	printf("\n                                CATEGORY MANAGEMENT:\n");
    	printf("                              1. Add category\n");
    	printf("                              2. View category list\n");
    	printf("                              3. Delete category\n");
    	printf("                              4. Edit category information\n");
    	printf("                              5. Search categories by name\n");
    	printf("                              6. Sort categories by name\n");
    	printf("                              7. Product management\n");
    	printf("                              8. Exit\n");
    	printf("                              SELECT FUNCTION:");
    	scanf("%d",&choises);
    	fflush(stdin); 
    	switch (choises){
    		case 1:{
    			system("cls");
                addCategory();
				break;
			}
			case 2:{
				system("cls");
                viewCategoryList();
				break;
			}
			case 3:{
                system("cls");
                deleteCategory();
				break;
			}
			case 4:{
				system("cls");
                editCategory();
				break;
			}
			case 5:{
				system("cls");
                searchCategoryByName();
				break;
			}
			case 6:{
				system("cls");
				sortCategoriesByName();
				break;
			}
			case 7:{
				system("cls");
                productManagement();
                break;
				
			}
			case 8: {
                system("cls"); 
                startTheProgram();
            } 
			default:
			printf("        Invalid choice. Please try again.\n");
			break;
		}
	}
}
int isDuplicateCategoryID(int id, Category categories[], int count) {
    int i; 
    for (i = 0; i < count; i++) {
        if (categories[i].id == id) {
            return 1; // Tra ve 1 neu ID bi trung
        }
    }
    return 0; // Tra ve 0 neu khong tim thay ID trung
}
int isDuplicateCategoryName(const char *name,Category categories[], int count) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(categories[i].name, name) == 0) {
            return 1; // Tra ve 1 neu ten bi trung
        }
    }
    return 0; // Tra ve 0 neu khong tim thay ten trung
}
void addCategory() {
    FILE *file = fopen("categories.bin", "rb");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }
    Category categories[100]; 
    int count = 0; // Dem so danh muc hien co
    //doc danh sach danh muc hien co tu categories.bin vao mang categories 
    while (fread(&categories[count], sizeof(Category), 1, file)) {
        count++;
        if (count >= 100) {
            printf("Error: Maximum category limit reached.\n");
            fclose(file);
            return;
        }
    }
    fclose(file); 
    // Mo file de ghi danh muc moi
    file = fopen("categories.bin", "ab");//ab mo tep ghi du lieu cuoi tep 
    if (file == NULL) {
        printf("Error: Unable to open file for appending.\n");
        return;
    }
    int numCategories;
    printf("Enter the number of categories you want to add: ");
    // scanf kiem tra so nguyen 0: tra ve 1: so nguyen;0 ko nguyen;EOF loi ket thuc tep
    if (scanf("%d", &numCategories) != 1 || numCategories <= 0) {
        printf("Error: Invalid number of categories.\n");
        fclose(file);
        return;
    }
    getchar(); 
    int i;
    for (i = 0; i < numCategories; i++) {
        Category c;
        int isValid = 0;
        printf("\nAdding category %d/%d:\n", i + 1, numCategories);

        while (!isValid) {
            isValid = 1; // Gia su danh muc hop le
            printf("Enter category ID: ");
            if (scanf("%d", &c.id) != 1) { // Kiem tra ID la so nguyen ko 
                printf("Error: Invalid ID. Please enter a valid number.\n");
                isValid = 0;
                getchar(); 
                continue;
            }
            getchar(); 
            if (isDuplicateCategoryID(c.id, categories, count)) {
                printf("Error: ID %d already exists. Please enter a different ID.\n", c.id);
                isValid = 0;
                continue;
            }
            printf("Enter category name: ");
            fgets(c.name, sizeof(c.name), stdin);
            c.name[strcspn(c.name, "\n")] = '\0'; 
            if (strlen(c.name) == 0) {
                printf("Error: Category name cannot be empty. Please enter a valid name.\n");
                isValid = 0;
                continue;
            }
            if (isDuplicateCategoryName(c.name, categories, count)) {
                printf("Error: Category name '%s' already exists. Please enter a different name.\n", c.name);
                isValid = 0;
                continue;
            }
        }
        // Them danh muc vao mang va ghi vao file
        categories[count++] = c;
        //id,name,c
        fwrite(&c, sizeof(Category), 1, file);
        printf("Category added successfully!\n");
    }

    fclose(file); 
    printf("All categories have been added.\n");
}
void viewCategoryList() {
    FILE *file = fopen("categories.bin", "rb"); 
    if (file == NULL) {
        printf("Error: Unable to open file.\n"); 
        return;
    }
    Category c;
    int maxIdLength = 2;       // Chieu dai lon nhat cua ID
    int maxNameLength = 4;     // Chieu dai lon nhat cua ten danh muc
    //tim do dai max cua id va ten
    while (fread(&c, sizeof(Category), 1, file)) {
        int idLength = snprintf(NULL, 0, "%d", c.id); //tra ve do dai cua id
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(c.name) > maxNameLength) maxNameLength = strlen(c.name);
    }
    int tableWidth = maxIdLength + maxNameLength + 7; 
    rewind(file);//doc lai du lieu tu dau 
    printf("\n");
    printf("                         **** Category List ****\n");
    int i;
    printf("                              ");
    for(i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    //-can trai,*do rong,s chuoi,
    printf("                              | %-*s | %-*s |\n", maxIdLength, "ID", maxNameLength, "Name"); 
    printf("                              ");
    for(i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    while (fread(&c, sizeof(Category), 1, file)) {
        printf("                              | %-*d | %-*s |\n", maxIdLength, c.id, maxNameLength, c.name);
    } 
    printf("                              ");
    for(i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    fclose(file); 
    char option;
    printf("                              Go back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls"); 
        return; // Quay lai CATEGORY MANAGEMENT
    } else if (option == '0') {
        system("cls"); 
        startTheProgram(); // Quay lai Choose Your Role
    } else {
        printf("                              Invalid option. Returning to CATEGORY MANAGEMENT...\n");
        system("cls"); 
    }
}

void deleteCategory() {
    FILE *file = fopen("categories.bin", "rb");
    if (file == NULL) {
        printf("Error: Unable to open file.\n"); 
        return;
    }
    Category categories[100]; // Mang tam luu danh muc
    int count = 0;            // Bien dem so luong danh muc
    while (fread(&categories[count], sizeof(Category), 1, file)) {
        count++;
    }
    fclose(file); 
    if (count == 0) { // Kiem tra neu khong co danh muc
        printf("        No categories available to delete.\n");
        return;
    }
    // Hien thi danh sach danh muc hien co
    int maxIdLength = 2;  
    int maxNameLength = 4; 
    int i; 
    for (i = 0; i < count; i++) {
        int idLength = snprintf(NULL, 0, "%d", categories[i].id);
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(categories[i].name) > maxNameLength) maxNameLength = strlen(categories[i].name);
    }
    int tableWidth = maxIdLength + maxNameLength + 7; 
    printf("\n                         **** Category List ****\n");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    printf("                              | %-*s | %-*s |\n", maxIdLength, "ID", maxNameLength, "Name");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("                              | %-*d | %-*s |\n", maxIdLength, categories[i].id, maxNameLength, categories[i].name);
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    // Nhap ID danh muc can xoa
    int idToDelete;
    printf("        Enter the category ID to delete: ");
    scanf("%d", &idToDelete);
    fflush(stdin);
    // Kiem tra danh muc co ton tai hay khong
    int found = 0;
    for (i = 0; i < count; i++) {
        if (categories[i].id == idToDelete) {
            found = 1;
            char confirmation;
            printf("        Are you sure you want to delete the category with ID %d and Name '%s'? (y/n): ", categories[i].id, categories[i].name);
            scanf(" %c", &confirmation);
            fflush(stdin);
            if (confirmation == 'y' || confirmation == 'Y') {
                // Mo file moi de luu danh muc con lai
                FILE *newFile = fopen("categories_temp.bin", "wb");//w neu tep ton tai noi dung cu se bi xoa trc khi them du lieu 
                if (newFile == NULL) {
                    printf("Error: Unable to open file for writing.\n");
                    return;
                }
                // Ghi cac danh muc khong bi xoa vao file moi
                int j; 
                for (j = 0; j < count; j++) {
                    if (categories[j].id != idToDelete) {
                        fwrite(&categories[j], sizeof(Category), 1, newFile);
                    }
                }
                fclose(newFile);
                // Thay the file cu bang file moi
                remove("categories.bin");
                rename("categories_temp.bin", "categories.bin");
                printf("        Category with ID %d and Name '%s' has been deleted successfully.\n", categories[i].id, categories[i].name);
            } else {
                printf("        Deletion cancelled.\n");
            }
            break;
        }
    }
    if (!found) {
        printf("        Error: Category with ID %d not found.\n", idToDelete);
    }
}
void editCategory() {
    FILE *file = fopen("categories.bin", "rb");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return; 
    }
    printf("\n                         **** Category List ****\n");
    Category c;
    int count = 0; 
    int maxIdLength = 2;      
    int maxNameLength = 4;   
    while (fread(&c, sizeof(Category), 1, file)) {
        count++;
        int idLength = snprintf(NULL, 0, "%d", c.id); // Lay do dai cua ID
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(c.name) > maxNameLength) maxNameLength = strlen(c.name); 
    }
    if (count == 0) { 
        printf("        No categories available to edit.\n");
        fclose(file);
        return;
    }
    int tableWidth = maxIdLength + maxNameLength + 7; // +7 cho 2 dau "|" va khoang trong " | "
    rewind(file); // Quay lai dau file de doc lai du lieu
    printf("                              ");
    int i;
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    printf("                              | %-*s | %-*s |\n", maxIdLength, "ID", maxNameLength, "Name");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    while (fread(&c, sizeof(Category), 1, file)) {
        printf("                              | %-*d | %-*s |\n", maxIdLength, c.id, maxNameLength, c.name);
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    fclose(file); 
    printf("        Enter the category ID to edit: ");
    int idToEdit; 
    scanf("%d", &idToEdit);
    fflush(stdin);
    file = fopen("categories.bin", "rb"); // Mo lai file de doc du lieu
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    Category categories[100]; // Mang tam thoi de luu danh muc
    count = 0;
    int found = 0; // Bien de kiem tra co tim thay danh muc can chinh sua khong
    while (fread(&categories[count], sizeof(Category), 1, file)) {
        if (categories[count].id == idToEdit) {
            found = 1; // Neu tim thay danh muc
            printf("\n        Editing category with ID %d:\n", categories[count].id);
            printf("        Current name: %s\n", categories[count].name);
            // Nhap ten moi (cho phep giu nguyen neu khong nhap)
            printf("        Enter new name (or press Enter to keep current): ");
            char newName[50];
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0'; 
            if (strlen(newName) > 0) { // Neu nguoi dung nhap ten moi
                strcpy(categories[count].name, newName); // Cap nhat ten moi
            }

            printf("        Category updated successfully!\n");
        }
        count++;
    }
    fclose(file); 
    if (!found) { 
        printf("        Error: Category with ID %d not found.\n", idToEdit);
        return;
    }
    file = fopen("categories.bin", "wb");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fwrite(&categories[i], sizeof(Category), 1, file); // Ghi tung danh muc vao file
    }
    fclose(file); 
}
void searchCategoryByName() {
    FILE *file = fopen("categories.bin", "rb"); 
    if (file == NULL) {
        printf("Error: Unable to open file.\n"); 
        return;
    }
    char searchName[50];
    printf("        Enter the category name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
    Category c;
    int found = 0;
    int maxIdLength = 2;       
    int maxNameLength = 4;    
    while (fread(&c, sizeof(Category), 1, file)) {
        if (strstr(c.name, searchName) != NULL) { // Tim kiem ten danh muc
            found = 1;
            int idLength = snprintf(NULL, 0, "%d", c.id); 
            if (idLength > maxIdLength) maxIdLength = idLength;
            if ((int)strlen(c.name) > maxNameLength) maxNameLength = strlen(c.name);
        }
    }
    if (!found) {
        printf("        No categories found with the name containing '%s'.\n", searchName);
        fclose(file);
        return;
    }
    int tableWidth = maxIdLength + maxNameLength + 7; 
    rewind(file); // Quay lai dau tep de doc lai du lieu
    printf("\n");
    printf("                         **** Search Results ****\n");
    int i;
    printf("                              ");
    for(i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    printf("                              | %-*s | %-*s |\n", maxIdLength, "ID", maxNameLength, "Name"); 
    printf("                              ");
    for(i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    while (fread(&c, sizeof(Category), 1, file)) {
        if (strstr(c.name, searchName) != NULL) {
            printf("                              | %-*d | %-*s |\n", maxIdLength, c.id, maxNameLength, c.name);
        }
    }
    printf("                              ");
    for(i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    fclose(file);
    char option;
    printf("                              Go back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls"); 
        return; // Quay lai CATEGORY MANAGEMENT
    } else if (option == '0') {
        system("cls"); 
        startTheProgram(); // Quay lai Choose Your Role
    } else {
        printf("                              Invalid option. Returning to CATEGORY MANAGEMENT...\n");
        system("cls"); 
    }
}
void sortCategoriesByName() {
    FILE *file = fopen("categories.bin", "rb");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    Category categories[100]; // Mang tam de luu cac danh muc
    int count = 0;           
    while (fread(&categories[count], sizeof(Category), 1, file)) {
        count++;
    }
    fclose(file);
    int i;
    for (i = 0; i < count - 1; i++) {
    	int j;
        for (j = i + 1; j < count; j++) {
            if (strcmp(categories[i].name, categories[j].name) > 0) {//strcmp so sanh theo thu tu tu dien 
                Category temp = categories[i];
                categories[i] = categories[j];
                categories[j] = temp;
            }
        }
    }
    int maxIdLength = 2;       
    int maxNameLength = 4;     
    for (i = 0; i < count; i++) {
        int idLength = snprintf(NULL, 0, "%d", categories[i].id);
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(categories[i].name) > maxNameLength) maxNameLength = strlen(categories[i].name);
    }
    int tableWidth = maxIdLength + maxNameLength + 7; 
    printf("\n");
    printf("                         **** Sorted Category List ****\n");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    printf("                              | %-*s | %-*s |\n", maxIdLength, "ID", maxNameLength, "Name");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("                              | %-*d | %-*s |\n", maxIdLength, categories[i].id, maxNameLength, categories[i].name);
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    file = fopen("categories.bin", "wb");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fwrite(&categories[i], sizeof(Category), 1, file);
    }
    fclose(file);
    char option;
    printf("                              Go back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls");
        return; // Quay lai CATEGORY MANAGEMENT
    } else if (option == '0') {
        system("cls");
        startTheProgram(); // Quay lai Choose Your Role
    } else {
        printf("                              Invalid option. Returning to CATEGORY MANAGEMENT...\n");
        system("cls");
    }
}
void productManagement() {
    int choice;
    while (1) {
        printf("\n                        PRODUCT MANAGEMENT:\n");
        printf("                        ====================\n");
        printf("                        1. Add product\n");
        printf("                        2. View products by category\n");
        printf("                        3. Edit products information\n");
        printf("                        4. Delete product\n");
    	printf("                        5. Search product by name\n");
    	printf("                        6. Sort products by price\n");
        printf("                        7. Filter products by price range\n");
        printf("                        8. Exit\n");
        printf("                        Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
            	system("cls");
                addProduct(); 
                break;
            case 2:
            	system("cls");
                viewProductsByCategory(); 
                break;
            case 3:{
            	system("cls");
            	editProductInformation();
				break;
			}
			case 4:{
				system("cls");
				deleteProduct();
				break;
			}
			case 5:{
				system("cls"); 
				searchProductByName();
				break;
			}
			case 6:{
				system("cls");
				sortProductsByPrice(); 
				break;
			}
			case 7:{
				system("cls");
				filterProductsByPriceRange();
				break;
			} 
            case 8:{
            	system("cls");
                return;
			}
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
void addProduct() {
    FILE *categoryFile = fopen("categories.bin", "rb");
    if (categoryFile == NULL) {
        printf("Error: No categories available. Add categories first.\n");
        return; 
    }
    Category category;
    int maxIdLength = 2;       
    int maxNameLength = 4;     
    while (fread(&category, sizeof(Category), 1, categoryFile)) {
        int idLength = snprintf(NULL, 0, "%d", category.id);
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(category.name) > maxNameLength) maxNameLength = strlen(category.name);
    }
    int tableWidth = maxIdLength + maxNameLength + 7; 
    rewind(categoryFile); // Quay lai dau file de in danh sach
    printf("\n");
    printf("                         **** Category List ****\n");
    printf("                              ");
    int i; 
    for ( i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    printf("                              | %-*s | %-*s |\n", maxIdLength, "ID", maxNameLength, "Name"); 
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    while (fread(&category, sizeof(Category), 1, categoryFile)) {
        printf("                              | %-*d | %-*s |\n", maxIdLength, category.id, maxNameLength, category.name); 
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    fclose(categoryFile); 
    FILE *productFile = fopen("products.bin", "ab");//a ghi noi tiep 
    if (productFile == NULL) {
        printf("Error: Unable to open products file.\n");
        return; 
    }
    int categoryId;
    printf("Enter the category ID to add a product: ");
    scanf("%d", &categoryId);
    fflush(stdin);
    // Kiem tra xem ID danh muc co ton tai hay khong
    if (!isCategoryExists(categoryId)) {
        printf("Error: Category ID %d does not exist.\n", categoryId);
        fclose(productFile); 
        return;
    }
    Product p;
    p.categoryId = categoryId; // Luu ID danh muc cho san pham
    printf("Enter product ID: ");
    scanf("%d", &p.id);
    fflush(stdin);
    printf("Enter product name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0'; 
    printf("Enter product price: ");
    scanf("%f", &p.price);
    fflush(stdin);
    printf("Enter product quantity: ");
    scanf("%d", &p.quantity);
    fflush(stdin);
    fwrite(&p, sizeof(Product), 1, productFile);
    printf("Product added successfully!\n");
    fclose(productFile);
}
void viewProductsByCategory() {
    FILE *categoryFile = fopen("categories.bin", "rb");
    FILE *productFile = fopen("products.bin", "rb");
    if (categoryFile == NULL) {
        printf("Error: No categories available.\n");
        return;
    }
    if (productFile == NULL) {
        printf("Error: No products available.\n");
        fclose(categoryFile);
        return;
    }
    Category category;
    Product product;
    int maxIdLength = 10;    
    int maxNameLength = 20;  
    int maxPriceLength = 10;  
    int maxQuantityLength = 10; 
    while (fread(&product, sizeof(Product), 1, productFile)) {
        int idLength = snprintf(NULL, 0, "%d", product.id);
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(product.name) > maxNameLength) maxNameLength = strlen(product.name);
        int priceLength = snprintf(NULL, 0, "%.2f", product.price);
        if (priceLength > maxPriceLength) maxPriceLength = priceLength;
        int quantityLength = snprintf(NULL, 0, "%d", product.quantity);
        if (quantityLength > maxQuantityLength) maxQuantityLength = quantityLength;
    }
    rewind(productFile); 
    while (fread(&category, sizeof(Category), 1, categoryFile)) {
        printf("\n\nProducts in Category: %s (ID: %d)\n", category.name, category.id);
        int tableWidth = maxIdLength + maxNameLength + maxPriceLength + maxQuantityLength + 13; // 13 bao gom 3 '|' và 10 khong trung
        int i;
        for (i = 0; i < tableWidth; i++) printf("=");
        printf("\n");
        printf("| %-*s | %-*s | %-*s | %-*s |\n", 
               maxIdLength, "Product ID", 
               maxNameLength, "Name", 
               maxPriceLength, "Price", 
               maxQuantityLength, "Quantity");
        for (i = 0; i < tableWidth; i++) printf("=");
        printf("\n");
        int found = 0;
        rewind(productFile); 
        while (fread(&product, sizeof(Product), 1, productFile)) {
            if (product.categoryId == category.id) {
                found = 1;
                printf("| %-*d | %-*s | %-*.2f | %-*d |\n", 
                       maxIdLength, product.id, 
                       maxNameLength, product.name, 
                       maxPriceLength, product.price, 
                       maxQuantityLength, product.quantity);
            }
        }
        if (!found) {
            printf("| %-*s |\n", tableWidth - 2, "No products found in this category.");
        }
        for (i = 0; i < tableWidth; i++) printf("=");
        printf("\n");
    }
    fclose(categoryFile);
    fclose(productFile);
    char option;
    printf("\nGo back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls");
        return;
    } else if (option == '0') {
        system("cls");
        startTheProgram();
    } else {
        printf("Invalid option. Returning to CATEGORY MANAGEMENT...\n");
        system("cls");
    }
}
int isCategoryExists(int categoryId) {
    FILE *file = fopen("categories.bin", "rb");
    if (file == NULL) {
        return 0; 
    }
    Category c;
    // Doc tung danh muc va kiem tra ID
    while (fread(&c, sizeof(Category), 1, file)) {
        if (c.id == categoryId) { 
            fclose(file);
            return 1; // Tra ve 1 neu ID ton tai
        }
    }
    fclose(file);
    return 0; // Tra ve 0 neu khong tim thay
}
void editProductInformation() {
    FILE *productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error: No products available to edit.\n");
        return; 
    }
    Product products[100]; // Mang tam de luu cac san pham
    int count = 0;         // So luong san pham trong file
    while (fread(&products[count], sizeof(Product), 1, productFile)) {
        count++;
    }
    fclose(productFile); 
    if (count == 0) { 
        printf("No products available to edit.\n");
        return;
    }
    int maxIdLength = 10;      
    int maxNameLength = 20;     
    int maxPriceLength = 10;    
    int maxQuantityLength = 10; 
    int i; 
    for (i = 0; i < count; i++) {
        int idLength = snprintf(NULL, 0, "%d", products[i].id);
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(products[i].name) > maxNameLength) maxNameLength = strlen(products[i].name);
        int priceLength = snprintf(NULL, 0, "%.2f", products[i].price);
        if (priceLength > maxPriceLength) maxPriceLength = priceLength;
        int quantityLength = snprintf(NULL, 0, "%d", products[i].quantity);
        if (quantityLength > maxQuantityLength) maxQuantityLength = quantityLength;
    }
    int tableWidth = maxIdLength + maxNameLength + maxPriceLength + maxQuantityLength + 13; 
    printf("\n                         **** Product List ****\n");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    printf("                              | %-*s | %-*s | %-*s | %-*s |\n",
           maxIdLength, "Product ID",
           maxNameLength, "Name",
           maxPriceLength, "Price",
           maxQuantityLength, "Quantity");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("                              | %-*d | %-*s | %-*.2f | %-*d |\n",
               maxIdLength, products[i].id,
               maxNameLength, products[i].name,
               maxPriceLength, products[i].price,
               maxQuantityLength, products[i].quantity);
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    int productId;
    printf("Enter the product ID to edit: ");
    scanf("%d", &productId);
    fflush(stdin);
    int found = 0; 
    for (i = 0; i < count; i++) {
        if (products[i].id == productId) {
            found = 1;
            printf("\nEditing product with ID %d:\n", products[i].id);
            printf("Current name: %s\n", products[i].name);
            printf("Current price: %.2f\n", products[i].price);
            printf("Current quantity: %d\n", products[i].quantity);
            printf("Enter new name (or press Enter to keep current): ");
            char newName[50];
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0'; 
            if (strlen(newName) > 0) {
                strcpy(products[i].name, newName);
            }
            printf("Enter new price (or enter 0 to keep current): ");
            float newPrice;
            scanf("%f", &newPrice);
            fflush(stdin);
            if (newPrice > 0) {
                products[i].price = newPrice;
            }
            printf("Enter new quantity (or enter -1 to keep current): ");
            int newQuantity;
            scanf("%d", &newQuantity);
            fflush(stdin);
            if (newQuantity >= 0) {
                products[i].quantity = newQuantity;
            }
            printf("Product updated successfully!\n");
            break;
        }
    }

    if (!found) { 
        printf("Error: Product with ID %d not found.\n", productId);
        return;
    }
    productFile = fopen("products.bin", "wb");
    if (productFile == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fwrite(&products[i], sizeof(Product), 1, productFile);
    }
    fclose(productFile);
}
void deleteProduct() {
    FILE *productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error: No products available to delete.\n");
        return; 
    }
    Product products[100]; // Mang tam de luu cac san pham
    int count = 0;         // So luong san pham trong file
    while (fread(&products[count], sizeof(Product), 1, productFile)) {
        count++;
    }
    fclose(productFile); 
    if (count == 0) { 
        printf("No products available to delete.\n");
        return;
    }
    printf("\n                         **** Product List ****\n");
    int maxIdLength = 10;       
    int maxNameLength = 20;     
    int maxPriceLength = 10;    
    int maxQuantityLength = 10; 
    int i; 
    for (i = 0; i < count; i++) {
        int idLength = snprintf(NULL, 0, "%d", products[i].id);
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(products[i].name) > maxNameLength) maxNameLength = strlen(products[i].name);
        int priceLength = snprintf(NULL, 0, "%.2f", products[i].price);
        if (priceLength > maxPriceLength) maxPriceLength = priceLength;
        int quantityLength = snprintf(NULL, 0, "%d", products[i].quantity);
        if (quantityLength > maxQuantityLength) maxQuantityLength = quantityLength;
    }
    int tableWidth = maxIdLength + maxNameLength + maxPriceLength + maxQuantityLength + 13; // 13 la ky tu phan cach
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    printf("                              | %-*s | %-*s | %-*s | %-*s |\n",
           maxIdLength, "Product ID",
           maxNameLength, "Name",
           maxPriceLength, "Price",
           maxQuantityLength, "Quantity");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("                              | %-*d | %-*s | %-*.2f | %-*d |\n",
               maxIdLength, products[i].id,
               maxNameLength, products[i].name,
               maxPriceLength, products[i].price,
               maxQuantityLength, products[i].quantity);
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    int productId;
    printf("Enter the product ID to delete: ");
    scanf("%d", &productId);
    fflush(stdin);

    int found = 0;
    FILE *tempFile = fopen("products_temp.bin", "wb");
    if (tempFile == NULL) {
        printf("Error: Unable to open temporary file.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        if (products[i].id == productId) {
            found = 1;
            printf("Product with ID %d has been deleted successfully.\n", productId);
            continue; 
        }
        fwrite(&products[i], sizeof(Product), 1, tempFile); // Ghi cac san pham con lai vao file tam
    }
    fclose(tempFile);
    if (!found) {
        printf("Error: Product with ID %d not found.\n", productId);
        remove("products_temp.bin"); 
    } else {
        remove("products.bin"); 
        rename("products_temp.bin", "products.bin"); 
    }
}
void searchProductByName() {
    FILE *productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error: No products available to search.\n");
        return;
    }
    char searchName[50];
    printf("Enter the product name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    Product product;
    int found = 0;
    int maxIdLength = 10;
    int maxNameLength = 20;
    int maxPriceLength = 10;
    int maxQuantityLength = 10;
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (strstr(product.name, searchName) != NULL) {
            found = 1;

            int idLength = snprintf(NULL, 0, "%d", product.id);
            if (idLength > maxIdLength) maxIdLength = idLength;
            if ((int)strlen(product.name) > maxNameLength) maxNameLength = strlen(product.name);
            int priceLength = snprintf(NULL, 0, "%.2f", product.price);
            if (priceLength > maxPriceLength) maxPriceLength = priceLength;
            int quantityLength = snprintf(NULL, 0, "%d", product.quantity);
            if (quantityLength > maxQuantityLength) maxQuantityLength = quantityLength;
        }
    }
    if (!found) {
        printf("No products found with the name containing '%s'.\n", searchName);
        fclose(productFile);
        return;
    }
    int tableWidth = maxIdLength + maxNameLength + maxPriceLength + maxQuantityLength + 13;
    rewind(productFile);
    printf("\n");
    printf("                         **** Search Results ****\n");
    int i;
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    printf("                              | %-*s | %-*s | %-*s | %-*s |\n", 
           maxIdLength, "Product ID", 
           maxNameLength, "Name", 
           maxPriceLength, "Price", 
           maxQuantityLength, "Quantity");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (strstr(product.name, searchName) != NULL) {
            printf("                              | %-*d | %-*s | %-*.2f | %-*d |\n", 
                   maxIdLength, product.id, 
                   maxNameLength, product.name, 
                   maxPriceLength, product.price, 
                   maxQuantityLength, product.quantity);
        }
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("=");
    printf("\n");
    fclose(productFile);
    char option;
    printf("\nGo back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls");
        return;
    } else if (option == '0') {
        system("cls");
        startTheProgram();
    } else {
        printf("Invalid option. Returning to PRODUCT MANAGEMENT...\n");
        system("cls");
    }
}
void sortProductsByPrice() {
    FILE *productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error: No products available to sort.\n");
        return; 
    }
    Product products[100];
    int count = 0; 
    while (fread(&products[count], sizeof(Product), 1, productFile)) {
        count++;
    }
    fclose(productFile); 
    if (count == 0) { 
        printf("No products available to sort.\n");
        return;
    }
    int i; 
    for (i = 0; i < count - 1; i++) {
    	int j; 
        for (j = i + 1; j < count; j++) {
            if (products[i].price > products[j].price) { 
                Product temp = products[i];
                products[i] = products[j]; 
                products[j] = temp;
            }
        }
    }
    int maxIdLength = 10;      
    int maxNameLength = 20;     
    int maxPriceLength = 10;    
    int maxQuantityLength = 10; 
    for (i = 0; i < count; i++) {
        int idLength = snprintf(NULL, 0, "%d", products[i].id); 
        if (idLength > maxIdLength) maxIdLength = idLength;
        if ((int)strlen(products[i].name) > maxNameLength) maxNameLength = strlen(products[i].name); 
        int priceLength = snprintf(NULL, 0, "%.2f", products[i].price); 
        if (priceLength > maxPriceLength) maxPriceLength = priceLength;
        int quantityLength = snprintf(NULL, 0, "%d", products[i].quantity); 
        if (quantityLength > maxQuantityLength) maxQuantityLength = quantityLength;
    }
    int tableWidth = maxIdLength + maxNameLength + maxPriceLength + maxQuantityLength + 13; 
    printf("\n                         **** Sorted Products by Price ****\n");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    printf("                              | %-*s | %-*s | %-*s | %-*s |\n",
           maxIdLength, "Product ID",
           maxNameLength, "Name",
           maxPriceLength, "Price",
           maxQuantityLength, "Quantity");
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("                              | %-*d | %-*s | %-*.2f | %-*d |\n",
               maxIdLength, products[i].id,
               maxNameLength, products[i].name,
               maxPriceLength, products[i].price,
               maxQuantityLength, products[i].quantity);
    }
    printf("                              ");
    for (i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    productFile = fopen("products.bin", "wb");
    if (productFile == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fwrite(&products[i], sizeof(Product), 1, productFile); 
    }
    fclose(productFile); 
    char option;
    printf("\nGo back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls");
        return;
    } else if (option == '0') {
        system("cls");
        startTheProgram();
    } else {
        printf("Invalid option. Returning to PRODUCT MANAGEMENT...\n");
        system("cls");
    }
}
void filterProductsByPriceRange() {
    FILE *productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error: No products available to filter.\n");
        return;
    }
    float minPrice, maxPrice;
    printf("Enter the minimum price: ");
    scanf("%f", &minPrice);
    printf("Enter the maximum price: ");
    scanf("%f", &maxPrice);
    if (minPrice < 0 || maxPrice < 0 || minPrice > maxPrice) {
        printf("Invalid price range. Please try again.\n");
        fclose(productFile);
        return;
    }
    Product product;
    int found = 0; 
    int maxIdLength = 10;     
    int maxNameLength = 20;     
    int maxPriceLength = 10;    
    int maxQuantityLength = 10; 
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (product.price >= minPrice && product.price <= maxPrice) {
            found = 1;
            int idLength = snprintf(NULL, 0, "%d", product.id);
            if (idLength > maxIdLength) maxIdLength = idLength;
            if ((int)strlen(product.name) > maxNameLength) maxNameLength = strlen(product.name);//lay do rong tung cai mot de in ra bang 
            int priceLength = snprintf(NULL, 0, "%.2f", product.price);
            if (priceLength > maxPriceLength) maxPriceLength = priceLength;
            int quantityLength = snprintf(NULL, 0, "%d", product.quantity);
            if (quantityLength > maxQuantityLength) maxQuantityLength = quantityLength;
        }
    }
    if (!found) {
        printf("No products found in the price range %.2f - %.2f.\n", minPrice, maxPrice);
        fclose(productFile);
        return;
    }
    rewind(productFile); 
    int tableWidth = maxIdLength + maxNameLength + maxPriceLength + maxQuantityLength + 13; 
    printf("\n");
    printf("                         **** Products in Price Range %.2f - %.2f ****\n", minPrice, maxPrice);
    printf("                              ");
    int i; 
    for (i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    printf("                              | %-*s | %-*s | %-*s | %-*s |\n", 
           maxIdLength, "Product ID", 
           maxNameLength, "Name", 
           maxPriceLength, "Price", 
           maxQuantityLength, "Quantity");
    printf("                              ");
    for ( i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (product.price >= minPrice && product.price <= maxPrice) {
            printf("                              | %-*d | %-*s | %-*.2f | %-*d |\n", 
                   maxIdLength, product.id, 
                   maxNameLength, product.name, 
                   maxPriceLength, product.price, 
                   maxQuantityLength, product.quantity);
        }
    }
    printf("                              ");
    for ( i = 0; i < tableWidth; i++) printf("="); 
    printf("\n");
    fclose(productFile); 
    char option;
    printf("\nGo back (b) or Exit (0): ");
    scanf(" %c", &option);
    fflush(stdin);
    if (option == 'b' || option == 'B') {
        system("cls"); 
        return;
    } else if (option == '0') {
        system("cls"); 
        startTheProgram();
    } else {
        printf("Invalid option. Returning to PRODUCT MANAGEMENT...\n");
        system("cls");
    }
}
