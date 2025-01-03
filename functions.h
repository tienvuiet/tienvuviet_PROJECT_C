#include"datatypes.h"
//nguyen mau ham
void startTheProgram();
//admin
void adMin() ;
void saveAdminCredentials(const char *email, const char *password);
int verifyAdminCredentials(const char *email, const char *password);
void inputAdmin();
void endOfTheProgram();
// danh muc 
int isDuplicateCategoryID(int id,Category categories[], int count);
int isDuplicateCategoryName(const char *name, Category categories[], int count);
void addCategory();
void viewCategoryList();
void deleteCategory();
void editCategory();
void searchCategoryByName();
void sortCategoriesByName();
// san pham trong danh muc 
void productManagement();
void addProduct();
void viewProductsByCategory();
int isCategoryExists(int categoryId);
void editProductInformation();
void deleteProduct();
void searchProductByName();
void sortProductsByPrice();
void filterProductsByPriceRange();
