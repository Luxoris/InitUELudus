// Fill out your copyright notice in the Description page of Project Settings.

#include "MassTriggerBox.h"
#include "Components/MeshComponent.h"

/**************************************************************************************
Description: Called when trigger box overlap change, 
				broadcast OnTriggerStop and OnTriggerStart functions, 
				manage IsTriggered member.

Input:	AActor* owner : Overlapping actors, comming from OnOverlapStart and OnOverlapEnd;
		AActor* otherActor : Overlapped actors, comming from OnOverlapStart and OnOverlapEnd;

Output: Broadcast OnTriggerStart and OnTriggerStop

Note: -

***************************************************************************************/
void UMassTriggerBox::OnTriggerChange(AActor* owner, AActor* otherActor) {
	UE_LOG(LogTemp, Warning, TEXT("On Trigger Change called."));
	if (TestIsTriggered()) {
		if (!IsTriggered) {
			IsTriggered = true;
			OnTriggerStart.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Broadcast On Trigger Start"));
		}
	}
	else {
		if (IsTriggered) {
			IsTriggered = false;
			OnTriggerStop.Broadcast();
		}
	}
}

/**************************************************************************************
Description: Constructor of class, called before entering editor.
				Sets default values for this component's properties

Input: -

Output: -

Note: -

***************************************************************************************/
UMassTriggerBox::UMassTriggerBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize members
	TotalMassInKgToTrigger = 100.0f;
	TriggerBox = NULL;
}


/**************************************************************************************
Description: Function called when game starts, delegate OnTriggerChange Funtion to OnActorBeginOverlap and OnActorEndOverlap

Input: -

Output: -

Note: -

***************************************************************************************/
void UMassTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
	TriggerBox->OnActorBeginOverlap.AddDynamic(this, &UMassTriggerBox::OnTriggerChange);
	TriggerBox->OnActorEndOverlap.AddDynamic(this, &UMassTriggerBox::OnTriggerChange);
}


/**************************************************************************************
Description: TickComponent

Input:

Output: -

Note: Called every frame

***************************************************************************************/
void UMassTriggerBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/**************************************************************************************
Description: Return Total Mass From Overlapping Meshes of TriggerBox actor reference in TriggerBox

Input:

Output: float : Total MAss From Overlapping Meshes

Note: Mass is added from all child of UMeshComponent Class

***************************************************************************************/
float UMassTriggerBox::GetTotalMassFromOverlappingMeshes()
{
	float Mass = 0.0f;
	TArray<AActor*> OverlappingActors;
	TSubclassOf<UMeshComponent> MeshClass;
	TArray<UActorComponent*> children;
	UMeshComponent* mesh;
	if (TriggerBox != NULL) {
		TriggerBox->GetOverlappingActors(OverlappingActors);	//get all overlapping actors
		for (int i=0; i < OverlappingActors.Num(); i++) {
			OverlappingActors[i]->GetComponents(children);
			for (auto& actorComp : children) {
				mesh = Cast<UMeshComponent>(actorComp);
				if (mesh!=NULL) { //test if child of MeshClass
					Mass += mesh->GetMass(); //add the mass of the comp to the total mass
				}
			}
		}
	}
	return Mass;
}

/**************************************************************************************
Description: Call Get GetTotalMassFromOverlappingMeshes, return true if mass > TotalMassInKgToTrigger else return false

Input:

Output: bool : return the result of the test

Note:

***************************************************************************************/
bool UMassTriggerBox::TestIsTriggered()
{
	return this->GetTotalMassFromOverlappingMeshes() >= this->TotalMassInKgToTrigger;
}

