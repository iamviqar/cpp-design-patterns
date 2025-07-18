#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace patterns {
namespace structural {
namespace adapter {

// Media Player example - adapting different audio formats

// Target interface that client expects
class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
    virtual std::vector<std::string> getSupportedFormats() const = 0;
};

// Adaptee interfaces - existing classes with incompatible interfaces
class Mp3Player {
public:
    virtual ~Mp3Player() = default;
    virtual void playMp3(const std::string& fileName) = 0;
    virtual bool isValidMp3File(const std::string& fileName) const = 0;
};

class Mp4Player {
public:
    virtual ~Mp4Player() = default;
    virtual void playMp4Video(const std::string& fileName) = 0;
    virtual void extractAudioFromMp4(const std::string& fileName) = 0;
    virtual bool isValidMp4File(const std::string& fileName) const = 0;
};

class VlcPlayer {
public:
    virtual ~VlcPlayer() = default;
    virtual void playVlc(const std::string& fileName) = 0;
    virtual void playAvi(const std::string& fileName) = 0;
    virtual std::string getPlayerVersion() const = 0;
};

// Concrete implementations of adaptees
class AdvancedMp3Player : public Mp3Player {
public:
    void playMp3(const std::string& fileName) override;
    bool isValidMp3File(const std::string& fileName) const override;
};

class AdvancedMp4Player : public Mp4Player {
public:
    void playMp4Video(const std::string& fileName) override;
    void extractAudioFromMp4(const std::string& fileName) override;
    bool isValidMp4File(const std::string& fileName) const override;
};

class AdvancedVlcPlayer : public VlcPlayer {
public:
    void playVlc(const std::string& fileName) override;
    void playAvi(const std::string& fileName) override;
    std::string getPlayerVersion() const override;
};

// Adapter that makes adaptees compatible with target interface
class MediaAdapter : public MediaPlayer {
public:
    MediaAdapter(const std::string& audioType);
    void play(const std::string& audioType, const std::string& fileName) override;
    std::vector<std::string> getSupportedFormats() const override;
    
private:
    std::unique_ptr<Mp3Player> mp3Player;
    std::unique_ptr<Mp4Player> mp4Player;
    std::unique_ptr<VlcPlayer> vlcPlayer;
    std::string primaryType;
};

// Client class that uses the target interface
class AudioPlayer : public MediaPlayer {
public:
    AudioPlayer();
    void play(const std::string& audioType, const std::string& fileName) override;
    std::vector<std::string> getSupportedFormats() const override;
    
    void setVolume(int volume);
    int getVolume() const;
    void showPlaylist() const;
    void addToPlaylist(const std::string& audioType, const std::string& fileName);
    
private:
    std::unique_ptr<MediaAdapter> adapter;
    int volume;
    std::vector<std::pair<std::string, std::string>> playlist;
    bool isFormatSupported(const std::string& audioType) const;
};

// Database example - adapting different database interfaces

// Target interface for data access
class DatabaseConnection {
public:
    virtual ~DatabaseConnection() = default;
    virtual bool connect(const std::string& connectionString) = 0;
    virtual void disconnect() = 0;
    virtual std::string executeQuery(const std::string& query) = 0;
    virtual bool executeUpdate(const std::string& query) = 0;
    virtual bool isConnected() const = 0;
    virtual std::string getConnectionInfo() const = 0;
};

// Legacy database systems with different interfaces
class MySqlLegacyApi {
public:
    virtual ~MySqlLegacyApi() = default;
    virtual int mysql_connect(const char* host, const char* user, const char* password, const char* database) = 0;
    virtual void mysql_close() = 0;
    virtual char* mysql_query_select(const char* query) = 0;
    virtual int mysql_query_update(const char* query) = 0;
    virtual int mysql_get_connection_status() = 0;
};

class PostgreSqlLegacyApi {
public:
    virtual ~PostgreSqlLegacyApi() = default;
    virtual bool pg_connect_db(const std::string& connStr) = 0;
    virtual void pg_disconnect_db() = 0;
    virtual std::string pg_exec_query(const std::string& sql) = 0;
    virtual bool pg_exec_command(const std::string& sql) = 0;
    virtual bool pg_is_connection_ok() = 0;
};

class MongoDbLegacyApi {
public:
    virtual ~MongoDbLegacyApi() = default;
    virtual int mongo_initialize(const std::string& uri) = 0;
    virtual void mongo_cleanup() = 0;
    virtual std::string mongo_find_documents(const std::string& collection, const std::string& filter) = 0;
    virtual bool mongo_insert_document(const std::string& collection, const std::string& document) = 0;
    virtual int mongo_connection_status() = 0;
};

// Concrete implementations of legacy APIs
class ConcreteMySqlApi : public MySqlLegacyApi {
public:
    int mysql_connect(const char* host, const char* user, const char* password, const char* database) override;
    void mysql_close() override;
    char* mysql_query_select(const char* query) override;
    int mysql_query_update(const char* query) override;
    int mysql_get_connection_status() override;
    
private:
    bool connected = false;
    std::string connectionInfo;
};

class ConcretePostgreSqlApi : public PostgreSqlLegacyApi {
public:
    bool pg_connect_db(const std::string& connStr) override;
    void pg_disconnect_db() override;
    std::string pg_exec_query(const std::string& sql) override;
    bool pg_exec_command(const std::string& sql) override;
    bool pg_is_connection_ok() override;
    
private:
    bool connected = false;
    std::string connectionString;
};

class ConcreteMongoDbApi : public MongoDbLegacyApi {
public:
    int mongo_initialize(const std::string& uri) override;
    void mongo_cleanup() override;
    std::string mongo_find_documents(const std::string& collection, const std::string& filter) override;
    bool mongo_insert_document(const std::string& collection, const std::string& document) override;
    int mongo_connection_status() override;
    
private:
    bool initialized = false;
    std::string mongoUri;
};

// Database adapters
class MySqlAdapter : public DatabaseConnection {
public:
    MySqlAdapter();
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    std::string executeQuery(const std::string& query) override;
    bool executeUpdate(const std::string& query) override;
    bool isConnected() const override;
    std::string getConnectionInfo() const override;
    
private:
    std::unique_ptr<MySqlLegacyApi> mysqlApi;
    std::string parseConnectionString(const std::string& connStr, const std::string& key) const;
};

class PostgreSqlAdapter : public DatabaseConnection {
public:
    PostgreSqlAdapter();
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    std::string executeQuery(const std::string& query) override;
    bool executeUpdate(const std::string& query) override;
    bool isConnected() const override;
    std::string getConnectionInfo() const override;
    
private:
    std::unique_ptr<PostgreSqlLegacyApi> pgApi;
    std::string currentConnectionString;
};

class MongoDbAdapter : public DatabaseConnection {
public:
    MongoDbAdapter();
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    std::string executeQuery(const std::string& query) override;
    bool executeUpdate(const std::string& query) override;
    bool isConnected() const override;
    std::string getConnectionInfo() const override;
    
private:
    std::unique_ptr<MongoDbLegacyApi> mongoApi;
    std::string currentUri;
    std::string parseCollectionFromQuery(const std::string& query) const;
    std::string parseFilterFromQuery(const std::string& query) const;
};

// Database connection factory
class DatabaseConnectionFactory {
public:
    enum class DatabaseType {
        MYSQL,
        POSTGRESQL,
        MONGODB
    };
    
    static std::unique_ptr<DatabaseConnection> createConnection(DatabaseType type);
    static DatabaseType parseTypeFromConnectionString(const std::string& connectionString);
    static std::vector<std::string> getSupportedDatabases();
};

// Third-party library example - adapting graphics libraries

// Target interface for drawing
class GraphicsRenderer {
public:
    virtual ~GraphicsRenderer() = default;
    virtual void initialize(int width, int height) = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2, const std::string& color) = 0;
    virtual void drawRectangle(int x, int y, int width, int height, const std::string& color) = 0;
    virtual void drawCircle(int x, int y, int radius, const std::string& color) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;
    virtual std::string getRendererInfo() const = 0;
};

// Third-party graphics libraries (adaptees)
class OpenGLRenderer {
public:
    virtual ~OpenGLRenderer() = default;
    virtual void glInit(int w, int h) = 0;
    virtual void glDrawLine(float x1, float y1, float x2, float y2, float r, float g, float b) = 0;
    virtual void glDrawQuad(float x, float y, float w, float h, float r, float g, float b) = 0;
    virtual void glDrawCircle(float cx, float cy, float radius, float r, float g, float b) = 0;
    virtual void glClear(float r, float g, float b) = 0;
    virtual void glSwapBuffers() = 0;
    virtual std::string glGetVersion() = 0;
};

class DirectXRenderer {
public:
    virtual ~DirectXRenderer() = default;
    virtual bool d3dInitialize(unsigned int width, unsigned int height) = 0;
    virtual void d3dRenderLine(int startX, int startY, int endX, int endY, unsigned int color) = 0;
    virtual void d3dRenderRectangle(int x, int y, int w, int h, unsigned int color) = 0;
    virtual void d3dRenderEllipse(int centerX, int centerY, int radiusX, int radiusY, unsigned int color) = 0;
    virtual void d3dClearScreen(unsigned int backgroundColor) = 0;
    virtual void d3dPresent() = 0;
    virtual std::string d3dGetDeviceInfo() = 0;
};

// Concrete implementations
class ConcreteOpenGLRenderer : public OpenGLRenderer {
public:
    void glInit(int w, int h) override;
    void glDrawLine(float x1, float y1, float x2, float y2, float r, float g, float b) override;
    void glDrawQuad(float x, float y, float w, float h, float r, float g, float b) override;
    void glDrawCircle(float cx, float cy, float radius, float r, float g, float b) override;
    void glClear(float r, float g, float b) override;
    void glSwapBuffers() override;
    std::string glGetVersion() override;
    
private:
    int width = 0, height = 0;
    bool initialized = false;
};

class ConcreteDirectXRenderer : public DirectXRenderer {
public:
    bool d3dInitialize(unsigned int width, unsigned int height) override;
    void d3dRenderLine(int startX, int startY, int endX, int endY, unsigned int color) override;
    void d3dRenderRectangle(int x, int y, int w, int h, unsigned int color) override;
    void d3dRenderEllipse(int centerX, int centerY, int radiusX, int radiusY, unsigned int color) override;
    void d3dClearScreen(unsigned int backgroundColor) override;
    void d3dPresent() override;
    std::string d3dGetDeviceInfo() override;
    
private:
    unsigned int screenWidth = 0, screenHeight = 0;
    bool deviceInitialized = false;
};

// Graphics adapters
class OpenGLAdapter : public GraphicsRenderer {
public:
    OpenGLAdapter();
    void initialize(int width, int height) override;
    void drawLine(int x1, int y1, int x2, int y2, const std::string& color) override;
    void drawRectangle(int x, int y, int width, int height, const std::string& color) override;
    void drawCircle(int x, int y, int radius, const std::string& color) override;
    void clear() override;
    void present() override;
    std::string getRendererInfo() const override;
    
private:
    std::unique_ptr<OpenGLRenderer> glRenderer;
    struct RGBColor { float r, g, b; };
    RGBColor parseColor(const std::string& color) const;
};

class DirectXAdapter : public GraphicsRenderer {
public:
    DirectXAdapter();
    void initialize(int width, int height) override;
    void drawLine(int x1, int y1, int x2, int y2, const std::string& color) override;
    void drawRectangle(int x, int y, int width, int height, const std::string& color) override;
    void drawCircle(int x, int y, int radius, const std::string& color) override;
    void clear() override;
    void present() override;
    std::string getRendererInfo() const override;
    
private:
    std::unique_ptr<DirectXRenderer> dxRenderer;
    unsigned int parseColorToUInt(const std::string& color) const;
};

// Graphics factory
class GraphicsRendererFactory {
public:
    enum class RendererType {
        OPENGL,
        DIRECTX
    };
    
    static std::unique_ptr<GraphicsRenderer> createRenderer(RendererType type);
    static std::vector<std::string> getAvailableRenderers();
};

} // namespace adapter
} // namespace structural
} // namespace patterns
