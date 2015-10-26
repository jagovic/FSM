//#include <iostream>
//// back-end
//#include <boost/msm/back/state_machine.hpp>
////front-end
//#include <boost/msm/front/state_machine_def.hpp>
//
//namespace msm = boost::msm;
//namespace mpl = boost::mpl;
//
//using namespace std;
//
//namespace
//{
//	// events
//	struct beamReadyE {};
//	struct beamOffE {};
//	struct accessDeniedE {};
//	struct beamOnE{};
//	struct resetE{};
//
//
//	// front-end: define the FSM structure 
//	struct roomSmachine : public msm::front::state_machine_def<roomSmachine>
//	{
//		template <class Event, class FSM>
//		void on_entry(Event const&, FSM&)
//		{
//			std::cout << "entering: Player" << std::endl;
//		}
//		template <class Event, class FSM>
//		void on_exit(Event const&, FSM&)
//		{
//			std::cout << "leaving: Player" << std::endl;
//		}
//
//		// The list of FSM states
//		struct beamOff : public msm::front::state<>
//		{
//			// every (optional) entry/exit methods get the event passed.
//			template <class Event, class FSM>
//			void on_entry(Event const&, FSM&) { std::cout << "entering: beamOff" << std::endl; }
//			template <class Event, class FSM>
//			void on_exit(Event const&, FSM&) { std::cout << "leaving: beamOff" << std::endl; }
//		};
//
//		struct beamReady : public msm::front::state<>
//		{
//			template <class Event, class FSM>
//			void on_entry(Event const&, FSM&) { std::cout << "entering: beamReady" << std::endl; }
//			template <class Event, class FSM>
//			void on_exit(Event const&, FSM&) { std::cout << "leaving: beamReady" << std::endl; }
//		};
//
//		struct beamOn : public msm::front::state<>
//		{
//			template <class Event, class FSM>
//			void on_entry(Event const&, FSM&) { std::cout << "entering: beamOn" << std::endl; }
//			template <class Event, class FSM>
//			void on_exit(Event const&, FSM&) { std::cout << "leaving: beamOn" << std::endl; }
//		};
//
//		struct accessDenied : public msm::front::state<>
//		{
//			template <class Event, class FSM>
//			void on_entry(Event const&, FSM&) { std::cout << "entering: accessDenied" << std::endl; }
//			template <class Event, class FSM>
//			void on_exit(Event const&, FSM&) { std::cout << "leaving: accessDenied" << std::endl; }
//		};
//
//		// the initial state of the player SM. Must be defined
//		typedef beamOff initial_state;
//
//		// transition actions
//		void start_beam(beamReadyE const&) { std::cout << "rSm::start_beam\n"; }
//		void close_beam(beamOffE const&) { std::cout << "rSm::close_beam\n"; }
//
//		void beamOffAccessDenied(accessDeniedE const&) { std::cout << "rSm::beamOffAccessDenied Beam\n"; }
//
//		void beamReadyAccessDenied(accessDeniedE const&) { std::cout << "rSm::beamReadyAccessDenied Beam\n"; }
//		void beamReadyOn(beamReadyE const&) { std::cout << "rSm::beamReadyOn\n"; }
//		void beamOnReadyAccessDenied(accessDeniedE const&) { std::cout << "rSm::beamOnReadyAccessDenied \n"; };
//
//		void beamOnReady(beamReadyE const&) { std::cout << "rSm::beamOnReady \n"; }
//		void beamOnOff(beamOffE const&) { std::cout << "rSm::beamOnOff \n"; }
//		void beamOnAccessDenied(accessDeniedE const&) { std::cout << "rSm::beamOnAccessDenied \n"; };
//
//		void beamAccessDeniedReady(resetE const&) { std::cout << "rSm::beamAccessDeniedReady \n"; };
//
//
//		typedef roomSmachine rSm; // makes transition table cleaner
//
//		// Transition table for player
//		struct transition_table : mpl::vector<
//			//    Start         Event         Next                    Action				 Guard
//			//    +-----------+--------------+----------------+---------------------+----------------------+
//			a_row < beamOff, beamReadyE, beamReady, &rSm::start_beam                           >,
//			a_row < beamOff, accessDeniedE, accessDenied, &rSm::beamOffAccessDenied                  >,
//			//    +-----------+--------------+--------------+---------------------+----------------------+
//			a_row < beamReady, beamOffE, beamOff, &rSm::close_beam                           >,
//			a_row < beamReady, beamReadyE, beamOn, &rSm::beamReadyOn                          >,
//			a_row < beamReady, accessDeniedE, accessDenied, &rSm::beamOnReadyAccessDenied              >,
//			//    +-----------+-------------+----------------+---------------------+---------------------+
//			a_row < beamOn, beamReadyE, beamReady, &rSm::beamOnReady                           >,
//			a_row < beamOn, beamOffE, beamOff, &rSm::beamOnOff                             >,
//			a_row < beamOn, accessDeniedE, accessDenied, &rSm::beamOnAccessDenied                    >,
//			//    +-----------+-------------+----------------+---------------------+------------------------+
//			a_row < accessDenied, resetE, beamReady, &rSm::beamAccessDeniedReady                 >
//			////    +---------+-------------+----------------+---------------------+------------------------+
//		> {};
//
//		// Replaces the default no-transition response.
//		template <class FSM, class Event>
//		void no_transition(Event const& e, FSM&, int state)
//		{
//			std::cout << "no transition from state " << state
//				<< " on event " << typeid(e).name() << std::endl;
//		}
//	};
//	// Pick a back-end
//	typedef msm::back::state_machine<roomSmachine> stateMachine;
//
//
//	//
//	// Testing utilities.
//	//
//	static char const* const state_names[] = { "beamOff", "beamReady", "beamOn", "accessDenied" };
//
//	void pstate(stateMachine const& p)
//	{
//		std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
//	}
//
//
//
//	void test()
//	{
//		stateMachine sM;
//		// needed to start the highest-level SM. This will call on_entry and mark the start of the SM
//		sM.start();
//		int idEvent = 1;
//		while (idEvent != 0)
//		{
//			system("CLS");
//			cout << "Event" << std::endl;
//			cout << "1- Event beamReadyE" << std::endl;
//			cout << "2- Event beamOffE" << std::endl;
//			cout << "3- Event beamReadyE" << std::endl;
//			cout << "4- Event accessDeniedE" << std::endl;
//			cout << "5- Current state" << std::endl;
//			cout << "0- Exit" << std::endl;
//			cin >> idEvent;
//
//			switch (idEvent)
//			{
//			case (1) :
//				sM.process_event(beamReadyE());
//				pstate(sM);
//				break;
//			case (2) :
//				sM.process_event(beamOffE());
//				pstate(sM);
//				break;
//
//			case (3) :
//				sM.process_event(beamReadyE());
//				pstate(sM);
//				break;
//			case (4) :
//				sM.process_event(accessDeniedE());
//				pstate(sM);
//				break;
//			case (5) :
//				pstate(sM);
//				break;
//			default:
//				cout << "Default" << endl;
//			}
//			system("PAUSE");
//		}
//		//// go to Open, call on_exit on Empty, then action, then on_entry on Open
//
//		std::cout << "stop fsm" << std::endl;
//		sM.stop();
//	}
//
//}
//
//int main()
//{
//	test();
//	return 0;
//}