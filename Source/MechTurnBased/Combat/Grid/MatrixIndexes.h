#pragma once

#include "UObject/Class.h"
#include "MatrixIndexes.generated.h"

USTRUCT(Blueprintable)
struct FMatrixIndexes
{
	GENERATED_BODY()

	FMatrixIndexes();
	FMatrixIndexes(int x, int y, int z);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IndexX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IndexY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IndexZ = 0;
};

bool operator==(const FMatrixIndexes& indexesOne, const FMatrixIndexes& indexesTwo);
bool operator!=(const FMatrixIndexes& indexesOne, const FMatrixIndexes& indexesTwo);