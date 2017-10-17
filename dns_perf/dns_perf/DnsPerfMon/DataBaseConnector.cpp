//
//  DataBaseConnector.cpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#include "DataBaseConnector.hpp"

using namespace std;
using namespace Db;
using namespace chrono;

/**
 * Check if DB exists. If it does. This is most likely to be a restart scenario
 */
DbError MySqlDbConn::CreateDb (const std::string& db_name) {
    // Connect to database server
    mysqlpp::Connection con;
    try {
        con.connect(0, host_name_.c_str(), user_name_.c_str(),
                    password_.c_str());
    }
    catch (exception& er) {
        cerr << "Connection failed: " << er.what() << endl;
        return DbError::ConnectionFail;
    }
    // Create new database.  We suppress
    // exceptions, because it's not an error if DB doesn't yet exist.

    mysqlpp::NoExceptions ne(con);
    mysqlpp::Query query = con.query();
    if (con.select_db(db_name)) {
        /**
         * Database exists.
         * NOTE: This application assumes that database and tables are created
         * by this applicaiton only. There will be no intervention by the admin.
         */
        cerr << "Database exists so it is restart scenario\n";
        // Do nothing for now. This area can be leveraged later for handling
        // HA scenarios.
    }
    else {
        // Database doesn't exist yet, so create and select it.
        if (con.create_db(db_name) &&
            con.select_db(db_name)) {
        }
        else {
            cerr << "Error creating DB: " << con.error() << endl;
            return DbError::CreateDBFail;
        }
    }
    return DbError::NOERROR;
}

DbError MySqlDbConn::CreateTable() {
    // Connect to database server
    mysqlpp::Connection con;
    try {
        con.connect(0, host_name_.c_str(), user_name_.c_str(),
                    password_.c_str());
    }
    catch (exception& er) {
        cerr << "Connection failed: " << er.what() << endl;
        return DbError::ConnectionFail;
    }
    mysqlpp::NoExceptions ne(con);
    mysqlpp::Query query = con.query();
    if (con.select_db(db_name_)) {
        // Create sample data table within sample database.
            try {
                // check if table exists.
                query << "SELECT * FROM information_schema.tables "
                      << "WHERE table_schema = " <<  db_name_
                      << " AND table_name =" << table_name_ << " LIMIT 1";

                query.execute();
                /** Algorithm
                 * If table is present return.
                 * Else, create a table using Query
                 * CREATE TABLE 'table_name_' (
                 *      website, varchar
                 *      latency, double);
                 */
            }  catch (...) {
                return DbError::CreateTableFail;
            }
        
    } else {
        return DbError::CreateTableFail;
    }
    return DbError::NOERROR;
}


DbError MySqlDbConn::UpdateTime(const string website,
                                const duration<long long>) {
    // Run Select query to get top 10 columns and update the time
    // Keep track of last edited the row and moidfy only top 10 rows.
    return DbError::NOERROR;
}


duration<long long> MySqlDbConn::GetLatency(const std::string website) {
    //get top 10 rows and take the average and return .
    return duration<long long>(10); //hardcoded
}
