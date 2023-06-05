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
            // head가 nullptr인 경우 새로운 노드를 head로 설정
            if (head.compare_exchange_weak(curHead, newNode, memory_order_acq_rel)) {
                break;  // 삽입 성공
            }
        }
        else {
            while (true) {
                if (newNode->value.act_time < curHead->value.act_time) {
                    if (curHead == oldHead) {
                        newNode->next = curHead;
                        newHead = newNode;  // 새로운 노드를 새로운 head로 설정
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

            // head 변경 시도
            if (head.compare_exchange_weak(oldHead, newHead, memory_order_acq_rel)) {
                break;  // 삽입 성공
            }
        }
    }
}

bool LFPQ::pop(TIMER_EVENT& value)
{
    Node* currentHead = head.load(memory_order_acquire);

    while (currentHead != nullptr) {
        if (currentHead->value.act_time < system_clock::now()) {
            Node* newHead = currentHead->next.load(memory_order_relaxed);

            if (head.compare_exchange_weak(currentHead, newHead, memory_order_release)) {
                value = currentHead->value;
                delete currentHead;
                return true;  // 조건에 맞는 값 제거 성공
            }

            currentHead = head.load(memory_order_acquire);
        }
        else {
            break;
        }
    }

    return false;  // 큐가 비어있거나 조건에 맞는 값이 없음
}

bool LFPQ::top(TIMER_EVENT& value)
{
    Node* currentHead = head.load(memory_order_acquire);

    if (currentHead == nullptr) {
        return false;  // 큐가 비어있음
    }

    value = currentHead->value;
    return true;
}
