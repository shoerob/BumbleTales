/*
 *  FSM.h
 *  BoB
 *
 *  Created by Eric Duhon on 1/28/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include <vector>
#include <algorithm>
#include "FunctionObjects.h"
#include "Property.h"

namespace CR
{
	namespace Utility
	{
		struct StateHandlerBase
		{
			virtual void operator()() = 0; 
		};
		
		template<class T>
		class StateHandlerImpl : public StateHandlerBase
		{
		public:
			StateHandlerImpl(T *_object,void (T::*_func)()) : m_object(_object), m_func(_func) {}
			virtual void operator()()
			{
				(m_object->*m_func)();
			}
		private:
			T *m_object;
			void (T::*m_func)();
		};
		
		template<class T>
		StateHandlerBase* StateHandler(T *_object,void (T::*_func)())
		{
			return new StateHandlerImpl<T>(_object,_func);
		}
		
		template<int NumStates>
		class SimpleFSM
		{
		public:
			SimpleFSM() : m_state(0)
			{
				std::fill_n(std::back_inserter(m_handlers),NumStates,(StateHandlerBase*)NULL);
				State.Init(this,&SimpleFSM::GetState,&SimpleFSM::SetState);
			}
			~SimpleFSM()
			{
				CR::Utility::ForEach(m_handlers,CR::Utility::DeleteFO());
				m_handlers.clear();
			}
			void operator++(int _postfix)
			{
				if(m_state < (NumStates-1))
					m_state++;
			}
			void operator--(int _postfix)
			{
				if(m_state > 0)
					m_state--;
			}
			void Reset() { m_state = 0;}
			void operator()()
			{
				if(m_handlers[m_state] != NULL)
					(*m_handlers[m_state])();
			}
			void AddStateHandler(int _state,StateHandlerBase *_handler)
			{
				if(_state < (NumStates))
					m_handlers[_state] = _handler;
			}
			Property<int,SimpleFSM> State;
		private:
			int m_state;
			std::vector<StateHandlerBase*> m_handlers;
			int GetState() const {return m_state;}
			void SetState(int _state) {m_state = _state;}
		};
		
		class IState
		{
		public:
			static const unsigned int UNCHANGED = 0x80000000;
			static const unsigned int NEXT = 0x40000000;
			static const unsigned int PREVIOUS = 0x20000000;
			static const unsigned int DELAYED = 0x10000000;
			static const unsigned int DISABLED = 0x08000000;
			virtual bool Begin() {return false;}
			virtual void End() {}
			virtual int Process() {return UNCHANGED;}
		};
		
		template<typename StateInterface = IState>
		class FSM
		{
		public:
			FSM() : m_state(IState::DISABLED), m_skipUpdate(false), m_pendingState(IState::UNCHANGED)
			{
				State.Init(this,&FSM::GetState,&FSM::SetState);
			}
			~FSM()
			{
				CR::Utility::ForEach(m_states,CR::Utility::DeleteFO());
				m_states.clear();
			}
			FSM& operator<<(IState *_state) 
			{
				m_states.push_back(_state);
				return *this;
			}
			
			void operator++(int _postfix)
			{
				if(m_state < (m_states.size()-1))
					GoToState(m_state+1);
			}
			void operator--(int _postfix)
			{
				if(m_state > 0)
					GoToState(m_state-1);
			}
			void Reset() { m_state = 0;}
			void operator()()
			{
				if(m_state != IState::DISABLED)
				{
					if(m_state >= m_states.size())
						return;				
					
					if(!(m_pendingState & IState::UNCHANGED))
					{					
						if(m_pendingState & IState::NEXT)
							(*this)++;
						else if(m_pendingState & IState::PREVIOUS)
							(*this)--;
						else
							GoToState(m_pendingState);
					}					
					
					int new_state = IState::UNCHANGED;
					if(!m_skipUpdate && m_states[m_state] != NULL)
						new_state = m_states[m_state]->Process();
					m_skipUpdate = false;
					m_pendingState = IState::UNCHANGED;
					if(!(new_state & IState::UNCHANGED))
					{
						if(!(new_state & IState::DELAYED))
						{						
							if(new_state & IState::NEXT)
								(*this)++;
							else if(new_state & IState::PREVIOUS)
								(*this)--;
							else
								GoToState(new_state);
						}
						else
						{
							m_pendingState = new_state;
						}
					}
				}
			}			
			Property<unsigned int,FSM> State;
			void Disable() {m_state = IState::DISABLED;}
			StateInterface* operator->() 
			{
				if(m_state >= IState::DISABLED)
					return NULL;
				return dynamic_cast<StateInterface*>(m_states[m_state]);
			}
		private:
			static const unsigned int VALID_MASK = 0x0fffffff;
			bool m_skipUpdate; 
			unsigned int m_state;
			unsigned int m_pendingState;
			std::vector<IState*> m_states;
			unsigned int GetState() const {return m_state;}
			void SetState(unsigned int _state) {GoToState(_state);}
			void GoToState(unsigned int _state)
			{			
				_state = _state & VALID_MASK;
				if(_state == m_state)
					return;
				if(m_state != IState::DISABLED)
					m_states[m_state]->End();
				m_state = _state;
				if(m_state != IState::DISABLED)
					m_skipUpdate = m_states[m_state]->Begin();				
			}
		};
	}
}
