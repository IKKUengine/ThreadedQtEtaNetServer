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

bool DbHandler::createTable(QString message)
{
    bool success = false;
    QSqlQuery query;
    QStringList messageList = message.split(';');
    const QString CREATETABLE = "CREATE TABLE ";
    query.prepare(CREATETABLE + messageList[0] + messageList[1]);
    //query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, name TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table: one might already exist.";
        success = false;
    }
    return success;
}

bool DbHandler::insertTuble(QString& message)
{
    bool success = false;
    if (!message.isEmpty())
    {
        QSqlQuery query;
        QStringList messageList = message.split(';');
        const QString VALUES = " VALUES ";
        const QString INSERT = "INSERT INTO ";
        if(query.exec(INSERT + messageList[0] + VALUES + messageList[2]))
        {
            success = true;
        }
        else
        {
            qDebug() << "add tubel failed: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "add tubel failed: message cannot be empty";
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
