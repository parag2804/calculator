/*
Description: To make a calculator which can do operations and make a list of them.
Additionally, making a function to remove the last operation
*/
#include "CalcList.hpp"
#include <iomanip>
#include <sstream>

CalcList::CalcList()                                                        // Node Constructor
{
    final = 0.0;                                                            // Final initializing with zero
    head = new CalcListNode;
    tail = new CalcListNode;
    head->next = tail;
    tail->prev = head;
    size = 0;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand)     // performing new operation

{
    CalcListNode* newOP = new CalcListNode;
    newOP->operation = func;
    newOP->operand = operand;

    if(empty())
    {
        head->next = newOP;
        newOP->prev = head;
        newOP->next = tail;
        tail->prev = newOP;
    }

    else
    {
        newOP->next = tail;
        newOP->prev = tail->prev;
        tail->prev->next = newOP;
        tail->prev = newOP;
    }

    switch(func)                                                            // Performing the arithmetic to change the final
    {
        case ADDITION:
            final += operand;
            break;

        case SUBTRACTION:
            final -= operand;
            break;

        case MULTIPLICATION:
            final *= operand;
            break;

        case DIVISION:
            if(operand == 0) 
                throw("Divide By Zero");
            final /= operand;
            break;
    }

    newOP->nodeTotal = final;
    size++;                                                                     // number of elements in current linked List
}

void CalcList::removeLastOperation()                                            //removing last operation
{
    if(empty())
    {
        throw("Empty List. Cannot Remove!!");
    }
    CalcListNode* nodeRemove = tail->prev;

    switch(nodeRemove->operation)
    {
        case ADDITION:
            final -= nodeRemove->operand;
            break;

        case SUBTRACTION:
            final += nodeRemove->operand;
            break;

        case MULTIPLICATION:
            if(nodeRemove->operand == 0)
            {
                final = nodeRemove->prev->nodeTotal;
            }
            else
            {
                final /= nodeRemove->operand;
            }
            break;

        case DIVISION:
            final *= nodeRemove->operand;
            break;
    }

    if(size >= 1)
    {
        CalcListNode* prevNode = nodeRemove->prev;
        CalcListNode* next_node = tail;
        prevNode->next = next_node;
        tail->prev = prevNode;
    }

    else
    {
        final = 0.0;
        head->next = tail;
        tail->prev = head;
    }
    size--;                                                                     // number of elements in current linked List
    delete nodeRemove;
}

std::string CalcList::toString(unsigned short precision) const                  // String of list of operations
{
    std::ostringstream oSS;
    oSS << getOperationString(size, tail->prev, precision);
    return oSS.str();
}   

std::string CalcList::getOperationString(unsigned int length, const CalcListNode* node, unsigned short prec) const
{
    char op;
    switch(node->operation)
    {
        case ADDITION:
            op = '+';
            break;

        case SUBTRACTION:
            op = '-';
            break;

        case MULTIPLICATION:
            op = '*';
            break;

        case DIVISION:
            op = '/';
            break;
    }

    std::string op_strings = "";
    std::ostringstream oSS;

    if(node->prev == head)
    {
        double zero = 0.0;
        oSS << "1: " << std::setprecision(prec) << std::fixed << zero << op << node->operand << "=" << node->nodeTotal;
        oSS << std::endl;
        op_strings += oSS.str();
        return op_strings;
    }
    else
    {
        oSS << length << ": " << std::setprecision(prec) << std::fixed;
        oSS << node->prev->nodeTotal << op << std::setprecision(prec) << std::fixed;
        oSS << node->operand << "=" << std::setprecision(prec) << std::fixed;
        oSS << node->nodeTotal << std::endl;
        op_strings += oSS.str();
        return op_strings += getOperationString(length - 1, node->prev, prec);
    }
}
