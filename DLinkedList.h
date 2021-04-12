#pragma once
#include"DLinkedList.h"
#include<string>
using namespace std;

template <typename Elem>
class DNode {
private:
	Elem elem;//���ȿ� �ִ� ����
	DNode *prev;//���� ��带 ���ϴ� ������
	DNode *next;//���� ��带 ���ϴ� ������
	friend class DLinkedList;//DLinkeListŬ������ ģ���� ����
	friend class Stack;//StackŬ������ ģ���� ����
};

template <typename Elem>
class DLinkedList {
public:
	DLinkedList();//������
	~DLinkedList();//�Ҹ���
	bool empty()const;//����ִ� �� Ȯ���ϴ� �Լ�
	const Elem& front()const;//�Ǿտ� �ִ� ��忡 ���Ҹ� ������
	const Elem& back() const;//�ǵڿ� �ִ� ��忡 ���Ҹ� ������
	void addFront(const Elem& e);//�Ǿտ� ��忡 ���ο� ��带 �߰��� 
	void addBack(const Elem& e);//�ǵڿ� ��忡 ���ο� ��带 �߰���
	void removeFront();//�Ǿտ� ��带 ����
	void removeBack();//�ǵڿ� ��带 ����
private:
	DNode* header;//header������
	DNode* trailer;//trailer������
	friend class Stack;//StackŬ������ ���ٰ����ϰ� �������
protected:
	void add(DNode*v, const Elem& e);//��带 �߰��ϴ� �Լ�
	void remove(DNode *v);//��带 �����ϴ� �Լ�
};
