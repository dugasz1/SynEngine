#pragma once

#include <vector>

namespace SynEngine {
	template <class T>
	class Node
	{
	public:
		Node();
		~Node();
		std::string name;

		void AddElement(T element);
		void AddChild(Node<T> child);

		void ReserveElement(unsigned int size);
		void ReserveChildren(unsigned int size);
		void Reserve(unsigned int size);

		Node<T> * parent;
		std::vector<Node<T>*> children;
		std::vector<T> elements;
	private:
		
	};

	template<class T>
	SynEngine::Node<T>::Node() {
		parent == nullptr;
	}

	template<class T>
	SynEngine::Node<T>::~Node() {

	}

	template<class T>
	void SynEngine::Node<T>::AddElement(T element)
	{
		elements.push_back(element);
	}

	template<class T>
	void SynEngine::Node<T>::AddChild(Node<T> child)
	{
		children.push_back(child);
	}

	template<class T>
	void SynEngine::Node<T>::ReserveElement(unsigned int size)
	{
		elements.reserve(size);
	}

	template<class T>
	void SynEngine::Node<T>::ReserveChildren(unsigned int size)
	{
		children.reserve(size);
	}

	template<class T>
	void SynEngine::Node<T>::Reserve(unsigned int size)
	{
		ReserveElement(size);
		ReserveChildren(size);
	}

}