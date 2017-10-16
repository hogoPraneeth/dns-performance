//
//  DnsFacade.hpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/15/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#ifndef DnsFacade_hpp
#define DnsFacade_hpp


#include <string>

namespace  Dns {
    //DNS Header : Under works
    struct DNS_HEADER
    {
        unsigned int id; // identification number
    
        unsigned char rd :1; // recursion desired
        unsigned char tc :1; // truncated message
        unsigned char aa :1; // authoritive answer
        unsigned char opcode :4; // purpose of message
        unsigned char qr :1; // query/response flag
    
        unsigned char rcode :4; // response code
        unsigned char cd :1; // checking disabled
        unsigned char ad :1; // authenticated data
        unsigned char z :1; // its z! reserved
        unsigned char ra :1; // recursion available
    
        unsigned short q_count; // number of question entries
        unsigned short ans_count; // number of answer entries
        unsigned short auth_count; // number of authority entries
        unsigned short add_count; // number of resource entries
    };
    
    
    constexpr unsigned int NOERROR  =  0;
    constexpr unsigned int FORMERR  =  1;
    constexpr unsigned int SERVFAIL =  2;
    constexpr unsigned int NXDOMAIN =  3;
    constexpr unsigned int NOTIMP   =  4;
    constexpr unsigned int REFUSED  =  5;
    
    // Abstract class for DNS
    class DnsFacade {
    public:
        DnsFacade(const std::string& server);
        DnsFacade() = delete;
        DnsFacade(const DnsFacade&) = delete;
        DnsFacade& operator=(const DnsFacade&) = delete;
        DnsFacade& operator=(const DnsFacade&&) = delete;
        
        virtual int RunQuery(const std::string& website) = 0;
    protected:
        unsigned int GetResponseCode(unsigned char* buf,
                                     int response_size);
        std::string GenerateRandomStr(const std::string& website);
        void RecordParseHelper (unsigned char *buffer, size_t r,
                                const char *section, ns_sect s,
                                int idx, ns_msg *m);
    private:
        std::string host_serv_;        
    };
    class LinuxDnsFacade : public DnsFacade {
    public:
        LinuxDnsFacade(const std::string& website);
        LinuxDnsFacade() = delete;
        LinuxDnsFacade(const LinuxDnsFacade&) = delete;
        LinuxDnsFacade& operator=(const LinuxDnsFacade&) = delete;
        LinuxDnsFacade& operator=(const LinuxDnsFacade&&) = delete;
        
        int RunQuery(const std::string& website);
    };
}
#endif /* DnsFacade_hpp */
