#pragma once

#include <vector>
#include <list>

using namespace std;
#include "Input_Object.h"
#include "Input_Button.h"
//#include "AssetList.h"

class Input_Controller
	{
	public:
		virtual void InputChanged() = 0;
		vector<Input_Object*> input_objects;
	};

class Input_Engine
	{
	public:
		Input_Engine();
		virtual ~Input_Engine();
		
		bool RegisterInputController(Input_Controller* arg);
		bool UnregisterInputController();
		
		void Release();
		void AddRef(){ref_count++;}
		
		void Touched(Touch &_touch);
		void TouchMoved(Touch &_touch);
		//void TouchesEnded(std::vector<Touch> &_touches);
		
		//void DidAccelerate(UIAccelerometer *accelerometer, UIAcceleration *acceleration);
		// Input Objects
		//list<Input_Object*> input_objects;
		
		//Input_Button *CreateButton();
		//Input_Analog *CreateAnalogStick();
		
		void ResetControls();
		void InputChanged();
	private:
		void TransformTouch(Touch &_touch);
		Touch& GetTouch(int _id);
		Input_Controller *input_controller;
		long ref_count;
		std::vector<Touch> m_touches;
		float m_widthFactor;
		float m_heightFactor;
	};

Input_Engine* GetInputEngine();