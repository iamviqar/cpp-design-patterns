#pragma once

#include <string>
#include <memory>
#include <vector>

namespace patterns {
namespace structural {
namespace bridge {

// Bridge pattern example 1: Device and Remote Control

// Implementation interface (Bridge)
class Device {
public:
    virtual ~Device() = default;
    virtual bool isEnabled() const = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() const = 0;
    virtual void setVolume(int volume) = 0;
    virtual int getChannel() const = 0;
    virtual void setChannel(int channel) = 0;
    virtual std::string getDeviceInfo() const = 0;
};

// Concrete implementations
class Television : public Device {
public:
    Television(const std::string& brand, int maxVolume = 100);
    
    bool isEnabled() const override;
    void enable() override;
    void disable() override;
    int getVolume() const override;
    void setVolume(int volume) override;
    int getChannel() const override;
    void setChannel(int channel) override;
    std::string getDeviceInfo() const override;
    
    void setInputSource(const std::string& source);
    std::string getInputSource() const;
    void setBrightness(int brightness);
    int getBrightness() const;
    
private:
    std::string brand;
    bool enabled = false;
    int volume = 50;
    int channel = 1;
    int maxVolume;
    std::string inputSource = "HDMI1";
    int brightness = 50;
};

class Radio : public Device {
public:
    Radio(const std::string& brand, float minFreq = 88.0f, float maxFreq = 108.0f);
    
    bool isEnabled() const override;
    void enable() override;
    void disable() override;
    int getVolume() const override;
    void setVolume(int volume) override;
    int getChannel() const override;
    void setChannel(int channel) override;
    std::string getDeviceInfo() const override;
    
    void setFrequency(float frequency);
    float getFrequency() const;
    void scanForStations();
    std::vector<float> getAvailableStations() const;
    
private:
    std::string brand;
    bool enabled = false;
    int volume = 30;
    int channel = 1;
    float frequency = 100.0f;
    float minFreq, maxFreq;
    std::vector<float> availableStations;
};

class SoundSystem : public Device {
public:
    SoundSystem(const std::string& brand, int numberOfSpeakers = 2);
    
    bool isEnabled() const override;
    void enable() override;
    void disable() override;
    int getVolume() const override;
    void setVolume(int volume) override;
    int getChannel() const override;
    void setChannel(int channel) override;
    std::string getDeviceInfo() const override;
    
    void setEqualizer(const std::string& preset);
    std::string getEqualizer() const;
    void setBass(int level);
    void setTreble(int level);
    int getBass() const;
    int getTreble() const;
    
private:
    std::string brand;
    bool enabled = false;
    int volume = 40;
    int channel = 1;
    int numberOfSpeakers;
    std::string equalizer = "Normal";
    int bass = 50;
    int treble = 50;
};

// Abstraction (Remote Control)
class RemoteControl {
public:
    RemoteControl(std::shared_ptr<Device> device);
    virtual ~RemoteControl() = default;
    
    virtual void togglePower();
    virtual void volumeUp();
    virtual void volumeDown();
    virtual void channelUp();
    virtual void channelDown();
    virtual void setVolume(int volume);
    virtual void setChannel(int channel);
    virtual std::string getStatus() const;
    
protected:
    std::shared_ptr<Device> device;
};

// Refined Abstractions
class BasicRemote : public RemoteControl {
public:
    BasicRemote(std::shared_ptr<Device> device);
    
    void mute();
    void unmute();
    bool isMuted() const;
    
private:
    bool muted = false;
    int previousVolume = 0;
};

class AdvancedRemote : public RemoteControl {
public:
    AdvancedRemote(std::shared_ptr<Device> device);
    
    void mute();
    void unmute();
    void setFavoriteChannel(int channelNumber);
    void goToFavoriteChannel();
    void setTimer(int minutes);
    int getTimerRemaining() const;
    std::string getDetailedStatus() const;
    
    // Advanced features
    void programChannel(int slot, int channel);
    void goToProgrammedChannel(int slot);
    std::vector<int> getProgrammedChannels() const;
    
private:
    bool muted = false;
    int previousVolume = 0;
    int favoriteChannel = 1;
    int timerMinutes = 0;
    std::vector<int> programmedChannels;
};

class SmartRemote : public RemoteControl {
public:
    SmartRemote(std::shared_ptr<Device> device);
    
    void connectToWifi(const std::string& network, const std::string& password);
    bool isConnectedToWifi() const;
    void voiceCommand(const std::string& command);
    void updateFirmware();
    std::string getFirmwareVersion() const;
    
    // Smart features
    void setAutoChannelScan(bool enabled);
    void enableParentalControls(const std::string& pin);
    void disableParentalControls(const std::string& pin);
    bool areParentalControlsEnabled() const;
    void addBlockedChannel(int channel);
    void removeBlockedChannel(int channel);
    
private:
    bool wifiConnected = false;
    std::string wifiNetwork;
    std::string firmwareVersion = "1.0.0";
    bool autoChannelScan = false;
    bool parentalControls = false;
    std::string parentalPin;
    std::vector<int> blockedChannels;
    
    void processVoiceCommand(const std::string& command);
};

// Bridge pattern example 2: Message Sender

// Implementation interface
class MessageSender {
public:
    virtual ~MessageSender() = default;
    virtual bool send(const std::string& recipient, const std::string& message) = 0;
    virtual std::string getSenderType() const = 0;
    virtual bool isAvailable() const = 0;
    virtual void configure(const std::string& config) = 0;
};

// Concrete implementations
class EmailSender : public MessageSender {
public:
    EmailSender(const std::string& smtpServer, int port = 587);
    
    bool send(const std::string& recipient, const std::string& message) override;
    std::string getSenderType() const override;
    bool isAvailable() const override;
    void configure(const std::string& config) override;
    
    void setAuthentication(const std::string& username, const std::string& password);
    void setEncryption(bool useSSL);
    
private:
    std::string smtpServer;
    int port;
    std::string username;
    std::string password;
    bool useSSL = true;
    bool authenticated = false;
};

class SmsSender : public MessageSender {
public:
    SmsSender(const std::string& apiKey, const std::string& serviceProvider = "Twilio");
    
    bool send(const std::string& recipient, const std::string& message) override;
    std::string getSenderType() const override;
    bool isAvailable() const override;
    void configure(const std::string& config) override;
    
    void setFromNumber(const std::string& number);
    std::string getFromNumber() const;
    
private:
    std::string apiKey;
    std::string serviceProvider;
    std::string fromNumber;
    bool apiKeyValid = true;
};

class PushNotificationSender : public MessageSender {
public:
    PushNotificationSender(const std::string& appId, const std::string& apiKey);
    
    bool send(const std::string& recipient, const std::string& message) override;
    std::string getSenderType() const override;
    bool isAvailable() const override;
    void configure(const std::string& config) override;
    
    void setBadgeCount(int count);
    void setSound(const std::string& soundFile);
    
private:
    std::string appId;
    std::string apiKey;
    int badgeCount = 0;
    std::string soundFile = "default";
    bool serviceOnline = true;
};

// Abstraction (Message)
class Message {
public:
    Message(std::shared_ptr<MessageSender> sender);
    virtual ~Message() = default;
    
    virtual bool send(const std::string& recipient) = 0;
    virtual void setContent(const std::string& content);
    virtual std::string getContent() const;
    virtual std::string getSenderInfo() const;
    
protected:
    std::shared_ptr<MessageSender> sender;
    std::string content;
};

// Refined Abstractions
class TextMessage : public Message {
public:
    TextMessage(std::shared_ptr<MessageSender> sender);
    
    bool send(const std::string& recipient) override;
    void setPlainText(const std::string& text);
    std::string getPlainText() const;
    
private:
    std::string plainText;
};

class EncryptedMessage : public Message {
public:
    EncryptedMessage(std::shared_ptr<MessageSender> sender, const std::string& encryptionKey);
    
    bool send(const std::string& recipient) override;
    void setContent(const std::string& content) override;
    std::string getContent() const override;
    void setEncryptionKey(const std::string& key);
    
private:
    std::string encryptionKey;
    std::string encrypt(const std::string& text) const;
    std::string decrypt(const std::string& encryptedText) const;
};

class PriorityMessage : public Message {
public:
    enum class Priority {
        LOW,
        NORMAL,
        HIGH,
        URGENT
    };
    
    PriorityMessage(std::shared_ptr<MessageSender> sender, Priority priority = Priority::NORMAL);
    
    bool send(const std::string& recipient) override;
    void setPriority(Priority priority);
    Priority getPriority() const;
    std::string getPriorityString() const;
    void setExpirationTime(int minutes);
    int getExpirationTime() const;
    
private:
    Priority priority;
    int expirationMinutes = 60;
};

// Bridge pattern example 3: Database Connection and Query

// Implementation interface
class DatabaseDriver {
public:
    virtual ~DatabaseDriver() = default;
    virtual bool connect(const std::string& connectionString) = 0;
    virtual void disconnect() = 0;
    virtual bool execute(const std::string& query) = 0;
    virtual std::string fetch(const std::string& query) = 0;
    virtual bool isConnected() const = 0;
    virtual std::string getDriverInfo() const = 0;
    virtual void beginTransaction() = 0;
    virtual void commitTransaction() = 0;
    virtual void rollbackTransaction() = 0;
};

// Concrete implementations
class MySqlDriver : public DatabaseDriver {
public:
    MySqlDriver();
    
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    bool execute(const std::string& query) override;
    std::string fetch(const std::string& query) override;
    bool isConnected() const override;
    std::string getDriverInfo() const override;
    void beginTransaction() override;
    void commitTransaction() override;
    void rollbackTransaction() override;
    
private:
    bool connected = false;
    bool inTransaction = false;
    std::string connectionInfo;
};

class PostgreSqlDriver : public DatabaseDriver {
public:
    PostgreSqlDriver();
    
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    bool execute(const std::string& query) override;
    std::string fetch(const std::string& query) override;
    bool isConnected() const override;
    std::string getDriverInfo() const override;
    void beginTransaction() override;
    void commitTransaction() override;
    void rollbackTransaction() override;
    
private:
    bool connected = false;
    bool inTransaction = false;
    std::string connectionInfo;
};

// Abstraction (Database Connection)
class DatabaseConnection {
public:
    DatabaseConnection(std::shared_ptr<DatabaseDriver> driver);
    virtual ~DatabaseConnection() = default;
    
    virtual bool connect(const std::string& connectionString);
    virtual void disconnect();
    virtual bool executeQuery(const std::string& query);
    virtual std::string fetchData(const std::string& query);
    virtual bool isConnected() const;
    virtual std::string getConnectionInfo() const;
    
protected:
    std::shared_ptr<DatabaseDriver> driver;
};

// Refined Abstractions
class TransactionalConnection : public DatabaseConnection {
public:
    TransactionalConnection(std::shared_ptr<DatabaseDriver> driver);
    
    void startTransaction();
    void commit();
    void rollback();
    bool isInTransaction() const;
    bool executeInTransaction(const std::vector<std::string>& queries);
    
private:
    bool transactionActive = false;
};

class PooledConnection : public DatabaseConnection {
public:
    PooledConnection(std::shared_ptr<DatabaseDriver> driver, int maxConnections = 10);
    
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    int getActiveConnections() const;
    int getMaxConnections() const;
    void setMaxConnections(int max);
    std::vector<std::string> getConnectionStats() const;
    
private:
    int maxConnections;
    int activeConnections = 0;
    std::vector<std::string> connectionPool;
};

} // namespace bridge
} // namespace structural
} // namespace patterns
