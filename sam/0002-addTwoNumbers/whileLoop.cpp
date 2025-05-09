// Source : https://leetcode.com/problems/add-two-numbers/
// Author : Sam Gillam
// Date   : 2025-05-08
// Run    : g++ whileLoop.cpp && ./a.out

/*********************************************************************
You are given two non-empty linked lists representing two 
non-negative integers. The digits are stored in reverse 
order, and each of their nodes contains a single digit. Add 
the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading 
zero, except the number 0 itself.

examples: 
1. 342 + 465 = 807
  in:   [2,4,3]
        [5,6,4]
  out:  [7,0,8]    
2. 
  in:   [0]
        [0]
  out:  [0]
3.
  in:   [9,9,9, 9,9,9, 9]
        [9,9,9, 9]
  out:  [8,9,9, 9,0,0, 0,1]
*********************************************************************/

#include <string>
#include <iostream>
using namespace std;

// defined by problem
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

string toString(ListNode* node){
    if(!node)
        return "nullptr";
    return to_string(node->val)
        + " -> "
        + toString(node->next);
}

class Solution {
public:
    // Complexity where N is length of l1 & M is length of l2
    // Time: BigO(max(N, M)) 
    // Space: BigO(max(N,M))
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;  
        ListNode headHolder(-1, nullptr);
        ListNode* tail = &headHolder;
        
        while(l1 || l2 || carry) {
            // cout << "l1: " << toString(l1) << endl;
            // cout << "l2: " << toString(l2) << endl;
            // cout << "carry: " << carry << endl;
            // cout << "result: " << toString(result) << endl;
            
            int sum = (l1 ? l1->val : 0) 
                    + (l2 ? l2->val : 0) 
                    + carry;

            // create and place new decimal node
            tail->next = new ListNode(sum % 10, nullptr);
            tail = tail->next;

            // setup for next round
            carry = sum / 10;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        
        // return the head of the generated ListNode chain
        return headHolder.next;
    }
};

ListNode* toListNode(int val){
    return new ListNode(
        val % 10,
        val > 9
            ? toListNode(val / 10)
            : nullptr);
}

void test(int i1, int i2, int iexpect){
    ListNode* l1 = toListNode(i1);
    ListNode* l2 = toListNode(i2);
    ListNode* expect = toListNode(iexpect);

    Solution s;
    ListNode* actual = s.addTwoNumbers(l1, l2);
    bool pass = toString(actual) == toString(expect);
    
    cout << (pass ? "PASS" : "FAILED") << endl;
    
    // cout << "  l1: " << toString(l1) << endl;
    // cout << "  l2: " << toString(l2) << endl;
    // cout << "  expect: " << toString(expect) << endl;
    // cout << "  actual: " << toString(actual) << endl;
}

int main(){
    test(1, 2, 3);
    test(99, 8, 107);
    test(10008, 4, 10012);
}
