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
    DbHandler(const QString& path);

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
     * @brief Creates a new table if it doesn't already exist
     * @param {QString} table - name of new table
     * @param {QString} columns - names of new header
     * @return {bool} true - table created successfully, false - table not created
     */
    bool createTable(QString table, QString columns);

    /**
     * @brief Add tubel into one of a tabels
     * @param {QString} table - name of table
     * @param {QString} columns - set of the values
     * @return true - person added successfully, false - person not added
     */
    bool insertTuble( const QString& table, const QString& values);

    /**
     * @brief Delete tubel from one of a tabels
     * @param {QString} table - name of table
     * @param {QString} columns - name of the primary Key
     * @return true - person removed successfully, false - person not removed
     */
    bool deleteTuble(const QString& table, const QString& primaryKey);

    /**
     * @brief Check if person of name "name" exists in db
     * @param {QString} table - name of table
     * @param {QString} columns - name of the primary Key
     * @return true - person exists, false - person does not exist
     */
    bool isTubel(const QString& table, const QString& primaryKey) const;

    /**
     * @brief Print all tubel into one of a tabels
     * @param {QString} table - name of table
     */
    void printAllTubel(const QString& table) const;

    /**
     * @brief Remove all tubel into one of a tabels
     * @param {QString} table - name of table
     * @return {bool} true - all persons removed successfully, false - not removed
     */
    bool removeAllTubel(const QString& table);

private:
    /**
     * @brief database object - represents a connection to a database.
     */
    QSqlDatabase m_db;
};

#endif // DBHANDLER_H
