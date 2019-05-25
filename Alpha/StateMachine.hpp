#pragma once

#include <memory>
#include <stack>
#include "State.hpp"
#include "DEFINITIONS.hpp"

namespace Sarang {
    typedef std::unique_ptr<State> StateRef;
    
    class StateMachine {
    public:     
        void AddState(StateRef newState, bool isReplacing = true);
        void ProcessStateChanges();
        StateRef &GetActiveState();
        
    private:
        std::stack<StateRef> _states;
        StateRef _newState;
        bool _isAdding;
        bool _isReplacing;
    };
}