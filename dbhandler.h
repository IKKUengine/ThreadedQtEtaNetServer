#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QSqlDatabase>

/**
 * \class DbHandler
 *
 * \brief SQL Database Handler class
 *
 * DbHandler sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database.
 * There are advantages and disadvantages to using a serverless db.
 * The main advantage is that there is no separate server process to install,
 * setup, configure, initialize, manage, and troubleshoot.
 * This is one reason why SQLite is a "zero-configuration" database engine.
 * etaNet application will be easier to handle.
 * The clients are not allowed to talk directly to the database,
 * because they should initially authenticated by the management.
 * And for security reasons, only the management should have access to db.
 */
class DbHandler
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param {const QString&} path - absolute path to db file
     */
    DbHandler();

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbHandler();

    /**
     * @brief Check if db exists and available
     * @return {bool} true - db reachable, false - db not reachable
     */
    bool isOpen() const;

    /**
     * @brief Creates a new monitoring table if it doesn't already exist
     * @param {QString} message - message to create the insert query
     * @return {bool} true - table created successfully, false - table not created
     */
    bool createMonitoringTable(QString message);

    /**
     * @brief Creates a new controll table if it doesn't already exist
     * @param {QString} message - message to create the insert query
     * @return {bool} true - table created successfully, false - table not created
     */
    bool createControllTable(QString message);

    /**
     * @brief Add tubel into one of a tabels
     * @param {QString} message - message to create the insert query
     * @return true - person added successfully, false - person not added
     */
    bool insertMonitoringTuble(QString& message);

    /**
     * @brief Creation of the Controll Matrix header
     * @return true - created successfully
     */
    bool initControllMatrix(void);

    /**
     * @brief Gets Controll Matrix String of one field element.
     * @param {QString} field element name
     * @return {QString} String of all controll parameters
     */
    QString selectControllValues(QString& name);

private:
    /**
     * @brief database object - represents a connection to a monitoring database.
     */
    QSqlDatabase m_db;

    /**
     * @brief Create a Log-Table
     * @return {bool} true - Log-Table creation was sucessful
     */
    bool log(void);
};

#endif // DBHANDLER_H
