//
//  DnsPerfApp.hpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#ifndef DnsPerfApp_hpp
#define DnsPerfApp_hpp

#include <memory>
#include <vector>
#include <string>
#include "DnsFacade.hpp"
#include "DataBaseConnector.hpp"

/* Singleton class */
class DnsPerfApp final {
public:
    static DnsPerfApp& GetInstance();
    int AppInit();
    void SetFrequence(int freq) { frequency_ = freq; }
    void Run();
private:
    // Data members
    std::unique_ptr<Db::DbConnInterface> db_ = nullptr;
    std::unique_ptr<Dns::DnsFacade> dns_ = nullptr;
    int frequency_; /**< How often to poll(run query) */

    // Get this from the web parsing or a config file. For now,
    std::vector<std::string> websites_ {
        "google.com",
        "outube.com",
        "facebook.com",
        "baidu.com",
        "wikipedia.org",
        "yahoo.com",
        "google.co.in",
        "reddit.com",
        "taobao.com"
    };

    DnsPerfApp() = default; //ctor
    ~DnsPerfApp() = default; // dtor
    DnsPerfApp(const DnsPerfApp&) = delete; //copy
    DnsPerfApp& operator=(const DnsPerfApp&) = delete; // copy assignement
    DnsPerfApp(const DnsPerfApp&&) = delete; //move
    DnsPerfApp& operator=(const DnsPerfApp&&) = delete; // move assignement
    
    void Reconcile(); // if restart
    //callback.
    void operator()(void);
};

#endif /* DnsPerfApp_hpp */
