#pragma once

namespace Input
{
	class InputManager
	{
	public:
		// get instance
		static InputManager& GetInstance();

		// update
		void Update();

		// is key down
		bool IsKeyDown();

		// is key tapped (down at current frame)
		bool IsKeyTapped();

		// temp: Is Quit
		bool TempIsQuit();

	protected:
		// Constructor
		InputManager();

		// Destructor
		virtual ~InputManager();

	private:
		// temp
		bool m_IsQuit;
	};
}