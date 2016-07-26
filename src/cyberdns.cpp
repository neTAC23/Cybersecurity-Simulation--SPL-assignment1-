#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../include/cyberdns.h"
using namespace std;

  CyberDNS::CyberDNS(): cyber_DNS_() {
  };

  CyberDNS::~CyberDNS() { //iterate through dns map and delete computers
	map<const string, CyberPC &>::iterator it;
    for (it=cyber_DNS_.begin(); it!=cyber_DNS_.end(); ++it) {
    	delete &(it->second);
    }
  }

  void CyberDNS::AddPC(CyberPC & cyber_pc_) { //insert by map function
	  cyber_DNS_.insert(pair<string, CyberPC&> (cyber_pc_.getName(), cyber_pc_));
  }

  CyberPC & CyberDNS::GetCyberPC(const string & cyber_pc_name) const {
	  return cyber_DNS_.find(cyber_pc_name)->second;
  }

   vector<string> CyberDNS::GetCyberPCList() {
     vector <string> pclist;
     map<const string, CyberPC &>::reverse_iterator it;
     for (it=cyber_DNS_.rbegin(); it!=cyber_DNS_.rend(); ++it) {
     	pclist.push_back (it->first);
     }

     return pclist; // Return list of PC's as a vector of strings by reverse iterate
   }
