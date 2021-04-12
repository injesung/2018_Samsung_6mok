#include "DLinkedList.h"

template <typename Elem>
DLinkedList::DLinkedList() {//������
	header = new DNode;//header�� �����Ҵ�
	trailer = new DNode;//trailer�� �����Ҵ�
	header->next = trailer;//����� next�� trailer�� ����Ű����
	trailer->prev = header;//Ʈ���Ϸ��� prev�� ����� ����Ű����
}
template <typename Elem>
DLinkedList::~DLinkedList() {//�Ҹ���
	while (!empty())removeFront();//��尡 ���� ������ �տ��� ��带 ������
	delete header;//��� �����Ҵ� ����
	delete trailer;//Ʈ���Ϸ� �����Ҵ� ����
}
template <typename Elem>
void DLinkedList::add(DNode *v, const Elem& e) {//add�Լ�
	DNode *u = new DNode;//���ο� ��� �����Ҵ� 
	u->elem = e;//��忡 ���Ҹ� ����
	u->next = v;//���ο� ��忡 next�� �־��� ��带 ����Ű����
	u->prev = v->prev;//���ο� ��忡 prev�� ���� v�� prev�� ����Ű�� ���� ����Ű����
	v->prev->next = u;//v�� prev�� next�� ����Ű�� ���� ���ο� ���� ����Ű����
	v->prev = u;//v�� prev�� u�� ����Ű����
}
template <typename Elem>
void DLinkedList::addFront(const Elem&e)
{
	add(header->next, e);//����� next�տ� ���ο� ����߰�
}
template <typename Elem>
void DLinkedList::addBack(const Elem& e)
{
	add(trailer, e);//Ʈ���Ϸ��տ� ���ο� ��� �߰�
}
template <typename Elem>
void DLinkedList::remove(DNode *v) {
	DNode *u = v->prev;//����� ������ u�� ����� v->prev���� ������
	DNode *w = v->next;//����� ������ w�� ����� v->next���� ������
	u->next = w;//u->next�� w�� ����Ű����
	w->prev = u;//w->prev�� u�� ����Ű����
	delete v;//v����
}
template <typename Elem>
void DLinkedList::removeFront() {
	remove(header->next);//header->next�� ����
}
template <typename Elem>
void DLinkedList::removeBack() {
	remove(trailer->prev);//trailer->prev�� ����
}
template <typename Elem>
bool DLinkedList::empty()const
{
	return (header->next == trailer);//����� next�� Ʈ���Ϸ��� ����Ű�� 1�� ��������� ��
}
template <typename Elem>
const Elem& DLinkedList::front()const
{
	return(header->next->elem);//header->next�� ���Ұ��� ����γ�
}
template <typename Elem>
const Elem& DLinkedList::back()const
{
	return(trailer->prev->elem);//trailer->prev�� ���Ұ��� ����γ�
}