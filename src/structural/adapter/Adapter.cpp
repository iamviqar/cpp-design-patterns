#include "Adapter.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>

namespace patterns {
namespace structural {
namespace adapter {

// AdvancedMp3Player implementation
void AdvancedMp3Player::playMp3(const std::string& fileName) {
    std::cout << "Playing MP3 file: " << fileName << std::endl;
}

bool AdvancedMp3Player::isValidMp3File(const std::string& fileName) const {
    return fileName.size() > 4 && 
           fileName.substr(fileName.size() - 4) == ".mp3";
}

// AdvancedMp4Player implementation
void AdvancedMp4Player::playMp4Video(const std::string& fileName) {
    std::cout << "Playing MP4 video file: " << fileName << std::endl;
}

void AdvancedMp4Player::extractAudioFromMp4(const std::string& fileName) {
    std::cout << "Extracting and playing audio from MP4 file: " << fileName << std::endl;
}

bool AdvancedMp4Player::isValidMp4File(const std::string& fileName) const {
    return fileName.size() > 4 && 
           fileName.substr(fileName.size() - 4) == ".mp4";
}

// AdvancedVlcPlayer implementation
void AdvancedVlcPlayer::playVlc(const std::string& fileName) {
    std::cout << "Playing VLC format file: " << fileName << std::endl;
}

void AdvancedVlcPlayer::playAvi(const std::string& fileName) {
    std::cout << "Playing AVI file with VLC: " << fileName << std::endl;
}

std::string AdvancedVlcPlayer::getPlayerVersion() const {
    return "VLC Media Player 3.0.18";
}

// MediaAdapter implementation
MediaAdapter::MediaAdapter(const std::string& audioType) : primaryType(audioType) {
    std::string lowerType = audioType;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    if (lowerType == "mp3") {
        mp3Player = std::make_unique<AdvancedMp3Player>();
    } else if (lowerType == "mp4") {
        mp4Player = std::make_unique<AdvancedMp4Player>();
    } else if (lowerType == "vlc" || lowerType == "avi") {
        vlcPlayer = std::make_unique<AdvancedVlcPlayer>();
    }
}

void MediaAdapter::play(const std::string& audioType, const std::string& fileName) {
    std::string lowerType = audioType;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    if (lowerType == "mp3" && mp3Player) {
        mp3Player->playMp3(fileName);
    } else if (lowerType == "mp4" && mp4Player) {
        mp4Player->extractAudioFromMp4(fileName);
    } else if (lowerType == "vlc" && vlcPlayer) {
        vlcPlayer->playVlc(fileName);
    } else if (lowerType == "avi" && vlcPlayer) {
        vlcPlayer->playAvi(fileName);
    } else {
        std::cout << "Unsupported format: " << audioType << std::endl;
    }
}

std::vector<std::string> MediaAdapter::getSupportedFormats() const {
    std::vector<std::string> formats;
    if (mp3Player) formats.push_back("mp3");
    if (mp4Player) formats.push_back("mp4");
    if (vlcPlayer) {
        formats.push_back("vlc");
        formats.push_back("avi");
    }
    return formats;
}

// AudioPlayer implementation
AudioPlayer::AudioPlayer() : volume(50) {
    // AudioPlayer natively supports basic formats
}

void AudioPlayer::play(const std::string& audioType, const std::string& fileName) {
    std::string lowerType = audioType;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    if (lowerType == "mp3") {
        std::cout << "AudioPlayer: Playing MP3 file " << fileName << " at volume " << volume << std::endl;
    } else if (isFormatSupported(lowerType)) {
        if (!adapter) {
            adapter = std::make_unique<MediaAdapter>(audioType);
        }
        adapter->play(audioType, fileName);
    } else {
        std::cout << "Unsupported audio format: " << audioType << std::endl;
    }
}

std::vector<std::string> AudioPlayer::getSupportedFormats() const {
    std::vector<std::string> formats = {"mp3"}; // Native support
    
    // Add formats supported through adapter
    std::vector<std::string> adaptedFormats = {"mp4", "vlc", "avi"};
    formats.insert(formats.end(), adaptedFormats.begin(), adaptedFormats.end());
    
    return formats;
}

void AudioPlayer::setVolume(int volume) {
    this->volume = std::max(0, std::min(100, volume));
}

int AudioPlayer::getVolume() const {
    return volume;
}

void AudioPlayer::showPlaylist() const {
    std::cout << "Current Playlist:" << std::endl;
    for (size_t i = 0; i < playlist.size(); ++i) {
        std::cout << (i + 1) << ". " << playlist[i].second 
                  << " (" << playlist[i].first << ")" << std::endl;
    }
}

void AudioPlayer::addToPlaylist(const std::string& audioType, const std::string& fileName) {
    if (isFormatSupported(audioType)) {
        playlist.emplace_back(audioType, fileName);
        std::cout << "Added to playlist: " << fileName << " (" << audioType << ")" << std::endl;
    } else {
        std::cout << "Cannot add unsupported format: " << audioType << std::endl;
    }
}

bool AudioPlayer::isFormatSupported(const std::string& audioType) const {
    std::string lowerType = audioType;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    return lowerType == "mp3" || lowerType == "mp4" || 
           lowerType == "vlc" || lowerType == "avi";
}

// ConcreteMySqlApi implementation
int ConcreteMySqlApi::mysql_connect(const char* host, const char* user, const char* password, const char* database) {
    std::cout << "MySQL: Connecting to " << host << " with user " << user << std::endl;
    connected = true;
    connectionInfo = std::string("mysql://") + user + "@" + host + "/" + database;
    return 1; // Success
}

void ConcreteMySqlApi::mysql_close() {
    std::cout << "MySQL: Connection closed" << std::endl;
    connected = false;
    connectionInfo.clear();
}

char* ConcreteMySqlApi::mysql_query_select(const char* query) {
    if (!connected) return nullptr;
    
    std::cout << "MySQL: Executing SELECT query: " << query << std::endl;
    static char result[] = "MySQL query result data";
    return result;
}

int ConcreteMySqlApi::mysql_query_update(const char* query) {
    if (!connected) return 0;
    
    std::cout << "MySQL: Executing UPDATE query: " << query << std::endl;
    return 1; // Success
}

int ConcreteMySqlApi::mysql_get_connection_status() {
    return connected ? 1 : 0;
}

// ConcretePostgreSqlApi implementation
bool ConcretePostgreSqlApi::pg_connect_db(const std::string& connStr) {
    std::cout << "PostgreSQL: Connecting with connection string: " << connStr << std::endl;
    connected = true;
    connectionString = connStr;
    return true;
}

void ConcretePostgreSqlApi::pg_disconnect_db() {
    std::cout << "PostgreSQL: Disconnected from database" << std::endl;
    connected = false;
    connectionString.clear();
}

std::string ConcretePostgreSqlApi::pg_exec_query(const std::string& sql) {
    if (!connected) return "";
    
    std::cout << "PostgreSQL: Executing query: " << sql << std::endl;
    return "PostgreSQL query result data";
}

bool ConcretePostgreSqlApi::pg_exec_command(const std::string& sql) {
    if (!connected) return false;
    
    std::cout << "PostgreSQL: Executing command: " << sql << std::endl;
    return true;
}

bool ConcretePostgreSqlApi::pg_is_connection_ok() {
    return connected;
}

// ConcreteMongoDbApi implementation
int ConcreteMongoDbApi::mongo_initialize(const std::string& uri) {
    std::cout << "MongoDB: Initializing connection to: " << uri << std::endl;
    initialized = true;
    mongoUri = uri;
    return 1; // Success
}

void ConcreteMongoDbApi::mongo_cleanup() {
    std::cout << "MongoDB: Cleaning up connection" << std::endl;
    initialized = false;
    mongoUri.clear();
}

std::string ConcreteMongoDbApi::mongo_find_documents(const std::string& collection, const std::string& filter) {
    if (!initialized) return "";
    
    std::cout << "MongoDB: Finding documents in " << collection << " with filter: " << filter << std::endl;
    return "{\"result\": \"MongoDB documents found\"}";
}

bool ConcreteMongoDbApi::mongo_insert_document(const std::string& collection, const std::string& document) {
    if (!initialized) return false;
    
    std::cout << "MongoDB: Inserting document into " << collection << ": " << document << std::endl;
    return true;
}

int ConcreteMongoDbApi::mongo_connection_status() {
    return initialized ? 1 : 0;
}

// MySqlAdapter implementation
MySqlAdapter::MySqlAdapter() {
    mysqlApi = std::make_unique<ConcreteMySqlApi>();
}

bool MySqlAdapter::connect(const std::string& connectionString) {
    // Parse connection string: mysql://user:password@host:port/database
    std::string host = parseConnectionString(connectionString, "host");
    std::string user = parseConnectionString(connectionString, "user");
    std::string password = parseConnectionString(connectionString, "password");
    std::string database = parseConnectionString(connectionString, "database");
    
    return mysqlApi->mysql_connect(host.c_str(), user.c_str(), password.c_str(), database.c_str()) == 1;
}

void MySqlAdapter::disconnect() {
    mysqlApi->mysql_close();
}

std::string MySqlAdapter::executeQuery(const std::string& query) {
    char* result = mysqlApi->mysql_query_select(query.c_str());
    return result ? std::string(result) : "";
}

bool MySqlAdapter::executeUpdate(const std::string& query) {
    return mysqlApi->mysql_query_update(query.c_str()) == 1;
}

bool MySqlAdapter::isConnected() const {
    return mysqlApi->mysql_get_connection_status() == 1;
}

std::string MySqlAdapter::getConnectionInfo() const {
    return "MySQL Database Connection";
}

std::string MySqlAdapter::parseConnectionString(const std::string& connStr, const std::string& key) const {
    // Simple parser for demonstration
    if (key == "host") return "localhost";
    if (key == "user") return "root";
    if (key == "password") return "password";
    if (key == "database") return "testdb";
    return "";
}

// PostgreSqlAdapter implementation
PostgreSqlAdapter::PostgreSqlAdapter() {
    pgApi = std::make_unique<ConcretePostgreSqlApi>();
}

bool PostgreSqlAdapter::connect(const std::string& connectionString) {
    currentConnectionString = connectionString;
    return pgApi->pg_connect_db(connectionString);
}

void PostgreSqlAdapter::disconnect() {
    pgApi->pg_disconnect_db();
    currentConnectionString.clear();
}

std::string PostgreSqlAdapter::executeQuery(const std::string& query) {
    return pgApi->pg_exec_query(query);
}

bool PostgreSqlAdapter::executeUpdate(const std::string& query) {
    return pgApi->pg_exec_command(query);
}

bool PostgreSqlAdapter::isConnected() const {
    return pgApi->pg_is_connection_ok();
}

std::string PostgreSqlAdapter::getConnectionInfo() const {
    return "PostgreSQL Database Connection: " + currentConnectionString;
}

// MongoDbAdapter implementation
MongoDbAdapter::MongoDbAdapter() {
    mongoApi = std::make_unique<ConcreteMongoDbApi>();
}

bool MongoDbAdapter::connect(const std::string& connectionString) {
    currentUri = connectionString;
    return mongoApi->mongo_initialize(connectionString) == 1;
}

void MongoDbAdapter::disconnect() {
    mongoApi->mongo_cleanup();
    currentUri.clear();
}

std::string MongoDbAdapter::executeQuery(const std::string& query) {
    // For MongoDB, we need to parse the query to extract collection and filter
    std::string collection = parseCollectionFromQuery(query);
    std::string filter = parseFilterFromQuery(query);
    return mongoApi->mongo_find_documents(collection, filter);
}

bool MongoDbAdapter::executeUpdate(const std::string& query) {
    // Parse MongoDB insert/update operation
    std::string collection = parseCollectionFromQuery(query);
    return mongoApi->mongo_insert_document(collection, query);
}

bool MongoDbAdapter::isConnected() const {
    return mongoApi->mongo_connection_status() == 1;
}

std::string MongoDbAdapter::getConnectionInfo() const {
    return "MongoDB Connection: " + currentUri;
}

std::string MongoDbAdapter::parseCollectionFromQuery(const std::string& query) const {
    // Simple parser - in real implementation, would parse MongoDB query syntax
    return "collection";
}

std::string MongoDbAdapter::parseFilterFromQuery(const std::string& query) const {
    // Simple parser - in real implementation, would parse MongoDB filter syntax
    return "{}";
}

// DatabaseConnectionFactory implementation
std::unique_ptr<DatabaseConnection> DatabaseConnectionFactory::createConnection(DatabaseType type) {
    switch (type) {
        case DatabaseType::MYSQL:
            return std::make_unique<MySqlAdapter>();
        case DatabaseType::POSTGRESQL:
            return std::make_unique<PostgreSqlAdapter>();
        case DatabaseType::MONGODB:
            return std::make_unique<MongoDbAdapter>();
        default:
            return nullptr;
    }
}

DatabaseConnectionFactory::DatabaseType DatabaseConnectionFactory::parseTypeFromConnectionString(const std::string& connectionString) {
    if (connectionString.find("mysql://") == 0) {
        return DatabaseType::MYSQL;
    } else if (connectionString.find("postgresql://") == 0 || connectionString.find("postgres://") == 0) {
        return DatabaseType::POSTGRESQL;
    } else if (connectionString.find("mongodb://") == 0) {
        return DatabaseType::MONGODB;
    }
    return DatabaseType::MYSQL; // Default
}

std::vector<std::string> DatabaseConnectionFactory::getSupportedDatabases() {
    return {"MySQL", "PostgreSQL", "MongoDB"};
}

// ConcreteOpenGLRenderer implementation
void ConcreteOpenGLRenderer::glInit(int w, int h) {
    width = w;
    height = h;
    initialized = true;
    std::cout << "OpenGL: Initialized with resolution " << w << "x" << h << std::endl;
}

void ConcreteOpenGLRenderer::glDrawLine(float x1, float y1, float x2, float y2, float r, float g, float b) {
    std::cout << "OpenGL: Drawing line from (" << x1 << "," << y1 << ") to (" 
              << x2 << "," << y2 << ") with color (" << r << "," << g << "," << b << ")" << std::endl;
}

void ConcreteOpenGLRenderer::glDrawQuad(float x, float y, float w, float h, float r, float g, float b) {
    std::cout << "OpenGL: Drawing quad at (" << x << "," << y << ") size " << w << "x" << h 
              << " with color (" << r << "," << g << "," << b << ")" << std::endl;
}

void ConcreteOpenGLRenderer::glDrawCircle(float cx, float cy, float radius, float r, float g, float b) {
    std::cout << "OpenGL: Drawing circle at (" << cx << "," << cy << ") radius " << radius 
              << " with color (" << r << "," << g << "," << b << ")" << std::endl;
}

void ConcreteOpenGLRenderer::glClear(float r, float g, float b) {
    std::cout << "OpenGL: Clearing screen with color (" << r << "," << g << "," << b << ")" << std::endl;
}

void ConcreteOpenGLRenderer::glSwapBuffers() {
    std::cout << "OpenGL: Swapping buffers" << std::endl;
}

std::string ConcreteOpenGLRenderer::glGetVersion() {
    return "OpenGL 4.6.0";
}

// ConcreteDirectXRenderer implementation
bool ConcreteDirectXRenderer::d3dInitialize(unsigned int width, unsigned int height) {
    screenWidth = width;
    screenHeight = height;
    deviceInitialized = true;
    std::cout << "DirectX: Device initialized with resolution " << width << "x" << height << std::endl;
    return true;
}

void ConcreteDirectXRenderer::d3dRenderLine(int startX, int startY, int endX, int endY, unsigned int color) {
    std::cout << "DirectX: Rendering line from (" << startX << "," << startY << ") to (" 
              << endX << "," << endY << ") with color 0x" << std::hex << color << std::dec << std::endl;
}

void ConcreteDirectXRenderer::d3dRenderRectangle(int x, int y, int w, int h, unsigned int color) {
    std::cout << "DirectX: Rendering rectangle at (" << x << "," << y << ") size " << w << "x" << h 
              << " with color 0x" << std::hex << color << std::dec << std::endl;
}

void ConcreteDirectXRenderer::d3dRenderEllipse(int centerX, int centerY, int radiusX, int radiusY, unsigned int color) {
    std::cout << "DirectX: Rendering ellipse at (" << centerX << "," << centerY << ") radii " 
              << radiusX << "x" << radiusY << " with color 0x" << std::hex << color << std::dec << std::endl;
}

void ConcreteDirectXRenderer::d3dClearScreen(unsigned int backgroundColor) {
    std::cout << "DirectX: Clearing screen with color 0x" << std::hex << backgroundColor << std::dec << std::endl;
}

void ConcreteDirectXRenderer::d3dPresent() {
    std::cout << "DirectX: Presenting frame" << std::endl;
}

std::string ConcreteDirectXRenderer::d3dGetDeviceInfo() {
    return "DirectX 12 Device";
}

// OpenGLAdapter implementation
OpenGLAdapter::OpenGLAdapter() {
    glRenderer = std::make_unique<ConcreteOpenGLRenderer>();
}

void OpenGLAdapter::initialize(int width, int height) {
    glRenderer->glInit(width, height);
}

void OpenGLAdapter::drawLine(int x1, int y1, int x2, int y2, const std::string& color) {
    auto rgb = parseColor(color);
    glRenderer->glDrawLine(static_cast<float>(x1), static_cast<float>(y1), 
                          static_cast<float>(x2), static_cast<float>(y2), 
                          rgb.r, rgb.g, rgb.b);
}

void OpenGLAdapter::drawRectangle(int x, int y, int width, int height, const std::string& color) {
    auto rgb = parseColor(color);
    glRenderer->glDrawQuad(static_cast<float>(x), static_cast<float>(y), 
                          static_cast<float>(width), static_cast<float>(height), 
                          rgb.r, rgb.g, rgb.b);
}

void OpenGLAdapter::drawCircle(int x, int y, int radius, const std::string& color) {
    auto rgb = parseColor(color);
    glRenderer->glDrawCircle(static_cast<float>(x), static_cast<float>(y), 
                            static_cast<float>(radius), rgb.r, rgb.g, rgb.b);
}

void OpenGLAdapter::clear() {
    glRenderer->glClear(0.0f, 0.0f, 0.0f); // Clear to black
}

void OpenGLAdapter::present() {
    glRenderer->glSwapBuffers();
}

std::string OpenGLAdapter::getRendererInfo() const {
    return "OpenGL Adapter using " + glRenderer->glGetVersion();
}

OpenGLAdapter::RGBColor OpenGLAdapter::parseColor(const std::string& color) const {
    // Simple color parser - in real implementation would handle hex, named colors, etc.
    if (color == "red") return {1.0f, 0.0f, 0.0f};
    if (color == "green") return {0.0f, 1.0f, 0.0f};
    if (color == "blue") return {0.0f, 0.0f, 1.0f};
    if (color == "white") return {1.0f, 1.0f, 1.0f};
    return {0.5f, 0.5f, 0.5f}; // Default gray
}

// DirectXAdapter implementation
DirectXAdapter::DirectXAdapter() {
    dxRenderer = std::make_unique<ConcreteDirectXRenderer>();
}

void DirectXAdapter::initialize(int width, int height) {
    dxRenderer->d3dInitialize(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

void DirectXAdapter::drawLine(int x1, int y1, int x2, int y2, const std::string& color) {
    unsigned int colorValue = parseColorToUInt(color);
    dxRenderer->d3dRenderLine(x1, y1, x2, y2, colorValue);
}

void DirectXAdapter::drawRectangle(int x, int y, int width, int height, const std::string& color) {
    unsigned int colorValue = parseColorToUInt(color);
    dxRenderer->d3dRenderRectangle(x, y, width, height, colorValue);
}

void DirectXAdapter::drawCircle(int x, int y, int radius, const std::string& color) {
    unsigned int colorValue = parseColorToUInt(color);
    dxRenderer->d3dRenderEllipse(x, y, radius, radius, colorValue);
}

void DirectXAdapter::clear() {
    dxRenderer->d3dClearScreen(0x000000); // Clear to black
}

void DirectXAdapter::present() {
    dxRenderer->d3dPresent();
}

std::string DirectXAdapter::getRendererInfo() const {
    return "DirectX Adapter using " + dxRenderer->d3dGetDeviceInfo();
}

unsigned int DirectXAdapter::parseColorToUInt(const std::string& color) const {
    // Simple color parser returning RGB packed into uint
    if (color == "red") return 0xFF0000;
    if (color == "green") return 0x00FF00;
    if (color == "blue") return 0x0000FF;
    if (color == "white") return 0xFFFFFF;
    return 0x808080; // Default gray
}

// GraphicsRendererFactory implementation
std::unique_ptr<GraphicsRenderer> GraphicsRendererFactory::createRenderer(RendererType type) {
    switch (type) {
        case RendererType::OPENGL:
            return std::make_unique<OpenGLAdapter>();
        case RendererType::DIRECTX:
            return std::make_unique<DirectXAdapter>();
        default:
            return nullptr;
    }
}

std::vector<std::string> GraphicsRendererFactory::getAvailableRenderers() {
    return {"OpenGL", "DirectX"};
}

} // namespace adapter
} // namespace structural
} // namespace patterns
