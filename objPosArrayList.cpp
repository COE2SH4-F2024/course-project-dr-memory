#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
objPosArrayList :: objPosArrayList()
{
    listSize = 0; //empty list 
    arrayCapacity = ARRAY_MAX_CAP; // Set the maximum capacity for the array.
    aList = new objPos[arrayCapacity];
}


objPosArrayList ::~objPosArrayList() 
{
    delete[] aList;
}

int objPosArrayList ::getSize() const //return list size 
{
    return listSize;
}


void objPosArrayList ::insertHead(objPos thisPos) // Inserts an element at the beginning of the list.
{
    int i;

    if(listSize < arrayCapacity)
    {
        listSize++;

        // Shift all elements one position to the right
        for(i = listSize - 1; i > 0; i--)
        {
            aList[i] = aList[i - 1];
        }

        aList[0] = thisPos;
    }
}
void objPosArrayList ::insertTail(objPos thisPos) // Inserts an element at the end of the list.
{
    // Ensure there is space to insert the element.
    if(listSize < arrayCapacity)
    {
        aList[listSize] = thisPos;
        listSize++;
    }
}

// Adds a specified number of elements to the end of the list.
void objPosArrayList ::insertTails(int num)
{
    if(listSize < arrayCapacity)
    {
        listSize = listSize + num;
    }
}

void objPosArrayList ::removeHead() // Removes the first element from the list.
{
    if(listSize >= 1)
    {
        int i;

        // Shift all elements one position to the left
        for(i = 0; i < listSize - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}

void objPosArrayList ::removeTail() // Removes the last element from the list.
{
    if(listSize >= 1)
    {
        listSize--;
    }
}
        
objPos objPosArrayList ::getHeadElement() const // Returns the first element in the list.
{
    return aList[0];
}

objPos objPosArrayList ::getTailElement() const // Returns the last element in the list.
{
    return aList[listSize - 1];
}

objPos objPosArrayList ::getElement(int index) const // Returns the element at a specified index in the list.
{
    return aList[index];
}

void objPosArrayList::removeElement(int index) // Removes the element at a specified index in the list.
{
    int i;

    if(listSize >= 1 && index < listSize)
    {
        for(i = index; i < listSize - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}