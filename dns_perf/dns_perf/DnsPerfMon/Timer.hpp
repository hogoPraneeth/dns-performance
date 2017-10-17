//
//  Timer.hpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/16/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

# include <chrono>
#include <functional>

class Timer {
public:
    Timer(std::function<void(long long)> callback);
    ~Timer();
private:
    std::chrono::steady_clock::time_point t0;
    std::function<void(long long)> cb;
};
#endif /* Timer_hpp */
