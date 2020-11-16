#include "MatrixIndexes.h"

FMatrixIndexes::FMatrixIndexes()
{

}

FMatrixIndexes::FMatrixIndexes(int x, int y, int z)
{
	IndexX = x;
	IndexY = y;
	IndexZ = z;
}

bool operator==(const FMatrixIndexes& indexesOne, const FMatrixIndexes& indexesTwo)
{
	if (indexesOne.IndexX == indexesTwo.IndexX && indexesOne.IndexY == indexesTwo.IndexY && indexesOne.IndexZ == indexesTwo.IndexZ)
		return true;
	else return false;
}

bool operator!=(const FMatrixIndexes& indexesOne, const FMatrixIndexes& indexesTwo)
{
	if (indexesOne.IndexX == indexesTwo.IndexX && indexesOne.IndexY == indexesTwo.IndexY && indexesOne.IndexZ == indexesTwo.IndexZ)
		return false;
	else return true;
}