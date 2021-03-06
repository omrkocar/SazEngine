#pragma once

#include <Saz/System.h>

namespace Saz
{
	class GameTime;

	class Window;
	
}

namespace ecs 
{

	class SAZ_API InputSystem final : public System
	{
	public:
		
		InputSystem(Saz::Window& window);
		~InputSystem();

		virtual void Init() override;
		virtual void Update(const Saz::GameTime& gameTime) override;

	private:
		Saz::Window& m_Window;

		Set<Input::EKeyboard> m_KeyboardPrevious;
		Set<Input::EKeyboard> m_KeyboardCurrent;
		Set<Input::EMouse> m_MousePrevious;
		Set<Input::EMouse> m_MouseCurrent;
	};
}
