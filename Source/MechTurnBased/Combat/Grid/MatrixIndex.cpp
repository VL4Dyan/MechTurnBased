#include "MatrixIndex.h"

FMatrixIndex::FMatrixIndex()
{
	IndexX = 0;
	IndexY = 0;
	IndexZ = 0;
}

FMatrixIndex::FMatrixIndex(int X, int Y, int Z)
{
	IndexX = X;
	IndexY = Y;
	IndexZ = Z;
}

bool operator==(const FMatrixIndex& IndexOne, const FMatrixIndex& IndexTwo)
{
	if (IndexOne.IndexX == IndexTwo.IndexX && IndexOne.IndexY == IndexTwo.IndexY && IndexOne.IndexZ == IndexTwo.IndexZ)
		return true;
	else return false;
}

bool operator!=(const FMatrixIndex& IndexOne, const FMatrixIndex& IndexTwo)
{
	if (IndexOne.IndexX == IndexTwo.IndexX && IndexOne.IndexY == IndexTwo.IndexY && IndexOne.IndexZ == IndexTwo.IndexZ)
		return false;
	else return true;
}