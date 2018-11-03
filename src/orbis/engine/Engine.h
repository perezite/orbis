
namespace orb 
{
	class Engine
	{
	public:
		static Engine* instance();

		const bool isRunning() const { return m_isRunning; }

		void heartbeat();

	private:
		Engine() 
			: m_isRunning(true) 
		{ };

		virtual ~Engine() { }

	private: 
		bool m_isRunning;
	};

}