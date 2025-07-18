#include "Bridge.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

namespace patterns {
namespace structural {
namespace bridge {

// Television implementation
Television::Television(const std::string& brand, int maxVolume)
    : brand(brand), maxVolume(maxVolume) {}

bool Television::isEnabled() const {
    return enabled;
}

void Television::enable() {
    enabled = true;
    std::cout << brand << " TV: Powered ON" << std::endl;
}

void Television::disable() {
    enabled = false;
    std::cout << brand << " TV: Powered OFF" << std::endl;
}

int Television::getVolume() const {
    return volume;
}

void Television::setVolume(int volume) {
    this->volume = std::max(0, std::min(maxVolume, volume));
    std::cout << brand << " TV: Volume set to " << this->volume << std::endl;
}

int Television::getChannel() const {
    return channel;
}

void Television::setChannel(int channel) {
    this->channel = std::max(1, channel);
    std::cout << brand << " TV: Channel changed to " << this->channel << std::endl;
}

std::string Television::getDeviceInfo() const {
    std::ostringstream oss;
    oss << brand << " Television - Status: " << (enabled ? "ON" : "OFF")
        << ", Volume: " << volume << "/" << maxVolume
        << ", Channel: " << channel
        << ", Input: " << inputSource
        << ", Brightness: " << brightness;
    return oss.str();
}

void Television::setInputSource(const std::string& source) {
    inputSource = source;
    std::cout << brand << " TV: Input source changed to " << source << std::endl;
}

std::string Television::getInputSource() const {
    return inputSource;
}

void Television::setBrightness(int brightness) {
    this->brightness = std::max(0, std::min(100, brightness));
    std::cout << brand << " TV: Brightness set to " << this->brightness << std::endl;
}

int Television::getBrightness() const {
    return brightness;
}

// Radio implementation
Radio::Radio(const std::string& brand, float minFreq, float maxFreq)
    : brand(brand), minFreq(minFreq), maxFreq(maxFreq) {
    // Initialize some available stations
    availableStations = {88.5f, 92.3f, 95.7f, 98.1f, 101.5f, 104.9f, 107.3f};
}

bool Radio::isEnabled() const {
    return enabled;
}

void Radio::enable() {
    enabled = true;
    std::cout << brand << " Radio: Powered ON" << std::endl;
}

void Radio::disable() {
    enabled = false;
    std::cout << brand << " Radio: Powered OFF" << std::endl;
}

int Radio::getVolume() const {
    return volume;
}

void Radio::setVolume(int volume) {
    this->volume = std::max(0, std::min(100, volume));
    std::cout << brand << " Radio: Volume set to " << this->volume << std::endl;
}

int Radio::getChannel() const {
    return channel;
}

void Radio::setChannel(int channel) {
    this->channel = std::max(1, channel);
    if (channel <= static_cast<int>(availableStations.size())) {
        frequency = availableStations[channel - 1];
    }
    std::cout << brand << " Radio: Station " << this->channel 
              << " (FM " << frequency << ")" << std::endl;
}

std::string Radio::getDeviceInfo() const {
    std::ostringstream oss;
    oss << brand << " Radio - Status: " << (enabled ? "ON" : "OFF")
        << ", Volume: " << volume
        << ", Station: " << channel
        << ", Frequency: FM " << frequency;
    return oss.str();
}

void Radio::setFrequency(float frequency) {
    this->frequency = std::max(minFreq, std::min(maxFreq, frequency));
    std::cout << brand << " Radio: Frequency tuned to FM " << this->frequency << std::endl;
}

float Radio::getFrequency() const {
    return frequency;
}

void Radio::scanForStations() {
    std::cout << brand << " Radio: Scanning for stations..." << std::endl;
    // Simulate finding stations
    availableStations.clear();
    for (float freq = minFreq; freq <= maxFreq; freq += 0.2f) {
        if (static_cast<int>(freq * 10) % 17 == 0) { // Arbitrary condition for "finding" stations
            availableStations.push_back(freq);
        }
    }
    std::cout << "Found " << availableStations.size() << " stations" << std::endl;
}

std::vector<float> Radio::getAvailableStations() const {
    return availableStations;
}

// SoundSystem implementation
SoundSystem::SoundSystem(const std::string& brand, int numberOfSpeakers)
    : brand(brand), numberOfSpeakers(numberOfSpeakers) {}

bool SoundSystem::isEnabled() const {
    return enabled;
}

void SoundSystem::enable() {
    enabled = true;
    std::cout << brand << " Sound System: Powered ON (" << numberOfSpeakers << " speakers)" << std::endl;
}

void SoundSystem::disable() {
    enabled = false;
    std::cout << brand << " Sound System: Powered OFF" << std::endl;
}

int SoundSystem::getVolume() const {
    return volume;
}

void SoundSystem::setVolume(int volume) {
    this->volume = std::max(0, std::min(100, volume));
    std::cout << brand << " Sound System: Volume set to " << this->volume << std::endl;
}

int SoundSystem::getChannel() const {
    return channel;
}

void SoundSystem::setChannel(int channel) {
    this->channel = std::max(1, channel);
    std::cout << brand << " Sound System: Input " << this->channel << " selected" << std::endl;
}

std::string SoundSystem::getDeviceInfo() const {
    std::ostringstream oss;
    oss << brand << " Sound System (" << numberOfSpeakers << " speakers) - "
        << "Status: " << (enabled ? "ON" : "OFF")
        << ", Volume: " << volume
        << ", Input: " << channel
        << ", EQ: " << equalizer
        << ", Bass: " << bass
        << ", Treble: " << treble;
    return oss.str();
}

void SoundSystem::setEqualizer(const std::string& preset) {
    equalizer = preset;
    std::cout << brand << " Sound System: Equalizer set to " << preset << std::endl;
}

std::string SoundSystem::getEqualizer() const {
    return equalizer;
}

void SoundSystem::setBass(int level) {
    bass = std::max(0, std::min(100, level));
    std::cout << brand << " Sound System: Bass set to " << bass << std::endl;
}

void SoundSystem::setTreble(int level) {
    treble = std::max(0, std::min(100, level));
    std::cout << brand << " Sound System: Treble set to " << treble << std::endl;
}

int SoundSystem::getBass() const {
    return bass;
}

int SoundSystem::getTreble() const {
    return treble;
}

// RemoteControl implementation
RemoteControl::RemoteControl(std::shared_ptr<Device> device) : device(device) {}

void RemoteControl::togglePower() {
    if (device->isEnabled()) {
        device->disable();
    } else {
        device->enable();
    }
}

void RemoteControl::volumeUp() {
    int currentVolume = device->getVolume();
    device->setVolume(currentVolume + 1);
}

void RemoteControl::volumeDown() {
    int currentVolume = device->getVolume();
    device->setVolume(currentVolume - 1);
}

void RemoteControl::channelUp() {
    int currentChannel = device->getChannel();
    device->setChannel(currentChannel + 1);
}

void RemoteControl::channelDown() {
    int currentChannel = device->getChannel();
    device->setChannel(std::max(1, currentChannel - 1));
}

void RemoteControl::setVolume(int volume) {
    device->setVolume(volume);
}

void RemoteControl::setChannel(int channel) {
    device->setChannel(channel);
}

std::string RemoteControl::getStatus() const {
    return device->getDeviceInfo();
}

// BasicRemote implementation
BasicRemote::BasicRemote(std::shared_ptr<Device> device) : RemoteControl(device) {}

void BasicRemote::mute() {
    if (!muted) {
        previousVolume = device->getVolume();
        device->setVolume(0);
        muted = true;
        std::cout << "Device muted (previous volume: " << previousVolume << ")" << std::endl;
    }
}

void BasicRemote::unmute() {
    if (muted) {
        device->setVolume(previousVolume);
        muted = false;
        std::cout << "Device unmuted" << std::endl;
    }
}

bool BasicRemote::isMuted() const {
    return muted;
}

// AdvancedRemote implementation
AdvancedRemote::AdvancedRemote(std::shared_ptr<Device> device) 
    : RemoteControl(device), programmedChannels(10, 0) {}

void AdvancedRemote::mute() {
    if (!muted) {
        previousVolume = device->getVolume();
        device->setVolume(0);
        muted = true;
        std::cout << "Advanced Remote: Device muted" << std::endl;
    }
}

void AdvancedRemote::unmute() {
    if (muted) {
        device->setVolume(previousVolume);
        muted = false;
        std::cout << "Advanced Remote: Device unmuted" << std::endl;
    }
}

void AdvancedRemote::setFavoriteChannel(int channelNumber) {
    favoriteChannel = channelNumber;
    std::cout << "Favorite channel set to " << channelNumber << std::endl;
}

void AdvancedRemote::goToFavoriteChannel() {
    device->setChannel(favoriteChannel);
    std::cout << "Switched to favorite channel " << favoriteChannel << std::endl;
}

void AdvancedRemote::setTimer(int minutes) {
    timerMinutes = minutes;
    std::cout << "Timer set for " << minutes << " minutes" << std::endl;
}

int AdvancedRemote::getTimerRemaining() const {
    return timerMinutes;
}

std::string AdvancedRemote::getDetailedStatus() const {
    std::ostringstream oss;
    oss << getStatus() << "\n";
    oss << "Advanced Remote Features:\n";
    oss << "- Muted: " << (muted ? "Yes" : "No") << "\n";
    oss << "- Favorite Channel: " << favoriteChannel << "\n";
    oss << "- Timer: " << timerMinutes << " minutes\n";
    oss << "- Programmed Channels: ";
    for (size_t i = 0; i < programmedChannels.size(); ++i) {
        if (programmedChannels[i] > 0) {
            oss << "[" << i << ":" << programmedChannels[i] << "] ";
        }
    }
    return oss.str();
}

void AdvancedRemote::programChannel(int slot, int channel) {
    if (slot >= 0 && slot < static_cast<int>(programmedChannels.size())) {
        programmedChannels[slot] = channel;
        std::cout << "Programmed slot " << slot << " with channel " << channel << std::endl;
    }
}

void AdvancedRemote::goToProgrammedChannel(int slot) {
    if (slot >= 0 && slot < static_cast<int>(programmedChannels.size()) && programmedChannels[slot] > 0) {
        device->setChannel(programmedChannels[slot]);
        std::cout << "Switched to programmed channel " << programmedChannels[slot] 
                  << " (slot " << slot << ")" << std::endl;
    }
}

std::vector<int> AdvancedRemote::getProgrammedChannels() const {
    return programmedChannels;
}

// SmartRemote implementation
SmartRemote::SmartRemote(std::shared_ptr<Device> device) : RemoteControl(device) {}

void SmartRemote::connectToWifi(const std::string& network, const std::string& password) {
    wifiNetwork = network;
    wifiConnected = true;
    std::cout << "Smart Remote: Connected to WiFi network '" << network << "'" << std::endl;
}

bool SmartRemote::isConnectedToWifi() const {
    return wifiConnected;
}

void SmartRemote::voiceCommand(const std::string& command) {
    std::cout << "Smart Remote: Processing voice command: '" << command << "'" << std::endl;
    processVoiceCommand(command);
}

void SmartRemote::updateFirmware() {
    std::cout << "Smart Remote: Updating firmware..." << std::endl;
    firmwareVersion = "1.1.0";
    std::cout << "Firmware updated to version " << firmwareVersion << std::endl;
}

std::string SmartRemote::getFirmwareVersion() const {
    return firmwareVersion;
}

void SmartRemote::setAutoChannelScan(bool enabled) {
    autoChannelScan = enabled;
    std::cout << "Auto channel scan " << (enabled ? "enabled" : "disabled") << std::endl;
}

void SmartRemote::enableParentalControls(const std::string& pin) {
    parentalPin = pin;
    parentalControls = true;
    std::cout << "Parental controls enabled" << std::endl;
}

void SmartRemote::disableParentalControls(const std::string& pin) {
    if (pin == parentalPin) {
        parentalControls = false;
        std::cout << "Parental controls disabled" << std::endl;
    } else {
        std::cout << "Invalid PIN - parental controls remain active" << std::endl;
    }
}

bool SmartRemote::areParentalControlsEnabled() const {
    return parentalControls;
}

void SmartRemote::addBlockedChannel(int channel) {
    blockedChannels.push_back(channel);
    std::cout << "Channel " << channel << " added to blocked list" << std::endl;
}

void SmartRemote::removeBlockedChannel(int channel) {
    auto it = std::find(blockedChannels.begin(), blockedChannels.end(), channel);
    if (it != blockedChannels.end()) {
        blockedChannels.erase(it);
        std::cout << "Channel " << channel << " removed from blocked list" << std::endl;
    }
}

void SmartRemote::processVoiceCommand(const std::string& command) {
    std::string lowerCommand = command;
    std::transform(lowerCommand.begin(), lowerCommand.end(), lowerCommand.begin(), ::tolower);
    
    if (lowerCommand.find("turn on") != std::string::npos) {
        device->enable();
    } else if (lowerCommand.find("turn off") != std::string::npos) {
        device->disable();
    } else if (lowerCommand.find("volume up") != std::string::npos) {
        volumeUp();
    } else if (lowerCommand.find("volume down") != std::string::npos) {
        volumeDown();
    } else if (lowerCommand.find("channel") != std::string::npos) {
        // Simple channel extraction
        for (char c : lowerCommand) {
            if (std::isdigit(c)) {
                int channel = c - '0';
                device->setChannel(channel);
                break;
            }
        }
    } else {
        std::cout << "Voice command not recognized" << std::endl;
    }
}

// EmailSender implementation
EmailSender::EmailSender(const std::string& smtpServer, int port)
    : smtpServer(smtpServer), port(port) {}

bool EmailSender::send(const std::string& recipient, const std::string& message) {
    if (!authenticated) {
        std::cout << "Email: Authentication required" << std::endl;
        return false;
    }
    
    std::cout << "Email: Sending message to " << recipient 
              << " via " << smtpServer << ":" << port << std::endl;
    std::cout << "Subject: Message from application" << std::endl;
    std::cout << "Body: " << message << std::endl;
    return true;
}

std::string EmailSender::getSenderType() const {
    return "Email (SMTP)";
}

bool EmailSender::isAvailable() const {
    return !smtpServer.empty() && port > 0;
}

void EmailSender::configure(const std::string& config) {
    // Parse configuration string
    std::cout << "Email: Configuring with: " << config << std::endl;
}

void EmailSender::setAuthentication(const std::string& username, const std::string& password) {
    this->username = username;
    this->password = password;
    authenticated = true;
    std::cout << "Email: Authentication set for " << username << std::endl;
}

void EmailSender::setEncryption(bool useSSL) {
    this->useSSL = useSSL;
    std::cout << "Email: Encryption " << (useSSL ? "enabled" : "disabled") << std::endl;
}

// Continue with other implementations...
// (Due to length constraints, I'll provide a condensed version of remaining implementations)

// Message implementations
Message::Message(std::shared_ptr<MessageSender> sender) : sender(sender) {}

void Message::setContent(const std::string& content) {
    this->content = content;
}

std::string Message::getContent() const {
    return content;
}

std::string Message::getSenderInfo() const {
    return sender->getSenderType();
}

// TextMessage implementation
TextMessage::TextMessage(std::shared_ptr<MessageSender> sender) : Message(sender) {}

bool TextMessage::send(const std::string& recipient) {
    return sender->send(recipient, content);
}

void TextMessage::setPlainText(const std::string& text) {
    plainText = text;
    content = text;
}

std::string TextMessage::getPlainText() const {
    return plainText;
}

// Database implementations (condensed for brevity)
MySqlDriver::MySqlDriver() {}

bool MySqlDriver::connect(const std::string& connectionString) {
    std::cout << "MySQL Driver: Connecting to " << connectionString << std::endl;
    connected = true;
    connectionInfo = connectionString;
    return true;
}

void MySqlDriver::disconnect() {
    std::cout << "MySQL Driver: Disconnected" << std::endl;
    connected = false;
}

bool MySqlDriver::execute(const std::string& query) {
    std::cout << "MySQL Driver: Executing - " << query << std::endl;
    return connected;
}

std::string MySqlDriver::fetch(const std::string& query) {
    if (connected) {
        std::cout << "MySQL Driver: Fetching - " << query << std::endl;
        return "MySQL result data";
    }
    return "";
}

bool MySqlDriver::isConnected() const {
    return connected;
}

std::string MySqlDriver::getDriverInfo() const {
    return "MySQL Driver v8.0";
}

void MySqlDriver::beginTransaction() {
    inTransaction = true;
    std::cout << "MySQL Driver: Transaction started" << std::endl;
}

void MySqlDriver::commitTransaction() {
    inTransaction = false;
    std::cout << "MySQL Driver: Transaction committed" << std::endl;
}

void MySqlDriver::rollbackTransaction() {
    inTransaction = false;
    std::cout << "MySQL Driver: Transaction rolled back" << std::endl;
}

// DatabaseConnection implementation
DatabaseConnection::DatabaseConnection(std::shared_ptr<DatabaseDriver> driver) : driver(driver) {}

bool DatabaseConnection::connect(const std::string& connectionString) {
    return driver->connect(connectionString);
}

void DatabaseConnection::disconnect() {
    driver->disconnect();
}

bool DatabaseConnection::executeQuery(const std::string& query) {
    return driver->execute(query);
}

std::string DatabaseConnection::fetchData(const std::string& query) {
    return driver->fetch(query);
}

bool DatabaseConnection::isConnected() const {
    return driver->isConnected();
}

std::string DatabaseConnection::getConnectionInfo() const {
    return driver->getDriverInfo();
}

} // namespace bridge
} // namespace structural
} // namespace patterns
