//
//  DnsPerfApp.hpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#ifndef DnsPerfApp_hpp
#define DnsPerfApp_hpp

#include <stdio.h>
#include <memory>
#include "DataBaseConnector.hpp"

/* Singleton class */
class DnsPerfApp final {
public:
    static DnsPerfApp& GetInstance();
    void AppInit();
private:
    // Data members
    std::unique_ptr<Db::DbConnInterface> db_ = nullptr;
    
    DnsPerfApp() = default; //ctor
    ~DnsPerfApp() = default; // dtor
    DnsPerfApp(const DnsPerfApp&) = delete; //copy
    DnsPerfApp& operator=(const DnsPerfApp&) = delete; // copy assignement
    DnsPerfApp(const DnsPerfApp&&) = delete; //move
    DnsPerfApp& operator=(const DnsPerfApp&&) = delete; // move assignement
    
    void Reconcile(); // if restart
    
};

#endif /* DnsPerfApp_hpp */
