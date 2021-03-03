// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Grid/TileData.h"
#include "../../Grid/MatrixIndex.h"
#include "TileDataUpdate.generated.h"

UCLASS()
class MECHTURNBASED_API UTileDataUpdate : public UObject
{
	GENERATED_BODY()

public:
	UTileDataUpdate();

	UPROPERTY()
		FMatrixIndex TileIndex;
	UPROPERTY()
		FTileData TileDataReplacement;
};
