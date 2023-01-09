/*
Name: PARAG JAIN
U ID: U85118615
Description: Header file for CalcList
*/
#include <iostream>
#include "CalcListInterface.hpp"

class CalcListNode
{
    private:
        CalcListNode* prev;
        CalcListNode* next;
        FUNCTIONS operation;
        double nodeTotal;
        double operand;

    friend class CalcList;
};

class CalcList : public CalcListInterface
{
    public:
        CalcList();

        double total() const
        {
            return final;
        }
        void newOperation(const FUNCTIONS func, const double operand);
        void removeLastOperation();
        std::string toString(unsigned short precision) const;
        bool empty() 
        {
            return head->next == tail;
        }
        std::string getOperationString(unsigned int length, const CalcListNode* node, unsigned short prec) const;
        
    private:
        unsigned int size;
        CalcListNode* head;
        CalcListNode* tail;
        double final;
};