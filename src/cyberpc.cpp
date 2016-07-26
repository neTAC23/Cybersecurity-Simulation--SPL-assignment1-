#include "../include/cyberpc.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

  CyberPC::CyberPC(std::string cyber_pc_os, std::string cyber_pc_name) :
		  cyber_pc_os_(cyber_pc_os),cyber_pc_name_(cyber_pc_name),cyber_pc_connections_(), cyber_pc_time_to_infect_(-1)  {};

  CyberPC::~CyberPC() {
	  if (cyber_pc_time_to_infect_!=-1) 
		  delete cyber_worm_;
	 
  }

  const string CyberPC::getName() const {
	return cyber_pc_name_;
  }

  const string CyberPC::getOs() const{
	return cyber_pc_os_;
  }

  const int CyberPC::getTime() const {
	  return cyber_pc_time_to_infect_;
  }

  void CyberPC::setTime(int wormTime) {
	  cyber_pc_time_to_infect_=wormTime;
  }

  void CyberPC::AddConnection(string  second_pc) { //vector of connections for every computer
	cyber_pc_connections_.push_back(second_pc);
	cout << "	"	+ getName() + " now connected to " +second_pc << endl;
  }

  void CyberPC::Infect(CyberWorm & worm) {
    if (worm.getWormOs()==this->getOs()) {
    	if (cyber_pc_time_to_infect_!=-1) //if there is a worm delete it first
			delete cyber_worm_;
		this->setTime(worm.getWormTime()); //update new worm time
		this->cyber_worm_=new CyberWorm (worm); //create new worm
		cout << "		" + getName() + " infected by " + worm.getWormName() << endl;
    }
    else
      cout << "		" + worm.getWormName() + " is incompatible with " + getName() << endl;
  }

  void CyberPC::Run(const CyberDNS & server) { //connect computer, check status of worm
	  int check = this->getTime();
	  if (check!=-1) {
		  if (check>0) {
			  this->setTime(check-1);
			  cout <<"	" +getName()+ ": Worm " + cyber_worm_->getWormName() + " is dormant" << endl;
		  }
		  else {
			  cout <<"	" +getName() + " infecting..." << endl; //infect all computers connected
			  if (!cyber_pc_connections_.empty()) {
			    for (vector<string>::iterator it = cyber_pc_connections_.begin(); it!=cyber_pc_connections_.end(); ++it)
				    server.GetCyberPC(*it).Infect(*cyber_worm_);
			  }
		  }
	  }
  }

  void CyberPC::Disinfect() { //if there is a worm delete it.
	  if (this->getTime()!=-1) {
		  this->setTime(-1); //update worm time to flag (-1)
		  cout<< "		Worm " +cyber_worm_->getWormName() + " successfully removed from " + getName() << endl;
	  	  delete cyber_worm_;
		  cyber_worm_=NULL;
	  }
  }

  CyberPC::CyberPC(const CyberPC& other) : //copy constructor
	  cyber_pc_os_(other.cyber_pc_os_), cyber_pc_name_(other.cyber_pc_name_),cyber_pc_connections_(other.cyber_pc_connections_), 
	  cyber_worm_(other.cyber_worm_),cyber_pc_time_to_infect_(other.cyber_pc_time_to_infect_) {}
