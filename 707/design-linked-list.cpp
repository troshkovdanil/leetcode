#include <iostream>
#include <memory>
#include <utility>


class MyLinkedList {
	struct Node {
		int val;
		std::unique_ptr<Node> next;
		Node(int val) : val(val), next(nullptr) {}
	};
	std::unique_ptr<Node> head;
public:
	MyLinkedList() : head(nullptr) {}

	int get(int index) {
		auto cur = head.get();
		while (cur && index) {
			cur = cur->next.get();
			index--;
		}
		return cur ? cur->val : -1;
	}

	void addAtHead(int val) {
		auto n = std::make_unique<Node>(val);
		n->next = std::move(head);
		head = std::move(n);
	}

	void addAtTail(int val) {
		if (head == nullptr) {
			addAtHead(val);
		} else {
			auto cur = head.get();
			decltype(cur) prev = nullptr;
			while (cur) {
				prev = cur;
				cur = cur->next.get();
			}
			prev->next = std::make_unique<Node>(val);
		}
	}

	void addAtIndex(int index, int val) {
		if (index == 0) {
			addAtHead(val);
		} else if (head == nullptr) {
			return;
		} else {
			auto cur = head.get();
			decltype(cur) prev = nullptr;
			while (cur && index) {
				prev = cur;
				cur = cur->next.get();
				index--;
			}
			if (index) {
				return;
			}
			auto n = std::make_unique<Node>(val);
			n->next = std::move(prev->next);
			prev->next = std::move(n);
		}
	}

	void deleteAtIndex(int index) {
		auto cur = head.get();
		decltype(cur) prev = nullptr;
		while (cur && index) {
			prev = cur;
			cur = cur->next.get();
			index--;
		}
		if (cur) {
		       if (prev) {
			       prev->next = std::move(cur->next);
		       } else {
			       head = std::move(cur->next);
		       }
		}
	}

	void print() {
		std::cout << "[ ";
		auto cur = head.get();
		while (cur) {
			std::cout << cur-> val << " ";
			cur = cur->next.get();
		}
		std::cout << "]" << std::endl;
	}
};

int main() {
	auto list = new MyLinkedList();
#if 0
	list->addAtHead(1);
	list->deleteAtIndex(1);
	list->deleteAtIndex(1);
	list->addAtTail(7);
	list->deleteAtIndex(2);
	list->addAtTail(1);
	list->addAtTail(8);
	list->addAtHead(2);
	list->addAtIndex(5, 2);
	list->addAtTail(7);
	list->print();
	std::cout << list->get(2) << std::endl;
#endif
#if 0
	list->addAtHead(1);
	list->addAtTail(3);
	list->addAtIndex(1, 2);
	list->print();
	std::cout << list->get(1) << std::endl;
	list->deleteAtIndex(1);
	list->print();
	std::cout << list->get(1) << std::endl;
#endif
	list->addAtIndex(1, 0);
	list->print();
	std::cout << list->get(0) << std::endl;
	return 0;
}
