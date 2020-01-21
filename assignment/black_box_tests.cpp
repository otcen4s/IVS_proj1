//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     MATEJ OTCENAS <xotcen01@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author MATEJ OTCENAS
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

namespace BlackBoxTesting{

class EmptyTree :public ::testing::Test{
	protected: BinaryTree tree;
};

class NonEmptyTree :public ::testing::Test{
	protected:
			int values[8];
				
			virtual void SetUp(){
			   	int testedValues[] = {10, 25, 15, 5, 100, 0, 65, 120};
				for(int i = 0; i < 8; i++){
					values[i] = testedValues[i];

					tree.InsertNode(values[i]);
				}
			}
		BinaryTree tree;
};
	
class TreeAxioms :public ::testing::Test{
		protected:
				void SetUp(){
					int axiomValues[] = {100, 0, 1000, 240, 420, 42, 13, 1, 10, 101, 33, 3, 1005, 12};
					for(int i = 0; i < 14; i++){
						tree.InsertNode(axiomValues[i]);
					}	
				}
				BinaryTree tree;
};

////////////////////////////////////////EMPTY TREE///////////////////////////////////////

TEST_F(EmptyTree, Insert){
		EXPECT_TRUE(tree.GetRoot() == NULL);
			
		tree.InsertNode(10000);
		ASSERT_TRUE(tree.GetRoot() != NULL);
		EXPECT_EQ(tree.GetRoot()->key, 10000);

		tree.InsertNode(0);
		ASSERT_TRUE(tree.GetRoot() != NULL);
		EXPECT_FALSE(tree.GetRoot()->key == 0);
}

TEST_F(EmptyTree, InsertTwoValues){
		std::pair<bool, BinaryTree::Node_t *> node = tree.InsertNode(42);
		
		//testing first value	
		ASSERT_TRUE(node.second->color == ::BinaryTree::BLACK);
		ASSERT_TRUE(node.first);
		ASSERT_TRUE(node.second->pParent == NULL);
		ASSERT_TRUE(node.second->key == 42);
		ASSERT_NE(node.second->pLeft->color, ::BinaryTree::RED);
		ASSERT_NE(node.second->pRight->color, ::BinaryTree::RED);
		
		std::pair<bool, BinaryTree::Node_t *> newNode = tree.InsertNode(24);
		
		//testing second value 
		ASSERT_TRUE(newNode.first);
		ASSERT_TRUE(newNode.second->key == 24);
		ASSERT_TRUE(newNode.second->pParent != NULL);
		ASSERT_TRUE(newNode.second->color == ::BinaryTree::RED);
		ASSERT_TRUE(newNode.second->pParent->pLeft->key == 24);
		ASSERT_TRUE(newNode.second->pParent->key == 42);
		
		ASSERT_NE(newNode.second->pLeft->color, ::BinaryTree::RED);
		ASSERT_NE(newNode.second->pRight->color, ::BinaryTree::RED);

		std::vector<Node_t *> leafValues;
	   	tree.GetLeafNodes(leafValues);
		
		for(int i = 0; i < leafValues.size(); i++){
			EXPECT_TRUE(leafValues[i]->pParent != NULL);
		}
}

TEST_F(EmptyTree, Remove){
		const int values [] = {-100000, 40, 0, 10, 10000};

		EXPECT_FALSE(tree.DeleteNode(0));
		EXPECT_FALSE(tree.DeleteNode(100));
		
		for(int i = 0; i < 5; i++){
			tree.InsertNode(values[i]);
		}

		for(int i = 0; i < 5; i++){
			EXPECT_TRUE(tree.DeleteNode(values[i]));
		}

		tree.InsertNode(42);
		EXPECT_TRUE(tree.DeleteNode(42));
}

TEST_F(EmptyTree, Find){
		EXPECT_FALSE(tree.FindNode(0));
		EXPECT_FALSE(tree.FindNode(42));

		const int values [] = {10, 20 ,30, 40};
		for(int i = 0; i < 8; i++){
			tree.InsertNode(values[i]);
			EXPECT_TRUE(tree.FindNode(values[i]));
		}

		tree.InsertNode(42);
		EXPECT_TRUE(tree.FindNode(42));
}

TEST_F(EmptyTree, LeafNodes){
		const int nodeValue = 42;
	
		tree.InsertNode(nodeValue);
	
		std::vector<Node_t *> node;

		tree.GetLeafNodes(node);
		ASSERT_EQ(node.size(), 2);
}

TEST_F(EmptyTree, AllNodes){
		const int nodeValue = 42;

		tree.InsertNode(nodeValue);

		std::vector<Node_t *> node;

		tree.GetAllNodes(node);
		ASSERT_EQ(node.size(), 3);
}

TEST_F(EmptyTree, NonLeafNodes){
		const int nodeValue = 42;

		tree.InsertNode(nodeValue);

		std::vector<Node_t *> node;

		tree.GetNonLeafNodes(node);
		ASSERT_EQ(node.size(), 1);
}

TEST_F(EmptyTree, InsertNodes){
		std::vector<int> values {42, 420, 0, 10, 180, 24};
		std::vector<std::pair<bool, Node_t *>> newNodes;

		tree.InsertNodes(values, newNodes);

		for(int i = 0; i < newNodes.size(); i++){
				ASSERT_EQ(newNodes[i].second->key, values[i]);
		}

		std::vector<int> wrongValues {42, 420, 0, 10};
		
		tree.InsertNodes(wrongValues, newNodes);

		for(int i = 0; i < newNodes.size(); i++){
				ASSERT_FALSE(newNodes[i].first);
		}
}


////////////////////////////////////NONEMPTY TREE////////////////////////////////////////

TEST_F(NonEmptyTree, Remove){

		for(int i = 0; i < 7; i++){
			EXPECT_TRUE(tree.DeleteNode(values[i]));
		}
		EXPECT_TRUE(tree.DeleteNode(tree.GetRoot()->key));

		const double wrongValues [] = {-1.0, 1000000, -5.0, 7420.0};
		for(int i = 0; i < 4; i++){
				EXPECT_FALSE(tree.DeleteNode(wrongValues[i]));
		}
}

TEST_F(NonEmptyTree, Insert){	
		std::pair<bool, BinaryTree::Node_t *> node = tree.InsertNode(42);

		ASSERT_TRUE(node.first);
		ASSERT_TRUE(node.second->key == 42);
		ASSERT_TRUE(node.second->color == ::BinaryTree::RED);

		//test root
		Node_t * root = tree.GetRoot();
		ASSERT_TRUE(root->pParent == NULL);
		ASSERT_TRUE(root->color == ::BinaryTree::BLACK);
		ASSERT_TRUE(root->pLeft->color == ::BinaryTree::BLACK);
		ASSERT_TRUE(root->pRight->color == ::BinaryTree::RED);
		EXPECT_TRUE(root->pLeft->key == 5);
		EXPECT_TRUE(root->pRight->key == 65);

		node = tree.InsertNode(10);
		ASSERT_FALSE(node.first);
}

TEST_F(NonEmptyTree, Find){
		EXPECT_TRUE(tree.FindNode(120));
		EXPECT_TRUE(tree.FindNode(0));
		EXPECT_TRUE(tree.FindNode(100));
	
		int wrongValues [] = {-10, -42, -24, 100000};
		for(int i = 0; i < 4; i++){
			EXPECT_FALSE(tree.FindNode(wrongValues[i]));
		}

		for(int i = 0; i < 8; i++){
			EXPECT_TRUE(tree.FindNode(values[i]));
		}
}

TEST_F(NonEmptyTree, LeafNodes){
		std::vector<Node_t*> leafNodes;
	
		tree.GetLeafNodes(leafNodes);
		EXPECT_EQ(leafNodes.size(), 9);		
}

TEST_F(NonEmptyTree, AllNodes){
		std::vector<Node_t *> allNodes;
		
		tree.GetAllNodes(allNodes);
		EXPECT_EQ(allNodes.size(), 17);
}

TEST_F(NonEmptyTree, NonLeafNodes){
		std::vector<Node_t *> nonLeafNodes;

		tree.GetNonLeafNodes(nonLeafNodes);
		EXPECT_EQ(nonLeafNodes.size(), 8);
}

TEST_F(NonEmptyTree, InsertNodes){
		std::vector<int> nodeValues {1,2,3,4};
		
		std::vector<std::pair<bool, Node_t *>> newNodes; 
		
		tree.InsertNodes(nodeValues, newNodes);
		
		for(int i = 0; i < nodeValues.size(); i++){
			ASSERT_TRUE(newNodes[i].second->key == nodeValues[i]);
		}

		std::vector<int> wrongNodeValues {10,5,0,15,65};

		tree.InsertNodes(wrongNodeValues, newNodes);

		for(int i = 0; i < wrongNodeValues.size(); i++){
				ASSERT_FALSE(newNodes[i].first);
		}

}

////////////////////////////////////////TEST AXIOMS///////////////////////////////////////////

TEST_F(TreeAxioms, fisrtAxiom){
		std::vector<Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);

		for(int i = 0; i < leafNodes.size(); i++){	
			ASSERT_TRUE(leafNodes[i]->color == ::BinaryTree::BLACK);
		}
}

TEST_F(TreeAxioms, secondAxiom){
		std::vector<Node_t *> NonLeafNodes;
		tree.GetNonLeafNodes(NonLeafNodes);

		for(int i = 0; i < NonLeafNodes.size(); i++){
				if(NonLeafNodes[i]->color == ::BinaryTree::RED){
					ASSERT_TRUE(NonLeafNodes[i]->pLeft->color == ::BinaryTree::BLACK);
					ASSERT_TRUE(NonLeafNodes[i]->pRight->color == ::BinaryTree::BLACK);
				}
		}
}

TEST_F(TreeAxioms, thirdAxiom){
		std::vector<Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);
			
		 int blackNodesConstant;

		for(int i = 0; i < leafNodes.size(); i++){
				int blackNodes = 0;
				
				while(leafNodes[i]->pParent != NULL){
						if(leafNodes[i]->color == ::BinaryTree::BLACK){
							blackNodes++;
							if(i == 0) blackNodesConstant = blackNodes;
						}
						leafNodes[i] = leafNodes[i]->pParent;
				}
			ASSERT_TRUE(blackNodes == blackNodesConstant);
		}
}


}
/*** Konec souboru black_box_tests.cpp ***/
