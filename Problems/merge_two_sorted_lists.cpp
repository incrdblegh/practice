#include <iostream>

struct ListNode {
    int m_value{};
    ListNode* m_next{nullptr};
};

ListNode* mergeTwoLists(ListNode* A, ListNode* B) {
    ListNode head;
    ListNode* tail = &head;
    while (A && B) {
        if (A->m_value < B->m_value) {
            tail->m_next = A;
            A = A->m_next;
        } else {
            tail->m_next = B;
            B = B->m_next;
        }
        tail = tail->m_next;
    }
    tail->m_next = A ?: B;
    return head.m_next;
}

int main() {
    auto* head1 = new ListNode{1};
    head1->m_next = new ListNode{4};
    head1->m_next->m_next = new ListNode{6};
    head1->m_next->m_next->m_next = new ListNode{8};

    auto* head2 = new ListNode{2};
    head2->m_next = new ListNode{3};
    head2->m_next->m_next = new ListNode{10};

    auto* result = mergeTwoLists(head1, head2);

    for (auto* node = result; node != nullptr; node = node->m_next) {
        std::cout << node->m_value << "->";
    }
}
