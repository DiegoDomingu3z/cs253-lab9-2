/*
 * File: DataNode.c
 * Description: Implements functions for DataNode, a simple linked list node for strings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataNode.h"

/* CreateDataNode: Allocate a new node with a copy of the provided string. */
DataNode *CreateDataNode(const char data[])
{
    if (data == NULL)
    {
        return NULL;
    }
    DataNode *newNode = (DataNode *)malloc(sizeof(DataNode));
    if (newNode == NULL)
    {
        return NULL;
    }
    size_t len = strlen(data) + 1; // include space for null terminator
    newNode->dataValue = (char *)malloc(len * sizeof(char));
    if (newNode->dataValue == NULL)
    {
        free(newNode);
        return NULL;
    }
    strcpy(newNode->dataValue, data);
    newNode->dataSize = len;
    newNode->nextNodePtr = NULL;
    return newNode;
}

/* InsertDataNodeAfter: Insert newNode immediately after nodeInList. */
int InsertDataNodeAfter(DataNode *nodeInList, DataNode *newNode)
{
    if (nodeInList == NULL || newNode == NULL)
    {
        return -1;
    }
    newNode->nextNodePtr = nodeInList->nextNodePtr;
    nodeInList->nextNodePtr = newNode;
    return 0;
}

/* SetNextDataNode: Set the next pointer of nodeInList to newNode. */
int SetNextDataNode(DataNode *nodeInList, DataNode *newNode)
{
    if (nodeInList == NULL)
    {
        return -1;
    }
    nodeInList->nextNodePtr = newNode;
    return 0;
}

/* GetNextDataNode: Return the next node in the list. */
DataNode *GetNextDataNode(DataNode *nodeInList)
{
    if (nodeInList == NULL)
    {
        return NULL;
    }
    return nodeInList->nextNodePtr;
}

/* PrintDataNode: Print the node's dataValue to stdout. */
void PrintDataNode(DataNode *thisNode)
{
    if (thisNode != NULL && thisNode->dataValue != NULL)
    {
        printf("%s", thisNode->dataValue);
    }
}

/* DestroyDataNode: Free the memory allocated for this node. */
void DestroyDataNode(DataNode *thisNode)
{
    if (thisNode != NULL)
    {
        free(thisNode->dataValue);
        free(thisNode);
    }
}

/* BuildDataList: Build a linked list from an array of strings. */
DataNode *BuildDataList(char *data[], int numElements)
{
    if (data == NULL || numElements <= 0)
    {
        return NULL;
    }

    DataNode *listHead = CreateDataNode(data[0]);
    if (listHead == NULL)
    {
        return NULL;
    }

    DataNode *current = listHead;
    for (int i = 1; i < numElements; i++)
    {
        DataNode *newNode = CreateDataNode(data[i]);
        if (newNode == NULL)
        {
            // Oops! Something went wrong; free what we've built so far.
            DestroyDataList(listHead);
            return NULL;
        }
        if (InsertDataNodeAfter(current, newNode) != 0)
        {
            DestroyDataNode(newNode);
            DestroyDataList(listHead);
            return NULL;
        }
        current = newNode;
    }
    return listHead;
}

/* GetDataListSize: Count and return the number of nodes in the list. */
int GetDataListSize(DataNode *listHead)
{
    if (listHead == NULL)
    {
        return -1;
    }
    int count = 0;
    DataNode *current = listHead;
    while (current != NULL)
    {
        count++;
        current = current->nextNodePtr;
    }
    return count;
}

/* PrintDataList: Print the dataValues of each node, separated by commas. */
void PrintDataList(DataNode *listHead)
{
    if (listHead == NULL)
    {
        return;
    }
    DataNode *current = listHead;
    while (current != NULL)
    {
        printf("%s", current->dataValue);
        if (current->nextNodePtr != NULL)
        {
            printf(", ");
        }
        current = current->nextNodePtr;
    }
    printf("\n");
}

/* GetRandomDataNode: Return a randomly selected node from the list. */
DataNode *GetRandomDataNode(DataNode *listHead)
{
    if (listHead == NULL)
    {
        return NULL;
    }
    int size = GetDataListSize(listHead);
    if (size <= 0)
    {
        return NULL;
    }
    int randomIndex = rand() % size;
    DataNode *current = listHead;
    for (int i = 0; i < randomIndex; i++)
    {
        current = current->nextNodePtr;
    }
    return current;
}

/* DestroyDataList: Free all nodes in the linked list. */
void DestroyDataList(DataNode *listHead)
{
    DataNode *current = listHead;
    while (current != NULL)
    {
        DataNode *next = current->nextNodePtr; // save next pointer before destruction
        DestroyDataNode(current);
        current = next;
    }
}
