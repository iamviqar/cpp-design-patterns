#pragma once

#include <memory>
#include <string>
#include <vector>

namespace patterns {
namespace creational {
namespace abstract_factory {

// Abstract Product interfaces
class Button {
public:
    virtual ~Button() = default;
    virtual std::string render() const = 0;
    virtual void onClick() = 0;
    virtual void setEnabled(bool enabled) = 0;
    virtual bool isEnabled() const = 0;
};

class Window {
public:
    virtual ~Window() = default;
    virtual std::string render() const = 0;
    virtual void setTitle(const std::string& title) = 0;
    virtual std::string getTitle() const = 0;
    virtual void close() = 0;
};

class Menu {
public:
    virtual ~Menu() = default;
    virtual std::string render() const = 0;
    virtual void addItem(const std::string& item) = 0;
    virtual std::vector<std::string> getItems() const = 0;
};

// Abstract Factory interface
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Window> createWindow() = 0;
    virtual std::unique_ptr<Menu> createMenu() = 0;
};

// Windows implementations
class WindowsButton : public Button {
private:
    bool enabled = true;

public:
    std::string render() const override;
    void onClick() override;
    void setEnabled(bool enabled) override;
    bool isEnabled() const override;
};

class WindowsWindow : public Window {
private:
    std::string title = "Windows Window";

public:
    std::string render() const override;
    void setTitle(const std::string& title) override;
    std::string getTitle() const override;
    void close() override;
};

class WindowsMenu : public Menu {
private:
    std::vector<std::string> items;

public:
    std::string render() const override;
    void addItem(const std::string& item) override;
    std::vector<std::string> getItems() const override;
};

// macOS implementations
class MacOSButton : public Button {
private:
    bool enabled = true;

public:
    std::string render() const override;
    void onClick() override;
    void setEnabled(bool enabled) override;
    bool isEnabled() const override;
};

class MacOSWindow : public Window {
private:
    std::string title = "macOS Window";

public:
    std::string render() const override;
    void setTitle(const std::string& title) override;
    std::string getTitle() const override;
    void close() override;
};

class MacOSMenu : public Menu {
private:
    std::vector<std::string> items;

public:
    std::string render() const override;
    void addItem(const std::string& item) override;
    std::vector<std::string> getItems() const override;
};

// Linux implementations
class LinuxButton : public Button {
private:
    bool enabled = true;

public:
    std::string render() const override;
    void onClick() override;
    void setEnabled(bool enabled) override;
    bool isEnabled() const override;
};

class LinuxWindow : public Window {
private:
    std::string title = "Linux Window";

public:
    std::string render() const override;
    void setTitle(const std::string& title) override;
    std::string getTitle() const override;
    void close() override;
};

class LinuxMenu : public Menu {
private:
    std::vector<std::string> items;

public:
    std::string render() const override;
    void addItem(const std::string& item) override;
    std::vector<std::string> getItems() const override;
};

// Concrete Factories
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override;
    std::unique_ptr<Window> createWindow() override;
    std::unique_ptr<Menu> createMenu() override;
};

class MacOSFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override;
    std::unique_ptr<Window> createWindow() override;
    std::unique_ptr<Menu> createMenu() override;
};

class LinuxFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override;
    std::unique_ptr<Window> createWindow() override;
    std::unique_ptr<Menu> createMenu() override;
};

// Client class
class Application {
private:
    std::unique_ptr<Button> button;
    std::unique_ptr<Window> window;
    std::unique_ptr<Menu> menu;

public:
    Application(std::unique_ptr<GUIFactory> factory);
    void setupUI();
    std::string render() const;
    void handleButtonClick();
    void closeApplication();
};

// Factory method to get appropriate factory
enum class Platform { WINDOWS, MACOS, LINUX };
std::unique_ptr<GUIFactory> getGUIFactory(Platform platform);

} // namespace abstract_factory
} // namespace creational
} // namespace patterns
