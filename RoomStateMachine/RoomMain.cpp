#include <iostream>

#include "FSMstates.h"

using namespace std;
using namespace stateMachine;

namespace 
{
// Pick a back-end
typedef msm::back::state_machine<roomSmachine> stateMachine;

//
// Testing utilities.
//
static char const* const state_names[] = { "beamOff", "beamReady", "beamOn", "accessDenied" };

void pstate(stateMachine const& p)
{
	std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
}

void test()
{
	stateMachine sM;
	// needed to start the highest-level SM. This will call on_entry and mark the start of the SM
	sM.start();
	int idEvent=1;
	while (idEvent!=0)
	{
		system("CLS");
		cout << "Event" << std::endl;
		cout << "1- Event beamReadyE" << std::endl;
		cout << "2- Event beamOffE" << std::endl;
		cout << "3- Event beamReadyE" << std::endl;
		cout << "4- Event accessDeniedE" << std::endl;
		cout << "5- Current state" << std::endl;
		cout << "0- Exit" << std::endl;
		cin >> idEvent;
		
		switch (idEvent)
		{
		case (1) :
			sM.process_event(beamReadyE());
			pstate(sM);
			break;
		case (2):
			sM.process_event(beamOffE());
			pstate(sM);
			break;
				
		case (3):
			sM.process_event(beamReadyE());
			pstate(sM);
			break;
		case (4):
			sM.process_event(accessDeniedE());
			pstate(sM);
			break;
		case (5) :
			pstate(sM);
			break;
		default:
			cout << "Default" << endl;
		}
		system("PAUSE");
	}
	//// go to Open, call on_exit on Empty, then action, then on_entry on Open
	
	std::cout << "stop fsm" << std::endl;
	sM.stop();
}

}

int main()
{
	test();
	return 0;
}