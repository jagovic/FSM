/*  Events.H - Example header file  */
#if !defined( EVENTS_H )
#define EVENTS_H

namespace stateMachine
{
	// events
	struct beamReadyE {};
	struct beamOffE {};
	struct accessDeniedE {};
	struct beamOnE{};
	struct resetE{};

};


#endif // !defined( EVENTS_H )