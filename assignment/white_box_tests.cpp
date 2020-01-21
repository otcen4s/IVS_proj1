//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     MATEJ OTCENAS <xotcen01@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author MATEJ OTCENAS
 * 
 * @brief Implementace testu prace s maticemi.
 */
#include <vector>
#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

namespace GlassTesting{

class MatrixTests :public ::testing:: Test {
	protected:


			Matrix matrix;
			
			Matrix SetUpFoo(){

					return Matrix();
			}
			void setValue1x1(){
					matrix = SetUpFoo();
			}

			Matrix Set2x2(){
					matrix = Matrix(2,2);
								
					matrix.set(std::vector<std::vector<double>>{ {0,0}
																,{0,0}});		
					return matrix;
			}
			void setValue2x2(){
					matrix = Set2x2();
			}

			Matrix Set3x3(){
					matrix	= Matrix(3,3);
				
					matrix.set(std::vector<std::vector<double>>{{5,-4,1},
									   							{0,0,0},
																{1,1,3}});		
					return matrix;
			}
			void setValue3x3(){
					matrix = Set3x3();
			}
			
};

TEST_F(MatrixTests, Constructor){
	setValue1x1();

	EXPECT_NO_THROW(Matrix());
	EXPECT_NO_THROW(Matrix(1,1));
	EXPECT_NO_THROW(Matrix(1,10000));
	EXPECT_NO_THROW(Matrix(1000,500));
	
	EXPECT_ANY_THROW(Matrix(0,0));
	EXPECT_ANY_THROW(Matrix(-0,3));
	EXPECT_ANY_THROW(Matrix(-100,-4));
	EXPECT_ANY_THROW(Matrix(100,-1));
	EXPECT_ANY_THROW(Matrix(-1,100));
}

TEST_F(MatrixTests, setMatrixValues){
		setValue1x1();
		
		EXPECT_TRUE(matrix.set(0,0,-10.4));
		EXPECT_TRUE(matrix.set(0,0,10.4));
		EXPECT_TRUE(matrix.set(0,0,-3));
		EXPECT_TRUE(matrix.set(0,0,3));
		EXPECT_TRUE(matrix.set(0,0,0));

		EXPECT_FALSE(matrix.set(0,10,1));
		EXPECT_FALSE(matrix.set(1,0,1));
		EXPECT_FALSE(matrix.set(10,1,-2.4));
		EXPECT_FALSE(matrix.set(1,-1,10));
}

TEST_F(MatrixTests,setMatrixArrayValues){
		setValue2x2();

		EXPECT_TRUE(matrix.set(0,0,-1.1));
		EXPECT_TRUE(matrix.set(0,0,1.1));
		EXPECT_TRUE(matrix.set(1,1,3.14));
		EXPECT_TRUE(matrix.set(1,0,1001));
		EXPECT_TRUE(matrix.set(0,1,-1001));

		EXPECT_FALSE(matrix.set(0,2,-100));
		EXPECT_FALSE(matrix.set(-100,2,100));
		EXPECT_FALSE(matrix.set(100,0,5));
		EXPECT_FALSE(matrix.set(1,2,-3.14));
}

TEST_F(MatrixTests, getMatrixValues){
		setValue1x1();
		
		EXPECT_NO_THROW(matrix.get(0,0));
		
		EXPECT_ANY_THROW(matrix.get(1,1));
		EXPECT_ANY_THROW(matrix.get(1,0));
		EXPECT_ANY_THROW(matrix.get(0,1));
		EXPECT_ANY_THROW(matrix.get(-3,1));
}

TEST_F(MatrixTests, getMatrixValues3x3){
		setValue3x3();

		EXPECT_NO_THROW(matrix.get(0,0));
		EXPECT_NO_THROW(matrix.get(1,0));
		EXPECT_NO_THROW(matrix.get(2,0));
		EXPECT_NO_THROW(matrix.get(0,2));

		EXPECT_ANY_THROW(matrix.get(-10,0));
		EXPECT_ANY_THROW(matrix.get(1,10));
		EXPECT_ANY_THROW(matrix.get(4,2));
		EXPECT_ANY_THROW(matrix.get(1,1000));

}

TEST_F(MatrixTests, wrongSetSize){
		Matrix wrong2x2Matrix = Matrix(2,2);

		EXPECT_FALSE(wrong2x2Matrix.set(std::vector<std::vector<double>>{ {0},
																		  {1,1}}));
}



TEST_F(MatrixTests, isEqualValue1x1){
		setValue1x1();
		
		EXPECT_EQ(matrix.get(0,0),0);
		EXPECT_TRUE(matrix == matrix);
	
		//wrong zero matrix
		Matrix wrongMatrix = SetUpFoo();
		wrongMatrix.set(0,0,-1000);

		EXPECT_NE(matrix.get(0,0),1);
		EXPECT_FALSE(matrix == wrongMatrix);
}


TEST_F(MatrixTests, isEqualValue2x2){
		setValue2x2();

		//wrong 4x3 matrix
		Matrix wrong4x3Matrix = Matrix(4,3);
		wrong4x3Matrix.set(std::vector<std::vector<double>>{ {0,-1,-1.1}
															,{5,100,10}
															,{0,1,1}
															,{-1000,2,0}});	
		
		EXPECT_TRUE(matrix == matrix);
		
		//wrong 2x2 matrix
		//single value changed
		Matrix wrong2x2Matrix = Set2x2();
		wrong2x2Matrix.set(1,1,-100000);

		EXPECT_FALSE(matrix == wrong2x2Matrix);	
		EXPECT_ANY_THROW(matrix == wrong4x3Matrix);
}

//throw expect if sizeof matrices are different
//doing add of matrices
TEST_F(MatrixTests, addTest){

		Matrix matrix2x2Created = Matrix(2,2);
		matrix2x2Created.set(std::vector<std::vector<double>>{{1,1}
															 ,{2,2}});
		
		Matrix matrix2x3Created = Matrix(2,3);
		matrix2x3Created.set(std::vector<std::vector<double>>{ {5,0,1}
															  ,{4,4,2}});
		Matrix matrix2x2Set = Set2x2();

		EXPECT_NO_THROW(matrix2x2Created + matrix2x2Set);

		EXPECT_ANY_THROW(matrix2x3Created + matrix2x2Created);
}

TEST_F(MatrixTests, multiplyTest){
		setValue3x3();

		Matrix matrix3x2 = Matrix(3,2);
		Matrix matrix2x3 = Matrix(2,3);

		matrix3x2.set(std::vector<std::vector<double>>{  {1,1}
														,{1,2}
														,{4,4}});

		matrix2x3.set(std::vector<std::vector<double>>{  {0,0,1}
														,{5,3,1}});
		
		//c1 == r2
		EXPECT_NO_THROW(matrix2x3 * matrix3x2);
		EXPECT_NO_THROW(matrix * matrix);


		//c1 != r2
		EXPECT_ANY_THROW(matrix3x2 * matrix3x2);
		EXPECT_ANY_THROW(matrix2x3 * matrix2x3);
}

TEST_F(MatrixTests, scalarMultiplyTest){

		Matrix multipliedMatrix = Matrix(1,2);
		multipliedMatrix.set(std::vector<std::vector<double>>{{-1,5}});
		
		multipliedMatrix = multipliedMatrix * 3;
		
		Matrix comparedMatrix = Matrix(1,2);	
		comparedMatrix.set(std::vector<std::vector<double>>{{-3,15}});

		//matrices are equal
		EXPECT_TRUE(multipliedMatrix == comparedMatrix);
		
		
		Matrix oldMatrix = Matrix(1,2);	
		oldMatrix.set(std::vector<std::vector<double>>{{-1,5}});
		//matrices are not equal
		EXPECT_FALSE(multipliedMatrix ==oldMatrix);
}

TEST_F(MatrixTests, solveEquationTest){
		setValue1x1();

		EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double>{ {0} } ) );

		Matrix matrix2x2Created = Matrix(2,2);
		matrix2x2Created.set({{1,-10},
							  {10,100}});

		Matrix matrix4x4Created = Matrix(4,4);
		matrix4x4Created.set({{0,1,2,3},
						      {4,5,6,7},
							  {8,9,10,11},
							  {42,420,4200,42000}});

		//no error expected
		EXPECT_NO_THROW(matrix2x2Created.solveEquation(std::vector<double>{{0,10}}));
		EXPECT_NO_THROW(matrix2x2Created.solveEquation(std::vector<double>{{10,-10}}));
		EXPECT_NO_THROW(matrix2x2Created.solveEquation(std::vector<double>{{1000,0}}));	

		//vector has a wrong number values
		EXPECT_ANY_THROW(matrix2x2Created.solveEquation(std::vector<double>{{0}}));
		EXPECT_ANY_THROW(matrix2x2Created.solveEquation(std::vector<double>{{0,10,1000}}));
		EXPECT_ANY_THROW(matrix4x4Created.solveEquation(std::vector<double>{{0,2,-10,100}}));

		Matrix matrix3x2Created = Matrix(3,2);
		matrix3x2Created.set(std::vector<std::vector<double>>{  {-10.42,10.42},
																{42,-42},
																{420,-420}});
		//matrix is not square	
		EXPECT_ANY_THROW(matrix3x2Created.solveEquation(std::vector<double>{{42,420}}));
		EXPECT_ANY_THROW(matrix3x2Created.solveEquation(std::vector<double>{{420,4200,2400}}));
		EXPECT_ANY_THROW(matrix3x2Created.solveEquation(std::vector<double>{{-42,-100,4.2}}));
		
		//zero determinant/singular matrix
		Matrix matrix3x3Zero = Matrix(3,3);
		matrix3x3Zero.set(std::vector<std::vector<double>>{ {1,1,1},
															{1,1,1},
															{1,1,1}});
		
		EXPECT_ANY_THROW(matrix3x3Zero.solveEquation(std::vector<double>{{1,1,1}}));

		EXPECT_ANY_THROW(matrix3x2Created.solveEquation(std::vector<double>{{10.42, -42, -420}}));

		Matrix matrix1x1 = Matrix(1,1);
		matrix1x1.set(std::vector<std::vector<double>>{{1}});

		EXPECT_NO_THROW(matrix1x1.solveEquation(std::vector<double>{{1}}));

		Matrix matrix1x2 = Matrix(1,2);
		matrix1x2.set(std::vector<std::vector<double>>{{0,1}});
		EXPECT_ANY_THROW(matrix1x2.solveEquation(std::vector<double>{{}}));
}




}











/*** Konec souboru white_box_tests.cpp ***/
