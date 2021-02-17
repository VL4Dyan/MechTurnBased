// Fill out your copyright notice in the Description page of Project Settings.

#include "TileTargetingResult.h"

UTileTargetingResult::UTileTargetingResult()
{

}

void UTileTargetingResult::Initialize(FMatrixIndex TileIndexToSet)
{
	TileIndex = TileIndexToSet;
}