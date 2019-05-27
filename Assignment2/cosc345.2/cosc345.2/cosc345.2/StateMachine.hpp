//@author Max Stewart //1086706, Elbert Alcantara //4435223, Sarang Han //5098495
#pragma once
#include <memory>
#include <stack>
#include "State.hpp"
#include "DEFINITIONS.hpp"

namespace MESY {
    typedef std::unique_ptr<State> StateRef;
    
    class StateMachine {
    public:     
        void AddState(StateRef newState, bool isReplacing = true);
        void ProcessStateChanges();
        StateRef &GetActiveState();
        
    private:
        std::stack<StateRef> _states;
        StateRef _newState;
        bool _isAdding, _isReplacing;
    };
}
