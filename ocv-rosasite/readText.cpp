#include "readText.hpp"
#include "OCRWrapper.hpp"
#include <sqlite3.h>
#include <ctime>
#include <chrono>

int callback(void* data, int argc, char** argv, char** colName)
{
    int* ID = (int*)data;
    *ID = std::atoi(argv[0]);
    return 0;
}

void createTables()
{
    sqlite3 *db = nullptr;
    int err = sqlite3_open("database.db", &db);
    if (err != SQLITE_OK)
        throw std::runtime_error("Can not read or create the database!");
    
    std::string createRunTypeTable = R"(
        CREATE TABLE IF NOT EXISTS RunType (
            ID      INTEGER PRIMARY KEY AUTOINCREMENT,
            NAME    TEXT    NOT NULL,
            UNIQUE(NAME)
    );)";
    
    char* errorMessage;
    err = sqlite3_exec(db, createRunTypeTable.c_str(), callback, nullptr, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
    
    std::string createRunTable = R"(
        CREATE TABLE IF NOT EXISTS Run (
            ID            INTEGER   PRIMARY KEY AUTOINCREMENT,
            RUNTYPE_ID    INTEGER   NOT NULL,
            TIMESTAMP     DATETIME  NOT NULL,
            RUNTIME       TIME      NOT NULL,
            IMAGE_PATH    TEXT      NOT NULL,
            FOREIGN KEY   (RUNTYPE_ID) REFERENCES RunType(ID)
    );)";
    
    err = sqlite3_exec(db, createRunTable.c_str(), callback, nullptr, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
    
    std::string createReadTextTable = R"(
        CREATE TABLE IF NOT EXISTS ReadTextResults (
            ID            INTEGER   PRIMARY KEY AUTOINCREMENT,
            RUN_ID        INT       NOT NULL,
            OCR_TEXT      TEXT      NOT NULL,
            FOREIGN KEY   (RUN_ID) REFERENCES Run(ID)
    );)";
    
    err = sqlite3_exec(db, createReadTextTable.c_str(), callback, nullptr, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
    
    std::string insertRunType = R"(
        INSERT OR IGNORE INTO RunType(NAME)
        VALUES ('ReadText')
    ;)";
    
    err = sqlite3_exec(db, insertRunType.c_str(), callback, nullptr, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
}

void addRecord(std::string path, std::string text, int runtime)
{
    sqlite3 *db = nullptr;
    char* errorMessage;
    sqlite3_stmt* sqlStatement;
    int runTypeID = 0;
    
    int err = sqlite3_open("database.db", &db);
    if (err != SQLITE_OK)
        throw std::runtime_error("Can not read or create the database!");
    
    std::string insertRun = R"(
        INSERT INTO Run (RUNTYPE_ID, TIMESTAMP, RUNTIME, IMAGE_PATH)
        VALUES(?1, ?2, ?3, ?4)
    ;)";
    
    err = sqlite3_prepare_v2(db, insertRun.c_str(), -1, &sqlStatement, nullptr);
    
    std::string queryID = "SELECT * FROM RunType WHERE NAME='ReadText';";
    err = sqlite3_exec(db, queryID.c_str(), callback, (void*)&runTypeID, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
    
    sqlite3_bind_int(sqlStatement, 1, runTypeID);
    sqlite3_bind_int64(sqlStatement, 2, time(nullptr));
    sqlite3_bind_int64(sqlStatement, 3, runtime);
    sqlite3_bind_text(sqlStatement, 4, path.c_str(), -1, nullptr);
    
    err = sqlite3_step(sqlStatement);
    if (err != SQLITE_DONE)
        throw std::runtime_error("Can not bind the given values!");
    
    long int lastID = sqlite3_last_insert_rowid(db);
    
    std::string insertReadTextResults = R"(
        INSERT INTO ReadTextResults(RUN_ID, OCR_TEXT)
        VALUES (?1, ?2)
    ;)";
    
    err = sqlite3_prepare_v2(db, insertReadTextResults.c_str(), -1, &sqlStatement, nullptr);
    
    sqlite3_bind_int(sqlStatement, 1, int(lastID));
    sqlite3_bind_text(sqlStatement, 2, text.c_str(), -1, nullptr);
    
    err = sqlite3_step(sqlStatement);
    if (err != SQLITE_DONE)
        throw std::runtime_error("Can not bind the given values!");
}

void preprocess(cv::Mat *image, int border)
{
    if (image->channels() != 1)
        cv::cvtColor(*image, *image, cv::COLOR_RGB2GRAY);
    
    cv::adaptiveThreshold(*image, *image, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 99, 30);
    cv::copyMakeBorder(*image, *image, image->rows * (float)border/100, image->rows * (float) border / 100, image->cols * (float) border / 100, image->cols * (float) border / 100, cv::BORDER_CONSTANT, 255);
}

std::string readText(cv::Mat image, int border, bool isWordToRecognize)
{
    preprocess(&image, border);
    OCR ocr(isWordToRecognize);
    return ocr.getText(&image);;
}

void readText(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<std::string> paths = inputHandler.getFilePaths();
    std::string textOCR;
    int runtime;
    
    createTables();
    for (int i = 0; i < images.size(); i++) {
        auto start = std::chrono::steady_clock::now();
        textOCR = readText(images.at(i));
        auto end = std::chrono::steady_clock::now();
        runtime = (int)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        addRecord(paths.at(i), textOCR, runtime);
        std::cout << textOCR << std::endl;
    }
}
