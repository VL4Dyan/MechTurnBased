// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatUnit.h"

// Sets default values
ACombatUnit::ACombatUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

