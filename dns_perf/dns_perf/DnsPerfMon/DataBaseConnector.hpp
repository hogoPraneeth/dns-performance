//
//  DataBaseConnectorInterface.hpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#ifndef DataBaseConnectorInterface_hpp
#define DataBaseConnectorInterface_hpp

#include "mysql++.h"
#include <string>
#include <chrono>

namespace Db {
    enum class DbError {
        ConnectionFail,
        CreateDBFail,
        CreateTableFail,
        LookUpEntryFail,
        UpdateTableFail,
        DeleteEntryFail
    };

    /**
     * @brief: A Facade to database.
     * This interface is defined so that it could be used with other types
     * (non SQL) types of databases.
     */
    class DbConnInterface {
    public:
        virtual DbError CreateDb() = 0;
        virtual DbError CreateTable() = 0;
        virtual DbError UpdateTime(const std::string website,
            const std::chrono::high_resolution_clock::time_point) = 0;
        virtual std::chrono::high_resolution_clock::time_point
            GetTime(const std::string website) = 0;
    private:
    };

    /**
     * @brief: Concrete implementations of database facade to MySql
     */
    class MySqlDbConn : public DbConnInterface {
    public:
        DbError CreateDb();
        DbError CreateTable();
        DbError UpdateTime(const std::string website,
            const std::chrono::high_resolution_clock::time_point);
        std::chrono::high_resolution_clock::time_point
            GetTime(const std::string website);
    };
}



#endif /* DataBaseConnectorInterface_hpp */
