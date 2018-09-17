#include "..\..\include\SynEngine\Core\Pool.h"

#include <unordered_map>
#include <string>

namespace SynEngine {
	template <class T>
	class Pool
	{
	public:
		Pool();
		~Pool();

		void AddElement(std::string key, T element);
		T Find(std::string key);


	private:
		std::unordered_map<std::string, T> pool;
	};

	template<class T>
	SynEngine::Pool<T>::Pool() {

	}

	template<class T>
	SynEngine::Pool<T>::~Pool() {

	}

	template<class T>
	void SynEngine::Pool<T>::AddElement(std::string key,T element)
	{
		pool.insert({ key, element });
	}

	template<class T>
	T SynEngine::Pool<T>::Find(std::string key)
	{
		return pool.find(key);
	}
}