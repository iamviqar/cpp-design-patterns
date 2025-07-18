/**
 * @file Singleton.h
 * @brief Singleton Pattern Implementation
 * 
 * Ensures a class has only one instance and provides global access to it.
 * Thread-safe implementation using modern C++ features.
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <atomic>

namespace CreationalPatterns {

/**
 * @class Singleton
 * @brief Basic thread-safe Singleton implementation
 */
class Singleton {
private:
    static std::unique_ptr<Singleton> instance_;
    static std::mutex mutex_;
    
    std::vector<std::string> data_;
    std::chrono::system_clock::time_point timestamp_;
    
    // Private constructor
    Singleton() : timestamp_(std::chrono::system_clock::now()) {
        std::cout << "Singleton instance created at: " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                       timestamp_.time_since_epoch()).count() << "ms" << std::endl;
    }

public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    // Delete move constructor and assignment operator
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    
    /**
     * @brief Get the singleton instance (thread-safe)
     * @return Reference to the singleton instance
     */
    static Singleton& getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = std::unique_ptr<Singleton>(new Singleton());
        }
        return *instance_;
    }
    
    /**
     * @brief Add data to the singleton
     * @param item Data item to add
     */
    void addData(const std::string& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        data_.push_back(item);
    }
    
    /**
     * @brief Get all data from the singleton
     * @return Vector of data items
     */
    std::vector<std::string> getData() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_;
    }
    
    /**
     * @brief Get creation timestamp
     * @return Timestamp when singleton was created
     */
    std::chrono::system_clock::time_point getTimestamp() const {
        return timestamp_;
    }
    
    /**
     * @brief Clear all data
     */
    void clearData() {
        std::lock_guard<std::mutex> lock(mutex_);
        data_.clear();
    }
    
    /**
     * @brief Get data count
     * @return Number of data items
     */
    size_t getDataCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_.size();
    }
};

/**
 * @class ConfigManager
 * @brief Configuration manager singleton for application settings
 */
class ConfigManager {
private:
    static std::unique_ptr<ConfigManager> instance_;
    static std::mutex mutex_;
    
    std::unordered_map<std::string, std::string> config_;
    
    ConfigManager() {
        // Initialize default configuration
        config_["api_url"] = "https://api.example.com";
        config_["timeout"] = "5000";
        config_["retries"] = "3";
        config_["debug"] = "false";
        config_["max_connections"] = "100";
    }

public:
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    ConfigManager(ConfigManager&&) = delete;
    ConfigManager& operator=(ConfigManager&&) = delete;
    
    static ConfigManager& getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = std::unique_ptr<ConfigManager>(new ConfigManager());
        }
        return *instance_;
    }
    
    /**
     * @brief Get configuration value
     * @param key Configuration key
     * @return Configuration value or empty string if not found
     */
    std::string get(const std::string& key) const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = config_.find(key);
        return (it != config_.end()) ? it->second : "";
    }
    
    /**
     * @brief Set configuration value
     * @param key Configuration key
     * @param value Configuration value
     */
    void set(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        config_[key] = value;
    }
    
    /**
     * @brief Get all configuration as a map
     * @return Copy of all configuration settings
     */
    std::unordered_map<std::string, std::string> getAll() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return config_;
    }
    
    /**
     * @brief Check if configuration key exists
     * @param key Configuration key
     * @return True if key exists, false otherwise
     */
    bool hasKey(const std::string& key) const {
        std::lock_guard<std::mutex> lock(mutex_);
        return config_.find(key) != config_.end();
    }
    
    /**
     * @brief Remove configuration key
     * @param key Configuration key to remove
     * @return True if key was removed, false if it didn't exist
     */
    bool remove(const std::string& key) {
        std::lock_guard<std::mutex> lock(mutex_);
        return config_.erase(key) > 0;
    }
};

/**
 * @class DatabaseConnection
 * @brief Thread-safe database connection singleton
 */
class DatabaseConnection {
private:
    static std::unique_ptr<DatabaseConnection> instance_;
    static std::mutex mutex_;
    
    std::string connection_string_;
    std::atomic<bool> is_connected_{false};
    std::vector<std::string> query_history_;
    mutable std::mutex query_mutex_;
    
    DatabaseConnection() : connection_string_("mongodb://localhost:27017/designpatterns") {}

public:
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    DatabaseConnection(DatabaseConnection&&) = delete;
    DatabaseConnection& operator=(DatabaseConnection&&) = delete;
    
    static DatabaseConnection& getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = std::unique_ptr<DatabaseConnection>(new DatabaseConnection());
        }
        return *instance_;
    }
    
    /**
     * @brief Connect to database
     * @return True if connection successful
     */
    bool connect() {
        if (!is_connected_.load()) {
            std::cout << "Connecting to database: " << connection_string_ << std::endl;
            // Simulate connection delay
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            is_connected_.store(true);
            std::cout << "Database connection established" << std::endl;
        }
        return is_connected_.load();
    }
    
    /**
     * @brief Disconnect from database
     */
    void disconnect() {
        if (is_connected_.load()) {
            std::cout << "Disconnecting from database" << std::endl;
            is_connected_.store(false);
        }
    }
    
    /**
     * @brief Execute a query
     * @param query SQL query to execute
     * @return Query result message
     */
    std::string executeQuery(const std::string& query) {
        if (!is_connected_.load()) {
            throw std::runtime_error("Database not connected");
        }
        
        std::lock_guard<std::mutex> lock(query_mutex_);
        query_history_.push_back(query);
        return "Executed: " + query;
    }
    
    /**
     * @brief Get query history
     * @return Vector of executed queries
     */
    std::vector<std::string> getQueryHistory() const {
        std::lock_guard<std::mutex> lock(query_mutex_);
        return query_history_;
    }
    
    /**
     * @brief Check if database is connected
     * @return True if connected, false otherwise
     */
    bool isConnected() const {
        return is_connected_.load();
    }
    
    /**
     * @brief Get connection string
     * @return Database connection string
     */
    std::string getConnectionString() const {
        return connection_string_;
    }
    
    /**
     * @brief Set connection string
     * @param connectionString New connection string
     */
    void setConnectionString(const std::string& connectionString) {
        if (is_connected_.load()) {
            throw std::runtime_error("Cannot change connection string while connected");
        }
        connection_string_ = connectionString;
    }
};

/**
 * @class Logger
 * @brief Thread-safe logging singleton with different log levels
 */
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

struct LogEntry {
    LogLevel level;
    std::string message;
    std::string category;
    std::chrono::system_clock::time_point timestamp;
    
    LogEntry(LogLevel l, const std::string& msg, const std::string& cat = "")
        : level(l), message(msg), category(cat), timestamp(std::chrono::system_clock::now()) {}
};

class Logger {
private:
    static std::unique_ptr<Logger> instance_;
    static std::mutex mutex_;
    
    std::vector<LogEntry> logs_;
    LogLevel min_level_;
    mutable std::mutex log_mutex_;
    
    Logger() : min_level_(LogLevel::INFO) {}
    
    std::string logLevelToString(LogLevel level) const {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    
    static Logger& getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = std::unique_ptr<Logger>(new Logger());
        }
        return *instance_;
    }
    
    /**
     * @brief Set minimum log level
     * @param level Minimum level to log
     */
    void setLogLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(log_mutex_);
        min_level_ = level;
    }
    
    /**
     * @brief Log a message
     * @param level Log level
     * @param message Log message
     * @param category Optional category
     */
    void log(LogLevel level, const std::string& message, const std::string& category = "") {
        if (level >= min_level_) {
            std::lock_guard<std::mutex> lock(log_mutex_);
            logs_.emplace_back(level, message, category);
            
            // Print to console
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()) % 1000;
            
            std::cout << "[" << logLevelToString(level) << "]";
            if (!category.empty()) {
                std::cout << "[" << category << "]";
            }
            std::cout << " " << message << std::endl;
        }
    }
    
    void debug(const std::string& message, const std::string& category = "") {
        log(LogLevel::DEBUG, message, category);
    }
    
    void info(const std::string& message, const std::string& category = "") {
        log(LogLevel::INFO, message, category);
    }
    
    void warn(const std::string& message, const std::string& category = "") {
        log(LogLevel::WARN, message, category);
    }
    
    void error(const std::string& message, const std::string& category = "") {
        log(LogLevel::ERROR, message, category);
    }
    
    /**
     * @brief Get all logs
     * @return Vector of log entries
     */
    std::vector<LogEntry> getLogs() const {
        std::lock_guard<std::mutex> lock(log_mutex_);
        return logs_;
    }
    
    /**
     * @brief Get logs by level
     * @param level Log level to filter by
     * @return Vector of log entries matching the level
     */
    std::vector<LogEntry> getLogs(LogLevel level) const {
        std::lock_guard<std::mutex> lock(log_mutex_);
        std::vector<LogEntry> filtered;
        for (const auto& entry : logs_) {
            if (entry.level == level) {
                filtered.push_back(entry);
            }
        }
        return filtered;
    }
    
    /**
     * @brief Clear all logs
     */
    void clearLogs() {
        std::lock_guard<std::mutex> lock(log_mutex_);
        logs_.clear();
    }
    
    /**
     * @brief Get log count
     * @return Number of log entries
     */
    size_t getLogCount() const {
        std::lock_guard<std::mutex> lock(log_mutex_);
        return logs_.size();
    }
};

} // namespace CreationalPatterns

#endif // SINGLETON_H
