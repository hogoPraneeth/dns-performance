//
//  AppMain.cpp : Application will be instantiated here.
//  dns_perf
//
//  Created by Praneeth Patil on 10/14/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#include <memory>
#include <iostream>

#include "DnsPerfApp.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "USAGE: Frequence of query is not specified.\n";
        return -1;
    }
    // Add some santiy checks for the ASCII to integer conversion.
    int frequence = atoi(argv[1]);
    DnsPerfApp& app = DnsPerfApp::GetInstance();
    assert(app.AppInit() == 0);
    app.SetFrequence(frequence);
    app.Run();
    
    return 0;
}
