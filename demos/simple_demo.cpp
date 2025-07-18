#include <iostream>
#include <memory>

// Just test basic Singleton
#include "creational/singleton/Singleton.h"

using namespace patterns::creational::singleton;

int main() {
    std::cout << "=== C++ Design Patterns Demo ===" << std::endl;
    std::cout << "Testing Singleton Pattern:" << std::endl;
    
    // Test Database Connection Singleton
    auto& db1 = DatabaseConnection::getInstance();
    auto& db2 = DatabaseConnection::getInstance();
    
    std::cout << "Same instance? " << (&db1 == &db2 ? "Yes" : "No") << std::endl;
    
    db1.connect("localhost", "testapp", "pass123", "testdb");
    std::cout << "Connection status: " << (db1.isConnected() ? "Connected" : "Disconnected") << std::endl;
    
    db1.executeQuery("SELECT * FROM users LIMIT 5");
    
    // Test Configuration Manager
    auto& config = ConfigurationManager::getInstance();
    config.setConfigValue("app.name", "Test Application");
    config.setConfigValue("app.version", "1.0.0");
    
    std::cout << "App: " << config.getConfigValue("app.name") 
              << " v" << config.getConfigValue("app.version") << std::endl;
    
    // Test Logger
    auto& logger = Logger::getInstance();
    logger.setLogLevel(Logger::LogLevel::INFO);
    logger.log(Logger::LogLevel::INFO, "Application started successfully");
    logger.log(Logger::LogLevel::WARNING, "This is a warning message");
    
    std::cout << "\nDemo completed successfully!" << std::endl;
    return 0;
}
