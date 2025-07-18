# C++ Design Patterns Implementation

This is a comprehensive implementation of the 23 Gang of Four (GoF) design patterns in C++17, demonstrating modern C++ best practices and providing practical examples.

## Project Structure

```
cpp-design-patterns/
├── src/
│   ├── creational/
│   │   ├── singleton/           # ✅ Implemented
│   │   ├── factory-method/      # ✅ Implemented  
│   │   ├── abstract-factory/    # ✅ Implemented
│   │   ├── builder/             # ✅ Implemented
│   │   └── prototype/           # ✅ Implemented
│   ├── structural/
│   │   ├── adapter/             # ✅ Implemented
│   │   ├── bridge/              # ✅ Implemented
│   │   ├── composite/           # 🚧 In Progress
│   │   ├── decorator/           # 🚧 Planned
│   │   ├── facade/              # 🚧 Planned
│   │   ├── flyweight/           # 🚧 Planned
│   │   └── proxy/               # 🚧 Planned
│   └── behavioral/
│       ├── observer/            # 🚧 Planned
│       ├── strategy/            # 🚧 Planned
│       ├── command/             # 🚧 Planned
│       ├── state/               # 🚧 Planned
│       ├── template-method/     # 🚧 Planned
│       ├── chain-of-responsibility/ # 🚧 Planned
│       ├── iterator/            # 🚧 Planned
│       ├── mediator/            # 🚧 Planned
│       ├── memento/             # 🚧 Planned
│       ├── visitor/             # 🚧 Planned
│       └── interpreter/         # 🚧 Planned
├── demos/
│   ├── all_patterns_demo.cpp   # Comprehensive demo
│   └── simple_demo.cpp         # Basic examples
├── CMakeLists.txt              # CMake build configuration
├── Makefile                    # Alternative build system
└── README.md                   # This file
```

## Implemented Patterns (7/23)

### Creational Patterns (5/5) ✅

1. **Singleton** - Thread-safe singleton with various implementations
   - Database Connection Singleton
   - Configuration Manager Singleton  
   - Logger Singleton
   - Resource Manager Singleton

2. **Factory Method** - Creates objects without specifying exact classes
   - Document Factory (Word, PDF, PowerPoint)
   - Vehicle Factory (Car, Motorcycle, Truck)
   - UI Element Factory (Button, TextBox, etc.)

3. **Abstract Factory** - Creates families of related objects
   - Cross-platform UI Factory (Windows, macOS, Linux)
   - Complete with Buttons, TextBoxes, Dialogs, and Menus

4. **Builder** - Constructs complex objects step by step
   - Computer Builder (Gaming, Office, Workstation PCs)
   - SQL Query Builder with fluent interface
   - HTTP Request Builder with method chaining

5. **Prototype** - Creates objects by cloning existing instances
   - Document Prototypes with cloning
   - Character Prototypes for gaming
   - Shape Prototypes with Prototype Registry

### Structural Patterns (2/7) ✅

6. **Adapter** - Allows incompatible interfaces to work together
   - Media Player Adapter (MP3, MP4, VLC formats)
   - Database Connection Adapter (MySQL, PostgreSQL, MongoDB)
   - Graphics Renderer Adapter (OpenGL, DirectX)

7. **Bridge** - Separates abstraction from implementation
   - Remote Control Bridge (TV, Radio, Sound System)
   - Message Sender Bridge (Email, SMS, Push Notifications)
   - Database Connection Bridge with different drivers

## Features

- **Modern C++17** - Uses smart pointers, auto, lambdas, and other modern features
- **Thread Safety** - Singleton implementations are thread-safe
- **RAII** - Resource management using RAII principles  
- **Memory Safety** - Extensive use of smart pointers
- **Cross-platform** - Works on Windows, macOS, and Linux
- **Comprehensive Examples** - Each pattern includes multiple real-world examples
- **Demo Applications** - Interactive demos to test all patterns

## Building

### Using Make (Recommended)
```bash
# Build all patterns and demo
make

# Run the demo
make run

# Clean build artifacts
make clean
```

### Using CMake (If available)
```bash
mkdir build && cd build
cmake ..
make
./design_patterns_demo
```

## Pattern Examples

### Singleton Pattern
```cpp
#include "creational/singleton/Singleton.h"
using namespace CreationalPatterns;

// Thread-safe singleton access
auto& db = DatabaseConnection::getInstance();
db.connect();
```

### Builder Pattern  
```cpp
#include "creational/builder/Builder.h"
using namespace patterns::creational::builder;

// Fluent interface for building complex objects
auto query = SQLQueryBuilder()
    .select({"name", "email"})
    .from("users") 
    .where("age > 18")
    .orderBy("name", "ASC")
    .limit(10)
    .build();
```

### Adapter Pattern
```cpp
#include "structural/adapter/Adapter.h"
using namespace patterns::structural::adapter;

// Adapt incompatible interfaces
AudioPlayer player;
player.play("mp3", "song.mp3");  // Native support
player.play("mp4", "video.mp4"); // Adapted format
```

## Key Design Principles

1. **SOLID Principles** - Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
2. **DRY** - Don't Repeat Yourself
3. **KISS** - Keep It Simple, Stupid
4. **Modern C++ Best Practices** - Using smart pointers, RAII, move semantics
5. **Thread Safety** - All singleton implementations are thread-safe
6. **Exception Safety** - Proper exception handling throughout

## Testing

Each pattern includes comprehensive examples and can be tested through the demo applications:

```bash
# Build and run all demos
make run

# Or run specific demos
./build/design_patterns_demo
```

## Next Steps

The remaining 16 patterns are planned for implementation:

### Structural Patterns (5 remaining)
- Composite - Tree structures of objects
- Decorator - Add behavior to objects dynamically  
- Facade - Simplified interface to complex subsystems
- Flyweight - Share objects efficiently
- Proxy - Placeholder/surrogate for another object

### Behavioral Patterns (11 remaining)  
- Observer - Notify multiple objects of state changes
- Strategy - Encapsulate algorithms and make them interchangeable
- Command - Encapsulate requests as objects
- State - Change object behavior when internal state changes
- Template Method - Define algorithm structure, let subclasses override steps
- Chain of Responsibility - Pass requests along chain of handlers
- Iterator - Access elements of collection sequentially
- Mediator - Define how objects interact with each other
- Memento - Capture and restore object state
- Visitor - Define new operations without changing object structure
- Interpreter - Define grammar and interpreter for a language

## Contributing

This is a educational project demonstrating design pattern implementations in modern C++. The code emphasizes clarity, best practices, and practical examples over performance optimization.

## License

This project is for educational purposes and demonstrates various design patterns in C++17.
