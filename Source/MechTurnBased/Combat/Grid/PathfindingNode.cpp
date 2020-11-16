// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingNode.h"

void UPathfindingNode::Initialize(FMatrixIndexes indexes, float estimatedCost)
{
	Indexes = indexes;
	EstimatedCost = estimatedCost;
	CurrentCost = 0.0;
	OverallCost = 0.0;
}

UPathfindingNode::UPathfindingNode()
{
	Indexes = FMatrixIndexes(0, 0, 0);
	EstimatedCost = 0.0;
	CurrentCost = 0.0;
	OverallCost = 0.0;
}

void UPathfindingNode::SetNewCurrentCost(float currentCost)
{
	UPathfindingNode::CurrentCost = currentCost;
	OverallCost = EstimatedCost + currentCost;
}

bool operator<(const UPathfindingNode& nodeOne, const UPathfindingNode& nodeTwo)
{
	if (nodeOne.OverallCost < nodeTwo.OverallCost) return true;
	else return false;
}

bool operator==(const UPathfindingNode& nodeOne, const UPathfindingNode& nodeTwo)
{
	if (nodeOne.Indexes == nodeTwo.Indexes)
		return true;
	else return false;
}