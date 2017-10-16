//
//  DnsFacade.cpp
//  dns_perf
//
//  Created by Praneeth Patil on 10/15/17.
//  Copyright © 2017 Praneeth Patil. All rights reserved.
//

#include <iostream>

#include <arpa/nameser.h>
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

DnsFacade::DnsFacade(const std::string& server) : host_serv_(server) {}

LinuxDnsFacade::LinuxDnsFacade(const std::string& server) :
    DnsFacade(server){};

int LinuxDnsFacade::RunQuery(const std::string& website) {
    res_init();
    
    int response;
    unsigned char query_buffer[NS_MAXDNAME];

    /* c_in = Intenet, ns_t_srv = */
    response= res_query(website.c_str(), ns_c_in, ns_t_srv,
                        query_buffer, sizeof(query_buffer));
    if (response < 0) {
        cerr << "Error looking up service: '" << website << "'" << endl;
        return -1;
    }
    cout << "response :" << response << endl;
    return GetResponseCode(query_buffer, response);
}

unsigned int DnsFacade::GetResponseCode(unsigned char* buf, int response) {
    DNS_HEADER *hdr = reinterpret_cast<DNS_HEADER*> (buf);
    int nameservers = ntohs (hdr->ans_count);
    cout << "nameservers: " << nameservers << endl;
    ns_msg nsMsg;
    int  k = ns_initparse((unsigned char*)buf, response, &nsMsg);
    if (k == -1) {
        std::cerr << errno << " " << strerror (errno) << "\n";
        return 1;
    }
    for (int i = 0; i < nameservers; ++i) {
        RecordParseHelper(buf, response, "nameservers", ns_s_ns, i, &nsMsg);
    }
    return NOERROR;
}

/* Work in progress */
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
