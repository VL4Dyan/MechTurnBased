
#pragma once

#include "MatrixIndex.generated.h"

USTRUCT(BlueprintType)
struct FMatrixIndex
{
	GENERATED_BODY()

public:
	FMatrixIndex(int X, int Y, int Z);
	FMatrixIndex();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IndexX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IndexY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IndexZ = 0;
};

bool operator==(const FMatrixIndex& IndexOne, const FMatrixIndex& IndexTwo);
bool operator!=(const FMatrixIndex& IndexOne, const FMatrixIndex& IndexTwo);