/**
 * @file Singleton.cpp
 * @brief Singleton Pattern Implementation
 */

#include "Singleton.h"
#include <thread>

namespace CreationalPatterns {

// Static member definitions
std::unique_ptr<Singleton> Singleton::instance_ = nullptr;
std::mutex Singleton::mutex_;

std::unique_ptr<ConfigManager> ConfigManager::instance_ = nullptr;
std::mutex ConfigManager::mutex_;

std::unique_ptr<DatabaseConnection> DatabaseConnection::instance_ = nullptr;
std::mutex DatabaseConnection::mutex_;

std::unique_ptr<Logger> Logger::instance_ = nullptr;
std::mutex Logger::mutex_;

} // namespace CreationalPatterns
