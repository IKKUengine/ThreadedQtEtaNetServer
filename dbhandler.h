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
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 people.db
 * 2. sqilte> CREATE TABLE people(ids integer primary key, name text);
 * 3. sqlite> .quit
 */
class DbHandler
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbHandler(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbHandler();

    bool isOpen() const;

    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable(QString name, QString headerTable);

    /**
     * @brief Add person data to db
     * @param name - name of person to add
     * @return true - person added successfully, false - person not added
     */
    bool addPerson(const QString& name);

    /**
     * @brief Remove person data from db
     * @param name - name of person to remove.
     * @return true - person removed successfully, false - person not removed
     */
    bool removePerson(const QString& name);

    /**
     * @brief Check if person of name "name" exists in db
     * @param name - name of person to check.
     * @return true - person exists, false - person does not exist
     */
    bool personExists(const QString& name) const;

    /**
     * @brief Print names of all persons in db
     */
    void printAllPersons() const;

    /**
     * @brief Remove all persons from db
     * @return true - all persons removed successfully, false - not removed
     */
    bool removeAllPersons();

private:
    QSqlDatabase m_db;
};

#endif // DBHANDLER_H
