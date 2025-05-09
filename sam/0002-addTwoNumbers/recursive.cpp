// Source : https://leetcode.com/problems/add-two-numbers/
// Author : Sam Gillam
// Date   : 2025-05-08
// Run    : g++ recursive.cpp && ./a.out

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

// defined by LeetCode
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Adds 2 number chains together
    ListNode* add(ListNode* l1, ListNode* l2, int carry = 0){
        // cout << "add() called" << endl 
        //     << "  " << toString(l1) << endl 
        //     << "  " << toString(l2) << endl;

        // value to be stored in decimal node being created
        int newVal = (l1 ? l1->val : 0)
                + (l2 ? l2->val : 0) 
                + carry;
        // value to carry over to the next decimal place
        // 0 if there is no value that needs to be carried over
        // 1 if there is (ex. newVal > 9)
        int newCarry = newVal / 10;

        if(newCarry || (l1 && l1->next) || (l2 && l2->next)) {
            // there is more to do (more decimal places
            // need to be added)
            return new ListNode(
                newVal % 10, 
                add((l1 ? l1->next : nullptr),
                    (l2 ? l2->next : nullptr),
                    newCarry));
        }
        else { 
            // end of chain (largest decimal place just finished)
            return new ListNode(newVal, nullptr);
        }
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2);
    }
};

// recursive func. builds chain from decimal side up
ListNode* toListNode(int val){
    ListNode* result = new ListNode(val % 10, nullptr);
    if(val > 9)
        result->next = toListNode(val / 10);
    return result;
}

string toString(ListNode* node){
    if(!node)
        return "nullptr";
    return to_string(node->val)
           + " -> "
           + toString(node->next);
}

// check if add(..) has expected output and print result
void test(int _l1, int _l2, int _expected){
    // turn int form into ListNode form
    ListNode* l1 = toListNode(_l1);
    ListNode* l2 = toListNode(_l2);
    ListNode* expected = toListNode(_expected);
    Solution s;
    ListNode* result = s.addTwoNumbers(l1, l2);

    // // print info
    cout << "  l1: " << toString(l1) << endl;
    cout << "  l2: " << toString(l2) << endl;
    cout << "  expected: " << toString(expected) << endl;
    cout << "  result: " << toString(result) << endl;

    // print result
    if(toString(result) == toString(expected))
        cout << "PASS" << endl;
    else {
        cout << "FAILED!!" << endl;
    }

}

int main(){
    // tests
    // ex: 1+2=3
    test(1,2,3);
    test(5,8,13);
    test(2,15,17);
    test(1,999,1000);
}
