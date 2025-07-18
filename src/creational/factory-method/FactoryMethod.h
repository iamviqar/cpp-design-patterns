/**
 * @file FactoryMethod.h
 * @brief Factory Method Pattern Implementation
 * 
 * Create objects without specifying the exact class of object that will be created.
 * Provides an interface for creating objects but lets subclasses decide which class to instantiate.
 */

#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

namespace CreationalPatterns {

/**
 * @class Animal
 * @brief Abstract product interface for animals
 */
class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string makeSound() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getHabitat() const = 0;
    virtual void displayInfo() const {
        std::cout << "Type: " << getType() << std::endl;
        std::cout << "Sound: " << makeSound() << std::endl;
        std::cout << "Habitat: " << getHabitat() << std::endl;
    }
};

/**
 * @class Dog
 * @brief Concrete product - Dog
 */
class Dog : public Animal {
private:
    std::string breed_;

public:
    explicit Dog(const std::string& breed = "Generic") : breed_(breed) {}
    
    std::string makeSound() const override {
        return "Woof!";
    }
    
    std::string getType() const override {
        return "Dog (" + breed_ + ")";
    }
    
    std::string getHabitat() const override {
        return "Domestic";
    }
    
    std::string getBreed() const { return breed_; }
};

/**
 * @class Cat
 * @brief Concrete product - Cat
 */
class Cat : public Animal {
private:
    std::string breed_;

public:
    explicit Cat(const std::string& breed = "Generic") : breed_(breed) {}
    
    std::string makeSound() const override {
        return "Meow!";
    }
    
    std::string getType() const override {
        return "Cat (" + breed_ + ")";
    }
    
    std::string getHabitat() const override {
        return "Domestic";
    }
    
    std::string getBreed() const { return breed_; }
};

/**
 * @class Lion
 * @brief Concrete product - Lion
 */
class Lion : public Animal {
public:
    std::string makeSound() const override {
        return "Roar!";
    }
    
    std::string getType() const override {
        return "Lion";
    }
    
    std::string getHabitat() const override {
        return "Savanna";
    }
};

/**
 * @class Wolf
 * @brief Concrete product - Wolf
 */
class Wolf : public Animal {
public:
    std::string makeSound() const override {
        return "Howl!";
    }
    
    std::string getType() const override {
        return "Wolf";
    }
    
    std::string getHabitat() const override {
        return "Forest";
    }
};

/**
 * @class AnimalFactory
 * @brief Abstract creator for animals
 */
class AnimalFactory {
public:
    virtual ~AnimalFactory() = default;
    
    // Factory method - subclasses will override this
    virtual std::unique_ptr<Animal> createAnimal() = 0;
    
    // Template method that uses the factory method
    std::string introduceAnimal() {
        auto animal = createAnimal();
        return "This is a " + animal->getType() + 
               " that says \"" + animal->makeSound() + 
               "\" and lives in " + animal->getHabitat();
    }
    
    void demonstrateAnimal() {
        auto animal = createAnimal();
        animal->displayInfo();
    }
};

/**
 * @class DogFactory
 * @brief Concrete creator for dogs
 */
class DogFactory : public AnimalFactory {
private:
    std::string breed_;

public:
    explicit DogFactory(const std::string& breed = "Generic") : breed_(breed) {}
    
    std::unique_ptr<Animal> createAnimal() override {
        return std::make_unique<Dog>(breed_);
    }
};

/**
 * @class CatFactory
 * @brief Concrete creator for cats
 */
class CatFactory : public AnimalFactory {
private:
    std::string breed_;

public:
    explicit CatFactory(const std::string& breed = "Generic") : breed_(breed) {}
    
    std::unique_ptr<Animal> createAnimal() override {
        return std::make_unique<Cat>(breed_);
    }
};

/**
 * @class WildAnimalFactory
 * @brief Concrete creator for wild animals
 */
class WildAnimalFactory : public AnimalFactory {
public:
    enum class AnimalType { LION, WOLF };

private:
    AnimalType animal_type_;

public:
    explicit WildAnimalFactory(AnimalType type) : animal_type_(type) {}
    
    std::unique_ptr<Animal> createAnimal() override {
        switch (animal_type_) {
            case AnimalType::LION:
                return std::make_unique<Lion>();
            case AnimalType::WOLF:
                return std::make_unique<Wolf>();
            default:
                throw std::invalid_argument("Unknown animal type");
        }
    }
};

// Document creation example
/**
 * @class Document
 * @brief Abstract product interface for documents
 */
class Document {
public:
    virtual ~Document() = default;
    virtual std::string getType() const = 0;
    virtual std::string getContent() const = 0;
    virtual std::string save() const = 0;
    virtual std::string exportTo(const std::string& format) const = 0;
    virtual void setContent(const std::string& content) = 0;
};

/**
 * @class PDFDocument
 * @brief Concrete product - PDF document
 */
class PDFDocument : public Document {
private:
    std::string content_;

public:
    explicit PDFDocument(const std::string& content = "") : content_(content) {}
    
    std::string getType() const override {
        return "PDF";
    }
    
    std::string getContent() const override {
        return content_;
    }
    
    std::string save() const override {
        return "PDF document saved with content: \"" + content_ + "\"";
    }
    
    std::string exportTo(const std::string& format) const override {
        return "Exporting PDF to " + format + " format";
    }
    
    void setContent(const std::string& content) override {
        content_ = content;
    }
};

/**
 * @class WordDocument
 * @brief Concrete product - Word document
 */
class WordDocument : public Document {
private:
    std::string content_;

public:
    explicit WordDocument(const std::string& content = "") : content_(content) {}
    
    std::string getType() const override {
        return "Word";
    }
    
    std::string getContent() const override {
        return content_;
    }
    
    std::string save() const override {
        return "Word document saved with content: \"" + content_ + "\"";
    }
    
    std::string exportTo(const std::string& format) const override {
        return "Exporting Word document to " + format + " format";
    }
    
    void setContent(const std::string& content) override {
        content_ = content;
    }
};

/**
 * @class HTMLDocument
 * @brief Concrete product - HTML document
 */
class HTMLDocument : public Document {
private:
    std::string content_;

public:
    explicit HTMLDocument(const std::string& content = "") : content_(content) {}
    
    std::string getType() const override {
        return "HTML";
    }
    
    std::string getContent() const override {
        return "<html><body>" + content_ + "</body></html>";
    }
    
    std::string save() const override {
        return "HTML document saved with content: \"" + content_ + "\"";
    }
    
    std::string exportTo(const std::string& format) const override {
        return "Exporting HTML to " + format + " format";
    }
    
    void setContent(const std::string& content) override {
        content_ = content;
    }
};

/**
 * @class DocumentFactory
 * @brief Abstract creator for documents
 */
class DocumentFactory {
public:
    virtual ~DocumentFactory() = default;
    virtual std::unique_ptr<Document> createDocument(const std::string& content) = 0;
    
    std::string processDocument(const std::string& content) {
        auto doc = createDocument(content);
        return "Created " + doc->getType() + " document. " + doc->save();
    }
};

/**
 * @class PDFDocumentFactory
 * @brief Concrete creator for PDF documents
 */
class PDFDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument(const std::string& content) override {
        return std::make_unique<PDFDocument>(content);
    }
};

/**
 * @class WordDocumentFactory
 * @brief Concrete creator for Word documents
 */
class WordDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument(const std::string& content) override {
        return std::make_unique<WordDocument>(content);
    }
};

/**
 * @class HTMLDocumentFactory
 * @brief Concrete creator for HTML documents
 */
class HTMLDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument(const std::string& content) override {
        return std::make_unique<HTMLDocument>(content);
    }
};

// Payment processor example
/**
 * @class PaymentProcessor
 * @brief Abstract product interface for payment processors
 */
class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual std::string processPayment(double amount) = 0;
    virtual bool validatePayment(double amount) const = 0;
    virtual std::string getProcessorName() const = 0;
    virtual double getTransactionFee(double amount) const = 0;
};

/**
 * @class CreditCardProcessor
 * @brief Concrete product - Credit card processor
 */
class CreditCardProcessor : public PaymentProcessor {
private:
    std::string card_number_;

public:
    explicit CreditCardProcessor(const std::string& cardNumber) 
        : card_number_(cardNumber) {}
    
    std::string processPayment(double amount) override {
        if (!validatePayment(amount)) {
            throw std::invalid_argument("Invalid payment amount");
        }
        double fee = getTransactionFee(amount);
        return "Processed $" + std::to_string(amount) + 
               " (fee: $" + std::to_string(fee) + 
               ") via Credit Card ending in " + card_number_.substr(card_number_.length() - 4);
    }
    
    bool validatePayment(double amount) const override {
        return amount > 0 && amount <= 10000;
    }
    
    std::string getProcessorName() const override {
        return "Credit Card";
    }
    
    double getTransactionFee(double amount) const override {
        return amount * 0.029; // 2.9% fee
    }
};

/**
 * @class PayPalProcessor
 * @brief Concrete product - PayPal processor
 */
class PayPalProcessor : public PaymentProcessor {
private:
    std::string email_;

public:
    explicit PayPalProcessor(const std::string& email) : email_(email) {}
    
    std::string processPayment(double amount) override {
        if (!validatePayment(amount)) {
            throw std::invalid_argument("Invalid payment amount");
        }
        double fee = getTransactionFee(amount);
        return "Processed $" + std::to_string(amount) + 
               " (fee: $" + std::to_string(fee) + 
               ") via PayPal account: " + email_;
    }
    
    bool validatePayment(double amount) const override {
        return amount > 0 && amount <= 50000;
    }
    
    std::string getProcessorName() const override {
        return "PayPal";
    }
    
    double getTransactionFee(double amount) const override {
        return amount * 0.034; // 3.4% fee
    }
};

/**
 * @class PaymentProcessorFactory
 * @brief Abstract creator for payment processors
 */
class PaymentProcessorFactory {
public:
    virtual ~PaymentProcessorFactory() = default;
    virtual std::unique_ptr<PaymentProcessor> createProcessor() = 0;
    
    std::string executePayment(double amount) {
        auto processor = createProcessor();
        return processor->processPayment(amount);
    }
};

/**
 * @class CreditCardProcessorFactory
 * @brief Concrete creator for credit card processors
 */
class CreditCardProcessorFactory : public PaymentProcessorFactory {
private:
    std::string card_number_;

public:
    explicit CreditCardProcessorFactory(const std::string& cardNumber) 
        : card_number_(cardNumber) {}
    
    std::unique_ptr<PaymentProcessor> createProcessor() override {
        return std::make_unique<CreditCardProcessor>(card_number_);
    }
};

/**
 * @class PayPalProcessorFactory
 * @brief Concrete creator for PayPal processors
 */
class PayPalProcessorFactory : public PaymentProcessorFactory {
private:
    std::string email_;

public:
    explicit PayPalProcessorFactory(const std::string& email) : email_(email) {}
    
    std::unique_ptr<PaymentProcessor> createProcessor() override {
        return std::make_unique<PayPalProcessor>(email_);
    }
};

// Utility functions
/**
 * @brief Get appropriate payment factory based on type
 * @param type Payment type ("credit" or "paypal")
 * @param identifier Card number or email
 * @return Unique pointer to payment processor factory
 */
std::unique_ptr<PaymentProcessorFactory> getPaymentFactory(
    const std::string& type, 
    const std::string& identifier
) {
    if (type == "credit") {
        return std::make_unique<CreditCardProcessorFactory>(identifier);
    } else if (type == "paypal") {
        return std::make_unique<PayPalProcessorFactory>(identifier);
    } else {
        throw std::invalid_argument("Unknown payment type: " + type);
    }
}

} // namespace CreationalPatterns

#endif // FACTORY_METHOD_H
