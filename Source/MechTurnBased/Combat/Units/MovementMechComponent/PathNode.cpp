// Fill out your copyright notice in the Description page of Project Settings.

#include "PathNode.h"

UPathNode::UPathNode()
{
	TileIndex = FMatrixIndex(0, 0, 0);
	OverallCost = 0.0;
	EstimatedCost = 0.0;
	CurrentCost = 0.0;
	PreviousNode = nullptr;
}

void UPathNode::Initialize(FMatrixIndex TileIndexToSet, float EstimatedCostToSet)
{
	TileIndex = TileIndexToSet;
	EstimatedCost = EstimatedCostToSet;
	OverallCost = 0.0;
	CurrentCost = 0.0;
	PreviousNode = nullptr;
}

void UPathNode::SetCurrentCost(float CurrentCostToSet)
{
	CurrentCost = CurrentCostToSet;
	OverallCost = EstimatedCost + CurrentCostToSet;
}

bool operator<(const UPathNode& NodeOne, const UPathNode& NodeTwo)
{
	if (NodeOne.OverallCost < NodeTwo.OverallCost) return true;
	else return false;
}