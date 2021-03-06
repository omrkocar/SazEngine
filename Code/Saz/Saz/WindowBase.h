#pragma once

#include <Saz/Core.h>

namespace Saz
{
	class GameTime;

	struct WindowProps
	{
		char* m_Title = nullptr;
		ivec2 m_Size;

		WindowProps(char* title = "Saz",
					ivec2 size = ivec2(1280, 720))
			: m_Title(title), m_Size(size)
		{}
	};

	// Interface representing a desktop system based Window
	class SAZ_API WindowBase
	{
	public:
		WindowBase() = delete;
		WindowBase(const WindowProps& props) {}
		virtual ~WindowBase() {}

		virtual void Init() {}
		virtual void PostInit() {}
		virtual void Destroy() {}

		virtual void Update(const Saz::GameTime& gameTime) = 0;

		virtual ivec2 GetSize() const = 0;
		virtual void SetSize(ivec2 newSize) = 0;

		virtual bool ShouldClose() const { return false; }

	private:
		WindowBase(const WindowBase&) = delete;
		WindowBase& operator=(const WindowBase&) = delete;
	};
}