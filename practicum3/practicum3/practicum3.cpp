#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning (disable:4996)

constexpr int MAX_ROW_LENGTH = 100;

bool saveMatrixInFile(const char* filename, int** matrix, int rowsCount, int colsCount)
{
	std::ofstream outStream(filename);

	if (!outStream.is_open())
	{
		return false;
	}

	for (size_t i = 0; i < rowsCount; i++)
	{
		for (size_t j = 0; j < colsCount; j++)
		{
			outStream << matrix[i][j];
			if (j != colsCount - 1)
				outStream << ',';
		}

		if (i != rowsCount - 1)
			outStream << '|';
	}

	return true;
}

void getMatrixInfo(const char* fileWithMatrix, int& rowsCount, int& colsCount)
{
	std::stringstream strstream(fileWithMatrix);

	rowsCount = 0;
	colsCount = 0;
	bool passedRow = false;
	while (!strstream.eof())
	{
		char ch;
		ch = strstream.get();

		if (ch == ',' && !passedRow)
		{
			colsCount++;
		}

		if (ch == '|')
		{
			passedRow = true;
			rowsCount++;
		}
	}

	rowsCount++;
	colsCount++;
}

int** readMatrix(const char* filename, int& rowsCount, int& colsCount)
{
	std::ifstream toRead(filename);

	if (!toRead.is_open())
	{
		return nullptr;
	}

	char wholeRow[MAX_ROW_LENGTH];
	toRead.getline(wholeRow, MAX_ROW_LENGTH);

	std::stringstream wholeRowStream(wholeRow);

	getMatrixInfo(wholeRow, rowsCount, colsCount);

	int** matrix = new int* [rowsCount];
	for (size_t i = 0; i < rowsCount; i++)
	{
		matrix[i] = new int[colsCount];
	}

	int rowIndex = 0;
	int colIndex = 0;

	while (!wholeRowStream.eof())
	{
		char ch = wholeRowStream.peek();

		if (ch == ',')
		{
			wholeRowStream.ignore();
		}

		if (ch == '|')
		{
			wholeRowStream.ignore();
			colIndex = 0;
			rowIndex++;
			continue;
		}

		wholeRowStream >> matrix[rowIndex][colIndex++];
	}

	return matrix;
}

int** multiplyMatrices(int** matrix1, int** matrix2, size_t rows1, size_t cols1, size_t rows2, size_t cols2)
{
	int** answer = new int* [rows1];

	for (size_t i = 0; i < rows1; i++)
	{
		answer[i] = new int[cols2];
	}

	for (size_t i = 0; i < rows1; i++)
	{
		for (size_t j = 0; j < cols2; j++)
		{
			int sum = 0;
			for (size_t p = 0; p < rows2; p++)
			{
				sum += matrix1[i][p] * matrix2[p][j];
			}
			answer[i][j] = sum;
		}
	}

	return answer;
}
void freeMatrix(int** matrix, int rowsCount)
{
	for (size_t i = 0; i < rowsCount; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}


//02

constexpr int MAX_PRODUCT_NAME_LENGTH = 100;
constexpr int MAX_SUPPLIER_NAME_LENGTH = 100;

enum class ProductCategory
{
	ELECTRONICS,
	CLOTHING,
	BOOKS,
	FOOD,
	BEAUTY
};

struct Product
{
	char name[MAX_PRODUCT_NAME_LENGTH];
	int quantity;
	double price;
	ProductCategory category;
	char supplier[MAX_SUPPLIER_NAME_LENGTH];
};

constexpr int MAX_PRODUCTS_COUNT_IN_WAREHOUSE = 100;

struct Warehouse
{
	Product products[MAX_PRODUCTS_COUNT_IN_WAREHOUSE];
	int productsCount = 0;
};

void printProductCategory(ProductCategory type)
{
	switch (type)
	{
	case ProductCategory::ELECTRONICS:
		std::cout << "Electronics";
		break;
	case ProductCategory::CLOTHING:
		std::cout << "Clothing";
		break;
	case ProductCategory::BOOKS:
		std::cout << "Books";
		break;
	case ProductCategory::FOOD:
		std::cout << "Food";
		break;
	case ProductCategory::BEAUTY:
		std::cout << "Beauty";
		break;
	default:
		break;
	}
}

ProductCategory readProductCategory()
{
	int type;
	std::cin >> type;

	switch (type)
	{
	case 0:
		return ProductCategory::ELECTRONICS;
	case 1:
		return ProductCategory::CLOTHING;
	case 2:
		return ProductCategory::BOOKS;
	case 3:
		return ProductCategory::FOOD;
	case 4:
		return ProductCategory::BEAUTY;

	default:
		break;
	}
}

unsigned getFileSize(std::ifstream& ifs)
{
	unsigned startingIndex = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	unsigned finalIndex = ifs.tellg();

	ifs.seekg(startingIndex);

	return finalIndex;
}

Product readProductFromConsole()
{
	Product p;

	char buffer[MAX_ROW_LENGTH];

	std::cout << "Name: ";
	std::cin.getline(buffer, MAX_ROW_LENGTH);
	std::strcpy(p.name, buffer);

	std::cout << "Quantity: ";
	std::cin >> p.quantity;

	std::cout << "Price: ";
	std::cin >> p.price;

	std::cout << "Category: ";
	p.category = readProductCategory();

	std::cout << "Supplier: ";
	std::cin.ignore();
	std::cin.getline(buffer, MAX_ROW_LENGTH);
	std::strcpy(p.supplier, buffer);

	return p;
}

void readProductsFromConsole(Warehouse& wh, int count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (wh.productsCount == MAX_PRODUCTS_COUNT_IN_WAREHOUSE)
		{
			std::cout << "This warehouse is full!";
			return;
		}

		wh.products[wh.productsCount++] = readProductFromConsole();
	}
}

void saveProductsToFile(const char* filename, const Warehouse& wh)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Problem occured while trying to open file: " << filename;
		return;
	}

	for (size_t i = 0; i < wh.productsCount; i++)
	{
		file.write((char*)&wh.products[i], sizeof(Product));
	}

	file.close();
}

void readProductsFromFile(const char* filename, Warehouse& wh)
{
	std::ifstream ifs(filename);

	if (!ifs.is_open())
	{
		std::cerr << "Problem occured while trying to open file: " << filename;
		return;
	}

	unsigned fileSize = getFileSize(ifs);

	unsigned productsToRead = fileSize / sizeof(Product);
	wh.productsCount = productsToRead;

	ifs.read((char*)wh.products, fileSize);

	ifs.close();
}

void printProduct(const Product& product)
{
	std::cout << "Name: " << product.name << std::endl;
	std::cout << "Quantity: " << product.quantity << std::endl;
	std::cout << "Price: " << product.price << std::endl;
	std::cout << "Category: ";
	printProductCategory(product.category);
	std::cout << std::endl;
	std::cout << "Supplier: " << product.supplier << std::endl;
}

void printProductsInWarehouse(const Warehouse& wh)
{
	for (size_t i = 0; i < wh.productsCount; i++)
	{
		std::cout << "Product " << i + 1 << std::endl;
		printProduct(wh.products[i]);
	}
}

bool isProductValid(const Product& p)
{
	if (!std::strcmp(p.name, "") || p.price == 0 || p.quantity == 0 || !std::strcmp(p.supplier, ""))
	{
		return false;
	}

	return true;
}


int getIndexOfProductInWarehouseByName(const char* productName, const Warehouse& wh)
{
	for (size_t i = 0; i < wh.productsCount; i++)
	{
		if (!std::strcmp(wh.products[i].name, productName))
		{
			return i;
		}
	}

	return -1;
}

bool isValidProductToSaveInWarehouse(const Warehouse& wh, const Product& p)
{
	return (isProductValid(p) && getIndexOfProductInWarehouseByName(p.name, wh) == -1);
}

void addProductsToWarehouseFile(const char* filename, int count)
{
	Warehouse wh;
	readProductsFromFile(filename, wh);

	Product* newProducts = new Product[count];
	for (size_t i = 0; i < count; i++)
	{
		newProducts[i] = readProductFromConsole();

	}

	std::ofstream ofs(filename, std::ios::out | std::ios::binary | std::ios::app);

	if (!ofs.is_open())
	{
		std::cerr << "Problem occured while trying to open file " << filename;
		return;
	}

	for (size_t i = 0; i < count; i++)
	{
		if (isValidProductToSaveInWarehouse(wh, newProducts[i]))
		{
			ofs.write((char*)&newProducts[i], sizeof(Product));
		}
	}

	delete[] newProducts;
}

void changeQuantityOfProductByName(const char* filename, const char* productName, int newQuantity)
{
	Warehouse wh;
	readProductsFromFile(filename, wh);

	std::fstream fs(filename, std::ios::out | std::ios::in | std::ios::beg);

	if (!fs.is_open())
	{
		std::cerr << "Problem occured while trying to open file " << filename;
		return;
	}

	int indexOfProduct = getIndexOfProductInWarehouseByName(productName, wh);

	if (indexOfProduct == -1)
	{
		std::cerr << "This product is not in the warehouse!";
		return;
	}

	Product p;
	fs.seekp(indexOfProduct * sizeof(Product));
	fs.read((char*)&p, sizeof(Product));

	p.quantity = newQuantity;

	fs.seekp(indexOfProduct * sizeof(Product));
	fs.write((char*)&p, sizeof(Product));

	fs.close();
}

Product getProductFromWarehouseByName(const char* filename, const char* productName)
{
	Warehouse wh;
	readProductsFromFile(filename, wh);

	int indexOfProduct = getIndexOfProductInWarehouseByName(productName, wh);

	if (indexOfProduct == -1)
	{
		std::cerr << "This product is not in the warehouse!";
		return {};
	}

	return wh.products[indexOfProduct];
}

void findAndPrintProductFromWarehouseByName(const char* filename, const char* productName)
{
	printProduct(getProductFromWarehouseByName(filename, productName));
}

void filterAndSaveProductsByCategory(const char* sourceFilename, const ProductCategory& cat, const char* destinationFilename)
{
	Warehouse sourceWarehouse;
	readProductsFromFile(sourceFilename, sourceWarehouse);

	Warehouse destinationWarehouse;
	for (size_t i = 0; i < sourceWarehouse.productsCount; i++)
	{
		if (sourceWarehouse.products[i].category == cat)
		{
			destinationWarehouse.products[destinationWarehouse.productsCount++] = sourceWarehouse.products[i];
		}
	}

	saveProductsToFile(destinationFilename,destinationWarehouse);
}

int main()
{
	//01 demo

	/*int firstMatrixRows;
	int firstMatrixCols;
	int secondMatrixRows;
	int secondMatrixCols;
	int** matrix1 = readMatrix("firstMatrix.txt", firstMatrixRows, firstMatrixCols);
	int** matrix2 = readMatrix("secondMatrix.txt", secondMatrixRows, secondMatrixCols);

	int answerMatrixRows = firstMatrixRows;
	int answerMatrixCols = secondMatrixCols;

	int** answerMatrix = multiplyMatrices(matrix1, matrix2, firstMatrixRows, firstMatrixCols, secondMatrixRows, secondMatrixCols);

	saveMatrixInFile("answerMatrix.txt", answerMatrix, answerMatrixRows, answerMatrixCols);


	freeMatrix(matrix1,firstMatrixRows);
	freeMatrix(matrix2,secondMatrixRows);
	freeMatrix(answerMatrix,answerMatrixRows);*/

}
