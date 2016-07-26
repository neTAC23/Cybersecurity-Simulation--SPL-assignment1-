#include "../include/cyberexpert.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

    CyberExpert::CyberExpert(string cyber_expert_name, int cyber_expert_work_time, int cyber_expert_rest_time, int cyber_expert_efficiency):
    	cyber_expert_name_(cyber_expert_name), cyber_expert_work_time_(cyber_expert_work_time), cyber_expert_rest_time_(cyber_expert_rest_time),
		cyber_expert_efficiency_(cyber_expert_efficiency), isWorking_(true), counter_(0){};

 	void CyberExpert::Clean(CyberPC & cyber_pc) {
 		cout <<"	" + getExpertName() + " examining " + cyber_pc.getName() << endl;
 		if (cyber_pc.getTime()!=-1) //if there is a worm disinfect (-1 symbol for no worm)
 			cyber_pc.Disinfect();
    }

 	void CyberExpert::updateCounter() { //update experts rest\work time by counter and flipover isWorking status
 		if (cyber_expert_rest_time_>0){
		  counter_=counter_+1;
		  if (isWorking_==false && counter_-1==cyber_expert_rest_time_) { //rest -> working
			  isWorking_=true;
			  cout <<"	" + getExpertName() + " is back to work" << endl;
			  counter_=1; //reset counter
		  }
		  else {
			  if (isWorking_==true && counter_-1==cyber_expert_work_time_) { //working --> rest
			  isWorking_=false;
			  cout <<"	" + getExpertName() + " is taking a break" << endl;
			  counter_=1; //reset counter
			  }
		  }
		}
 	}

 	string CyberExpert::getExpertName() {
 		return cyber_expert_name_;
 	}

 	int CyberExpert::getEff() {
 		return cyber_expert_efficiency_;
 	}

 	bool CyberExpert::isWorking() { //working status
 		return isWorking_;
 	}


