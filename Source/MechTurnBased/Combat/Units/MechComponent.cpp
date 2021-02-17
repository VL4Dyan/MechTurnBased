// Fill out your copyright notice in the Description page of Project Settings.

#include "MechComponent.h"

UMechComponent::UMechComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMechComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

void UMechComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMechComponent::SetCollisionBoxRef(UBoxComponent* CollisionBox)
{
	CollisionBoxRef = CollisionBox;
}

UBoxComponent* UMechComponent::GetCollisionBoxRef()
{
	return CollisionBoxRef;
}

bool UMechComponent::TryGetSubComponents(TArray<UMechComponent*>& OutMechComponents)
{
	OutMechComponents = SubComponents;
	return false;
}

void UMechComponent::UpdateMechComponentState(const FGridObjectComponentState& MechComponentStateReplacement)
{

}

FGridObjectComponentState UMechComponent::GetMechComponentState()
{
	return MechComponentState;
}
