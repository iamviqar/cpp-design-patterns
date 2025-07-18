#include "AbstractFactory.h"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace patterns {
namespace creational {
namespace abstract_factory {

// Windows implementations
std::string WindowsButton::render() const {
    return std::string("[Windows Button] ") + (enabled ? "Enabled" : "Disabled");
}

void WindowsButton::onClick() {
    if (enabled) {
        std::cout << "Windows button clicked!" << std::endl;
    }
}

void WindowsButton::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool WindowsButton::isEnabled() const {
    return enabled;
}

std::string WindowsWindow::render() const {
    return "[Windows Window: " + title + "]";
}

void WindowsWindow::setTitle(const std::string& title) {
    this->title = title;
}

std::string WindowsWindow::getTitle() const {
    return title;
}

void WindowsWindow::close() {
    std::cout << "Closing Windows window: " << title << std::endl;
}

std::string WindowsMenu::render() const {
    std::ostringstream oss;
    oss << "[Windows Menu] Items: ";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << items[i];
    }
    return oss.str();
}

void WindowsMenu::addItem(const std::string& item) {
    items.push_back(item);
}

std::vector<std::string> WindowsMenu::getItems() const {
    return items;
}

// macOS implementations
std::string MacOSButton::render() const {
    return std::string("(macOS Button) ") + (enabled ? "Enabled" : "Disabled");
}

void MacOSButton::onClick() {
    if (enabled) {
        std::cout << "macOS button clicked!" << std::endl;
    }
}

void MacOSButton::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool MacOSButton::isEnabled() const {
    return enabled;
}

std::string MacOSWindow::render() const {
    return "(macOS Window: " + title + ")";
}

void MacOSWindow::setTitle(const std::string& title) {
    this->title = title;
}

std::string MacOSWindow::getTitle() const {
    return title;
}

void MacOSWindow::close() {
    std::cout << "Closing macOS window: " << title << std::endl;
}

std::string MacOSMenu::render() const {
    std::ostringstream oss;
    oss << "(macOS Menu) Items: ";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) oss << " | ";
        oss << items[i];
    }
    return oss.str();
}

void MacOSMenu::addItem(const std::string& item) {
    items.push_back(item);
}

std::vector<std::string> MacOSMenu::getItems() const {
    return items;
}

// Linux implementations
std::string LinuxButton::render() const {
    return std::string("{Linux Button} ") + (enabled ? "Enabled" : "Disabled");
}

void LinuxButton::onClick() {
    if (enabled) {
        std::cout << "Linux button clicked!" << std::endl;
    }
}

void LinuxButton::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool LinuxButton::isEnabled() const {
    return enabled;
}

std::string LinuxWindow::render() const {
    return "{Linux Window: " + title + "}";
}

void LinuxWindow::setTitle(const std::string& title) {
    this->title = title;
}

std::string LinuxWindow::getTitle() const {
    return title;
}

void LinuxWindow::close() {
    std::cout << "Closing Linux window: " << title << std::endl;
}

std::string LinuxMenu::render() const {
    std::ostringstream oss;
    oss << "{Linux Menu} Items: ";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) oss << "] [";
        else oss << "[";
        oss << items[i];
    }
    if (!items.empty()) oss << "]";
    return oss.str();
}

void LinuxMenu::addItem(const std::string& item) {
    items.push_back(item);
}

std::vector<std::string> LinuxMenu::getItems() const {
    return items;
}

// Factory implementations
std::unique_ptr<Button> WindowsFactory::createButton() {
    return std::make_unique<WindowsButton>();
}

std::unique_ptr<Window> WindowsFactory::createWindow() {
    return std::make_unique<WindowsWindow>();
}

std::unique_ptr<Menu> WindowsFactory::createMenu() {
    return std::make_unique<WindowsMenu>();
}

std::unique_ptr<Button> MacOSFactory::createButton() {
    return std::make_unique<MacOSButton>();
}

std::unique_ptr<Window> MacOSFactory::createWindow() {
    return std::make_unique<MacOSWindow>();
}

std::unique_ptr<Menu> MacOSFactory::createMenu() {
    return std::make_unique<MacOSMenu>();
}

std::unique_ptr<Button> LinuxFactory::createButton() {
    return std::make_unique<LinuxButton>();
}

std::unique_ptr<Window> LinuxFactory::createWindow() {
    return std::make_unique<LinuxWindow>();
}

std::unique_ptr<Menu> LinuxFactory::createMenu() {
    return std::make_unique<LinuxMenu>();
}

// Application implementation
Application::Application(std::unique_ptr<GUIFactory> factory) {
    button = factory->createButton();
    window = factory->createWindow();
    menu = factory->createMenu();
}

void Application::setupUI() {
    window->setTitle("My Application");
    menu->addItem("File");
    menu->addItem("Edit");
    menu->addItem("View");
    menu->addItem("Help");
}

std::string Application::render() const {
    return window->render() + "\n" + menu->render() + "\n" + button->render();
}

void Application::handleButtonClick() {
    button->onClick();
}

void Application::closeApplication() {
    window->close();
}

// Factory method
std::unique_ptr<GUIFactory> getGUIFactory(Platform platform) {
    switch (platform) {
        case Platform::WINDOWS:
            return std::make_unique<WindowsFactory>();
        case Platform::MACOS:
            return std::make_unique<MacOSFactory>();
        case Platform::LINUX:
            return std::make_unique<LinuxFactory>();
        default:
            throw std::invalid_argument("Unknown platform");
    }
}

} // namespace abstract_factory
} // namespace creational
} // namespace patterns
