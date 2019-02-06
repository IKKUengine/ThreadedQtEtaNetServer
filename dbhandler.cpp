#include <dbhandler.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include "dialog.h"

DbHandler::DbHandler()
{
    QString path = "etaNet.db";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    m_db.open();

    if(!m_db.isOpen())
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
    return this->m_db.isOpen();
}



bool DbHandler::createControllTable(QString message)
{
    bool success = false;
    const QString VALUES = " VALUES ";
    const QString INSERT = "INSERT INTO ";
    QSqlQuery query;
    QStringList messageList2 = message.split(" (");
    initControllMatrix();
    QString cmatrix = INSERT + "'ControlMatrix' ('Object Name',  'Activity (on / off)', 'Prioritization', 'El. Power Limitation',  "
                                   "'Th. Power Limitation', 'Release Time', 'Operating Mode')" +
                                   VALUES + "(" + messageList2[0] + ", 'None', 'None', 'None', 'None', 'None', 'None')" + ";";
    success = query.prepare(cmatrix);
    if (success)
    {
        if(!query.exec())
        {
            qDebug() << "Couldn't create the table: one might already exist.";
            success = false;
        }
        else
        {
            qDebug() << "Table is created!";
        }

    }
    else
    {
        qDebug() << "Couldn't prepare the query to create table: identical column names are not allowed for uniqueness!";
    }
    return success;
}

bool DbHandler::createMonitoringTable(QString message)
{
    bool success = false;
    const QString CREATETABLE = "CREATE TABLE IF NOT EXISTS ";
    const QString VALUES = " VALUES ";
    QSqlQuery query;
    QStringList messageList = message.split(VALUES);

    QString header = CREATETABLE + messageList[0] + ";";
    success = query.prepare(header);
    if (success)
    {
        if(!query.exec())
        {
            qDebug() << "Couldn't create the table: one might already exist.";
            success = false;
        }
        else
        {
            qDebug() << "Table is created (Monitoring)!";
        }

    }
    else
    {
        qDebug() << "Couldn't prepare the query to create table: identical column names are not allowed for uniqueness!";
    }
    return success;
}


bool DbHandler::insertMonitoringTuble(QString& message)
{
    bool success = false;
    QSqlQuery query;
    if (!message.isEmpty() && !query.isActive())
    {
        const QString INSERT = "INSERT INTO ";
        if(query.exec(INSERT + message + ";"))
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


bool DbHandler::updateLastMonitoringTuble(QString& message)
{
    //DELETE FROM NameOfClient WHERE rowid = (SELECT MAX(rowid) FROM NameOfClient);
    //INSERT INTO NameOfClient ( 'DBHeader 1', 'DBHeader 2', 'DBHeader 3') VALUES (125, 369, 1233)
    bool success = false;
    const QString header = "'";
    QStringList messageList = message.split(header);
     qDebug() << "splitted header: " << messageList[1];
    QSqlQuery query;
    QString value;
    if (!message.isEmpty() && !query.isActive())
    {
        if(query.exec("SELECT MAX(rowid) FROM " + messageList[1] + ";"))
        {
                query.next();

                value = query.value(0).toString();

            qDebug() << "max rowid: " << value;
            if (value >= 0)
            {
                const QString DELETE = "DELETE FROM ";
                if(query.exec(DELETE + messageList[1] + " WHERE rowid = (SELECT MAX(rowid) FROM " + messageList[1] + ");"))
                {
                    success = true;
                }
                else
                {
                    qDebug() << "add tubel failed: " << query.lastError();
                }
            }
        }

        const QString INSERT = "INSERT INTO ";
        if(query.exec(INSERT + message + ";"))
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


bool DbHandler::log(){
    /*
    BEGIN IMMEDIATE;   -- wrap initial work in a single transaction
    -- Example Log Table
    CREATE TABLE IF NOT EXISTS Log ('Time', 'Text');
    -- Example Trigger to autogenerate datetime
    DROP TRIGGER IF EXISTS insert_Timer;
    CREATE TRIGGER IF NOT EXISTS insert_Timer AFTER  INSERT ON Log
         BEGIN
          UPDATE Log SET Time = strftime('%Y-%m-%dT%H:%M:%fZ','now')  WHERE rowid = new.rowid;
    -- Note: using full ISO8601 timestamp format
         END;
    INSERT INTO Log (Text) VALUES ('Data Logging Started');
    SELECT Count(*) FROM Log;    -- count of log entries
    COMMIT;
    */
    bool success = false;
    QSqlQuery query;
    if(query.exec("BEGIN IMMEDIATE;"
                   "CREATE TABLE IF NOT EXISTS Log ('Time', 'Text');"
                   "DROP TRIGGER IF EXISTS insert_Timer;"
                   "CREATE TRIGGER IF NOT EXISTS insert_Timer AFTER  INSERT ON Log BEGIN UPDATE Log SET Time = strftime('%Y-%m-%dT%H:%M:%fZ','now')  WHERE rowid = new.rowid;"
                   "END;"
                   "INSERT INTO Log (Text) VALUES ('Server was started or used');"
                   "SELECT Count(*) FROM Log;"
                   "COMMIT;"))
    {
        success = true;
    }
    else
    {
        qDebug() << "Cration Log-Table failed: " << query.lastError();
    }
    return success;

}

bool DbHandler::initControllMatrix(void)
{
    bool success = false;
    QSqlQuery query;
    const QString CREATETABLE = "CREATE TABLE IF NOT EXISTS ";
    QString header = CREATETABLE + "'ControlMatrix' ('Object Name' PRIMARY KEY, 'Activity (on / off)', "
                                   "'Prioritization', 'El. Power Limitation',  'Th. Power Limitation', "
                                   "'Release Time', 'Operating Mode')" + ";";
    success = query.prepare(header);
    if (success)
    {
        if(!query.exec())
        {
            qDebug() << "Couldn't create the table: one might already exist.";
            success = false;
        }
        else
        {
            qDebug() << "Table is created (Init)!";
        }

    }
    else
    {
        qDebug() << "Couldn't prepare the query to create table: identical column names are not allowed for uniqueness!";
    }
    return success;
}

QString DbHandler::selectControllValues(QString& name)
{
    QString value = " ; ; ; ; ; ";
       QSqlQuery query;
       if(query.exec("SELECT * FROM 'ControlMatrix' WHERE 'ControlMatrix'.'Object Name' = " + name + ";"))
       {
           query.next();
           value =  query.value(1).toString()+ "; ";
           value = value + query.value(2).toString()+ "; ";
           value = value + query.value(3).toString()+ "; ";
           value = value + query.value(4).toString()+ "; ";
           value = value + query.value(5).toString()+ "; ";
           value = value + query.value(6).toString();
        }
       qDebug() << value;
    return value;
}
