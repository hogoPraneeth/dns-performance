//
//  Timer.cpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/16/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#include "Timer.hpp"

using namespace std;

/* Time class */
Timer::Timer(function<void(long long)> callback)
    : t0(chrono::steady_clock::now()) , cb(callback) {
        
}
Timer::~Timer(void) {
    auto  t1 = chrono::high_resolution_clock::now();
    auto nanos = chrono::duration_cast<chrono::nanoseconds>(t1-t0).count();
    cb(nanos);
}

