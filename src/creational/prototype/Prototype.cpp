#include "Prototype.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

namespace patterns {
namespace creational {
namespace prototype {

// Document implementation
Document::Document(Type type, const std::string& name, const std::string& content)
    : type(type), name(name), content(content), author("Unknown"), templateName("Default") {}

Document::Document(const Document& other)
    : type(other.type), name(other.name), content(other.content),
      author(other.author), templateName(other.templateName), pages(other.pages) {}

std::unique_ptr<Prototype> Document::clone() const {
    return std::make_unique<Document>(*this);
}

std::string Document::getInfo() const {
    std::ostringstream oss;
    oss << "Document: " << name << "\n";
    oss << "Type: " << getTypeString() << "\n";
    oss << "Author: " << author << "\n";
    oss << "Template: " << templateName << "\n";
    oss << "Pages: " << getPageCount() << "\n";
    oss << "Content length: " << content.length() << " characters";
    return oss.str();
}

void Document::setName(const std::string& name) {
    this->name = name;
}

void Document::setContent(const std::string& content) {
    this->content = content;
}

void Document::addPage(const std::string& pageContent) {
    pages.push_back(pageContent);
}

void Document::setAuthor(const std::string& author) {
    this->author = author;
}

void Document::setTemplate(const std::string& templateName) {
    this->templateName = templateName;
}

Document::Type Document::getType() const {
    return type;
}

std::string Document::getTypeString() const {
    switch (type) {
        case Type::WORD: return "Word Document";
        case Type::PDF: return "PDF Document";
        case Type::POWERPOINT: return "PowerPoint Presentation";
        case Type::EXCEL: return "Excel Spreadsheet";
        default: return "Unknown";
    }
}

int Document::getPageCount() const {
    return static_cast<int>(pages.size());
}

// Character implementation
Character::Character(CharacterClass charClass, const std::string& name)
    : characterClass(charClass), name(name), level(1) {
    
    // Set default stats based on class
    switch (charClass) {
        case CharacterClass::WARRIOR:
            stats = {150, 20, 15, 12, 8, 3};
            skills = {"Sword Mastery", "Shield Block", "Berserker Rage"};
            equipment = {{"weapon", "Iron Sword"}, {"armor", "Chain Mail"}, {"shield", "Wooden Shield"}};
            break;
        case CharacterClass::MAGE:
            stats = {80, 120, 6, 4, 12, 18};
            skills = {"Fireball", "Ice Shard", "Heal", "Teleport"};
            equipment = {{"weapon", "Magic Staff"}, {"armor", "Robes"}, {"accessory", "Spell Focus"}};
            break;
        case CharacterClass::ARCHER:
            stats = {100, 60, 12, 8, 16, 8};
            skills = {"Precise Shot", "Multi-Shot", "Eagle Eye"};
            equipment = {{"weapon", "Wooden Bow"}, {"armor", "Leather Armor"}, {"accessory", "Quiver"}};
            break;
        case CharacterClass::ROGUE:
            stats = {90, 40, 10, 6, 18, 6};
            skills = {"Stealth", "Backstab", "Lock Picking", "Poison Blade"};
            equipment = {{"weapon", "Dagger"}, {"armor", "Leather Armor"}, {"accessory", "Thieves' Tools"}};
            break;
    }
}

Character::Character(const Character& other)
    : characterClass(other.characterClass), name(other.name), level(other.level),
      stats(other.stats), skills(other.skills), equipment(other.equipment) {}

std::unique_ptr<Prototype> Character::clone() const {
    return std::make_unique<Character>(*this);
}

std::string Character::getInfo() const {
    std::ostringstream oss;
    oss << "Character: " << name << "\n";
    oss << "Class: " << getClassString() << "\n";
    oss << "Level: " << level << "\n";
    oss << "Stats - HP:" << stats.health << " MP:" << stats.mana 
        << " ATK:" << stats.attack << " DEF:" << stats.defense 
        << " SPD:" << stats.speed << " MAG:" << stats.magic << "\n";
    oss << "Skills: ";
    for (size_t i = 0; i < skills.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << skills[i];
    }
    oss << "\nEquipment: ";
    for (const auto& item : equipment) {
        oss << item.first << "=" << item.second << " ";
    }
    return oss.str();
}

void Character::setName(const std::string& name) {
    this->name = name;
}

void Character::setLevel(int level) {
    this->level = level;
}

void Character::addSkill(const std::string& skill) {
    skills.push_back(skill);
}

void Character::setEquipment(const std::string& slot, const std::string& item) {
    equipment[slot] = item;
}

void Character::setStats(const Stats& stats) {
    this->stats = stats;
}

Character::CharacterClass Character::getClass() const {
    return characterClass;
}

std::string Character::getClassString() const {
    switch (characterClass) {
        case CharacterClass::WARRIOR: return "Warrior";
        case CharacterClass::MAGE: return "Mage";
        case CharacterClass::ARCHER: return "Archer";
        case CharacterClass::ROGUE: return "Rogue";
        default: return "Unknown";
    }
}

int Character::getLevel() const {
    return level;
}

Character::Stats Character::getStats() const {
    return stats;
}

// Shape implementation
std::string Shape::Color::toString() const {
    std::ostringstream oss;
    oss << "RGB(" << r << "," << g << "," << b << ")";
    return oss.str();
}

Shape::Shape(ShapeType type, const std::string& name)
    : type(type), name(name), position({0.0, 0.0}), color({0, 0, 0}), visible(true) {}

Shape::Shape(const Shape& other)
    : type(other.type), name(other.name), position(other.position),
      color(other.color), visible(other.visible) {}

std::string Shape::getInfo() const {
    std::ostringstream oss;
    oss << "Shape: " << name << "\n";
    oss << "Type: " << getTypeString() << "\n";
    oss << "Position: (" << position.x << ", " << position.y << ")\n";
    oss << "Color: " << color.toString() << "\n";
    oss << "Visible: " << (visible ? "Yes" : "No") << "\n";
    oss << "Area: " << getArea() << "\n";
    oss << "Perimeter: " << getPerimeter();
    return oss.str();
}

void Shape::setName(const std::string& name) {
    this->name = name;
}

void Shape::setPosition(double x, double y) {
    position.x = x;
    position.y = y;
}

void Shape::setColor(int r, int g, int b) {
    color.r = std::max(0, std::min(255, r));
    color.g = std::max(0, std::min(255, g));
    color.b = std::max(0, std::min(255, b));
}

void Shape::setVisible(bool visible) {
    this->visible = visible;
}

Shape::ShapeType Shape::getType() const {
    return type;
}

std::string Shape::getTypeString() const {
    switch (type) {
        case ShapeType::CIRCLE: return "Circle";
        case ShapeType::RECTANGLE: return "Rectangle";
        case ShapeType::TRIANGLE: return "Triangle";
        default: return "Unknown";
    }
}

Shape::Position Shape::getPosition() const {
    return position;
}

Shape::Color Shape::getColor() const {
    return color;
}

bool Shape::isVisible() const {
    return visible;
}

// Circle implementation
Circle::Circle(const std::string& name, double radius)
    : Shape(ShapeType::CIRCLE, name), radius(radius) {}

Circle::Circle(const Circle& other)
    : Shape(other), radius(other.radius) {}

std::unique_ptr<Prototype> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

double Circle::getArea() const {
    return M_PI * radius * radius;
}

double Circle::getPerimeter() const {
    return 2 * M_PI * radius;
}

void Circle::setRadius(double radius) {
    this->radius = std::max(0.0, radius);
}

double Circle::getRadius() const {
    return radius;
}

// Rectangle implementation
Rectangle::Rectangle(const std::string& name, double width, double height)
    : Shape(ShapeType::RECTANGLE, name), width(width), height(height) {}

Rectangle::Rectangle(const Rectangle& other)
    : Shape(other), width(other.width), height(other.height) {}

std::unique_ptr<Prototype> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

double Rectangle::getArea() const {
    return width * height;
}

double Rectangle::getPerimeter() const {
    return 2 * (width + height);
}

void Rectangle::setDimensions(double width, double height) {
    this->width = std::max(0.0, width);
    this->height = std::max(0.0, height);
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::getHeight() const {
    return height;
}

// Triangle implementation
Triangle::Triangle(const std::string& name, double side1, double side2, double side3)
    : Shape(ShapeType::TRIANGLE, name), side1(side1), side2(side2), side3(side3) {
    
    if (!isValidTriangle()) {
        this->side1 = this->side2 = this->side3 = 1.0; // Default to unit triangle
    }
}

Triangle::Triangle(const Triangle& other)
    : Shape(other), side1(other.side1), side2(other.side2), side3(other.side3) {}

std::unique_ptr<Prototype> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

double Triangle::getArea() const {
    // Using Heron's formula
    double s = (side1 + side2 + side3) / 2;
    return std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
}

double Triangle::getPerimeter() const {
    return side1 + side2 + side3;
}

void Triangle::setSides(double side1, double side2, double side3) {
    this->side1 = side1;
    this->side2 = side2;
    this->side3 = side3;
    
    if (!isValidTriangle()) {
        this->side1 = this->side2 = this->side3 = 1.0;
    }
}

double Triangle::getSide1() const {
    return side1;
}

double Triangle::getSide2() const {
    return side2;
}

double Triangle::getSide3() const {
    return side3;
}

bool Triangle::isValidTriangle() const {
    return (side1 + side2 > side3) && 
           (side1 + side3 > side2) && 
           (side2 + side3 > side1) &&
           side1 > 0 && side2 > 0 && side3 > 0;
}

// PrototypeRegistry implementation
PrototypeRegistry& PrototypeRegistry::getInstance() {
    static PrototypeRegistry instance;
    return instance;
}

void PrototypeRegistry::registerPrototype(const std::string& key, std::unique_ptr<Prototype> prototype) {
    prototypes[key] = std::move(prototype);
}

std::unique_ptr<Prototype> PrototypeRegistry::createClone(const std::string& key) const {
    auto it = prototypes.find(key);
    if (it != prototypes.end()) {
        return it->second->clone();
    }
    return nullptr;
}

bool PrototypeRegistry::hasPrototype(const std::string& key) const {
    return prototypes.find(key) != prototypes.end();
}

void PrototypeRegistry::removePrototype(const std::string& key) {
    prototypes.erase(key);
}

std::vector<std::string> PrototypeRegistry::getAvailablePrototypes() const {
    std::vector<std::string> keys;
    for (const auto& pair : prototypes) {
        keys.push_back(pair.first);
    }
    std::sort(keys.begin(), keys.end());
    return keys;
}

void PrototypeRegistry::clear() {
    prototypes.clear();
}

void PrototypeRegistry::registerCommonDocuments() {
    registerPrototype("word_template", PrototypeFactory::createWordDocument("Document Template"));
    registerPrototype("pdf_template", PrototypeFactory::createPDFDocument("PDF Template"));
    registerPrototype("presentation_template", PrototypeFactory::createPresentationDocument("Presentation Template"));
    registerPrototype("spreadsheet_template", PrototypeFactory::createSpreadsheetDocument("Spreadsheet Template"));
}

void PrototypeRegistry::registerCommonCharacters() {
    registerPrototype("warrior_template", PrototypeFactory::createWarrior("Warrior Template"));
    registerPrototype("mage_template", PrototypeFactory::createMage("Mage Template"));
    registerPrototype("archer_template", PrototypeFactory::createArcher("Archer Template"));
    registerPrototype("rogue_template", PrototypeFactory::createRogue("Rogue Template"));
}

void PrototypeRegistry::registerCommonShapes() {
    registerPrototype("circle_template", PrototypeFactory::createCircle("Circle Template", 5.0));
    registerPrototype("rectangle_template", PrototypeFactory::createRectangle("Rectangle Template", 10.0, 6.0));
    registerPrototype("triangle_template", PrototypeFactory::createTriangle("Triangle Template", 3.0, 4.0, 5.0));
}

// PrototypeFactory implementation
std::unique_ptr<Document> PrototypeFactory::createWordDocument(const std::string& name) {
    auto doc = std::make_unique<Document>(Document::Type::WORD, name);
    doc->setTemplate("Microsoft Word Template");
    doc->setContent("This is a Word document template.");
    return doc;
}

std::unique_ptr<Document> PrototypeFactory::createPDFDocument(const std::string& name) {
    auto doc = std::make_unique<Document>(Document::Type::PDF, name);
    doc->setTemplate("PDF Template");
    doc->setContent("This is a PDF document template.");
    return doc;
}

std::unique_ptr<Document> PrototypeFactory::createPresentationDocument(const std::string& name) {
    auto doc = std::make_unique<Document>(Document::Type::POWERPOINT, name);
    doc->setTemplate("PowerPoint Template");
    doc->setContent("This is a presentation template.");
    doc->addPage("Title Slide");
    doc->addPage("Introduction");
    doc->addPage("Content");
    doc->addPage("Conclusion");
    return doc;
}

std::unique_ptr<Document> PrototypeFactory::createSpreadsheetDocument(const std::string& name) {
    auto doc = std::make_unique<Document>(Document::Type::EXCEL, name);
    doc->setTemplate("Excel Template");
    doc->setContent("This is a spreadsheet template.");
    return doc;
}

std::unique_ptr<Character> PrototypeFactory::createWarrior(const std::string& name) {
    return std::make_unique<Character>(Character::CharacterClass::WARRIOR, name);
}

std::unique_ptr<Character> PrototypeFactory::createMage(const std::string& name) {
    return std::make_unique<Character>(Character::CharacterClass::MAGE, name);
}

std::unique_ptr<Character> PrototypeFactory::createArcher(const std::string& name) {
    return std::make_unique<Character>(Character::CharacterClass::ARCHER, name);
}

std::unique_ptr<Character> PrototypeFactory::createRogue(const std::string& name) {
    return std::make_unique<Character>(Character::CharacterClass::ROGUE, name);
}

std::unique_ptr<Circle> PrototypeFactory::createCircle(const std::string& name, double radius) {
    return std::make_unique<Circle>(name, radius);
}

std::unique_ptr<Rectangle> PrototypeFactory::createRectangle(const std::string& name, double width, double height) {
    return std::make_unique<Rectangle>(name, width, height);
}

std::unique_ptr<Triangle> PrototypeFactory::createTriangle(const std::string& name, double side1, double side2, double side3) {
    return std::make_unique<Triangle>(name, side1, side2, side3);
}

} // namespace prototype
} // namespace creational
} // namespace patterns
