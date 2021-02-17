
#pragma once

#include "../GridObjects/GridObject.h"
#include "SpawnPoint.h"
#include "TileData.generated.h"

USTRUCT(BlueprintType)
struct FTileData
{
	GENERATED_BODY()

public:
	FTileData(float XAbsPosition, float YAbsPosition, float ZAbsPosition);

	FTileData();

	UPROPERTY(BlueprintReadWrite)
		bool bIsVoid = true;
	UPROPERTY(BlueprintReadOnly) //These coordinates represent bottom centre of the tile volume
		FVector AbsoluteCoordinates;
	UPROPERTY(BlueprintReadWrite)
		AGridObject* TileHolder = nullptr;
	UPROPERTY(BlueprintReadWrite)
		ASpawnPoint* SpawnPoint = nullptr;
};