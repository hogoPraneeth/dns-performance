//
//  DnsPerfApp.cpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#include "DnsPerfApp.hpp"

using namespace std;

DnsPerfApp& DnsPerfApp::GetInstance() {
    static DnsPerfApp instance_;
    return instance_;
}

void DnsPerfApp::AppInit() {
    // init the DB
    // init dns facade
}
