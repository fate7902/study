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
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    while (true) {
        Node* prevNode = nullptr;
        Node* currNode = head.load();

        while (currNode != nullptr && currNode->value.act_time < value.act_time) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        newNode->next = currNode;
        if (prevNode == nullptr) {
            if (head.compare_exchange_weak(currNode, newNode))
                break;
        }
        else {
            if (prevNode->next.compare_exchange_weak(currNode, newNode))
                break;
        }
    }
}

bool LFPQ::pop(TIMER_EVENT& value)
{
    Node* currNode = head.load();
    if (currNode != nullptr && currNode->value.act_time < system_clock::now()) {
        if (head.compare_exchange_weak(currNode, currNode->next)) {
            value = currNode->value;
            delete currNode;
            return true;
        }
    }
    return false;
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
