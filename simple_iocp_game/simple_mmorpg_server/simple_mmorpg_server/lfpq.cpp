#include "stdafx.h"
#include "lfpq.h"

LFPQ::LFPQ()
{
	head = nullptr;
}

LFPQ::~LFPQ()
{
}

void LFPQ::emplace(const TIMER_EVENT& value) {
    Node* newNode = new Node(value);

    while (true) {
        Node* oldHead = head.load(memory_order_acquire);
        Node* curHead = oldHead;
        Node* newHead = oldHead;
        Node* prev = nullptr;

        if (curHead == nullptr) {
            // head�� nullptr�� ��� ���ο� ��带 head�� ����
            if (head.compare_exchange_weak(curHead, newNode, memory_order_acq_rel)) {
                break;  // ���� ����
            }
        }
        else {
            while (true) {
                if (newNode->value.act_time < curHead->value.act_time) {
                    if (curHead == oldHead) {
                        newNode->next = curHead;
                        newHead = newNode;  // ���ο� ��带 ���ο� head�� ����
                    }
                    else {
                        prev->next = newNode;
                        newNode->next = curHead;
                    }
                    break;
                }
                else {
                    prev = curHead;
                    curHead = curHead->next;

                    if (curHead == nullptr) {
                        prev->next = newNode;
                        break;
                    }
                }
            }

            // head ���� �õ�
            if (head.compare_exchange_weak(oldHead, newHead, memory_order_acq_rel)) {
                break;  // ���� ����
            }
        }
    }
}

bool LFPQ::pop(TIMER_EVENT& value)
{
    Node* currentHead = nullptr;
    Node* newHead = nullptr;

    while (true) {
        currentHead = head.load(std::memory_order_acquire);
        if (currentHead == nullptr) {
            return false;  // ť�� �������
        }

        if (currentHead->value.act_time < system_clock::now()) {
            newHead = currentHead->next.load(std::memory_order_relaxed);

            if (head.compare_exchange_weak(currentHead, newHead, std::memory_order_release)) {
                value = currentHead->value;
                try {
                    delete currentHead;
                }
                catch (...){
                    // ���� ó��
                    cout << "delete ���� �߻�\n";
                    return false;
                }                
                return true;
            }
        }
        else {
            return false;
        }
    }
}

bool LFPQ::top(TIMER_EVENT& value)
{
    Node* currentHead = head.load(memory_order_acquire);

    if (currentHead == nullptr) {
        return false;  // ť�� �������
    }

    value = currentHead->value;
    return true;
}
