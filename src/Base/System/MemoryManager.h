#pragma once

#include <string>
#include <vector>

namespace System
{
	// singleton class which manages the memory of class members of a specific class
	template<class T>
	class MemoryManager
	{
	public:
		// get instance
		static MemoryManager* GetInstance();

		// dtor
		virtual ~MemoryManager();

		// get all managed objects
		std::vector<T*> GetAll();

		// add an object to be managed
		void Add(T* object);

		// delete all managed objects
		void DeleteAll();

	private: 
		// list of managed objects 
		std::vector<T*> m_objects;

		// singleton ctor
		MemoryManager() {}
	};
}

namespace System
{
	template <class T>
	MemoryManager<T>* MemoryManager<T>::GetInstance()
	{
		static MemoryManager<T> instance;
		return &instance;
	}

	template <class T>
	MemoryManager<T>::~MemoryManager()
	{
		DeleteAll();
	}

	template <class T>
	std::vector<T*> MemoryManager<T>::GetAll()
	{
		return m_objects;
	}

	template <class T>
	void MemoryManager<T>::Add(T* object)
	{
		m_objects.push_back(object);
	}

	template <class T>
	void MemoryManager<T>::DeleteAll()
	{
		for (unsigned int i = 0; i < m_objects.size(); i++)
			delete m_objects[i];

		m_objects.clear();
	}
}