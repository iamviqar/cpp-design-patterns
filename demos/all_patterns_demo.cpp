#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>

// Include all pattern headers
#include "creational/singleton/Singleton.h"
#include "creational/factory-method/FactoryMethod.h"
#include "creational/abstract-factory/AbstractFactory.h"
#include "creational/builder/Builder.h"
#include "creational/prototype/Prototype.h"
#include "structural/adapter/Adapter.h"
#include "structural/bridge/Bridge.h"

class PatternDemoRunner {
private:
    std::map<int, std::function<void()>> demos;
    
public:
    PatternDemoRunner() {
        setupDemos();
    }
    
    void run() {
        while (true) {
            showMenu();
            int choice = getUserChoice();
            
            if (choice == 0) {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            
            if (demos.find(choice) != demos.end()) {
                std::cout << "\n" << std::string(60, '=') << std::endl;
                demos[choice]();
                std::cout << std::string(60, '=') << std::endl;
                
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
    
private:
    void setupDemos() {
        demos[1] = []() { runSingletonDemo(); };
        demos[2] = []() { runFactoryMethodDemo(); };
        demos[3] = []() { runAbstractFactoryDemo(); };
        demos[4] = []() { runBuilderDemo(); };
        demos[5] = []() { runPrototypeDemo(); };
        demos[6] = []() { runAdapterDemo(); };
        demos[7] = []() { runBridgeDemo(); };
    }
    
    void showMenu() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "          C++ DESIGN PATTERNS DEMO" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "\nCreational Patterns:" << std::endl;
        std::cout << "  1. Singleton Pattern" << std::endl;
        std::cout << "  2. Factory Method Pattern" << std::endl;
        std::cout << "  3. Abstract Factory Pattern" << std::endl;
        std::cout << "  4. Builder Pattern" << std::endl;
        std::cout << "  5. Prototype Pattern" << std::endl;
        
        std::cout << "\nStructural Patterns:" << std::endl;
        std::cout << "  6. Adapter Pattern" << std::endl;
        std::cout << "  7. Bridge Pattern" << std::endl;
        
        std::cout << "\n  0. Exit" << std::endl;
        std::cout << "\nSelect a pattern to demo: ";
    }
    
    int getUserChoice() {
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer
        return choice;
    }
    
    // Demo implementations
    static void runSingletonDemo() {
        std::cout << "=== SINGLETON PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::creational::singleton;
        
        std::cout << "\n1. Database Connection Singleton:" << std::endl;
        auto& db1 = DatabaseConnection::getInstance();
        auto& db2 = DatabaseConnection::getInstance();
        
        std::cout << "Are both instances the same? " << (&db1 == &db2 ? "Yes" : "No") << std::endl;
        
        db1.connect("localhost", "myapp", "password123", "production_db");
        db1.executeQuery("SELECT * FROM users");
        
        std::cout << "\n2. Configuration Manager Singleton:" << std::endl;
        auto& config = ConfigurationManager::getInstance();
        config.setConfigValue("app.name", "My Application");
        config.setConfigValue("app.version", "1.0.0");
        config.setConfigValue("database.host", "localhost");
        
        std::cout << "App Name: " << config.getConfigValue("app.name") << std::endl;
        std::cout << "App Version: " << config.getConfigValue("app.version") << std::endl;
        
        std::cout << "\n3. Logger Singleton:" << std::endl;
        auto& logger = Logger::getInstance();
        logger.setLogLevel(Logger::LogLevel::INFO);
        logger.log(Logger::LogLevel::INFO, "Application started");
        logger.log(Logger::LogLevel::WARNING, "Low memory warning");
        logger.log(Logger::LogLevel::ERROR, "Database connection failed");
    }
    
    static void runFactoryMethodDemo() {
        std::cout << "=== FACTORY METHOD PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::creational::factory_method;
        
        std::cout << "\n1. Document Factory:" << std::endl;
        auto wordFactory = std::make_unique<WordDocumentFactory>();
        auto pdfFactory = std::make_unique<PdfDocumentFactory>();
        
        auto wordDoc = wordFactory->createDocument("Report.docx");
        auto pdfDoc = pdfFactory->createDocument("Report.pdf");
        
        wordDoc->open();
        wordDoc->save();
        wordDoc->close();
        
        std::cout << std::endl;
        
        pdfDoc->open();
        pdfDoc->save();
        pdfDoc->close();
        
        std::cout << "\n2. Vehicle Factory:" << std::endl;
        auto carFactory = std::make_unique<CarFactory>();
        auto motorcycleFactory = std::make_unique<MotorcycleFactory>();
        
        auto car = carFactory->createVehicle();
        auto motorcycle = motorcycleFactory->createVehicle();
        
        car->start();
        car->accelerate();
        car->brake();
        car->stop();
        
        std::cout << std::endl;
        
        motorcycle->start();
        motorcycle->accelerate();
        motorcycle->brake();
        motorcycle->stop();
    }
    
    static void runAbstractFactoryDemo() {
        std::cout << "=== ABSTRACT FACTORY PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::creational::abstract_factory;
        
        std::cout << "\n1. Windows UI Factory:" << std::endl;
        auto windowsFactory = UIElementFactory::createFactory(UIElementFactory::Platform::WINDOWS);
        
        auto winButton = windowsFactory->createButton();
        auto winTextBox = windowsFactory->createTextBox();
        auto winDialog = windowsFactory->createDialog();
        
        winButton->render();
        winTextBox->render();
        winDialog->render();
        
        std::cout << "\n2. macOS UI Factory:" << std::endl;
        auto macFactory = UIElementFactory::createFactory(UIElementFactory::Platform::MACOS);
        
        auto macButton = macFactory->createButton();
        auto macTextBox = macFactory->createTextBox();
        auto macDialog = macFactory->createDialog();
        
        macButton->render();
        macTextBox->render();
        macDialog->render();
        
        std::cout << "\n3. Linux UI Factory:" << std::endl;
        auto linuxFactory = UIElementFactory::createFactory(UIElementFactory::Platform::LINUX);
        
        auto linuxButton = linuxFactory->createButton();
        auto linuxTextBox = linuxFactory->createTextBox();
        auto linuxDialog = linuxFactory->createDialog();
        
        linuxButton->render();
        linuxTextBox->render();
        linuxDialog->render();
    }
    
    static void runBuilderDemo() {
        std::cout << "=== BUILDER PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::creational::builder;
        
        std::cout << "\n1. Computer Builder:" << std::endl;
        ConcreteComputerBuilder builder;
        ComputerDirector director(builder);
        
        auto gamingPC = director.buildGamingComputer();
        std::cout << "Gaming Computer:\n" << gamingPC->getSpecifications() << std::endl;
        std::cout << "Estimated Price: $" << gamingPC->getEstimatedPrice() << std::endl;
        
        auto officePC = director.buildOfficeComputer();
        std::cout << "\nOffice Computer:\n" << officePC->getSpecifications() << std::endl;
        std::cout << "Estimated Price: $" << officePC->getEstimatedPrice() << std::endl;
        
        std::cout << "\n2. SQL Query Builder:" << std::endl;
        SQLQueryBuilder queryBuilder;
        
        auto query = queryBuilder
            .select({"name", "email", "age"})
            .from("users")
            .where("age > 18")
            .where("active = 1")
            .orderBy("name", "ASC")
            .limit(10)
            .build();
            
        std::cout << "Generated SQL: " << query->toString() << std::endl;
        
        std::cout << "\n3. HTTP Request Builder:" << std::endl;
        auto request = HttpRequestBuilder::post("https://api.example.com/users")
            .header("Content-Type", "application/json")
            .header("Authorization", "Bearer token123")
            .json("{\"name\": \"John Doe\", \"email\": \"john@example.com\"}")
            .timeout(5000)
            .retries(3)
            .build();
            
        std::cout << "HTTP Request:\n" << request->toString() << std::endl;
    }
    
    static void runPrototypeDemo() {
        std::cout << "=== PROTOTYPE PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::creational::prototype;
        
        std::cout << "\n1. Document Prototype:" << std::endl;
        auto originalDoc = PrototypeFactory::createWordDocument("Template Document");
        originalDoc->setAuthor("John Doe");
        originalDoc->setContent("This is a template document with standard formatting.");
        
        std::cout << "Original Document:\n" << originalDoc->getInfo() << std::endl;
        
        auto clonedDoc = std::unique_ptr<Document>(
            static_cast<Document*>(originalDoc->clone().release())
        );
        clonedDoc->setName("Cloned Document");
        clonedDoc->setContent("This is a cloned document with modified content.");
        
        std::cout << "\nCloned Document:\n" << clonedDoc->getInfo() << std::endl;
        
        std::cout << "\n2. Character Prototype:" << std::endl;
        auto warrior = PrototypeFactory::createWarrior("Aragorn");
        warrior->setLevel(10);
        warrior->addSkill("Shield Slam");
        
        std::cout << "Original Warrior:\n" << warrior->getInfo() << std::endl;
        
        auto clonedWarrior = std::unique_ptr<Character>(
            static_cast<Character*>(warrior->clone().release())
        );
        clonedWarrior->setName("Legolas Clone");
        clonedWarrior->setLevel(5);
        
        std::cout << "\nCloned Warrior:\n" << clonedWarrior->getInfo() << std::endl;
        
        std::cout << "\n3. Shape Prototype with Registry:" << std::endl;
        auto& registry = PrototypeRegistry::getInstance();
        registry.registerCommonShapes();
        
        auto circle = std::unique_ptr<Circle>(
            static_cast<Circle*>(registry.createClone("circle_template").release())
        );
        circle->setName("My Circle");
        circle->setRadius(10.0);
        circle->setColor(255, 0, 0); // Red
        
        std::cout << "Cloned Circle:\n" << circle->getInfo() << std::endl;
        std::cout << "Area: " << circle->getArea() << ", Perimeter: " << circle->getPerimeter() << std::endl;
    }
    
    static void runAdapterDemo() {
        std::cout << "=== ADAPTER PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::structural::adapter;
        
        std::cout << "\n1. Audio Player Adapter:" << std::endl;
        AudioPlayer player;
        
        std::cout << "Supported formats: ";
        auto formats = player.getSupportedFormats();
        for (const auto& format : formats) {
            std::cout << format << " ";
        }
        std::cout << std::endl;
        
        player.play("mp3", "song.mp3");
        player.play("mp4", "video.mp4");
        player.play("vlc", "movie.vlc");
        player.play("avi", "clip.avi");
        
        std::cout << "\n2. Database Adapter:" << std::endl;
        auto mysqlConnection = DatabaseConnectionFactory::createConnection(
            DatabaseConnectionFactory::DatabaseType::MYSQL
        );
        
        mysqlConnection->connect("mysql://root:password@localhost:3306/testdb");
        std::cout << "Connection info: " << mysqlConnection->getConnectionInfo() << std::endl;
        
        mysqlConnection->executeQuery("SELECT * FROM users");
        mysqlConnection->executeUpdate("UPDATE users SET status = 'active'");
        
        mysqlConnection->disconnect();
        
        std::cout << "\n3. Graphics Renderer Adapter:" << std::endl;
        auto openglRenderer = GraphicsRendererFactory::createRenderer(
            GraphicsRendererFactory::RendererType::OPENGL
        );
        
        openglRenderer->initialize(800, 600);
        std::cout << "Renderer: " << openglRenderer->getRendererInfo() << std::endl;
        
        openglRenderer->clear();
        openglRenderer->drawLine(0, 0, 100, 100, "red");
        openglRenderer->drawRectangle(50, 50, 200, 150, "blue");
        openglRenderer->drawCircle(300, 300, 75, "green");
        openglRenderer->present();
    }
    
    static void runBridgeDemo() {
        std::cout << "=== BRIDGE PATTERN DEMO ===" << std::endl;
        
        using namespace patterns::structural::bridge;
        
        std::cout << "\n1. Remote Control Bridge:" << std::endl;
        auto tv = std::make_shared<Television>("Samsung", 100);
        auto radio = std::make_shared<Radio>("Sony");
        
        BasicRemote basicRemote(tv);
        AdvancedRemote advancedRemote(tv);
        SmartRemote smartRemote(radio);
        
        std::cout << "Basic Remote with TV:" << std::endl;
        basicRemote.togglePower();
        basicRemote.setVolume(75);
        basicRemote.setChannel(5);
        basicRemote.mute();
        std::cout << "Status: " << basicRemote.getStatus() << std::endl;
        
        std::cout << "\nAdvanced Remote with TV:" << std::endl;
        advancedRemote.setFavoriteChannel(7);
        advancedRemote.goToFavoriteChannel();
        advancedRemote.programChannel(1, 12);
        advancedRemote.goToProgrammedChannel(1);
        std::cout << "Detailed Status:\n" << advancedRemote.getDetailedStatus() << std::endl;
        
        std::cout << "\nSmart Remote with Radio:" << std::endl;
        smartRemote.togglePower();
        smartRemote.connectToWifi("HomeNetwork", "password123");
        smartRemote.voiceCommand("turn on");
        smartRemote.voiceCommand("volume up");
        smartRemote.voiceCommand("channel 3");
        
        std::cout << "\n2. Message Sender Bridge:" << std::endl;
        auto emailSender = std::make_shared<EmailSender>("smtp.gmail.com", 587);
        emailSender->setAuthentication("user@gmail.com", "password");
        
        TextMessage textMessage(emailSender);
        textMessage.setContent("Hello, this is a test message!");
        
        std::cout << "Sending via " << textMessage.getSenderInfo() << std::endl;
        textMessage.send("recipient@example.com");
        
        std::cout << "\n3. Database Connection Bridge:" << std::endl;
        auto mysqlDriver = std::make_shared<MySqlDriver>();
        TransactionalConnection transConn(mysqlDriver);
        
        transConn.connect("mysql://user:password@localhost/database");
        transConn.startTransaction();
        transConn.executeQuery("INSERT INTO users (name) VALUES ('Alice')");
        transConn.executeQuery("INSERT INTO users (name) VALUES ('Bob')");
        transConn.commit();
        std::cout << "Transaction completed successfully" << std::endl;
    }
};

int main() {
    std::cout << "C++ Design Patterns Implementation Demo" << std::endl;
    std::cout << "Version 1.0.0" << std::endl;
    
    PatternDemoRunner runner;
    runner.run();
    
    return 0;
}
