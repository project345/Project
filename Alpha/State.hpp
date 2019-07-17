//@author Max Stewart //1086706, Elbert Alcantara //4435223, Sarang Han //5098495
#pragma once

namespace MESY {
	class State {
	public:
		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(float dt) = 0;
	};
}
