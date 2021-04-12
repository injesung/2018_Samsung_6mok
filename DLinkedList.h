#pragma once
#include"DLinkedList.h"
#include<string>
using namespace std;

template <typename Elem>
class DNode {
private:
	Elem elem;//노드안에 있는 원소
	DNode *prev;//이전 노드를 향하는 포인터
	DNode *next;//다음 노드를 향하는 포인터
	friend class DLinkedList;//DLinkeList클래스와 친구를 맺음
	friend class Stack;//Stack클래스와 친구를 맺음
};

template <typename Elem>
class DLinkedList {
public:
	DLinkedList();//생성자
	~DLinkedList();//소멸자
	bool empty()const;//비어있는 지 확인하는 함수
	const Elem& front()const;//맨앞에 있는 노드에 원소를 내놓음
	const Elem& back() const;//맨뒤에 있는 노드에 원소를 내놓음
	void addFront(const Elem& e);//맨앞에 노드에 새로운 노드를 추가함 
	void addBack(const Elem& e);//맨뒤에 노드에 새로운 노드를 추가함
	void removeFront();//맨앞에 노드를 삭제
	void removeBack();//맨뒤에 노드를 삭제
private:
	DNode* header;//header포인터
	DNode* trailer;//trailer포인터
	friend class Stack;//Stack클래스가 접근가능하게 만들어줌
protected:
	void add(DNode*v, const Elem& e);//노드를 추가하는 함수
	void remove(DNode *v);//노드를 삭제하는 함수
};
