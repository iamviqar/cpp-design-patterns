#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace patterns {
namespace creational {
namespace prototype {

// Abstract prototype interface
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual std::string getInfo() const = 0;
    virtual void setName(const std::string& name) = 0;
};

// Document prototype example
class Document : public Prototype {
public:
    enum class Type {
        WORD,
        PDF,
        POWERPOINT,
        EXCEL
    };

    Document(Type type, const std::string& name, const std::string& content = "");
    Document(const Document& other);
    
    std::unique_ptr<Prototype> clone() const override;
    std::string getInfo() const override;
    void setName(const std::string& name) override;
    
    // Document-specific methods
    void setContent(const std::string& content);
    void addPage(const std::string& pageContent);
    void setAuthor(const std::string& author);
    void setTemplate(const std::string& templateName);
    Type getType() const;
    std::string getTypeString() const;
    int getPageCount() const;
    
private:
    Type type;
    std::string name;
    std::string content;
    std::string author;
    std::string templateName;
    std::vector<std::string> pages;
};

// Character prototype example for gaming
class Character : public Prototype {
public:
    enum class CharacterClass {
        WARRIOR,
        MAGE,
        ARCHER,
        ROGUE
    };

    struct Stats {
        int health = 100;
        int mana = 50;
        int attack = 10;
        int defense = 5;
        int speed = 10;
        int magic = 5;
    };

    Character(CharacterClass charClass, const std::string& name);
    Character(const Character& other);
    
    std::unique_ptr<Prototype> clone() const override;
    std::string getInfo() const override;
    void setName(const std::string& name) override;
    
    // Character-specific methods
    void setLevel(int level);
    void addSkill(const std::string& skill);
    void setEquipment(const std::string& slot, const std::string& item);
    void setStats(const Stats& stats);
    CharacterClass getClass() const;
    std::string getClassString() const;
    int getLevel() const;
    Stats getStats() const;
    
private:
    CharacterClass characterClass;
    std::string name;
    int level;
    Stats stats;
    std::vector<std::string> skills;
    std::unordered_map<std::string, std::string> equipment;
};

// Shape prototype example
class Shape : public Prototype {
public:
    enum class ShapeType {
        CIRCLE,
        RECTANGLE,
        TRIANGLE
    };

    struct Color {
        int r, g, b;
        std::string toString() const;
    };

    struct Position {
        double x, y;
    };

    Shape(ShapeType type, const std::string& name);
    Shape(const Shape& other);
    
    std::unique_ptr<Prototype> clone() const override;
    std::string getInfo() const override;
    void setName(const std::string& name) override;
    
    // Shape-specific methods
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    
    void setPosition(double x, double y);
    void setColor(int r, int g, int b);
    void setVisible(bool visible);
    ShapeType getType() const;
    std::string getTypeString() const;
    Position getPosition() const;
    Color getColor() const;
    bool isVisible() const;
    
protected:
    ShapeType type;
    std::string name;
    Position position;
    Color color;
    bool visible;
};

// Concrete shape implementations
class Circle : public Shape {
public:
    Circle(const std::string& name, double radius);
    Circle(const Circle& other);
    
    std::unique_ptr<Prototype> clone() const override;
    double getArea() const override;
    double getPerimeter() const override;
    
    void setRadius(double radius);
    double getRadius() const;
    
private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(const std::string& name, double width, double height);
    Rectangle(const Rectangle& other);
    
    std::unique_ptr<Prototype> clone() const override;
    double getArea() const override;
    double getPerimeter() const override;
    
    void setDimensions(double width, double height);
    double getWidth() const;
    double getHeight() const;
    
private:
    double width;
    double height;
};

class Triangle : public Shape {
public:
    Triangle(const std::string& name, double side1, double side2, double side3);
    Triangle(const Triangle& other);
    
    std::unique_ptr<Prototype> clone() const override;
    double getArea() const override;
    double getPerimeter() const override;
    
    void setSides(double side1, double side2, double side3);
    double getSide1() const;
    double getSide2() const;
    double getSide3() const;
    
private:
    double side1, side2, side3;
    bool isValidTriangle() const;
};

// Prototype registry/manager
class PrototypeRegistry {
public:
    static PrototypeRegistry& getInstance();
    
    void registerPrototype(const std::string& key, std::unique_ptr<Prototype> prototype);
    std::unique_ptr<Prototype> createClone(const std::string& key) const;
    bool hasPrototype(const std::string& key) const;
    void removePrototype(const std::string& key);
    std::vector<std::string> getAvailablePrototypes() const;
    void clear();
    
    // Convenience methods for common prototypes
    void registerCommonDocuments();
    void registerCommonCharacters();
    void registerCommonShapes();
    
private:
    PrototypeRegistry() = default;
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes;
};

// Prototype factory for easier creation
class PrototypeFactory {
public:
    // Document factories
    static std::unique_ptr<Document> createWordDocument(const std::string& name);
    static std::unique_ptr<Document> createPDFDocument(const std::string& name);
    static std::unique_ptr<Document> createPresentationDocument(const std::string& name);
    static std::unique_ptr<Document> createSpreadsheetDocument(const std::string& name);
    
    // Character factories
    static std::unique_ptr<Character> createWarrior(const std::string& name);
    static std::unique_ptr<Character> createMage(const std::string& name);
    static std::unique_ptr<Character> createArcher(const std::string& name);
    static std::unique_ptr<Character> createRogue(const std::string& name);
    
    // Shape factories
    static std::unique_ptr<Circle> createCircle(const std::string& name, double radius);
    static std::unique_ptr<Rectangle> createRectangle(const std::string& name, double width, double height);
    static std::unique_ptr<Triangle> createTriangle(const std::string& name, double side1, double side2, double side3);
};

} // namespace prototype
} // namespace creational
} // namespace patterns
