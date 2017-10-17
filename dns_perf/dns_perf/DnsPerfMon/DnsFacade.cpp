//
//  DnsFacade.cpp. A DNS query helped class.
//  dns_perf
//
//  Created by Praneeth Patil on 10/15/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#include <iostream>


#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <resolv.h>

#include <functional>

#include "DnsFacade.hpp"

using namespace std;
using namespace Dns;

DnsFacade::DnsFacade() {}

LinuxDnsFacade::LinuxDnsFacade() : DnsFacade(){};

int LinuxDnsFacade::RunQuery(const std::string& website) {
    res_init();
    
    int response;
    unsigned char query_buffer[NS_MAXDNAME];

    /* c_in = Intenet, ns_t_srv = */
    string mangled_web = GenerateRandomStr(website);
    response= res_query(mangled_web.c_str(), ns_c_in, ns_t_srv,
                        query_buffer, sizeof(query_buffer));
    if (response < 0) {
        return -1;
    }
    return GetResponseCode(query_buffer, response);
}

unsigned int DnsFacade::GetResponseCode(unsigned char* buf, int response) {
    DNS_HEADER *hdr = reinterpret_cast<DNS_HEADER*> (buf);
    return (unsigned int)hdr->rcode;
}

/* Work in progress: For getting more data*/
void DnsFacade::RecordParseHelper (unsigned char *buffer, size_t r,
                                   const char *section, ns_sect s,
                                   int idx, ns_msg *m) {    
    ns_rr rr;
    int k = ns_parserr (m, s, idx, &rr);
    if (k == -1) {
        std::cerr << errno << " " << strerror (errno) << "\n";
        return;
    }

    std::cout << section << " " << ns_rr_name (rr) << " "
        << ns_rr_type (rr) << " " << ns_rr_class (rr)
        << ns_rr_ttl (rr) << " ";
    
    const size_t size = NS_MAXDNAME;
    unsigned char name[size];

    const u_char *data = ns_rr_rdata (rr);
    
    int pref = ns_get16 (data);
    ns_name_unpack (buffer, buffer + r, data + sizeof (u_int16_t),
                    name, size);
    char name2[size];
    ns_name_ntop (name, name2, size);
    std::cout << pref << " " << name2;
}

std::string DnsFacade::GenerateRandomStr(const std::string& website) {
    // use random humber generator % 26 for a random %6 times and prepend it
    // with "." and return.
    //
    return website;
};
