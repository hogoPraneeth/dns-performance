//
//  DnsPerfApp.cpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//
#include <vector>
#include <string>
#include <memory>
# include <chrono>

#include "DnsPerfApp.hpp"
#include "DnsFacade.hpp"
#include "Timer.hpp"


using namespace std;
using namespace Dns;
using namespace Db;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

DnsPerfApp& DnsPerfApp::GetInstance() {
    static DnsPerfApp instance_;
    return instance_;
}

void DnsPerfApp::Reconcile() {
    // To be implemented.
    // start from where you left off. Database is the place to begine with
}

int DnsPerfApp::AppInit() {
    // Use Factory method if the need arises.
    // One design solution is to instantiate DB connectors (SQL, non-sql etc)
    // by command line argument or a config file.
    std::unique_ptr<DbConnInterface> db_con =
        make_unique<MySqlDbConn>("localhost", "root", "password");
    // Have a swtich case for DbError to reflect the state.
    if (db_con->CreateDb("DnsPerf") != DbError::NOERROR) {
        cerr << "Error encountered while accessing the DB\n";
        return -1;
    }
    Reconcile();
    // init dns facade
    dns_ = make_unique<LinuxDnsFacade>();
    return 0;
}

void DnsPerfApp::operator()() {
    for (auto& web : websites_) {
        auto start = get_time::now();
        dns_->RunQuery(web);
        auto end = get_time::now();
        auto diff = end - start;
        db_->UpdateTime(web, diff);
    }
}

void DnsPerfApp::Run() {
 
}



