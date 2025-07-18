#pragma once

#include <string>
#include <memory>
#include <vector>

namespace patterns {
namespace creational {
namespace builder {

// Product
class Computer {
public:
    std::string cpu;
    std::string memory;
    std::string storage;
    std::string graphics;
    std::string motherboard;
    std::string powerSupply;
    std::string coolingSystem;
    std::string networkCard;
    int warranty = 0;

    std::string getSpecifications() const;
    double getEstimatedPrice() const;
};

// Builder interface
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;
    virtual ComputerBuilder& setCPU(const std::string& cpu) = 0;
    virtual ComputerBuilder& setMemory(const std::string& memory) = 0;
    virtual ComputerBuilder& setStorage(const std::string& storage) = 0;
    virtual ComputerBuilder& setGraphics(const std::string& graphics) = 0;
    virtual ComputerBuilder& setMotherboard(const std::string& motherboard) = 0;
    virtual ComputerBuilder& setPowerSupply(const std::string& powerSupply) = 0;
    virtual ComputerBuilder& setCoolingSystem(const std::string& cooling) = 0;
    virtual ComputerBuilder& setNetworkCard(const std::string& network) = 0;
    virtual ComputerBuilder& setWarranty(int years) = 0;
    virtual std::unique_ptr<Computer> build() = 0;
};

// Concrete Builder
class ConcreteComputerBuilder : public ComputerBuilder {
private:
    std::unique_ptr<Computer> computer;

public:
    ConcreteComputerBuilder();
    ComputerBuilder& setCPU(const std::string& cpu) override;
    ComputerBuilder& setMemory(const std::string& memory) override;
    ComputerBuilder& setStorage(const std::string& storage) override;
    ComputerBuilder& setGraphics(const std::string& graphics) override;
    ComputerBuilder& setMotherboard(const std::string& motherboard) override;
    ComputerBuilder& setPowerSupply(const std::string& powerSupply) override;
    ComputerBuilder& setCoolingSystem(const std::string& cooling) override;
    ComputerBuilder& setNetworkCard(const std::string& network) override;
    ComputerBuilder& setWarranty(int years) override;
    std::unique_ptr<Computer> build() override;
};

// Director
class ComputerDirector {
private:
    ComputerBuilder& builder;

public:
    ComputerDirector(ComputerBuilder& builder);
    std::unique_ptr<Computer> buildGamingComputer();
    std::unique_ptr<Computer> buildOfficeComputer();
    std::unique_ptr<Computer> buildWorkstationComputer();
};

// SQL Query Builder example
class SQLQuery {
public:
    std::vector<std::string> selectColumns;
    std::string fromTable;
    std::vector<std::string> joins;
    std::vector<std::string> whereConditions;
    std::vector<std::string> groupByColumns;
    std::vector<std::string> havingConditions;
    std::vector<std::string> orderByColumns;
    int limitCount = -1;
    int offsetCount = -1;

    std::string toString() const;
};

class SQLQueryBuilder {
private:
    std::unique_ptr<SQLQuery> query;

public:
    SQLQueryBuilder();
    SQLQueryBuilder& select(const std::vector<std::string>& columns);
    SQLQueryBuilder& from(const std::string& table);
    SQLQueryBuilder& join(const std::string& table, const std::string& condition);
    SQLQueryBuilder& leftJoin(const std::string& table, const std::string& condition);
    SQLQueryBuilder& where(const std::string& condition);
    SQLQueryBuilder& groupBy(const std::vector<std::string>& columns);
    SQLQueryBuilder& having(const std::string& condition);
    SQLQueryBuilder& orderBy(const std::string& column, const std::string& direction = "ASC");
    SQLQueryBuilder& limit(int count);
    SQLQueryBuilder& offset(int count);
    std::unique_ptr<SQLQuery> build();
};

// HTTP Request Builder
struct HttpHeaders {
    std::vector<std::pair<std::string, std::string>> headers;
    
    void add(const std::string& key, const std::string& value);
    std::string get(const std::string& key) const;
    std::string toString() const;
};

class HttpRequest {
public:
    std::string method = "GET";
    std::string url;
    HttpHeaders headers;
    std::string body;
    int timeout = 30000;
    int retries = 0;

    std::string toString() const;
};

class HttpRequestBuilder {
private:
    std::unique_ptr<HttpRequest> request;

public:
    HttpRequestBuilder();
    HttpRequestBuilder& method(const std::string& method);
    HttpRequestBuilder& url(const std::string& url);
    HttpRequestBuilder& header(const std::string& key, const std::string& value);
    HttpRequestBuilder& body(const std::string& body);
    HttpRequestBuilder& json(const std::string& data);
    HttpRequestBuilder& timeout(int ms);
    HttpRequestBuilder& retries(int count);
    std::unique_ptr<HttpRequest> build();

    // Static factory methods
    static HttpRequestBuilder get(const std::string& url);
    static HttpRequestBuilder post(const std::string& url);
    static HttpRequestBuilder put(const std::string& url);
    static HttpRequestBuilder del(const std::string& url);
};

} // namespace builder
} // namespace creational
} // namespace patterns
