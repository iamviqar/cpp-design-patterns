#include "Builder.h"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace patterns {
namespace creational {
namespace builder {

// Computer implementation
std::string Computer::getSpecifications() const {
    std::ostringstream oss;
    oss << "CPU: " << (cpu.empty() ? "Not specified" : cpu) << "\n";
    oss << "Memory: " << (memory.empty() ? "Not specified" : memory) << "\n";
    oss << "Storage: " << (storage.empty() ? "Not specified" : storage) << "\n";
    oss << "Graphics: " << (graphics.empty() ? "Not specified" : graphics) << "\n";
    oss << "Motherboard: " << (motherboard.empty() ? "Not specified" : motherboard) << "\n";
    oss << "Power Supply: " << (powerSupply.empty() ? "Not specified" : powerSupply) << "\n";
    oss << "Cooling: " << (coolingSystem.empty() ? "Not specified" : coolingSystem) << "\n";
    oss << "Network: " << (networkCard.empty() ? "Not specified" : networkCard) << "\n";
    oss << "Warranty: " << warranty << " years";
    return oss.str();
}

double Computer::getEstimatedPrice() const {
    double price = 0.0;
    
    if (cpu.find("i9") != std::string::npos) price += 500;
    else if (cpu.find("i7") != std::string::npos) price += 350;
    else if (cpu.find("i5") != std::string::npos) price += 250;
    
    if (memory.find("32GB") != std::string::npos) price += 300;
    else if (memory.find("16GB") != std::string::npos) price += 150;
    else if (memory.find("8GB") != std::string::npos) price += 75;
    
    if (storage.find("1TB") != std::string::npos) price += 100;
    else if (storage.find("512GB") != std::string::npos) price += 50;
    
    if (graphics.find("RTX") != std::string::npos) price += 800;
    else if (graphics.find("GTX") != std::string::npos) price += 400;
    
    return price;
}

// ConcreteComputerBuilder implementation
ConcreteComputerBuilder::ConcreteComputerBuilder() {
    computer = std::make_unique<Computer>();
}

ComputerBuilder& ConcreteComputerBuilder::setCPU(const std::string& cpu) {
    computer->cpu = cpu;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setMemory(const std::string& memory) {
    computer->memory = memory;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setStorage(const std::string& storage) {
    computer->storage = storage;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setGraphics(const std::string& graphics) {
    computer->graphics = graphics;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setMotherboard(const std::string& motherboard) {
    computer->motherboard = motherboard;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setPowerSupply(const std::string& powerSupply) {
    computer->powerSupply = powerSupply;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setCoolingSystem(const std::string& cooling) {
    computer->coolingSystem = cooling;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setNetworkCard(const std::string& network) {
    computer->networkCard = network;
    return *this;
}

ComputerBuilder& ConcreteComputerBuilder::setWarranty(int years) {
    computer->warranty = years;
    return *this;
}

std::unique_ptr<Computer> ConcreteComputerBuilder::build() {
    auto result = std::move(computer);
    computer = std::make_unique<Computer>(); // Reset for next build
    return result;
}

// ComputerDirector implementation
ComputerDirector::ComputerDirector(ComputerBuilder& builder) : builder(builder) {}

std::unique_ptr<Computer> ComputerDirector::buildGamingComputer() {
    return builder
        .setCPU("Intel i9-13900K")
        .setMemory("32GB DDR5-5600")
        .setStorage("1TB NVMe SSD")
        .setGraphics("NVIDIA RTX 4080")
        .setMotherboard("ASUS ROG Strix Z790-E")
        .setPowerSupply("850W 80+ Gold Modular")
        .setCoolingSystem("AIO Liquid Cooler 280mm")
        .setNetworkCard("Wi-Fi 6E + Ethernet")
        .setWarranty(3)
        .build();
}

std::unique_ptr<Computer> ComputerDirector::buildOfficeComputer() {
    return builder
        .setCPU("Intel i5-13400")
        .setMemory("16GB DDR4-3200")
        .setStorage("512GB SATA SSD")
        .setGraphics("Integrated Intel UHD")
        .setMotherboard("MSI B760M Pro-A")
        .setPowerSupply("500W 80+ Bronze")
        .setCoolingSystem("Stock CPU Cooler")
        .setNetworkCard("Ethernet")
        .setWarranty(1)
        .build();
}

std::unique_ptr<Computer> ComputerDirector::buildWorkstationComputer() {
    return builder
        .setCPU("Intel i7-13700K")
        .setMemory("64GB DDR5-4800")
        .setStorage("2TB NVMe SSD")
        .setGraphics("NVIDIA RTX 4070")
        .setMotherboard("ASUS Pro WS W790-ACE")
        .setPowerSupply("750W 80+ Platinum")
        .setCoolingSystem("Tower Air Cooler")
        .setNetworkCard("Wi-Fi 6 + Dual Ethernet")
        .setWarranty(5)
        .build();
}

// SQLQuery implementation
std::string SQLQuery::toString() const {
    std::ostringstream oss;
    
    if (!selectColumns.empty()) {
        oss << "SELECT ";
        for (size_t i = 0; i < selectColumns.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << selectColumns[i];
        }
    }
    
    if (!fromTable.empty()) {
        oss << " FROM " << fromTable;
    }
    
    for (const auto& join : joins) {
        oss << " " << join;
    }
    
    if (!whereConditions.empty()) {
        oss << " WHERE ";
        for (size_t i = 0; i < whereConditions.size(); ++i) {
            if (i > 0) oss << " AND ";
            oss << whereConditions[i];
        }
    }
    
    if (!groupByColumns.empty()) {
        oss << " GROUP BY ";
        for (size_t i = 0; i < groupByColumns.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << groupByColumns[i];
        }
    }
    
    if (!havingConditions.empty()) {
        oss << " HAVING ";
        for (size_t i = 0; i < havingConditions.size(); ++i) {
            if (i > 0) oss << " AND ";
            oss << havingConditions[i];
        }
    }
    
    if (!orderByColumns.empty()) {
        oss << " ORDER BY ";
        for (size_t i = 0; i < orderByColumns.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << orderByColumns[i];
        }
    }
    
    if (limitCount >= 0) {
        oss << " LIMIT " << limitCount;
    }
    
    if (offsetCount >= 0) {
        oss << " OFFSET " << offsetCount;
    }
    
    return oss.str();
}

// SQLQueryBuilder implementation
SQLQueryBuilder::SQLQueryBuilder() {
    query = std::make_unique<SQLQuery>();
}

SQLQueryBuilder& SQLQueryBuilder::select(const std::vector<std::string>& columns) {
    query->selectColumns = columns;
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::from(const std::string& table) {
    query->fromTable = table;
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::join(const std::string& table, const std::string& condition) {
    query->joins.push_back("JOIN " + table + " ON " + condition);
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::leftJoin(const std::string& table, const std::string& condition) {
    query->joins.push_back("LEFT JOIN " + table + " ON " + condition);
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::where(const std::string& condition) {
    query->whereConditions.push_back(condition);
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::groupBy(const std::vector<std::string>& columns) {
    query->groupByColumns = columns;
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::having(const std::string& condition) {
    query->havingConditions.push_back(condition);
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::orderBy(const std::string& column, const std::string& direction) {
    query->orderByColumns.push_back(column + " " + direction);
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::limit(int count) {
    query->limitCount = count;
    return *this;
}

SQLQueryBuilder& SQLQueryBuilder::offset(int count) {
    query->offsetCount = count;
    return *this;
}

std::unique_ptr<SQLQuery> SQLQueryBuilder::build() {
    auto result = std::move(query);
    query = std::make_unique<SQLQuery>(); // Reset for next build
    return result;
}

// HttpHeaders implementation
void HttpHeaders::add(const std::string& key, const std::string& value) {
    headers.emplace_back(key, value);
}

std::string HttpHeaders::get(const std::string& key) const {
    for (const auto& header : headers) {
        if (header.first == key) {
            return header.second;
        }
    }
    return "";
}

std::string HttpHeaders::toString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < headers.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << headers[i].first << ": " << headers[i].second;
    }
    return oss.str();
}

// HttpRequest implementation
std::string HttpRequest::toString() const {
    std::ostringstream oss;
    oss << method << " " << url << "\n";
    oss << "Headers: " << headers.toString() << "\n";
    oss << "Timeout: " << timeout << "ms\n";
    oss << "Retries: " << retries;
    if (!body.empty()) {
        oss << "\nBody: " << body;
    }
    return oss.str();
}

// HttpRequestBuilder implementation
HttpRequestBuilder::HttpRequestBuilder() {
    request = std::make_unique<HttpRequest>();
}

HttpRequestBuilder& HttpRequestBuilder::method(const std::string& method) {
    request->method = method;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::url(const std::string& url) {
    request->url = url;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::header(const std::string& key, const std::string& value) {
    request->headers.add(key, value);
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::body(const std::string& body) {
    request->body = body;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::json(const std::string& data) {
    request->body = data;
    request->headers.add("Content-Type", "application/json");
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::timeout(int ms) {
    request->timeout = ms;
    return *this;
}

HttpRequestBuilder& HttpRequestBuilder::retries(int count) {
    request->retries = count;
    return *this;
}

std::unique_ptr<HttpRequest> HttpRequestBuilder::build() {
    auto result = std::move(request);
    request = std::make_unique<HttpRequest>(); // Reset for next build
    return result;
}

// Static factory methods
HttpRequestBuilder HttpRequestBuilder::get(const std::string& url) {
    HttpRequestBuilder builder;
    return builder.method("GET").url(url);
}

HttpRequestBuilder HttpRequestBuilder::post(const std::string& url) {
    HttpRequestBuilder builder;
    return builder.method("POST").url(url);
}

HttpRequestBuilder HttpRequestBuilder::put(const std::string& url) {
    HttpRequestBuilder builder;
    return builder.method("PUT").url(url);
}

HttpRequestBuilder HttpRequestBuilder::del(const std::string& url) {
    HttpRequestBuilder builder;
    return builder.method("DELETE").url(url);
}

} // namespace builder
} // namespace creational
} // namespace patterns
