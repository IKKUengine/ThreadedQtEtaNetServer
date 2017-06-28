#include <dbhandler.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbHandler::DbHandler(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbHandler::~DbHandler()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbHandler::isOpen() const
{
    return m_db.isOpen();
}

bool DbHandler::createTable(QString table, QString columns)
{
    bool success = false;

    QSqlQuery query;
    const QString CREATETABLE = "CREATE TABLE ";
    query.prepare(CREATETABLE + table + columns);
    //query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, name TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table: one might already exist.";
        success = false;
    }

    return success;
}

bool DbHandler::insertTuble(const QString& table, const QString& values)
{
    bool success = false;

    if (!table.isEmpty())
    {
        QSqlQuery queryAdd;
        const QString INSERTINTO = "INSERT INTO ";
        const QString VALUES = "VALUES ";
         queryAdd.prepare(INSERTINTO + table + VALUES + values);
//        queryAdd.prepare("INSERT INTO people (name) VALUES (:name)");
//        queryAdd.bindValue(":name", name);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add table failed: name cannot be empty";
    }

    return success;
}

bool DbHandler::deleteTuble(const QString& table, const QString& primaryKey)
{
    bool success = false;

//    if (personExists(name))
//    {
//        QSqlQuery queryDelete;
//        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
//        queryDelete.bindValue(":name", name);
//        success = queryDelete.exec();

//        if(!success)
//        {
//            qDebug() << "remove person failed: " << queryDelete.lastError();
//        }
//    }
//    else
//    {
//        qDebug() << "remove person failed: person doesnt exist";
//    }

    return success;
}

bool DbHandler::isTubel(const QString& table, const QString& primaryKey) const
{
    bool exists = false;

//    QSqlQuery checkQuery;
//    checkQuery.prepare("SELECT name FROM people WHERE name = (:name)");
//    checkQuery.bindValue(":name", name);

//    if (checkQuery.exec())
//    {
//        if (checkQuery.next())
//        {
//            exists = true;
//        }
//    }
//    else
//    {
//        qDebug() << "person exists failed: " << checkQuery.lastError();
//    }

    return exists;
}

void DbHandler::printAllTubel(const QString& table) const
{
    qDebug() << "Persons in db:";
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}

bool DbHandler::removeAllTubel(const QString& table)
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM people");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all persons failed: " << removeQuery.lastError();
    }

    return success;
}
