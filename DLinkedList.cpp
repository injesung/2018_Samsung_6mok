#include "DLinkedList.h"

template <typename Elem>
DLinkedList::DLinkedList() {//생성자
	header = new DNode;//header를 동적할당
	trailer = new DNode;//trailer를 동적할당
	header->next = trailer;//헤더에 next가 trailer를 가르키게함
	trailer->prev = header;//트레일러의 prev가 헤더를 가르키게함
}
template <typename Elem>
DLinkedList::~DLinkedList() {//소멸자
	while (!empty())removeFront();//노드가 없을 때까지 앞에서 노드를 삭제함
	delete header;//헤더 동적할당 해지
	delete trailer;//트레일러 동적할당 해지
}
template <typename Elem>
void DLinkedList::add(DNode *v, const Elem& e) {//add함수
	DNode *u = new DNode;//새로운 노드 동적할당 
	u->elem = e;//노드에 원소를 넣음
	u->next = v;//새로운 노드에 next를 주어진 노드를 가르키게함
	u->prev = v->prev;//새로운 노드에 prev를 원래 v의 prev가 가르키는 곳을 가르키게함
	v->prev->next = u;//v의 prev의 next가 가르키는 곳을 새로운 노드로 가르키게함
	v->prev = u;//v의 prev가 u를 가르키게함
}
template <typename Elem>
void DLinkedList::addFront(const Elem&e)
{
	add(header->next, e);//헤더의 next앞에 새로운 노드추가
}
template <typename Elem>
void DLinkedList::addBack(const Elem& e)
{
	add(trailer, e);//트레일러앞에 새로운 노드 추가
}
template <typename Elem>
void DLinkedList::remove(DNode *v) {
	DNode *u = v->prev;//노드형 포인터 u를 만들고 v->prev값을 저장함
	DNode *w = v->next;//노드형 포인터 w를 만들고 v->next값을 저장함
	u->next = w;//u->next를 w를 가르키게함
	w->prev = u;//w->prev를 u로 가르키게함
	delete v;//v삭제
}
template <typename Elem>
void DLinkedList::removeFront() {
	remove(header->next);//header->next를 삭제
}
template <typename Elem>
void DLinkedList::removeBack() {
	remove(trailer->prev);//trailer->prev를 삭제
}
template <typename Elem>
bool DLinkedList::empty()const
{
	return (header->next == trailer);//헤더의 next가 트레일러를 가르키면 1을 결과값으로 냄
}
template <typename Elem>
const Elem& DLinkedList::front()const
{
	return(header->next->elem);//header->next의 원소값을 결과로냄
}
template <typename Elem>
const Elem& DLinkedList::back()const
{
	return(trailer->prev->elem);//trailer->prev의 원소값을 결과로냄
}