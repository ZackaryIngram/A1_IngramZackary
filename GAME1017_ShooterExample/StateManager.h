#pragma once
#ifndef _STATES_MANAGER_
#define  _STATES_MANAGER_
#include "States.h"
#include <vector>
using namespace std;
class StateManager
{
private://public properties
	static vector<State*> s_states;
	static bool s_stateChange;
public: //Public methods
	static void Update();
	static void Render();
	static void PushState(State* pState); 
	static void PopState();
	static void ChangeState(State* pState);
	static void Quit(); 
	static vector<State*>& GetStates(); 
	static const bool StateChanging();
private://Private methods
	StateManager() {}
	
};

typedef StateManager STMA; // Creating a shorter alias

#endif

