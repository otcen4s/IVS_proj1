//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     MATEJ OTCENAS <xotcen01@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author MATEJ OTCENAS
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
	root = NULL;
}

PriorityQueue::~PriorityQueue()
{
	Element_t *helpointer = GetHead();
	Element_t *current;

	while(helpointer != NULL)
	{
		current = helpointer;
		helpointer = helpointer->pNext;
		delete current;
	}
}

void PriorityQueue::Insert(int value)
{
	Element_t *insertedNode =(Element_t*) new Element_t;
	insertedNode->value = value;
	
	//prvy prvok
	if(root == NULL){
		insertedNode->pPrev = NULL;
		insertedNode->pNext = NULL;
		root = insertedNode;
		return;
	}

	 if(root->value > value){
		//hodnota mensia ako root
			insertedNode->pNext = root;
			insertedNode->pPrev = NULL;
			root->pPrev = insertedNode;
			root = insertedNode;
			return;	
	 }

	 else{
		Element_t *current = root;
		//vlozi prvok medzi 2 rozne prvky 	
		while(current != NULL){

			if(current->value >= value){
				insertedNode->pNext = current;
				insertedNode->pPrev = current->pPrev;
				current->pPrev->pNext = insertedNode;
				current->pPrev = insertedNode;
				
				return;
			}
			if(current->pNext == NULL){
				insertedNode->pPrev = current;
				insertedNode->pNext = NULL;
				current->pNext = insertedNode;

				return;
			}

			current = current->pNext;
		}
	}
}



bool PriorityQueue::Remove(int value)
{
	Element_t *current = Find(value);
		
			if(current){	
				//ak je to prvy prvok v liste
				if(current->pPrev == NULL){
					if(root->pNext == NULL){ 
						delete current;
						root = NULL;
						return true;
					}
					current->pNext->pPrev = NULL;	
					root = current->pNext;
					delete current;
				}
				//ak je to posledny prvok v liste
				else if(current->pNext == NULL){
					current = current->pPrev;
					delete current->pNext;
					current->pNext = NULL;
				}
				//prvok je niekde v zozname
				else{
					current->pPrev->pNext = current->pNext;
					current->pNext->pPrev = current->pPrev;
					delete current;
				}

				 return true;
			}

	return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
	Element_t *current = root;

	while(current != NULL){
		if(current->value == value){
				
			return current;
		}
		current = current->pNext;
	}
    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return root;
}

/*** Konec souboru tdd_code.cpp ***/
