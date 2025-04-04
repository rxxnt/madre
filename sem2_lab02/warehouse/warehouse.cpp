#include "warehouse.h"

// warehouse.cpp
#include <cmath>
#include <algorithm>

int Warehouse::nextWarehouseCode = 100;

std::ostream& operator<<(std::ostream& os, const WarehouseType& type) {
    switch (type) {
        case WarehouseType::CENTER:
            os << "Center";
            break;
        case WarehouseType::WEST:
            os << "West";
            break;
        case WarehouseType::EAST:
            os << "East";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

// Реализация класса Product
Product::Product() : barcode(generateBarcode()), description(""), price(0.0), quantity(0), shipmentLatitude(0.0), shipmentLongitude(0.0) {}

Product::Product(const std::string& description, double price, int quantity, double shipmentLatitude, double shipmentLongitude)
    : barcode(generateBarcode()), description(description.substr(0, 50)), price(price), quantity(quantity), shipmentLatitude(shipmentLatitude), shipmentLongitude(shipmentLongitude) {}

Product::Product(const Product& other) : barcode(other.barcode), description(other.description), price(other.price), quantity(other.quantity), shipmentLatitude(other.shipmentLatitude), shipmentLongitude(other.shipmentLongitude) {}

std::string Product::getBarcode() const {
    return barcode;
}

std::string Product::getDescription() const {
    return description;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

double Product::getShipmentLatitude() const {
    return shipmentLatitude;
}

double Product::getShipmentLongitude() const {
    return shipmentLongitude;
}

void Product::setDescription(const std::string& description) {
    this->description = description.substr(0, 50);
}

void Product::setPrice(double price) {
    this->price = price;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Product::setShipmentLatitude(double shipmentLatitude) {
    if (shipmentLatitude >= 41.0 && shipmentLatitude <= 82.0) {
        this->shipmentLatitude = shipmentLatitude;
    } else {
        std::cerr << "Error: Incorrect latitude of transportation (" << shipmentLatitude << "). Must be in the range [41, 82]." << std::endl;
    }
}

void Product::setShipmentLongitude(double shipmentLongitude) {
    if (shipmentLongitude >= 19.0 && shipmentLongitude <= 169.0) {
        this->shipmentLongitude = shipmentLongitude;
    } else {
        std::cerr << "Error: Incorrect longitude of transportation (" << shipmentLongitude << "). Must be in the range [19, 169]." << std::endl;
    }
}

void Product::print() const {
    std::cout << "  Barcode: " << barcode << std::endl;
    std::cout << "  Description: " << description << std::endl;
    std::cout << "  Price: " << std::fixed << std::setprecision(2) << price << " руб." << std::endl;
    std::cout << "  Quantity: " << quantity << std::endl;
    std::cout << "  Latitude shipment: " << std::fixed << std::setprecision(6) << shipmentLatitude << std::endl;
    std::cout << "  Longtitude shipment: " << std::fixed << std::setprecision(6) << shipmentLongitude << std::endl;
}

// Implementation of class Warehouse
Warehouse::Warehouse() : id(generateWarehouseId()), type(WarehouseType::CENTER), latitude(0.0), longitude(0.0), maxCapacity(100), totalStock(0), products() {}

Warehouse::Warehouse(WarehouseType type, double latitude, double longitude, int maxCapacity)
    : id(generateWarehouseId()), type(type), latitude(latitude), longitude(longitude), maxCapacity(maxCapacity), totalStock(0), products() {
    if (latitude < 41.0 || latitude > 82.0 || longitude < 19.0 || longitude > 169.0) {
        std::cerr << "Error: Incorrect warehouse coordinates (" << latitude << ", " << longitude << ").They must be located within Russia." << std::endl;
        // You can throw an exception or set default values.
    }
    if (maxCapacity <= 0) {
        std::cerr << "Error: The maximum capacity should be positive." << std::endl;
        this->maxCapacity = 100; // Setting the default value
    }
}

Warehouse::Warehouse(const Warehouse& other)
    : id(other.id), type(other.type), latitude(other.latitude), longitude(other.longitude), maxCapacity(other.maxCapacity), totalStock(other.totalStock), products(other.products) {}

Warehouse::~Warehouse() {}

std::string Warehouse::getId() const {
    return id;
}

WarehouseType Warehouse::getType() const {
    return type;
}

double Warehouse::getLatitude() const {
    return latitude;
}

double Warehouse::getLongitude() const {
    return longitude;
}

int Warehouse::getMaxCapacity() const {
    return maxCapacity;
}

int Warehouse::getTotalStock() const {
    return totalStock;
}

const std::vector<Product>& Warehouse::getProducts() const {
    return products;
}

double Warehouse::calculateManhattanDistance(double productLatitude, double productLongitude) const {
    return std::abs(latitude - productLatitude) + std::abs(longitude - productLongitude);
}

bool Warehouse::hasSpace(int quantity) const {
    return (totalStock + quantity) <= maxCapacity;
}

void Warehouse::addProduct(const Product& product) {
    if (hasSpace(product.getQuantity())) {
        products.push_back(product);
        totalStock += product.getQuantity();
        std::cout << "Product \"" << product.getDescription() << "\" added to the warehouse " << id << " (" << type << ")." << std::endl;
    } else {
        std::cout << "Error: Insufficient warehouse space  " << id << " (" << type << ") for " << product.getQuantity() << " product units \"" << product.getDescription() << "\"." << std::endl;
    }
}

bool Warehouse::removeProduct(const std::string& description, int quantityToRemove) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getDescription() == description) {
            if (it->getQuantity() >= quantityToRemove) {
                it->setQuantity(it->getQuantity() - quantityToRemove);
                totalStock -= quantityToRemove;
                std::cout << quantityToRemove << " единиц продукта \"" << description << "\" удалено со склада " << id << " (" << type << ")." << std::endl;
                if (it->getQuantity() == 0) {
                    products.erase(it);
                }
                return true;
            } else {
                std::cout << "Error: In the warehouse " << id << " (" << type << ") insufficient quanity \"" << description << "\". Available: " << it->getQuantity() << ", requsted: " << quantityToRemove << "." << std::endl;
                return false;
            }
        }
    }
    std::cout << "Error: Product \"" << description << "\" not found " << id << " (" << type << ")." << std::endl;
    return false;
}

void Warehouse::listProducts() const {
    if (products.empty()) {
        std::cout << "Warehouse " << id << " (" << type << ") is empty." << std::endl;
        return;
    }
    std::cout << "List of products in stock " << id << " (" << type << "):" << std::endl;
    for (const auto& product : products) {
        product.print();
        std::cout << "----------" << std::endl;
    }
    std::cout << "Total stock: " << totalStock << "/" << maxCapacity << std::endl;
}

void Warehouse::searchProduct(const std::string& description) const {
    bool found = false;
    std::cout << "Search results for \"" << description << "\" in warehouse " << id << " (" << type << "):" << std::endl;
    for (const auto& product : products) {
        if (product.getDescription().find(description) != std::string::npos) {
            product.print();
            std::cout << "----------" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Products with a description containing \"" << description << "\", not found in the warehouse " << id << " (" << type << ")." << std::endl;
    }
}

void Warehouse::updateStock() {
    totalStock = 0;
    for (const auto& product : products) {
        totalStock += product.getQuantity();
    }
}

// Support functions
int generateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

double generateRandomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}

std::string generateBarcode() {
    std::string barcode = "460";
    int middlePartOptions[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
    barcode += std::to_string(middlePartOptions[generateRandomInt(0, 8)]);
    for (int i = 0; i < 6; ++i) {
        barcode += std::to_string(generateRandomInt(0, 9));
    }
    return barcode;
}

std::string generateWarehouseId() {
    std::string id = "W";
    std::string code = std::to_string(Warehouse::nextWarehouseCode++);
    while (code.length() < 3) {
        code = "0" + code;
    }
    id += code;
    return id;
}
