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
        NOERROR,
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
        DbConnInterface(std::string host, std::string user,
            std::string password) :
            host_name_(host) , user_name_(user), password_(password) {};
        virtual DbError CreateDb(std::string db_name) = 0;
        virtual DbError CreateTable() = 0;
        virtual DbError UpdateTime(const std::string website,
            const std::chrono::duration<long long>) = 0;
        virtual std::chrono::duration<long long>
            GetLatency(const std::string website) = 0;
    protected:
        std::string host_name_;
        std::string user_name_;
        std::string password_; // currently a plain test. Can use encryption
        std::string db_name_;
    };

    /**
     * @brief: Concrete implementations of database facade to MySql
     */
    class MySqlDbConn : public DbConnInterface {
    public:
        MySqlDbConn(std::string host, std::string user_name,
                    std::string password);
        DbError CreateDb(const std::string& db_name);
        DbError CreateTable();
        DbError UpdateTime(const std::string website,
            const std::chrono::duration<long long>);
        std::chrono::duration<long long>
            GetLatency(const std::string website);
    private:
        std::string table_name_{"dns_latency"}; /**< hardcoded in source
                                                 **< code as this is
                                                 **< application specific. */
    };
}



#endif /* DataBaseConnectorInterface_hpp */
