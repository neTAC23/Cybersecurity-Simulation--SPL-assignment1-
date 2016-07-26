#include "../include/main.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <istream>
#include <iostream>
#include <vector>
using boost::property_tree::ptree;
using namespace std;
using namespace boost;

int main () {
	int daysCounter=-1;
	int finish;
	//computers xml
    ptree pc;
    read_xml ("computers.xml", pc);
	CyberDNS *dns = new CyberDNS(); //create new dns map will be deleted in main
    BOOST_FOREACH (ptree::value_type const& v, pc.get_child("")) {
	  string name = v.second.get<string> ("name");
	  string os = v.second.get<string> ("os");
	  CyberPC *c = new CyberPC (os,name); //create new computer every time will be deleted through map
	  dns->AddPC(*c); //add pc to map
	  cout <<c->getName() + " connected to server" << endl;
    }
    //wires xml
    ptree wires;
    read_xml ("network.xml", wires); //add connections to every computer
    BOOST_FOREACH (ptree::value_type const&v, wires.get_child("")) {
    	string first = v.second.get<string> ("pointA");
    	string second = v.second.get<string> ("pointB");
    	cout <<"connecting " + first + " to " + second << endl;
    	dns->GetCyberPC(first).AddConnection(second);
    	dns->GetCyberPC(second).AddConnection(first);
    }
    //events xml
    ptree event;
    read_xml ("events.xml", event);
    vector<CyberExpert *> experts;
    vector<CyberExpert *>::iterator itExperts;
    vector<string>::iterator itComp;
    vector<string> pcList = dns->GetCyberPCList();
    itComp = pcList.begin();

    BOOST_FOREACH (ptree::value_type const&v, event.get_child("")) {
    	daysCounter++;
    	cout << "Day : " << daysCounter << endl;
    	//hack events
    	if (v.first == "hack") {
    		string comp = v.second.get<string> ("computer");
    		string wormName = v.second.get<string> ("wormName");
    		int wormDormancy = v.second.get<int> ("wormDormancy");
    		string wormOs = v.second.get<string> ("wormOs");
			cout << "	Hack occured on " + comp << endl;
    		CyberWorm *worm = new CyberWorm (wormOs, wormName, wormDormancy); //create new worm will be deleted in main
    		dns->GetCyberPC(comp).Infect(*worm); //send worm to computer, will be deleted through class computer
    		delete worm; //
    	}
    	//experts events
    	else if (v.first=="clock-in") {
    		string expertName = v.second.get<string> ("name");
    		int workTime = v.second.get<int> ("workTime");
    		int restTime = v.second.get<int> ("restTime");
    		int eff = v.second.get<int> ("efficiency");
    		CyberExpert *king = new CyberExpert (expertName, workTime, restTime, eff); //create new expert will be deleted in main
    		experts.push_back(king); //make a vector list of experts
    		cout << "	" + king->getExpertName() + " clocked in" << endl;
    	}
    	else
    		finish = v.second.get<int> ("time"); //finish event

//experts daily work
    	if (!experts.empty()) { //make sure there is an expert clocked in
			for (itExperts=experts.begin(); itExperts!=experts.end(); ++itExperts) { //iterate all experts
				(*itExperts)->updateCounter();
				if ((*itExperts)->isWorking()) { //if working clean computers
					for (int i=0; i<(*itExperts)->getEff(); i++) {
						(*itExperts)->Clean(dns->GetCyberPC(*itComp)); //clean computers, get computer from dns map
						if (*itComp==pcList.back()) //if finished list start all over again
							itComp = pcList.begin();
						else
							++itComp;
					}
				}
			}
    	}
//computers and worms daily work
    	vector<string>::iterator itRun;
    	for (itRun=pcList.begin(); itRun!=pcList.end(); ++itRun) {
    		dns->GetCyberPC(*itRun).Run(*dns);
    	}
    }
//termination time - experts and computers daily work till finish
    daysCounter++;
    for (int i=daysCounter; i<=finish; i++) {
    	cout << "Day : " << i << endl;
		if (!experts.empty()) {
			for (itExperts=experts.begin(); itExperts!=experts.end(); ++itExperts) {
				(*itExperts)->updateCounter();
				if ((*itExperts)->isWorking()) {
					for (int i=0; i<(*itExperts)->getEff(); i++) {
						(*itExperts)->Clean(dns->GetCyberPC(*itComp));
						if (*itComp==pcList.back())
							itComp = pcList.begin();
						else
							++itComp;
					}
				}
			}
		}
		vector<string>::iterator itRun;
		for (itRun=pcList.begin(); itRun!=pcList.end(); ++itRun) {
			dns->GetCyberPC(*itRun).Run(*dns);
		}
    }
//Deleting experts
    vector <CyberExpert*>::iterator itDeleteExp;
    for (itDeleteExp=experts.begin(); itDeleteExp!=experts.end(); ++itDeleteExp) {
    	delete *itDeleteExp;
    }
//Delete dns - will delete computers in DNS distructor and worms in computers distructor
    delete dns;
}
