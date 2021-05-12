// Fill out your copyright notice in the Description page of Project Settings.


#include "GridObjectComponent.h"

UGridObjectComponent::UGridObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UGridObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UGridObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FGridObjectComponentState UGridObjectComponent::GetComponentState()
{
	return FGridObjectComponentState();
}

void UGridObjectComponent::UpdateComponentState(FGridObjectComponentState ComponentStateReplacement)
{

}

UBoxComponent* UGridObjectComponent::GetCollisionRef()
{
	return CollisionBoxRef;
}

void UGridObjectComponent::SetCollisionRef(UBoxComponent* CollisionBoxRefToSet)
{
	CollisionBoxRef = CollisionBoxRefToSet;
}

FMatrixIndex UGridObjectComponent::GetTileToHighlight()
{
	return FMatrixIndex(0, 0, 0);
}

EGridObjectCompType UGridObjectComponent::GetComponentType()
{
	return ComponentType;
}

void UGridObjectComponent::SetGridObjectComponentOwner(AGridObject* GridObjectComponentOwnerToSet)
{
	GridObjectComponentOwner = GridObjectComponentOwnerToSet;
}

AGridObject* UGridObjectComponent::GetGridObjectComponentOwner()
{
	return GridObjectComponentOwner;
}
