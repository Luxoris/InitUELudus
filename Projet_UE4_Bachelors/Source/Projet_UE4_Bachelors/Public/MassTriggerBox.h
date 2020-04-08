// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MassTriggerBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerStop);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJET_UE4_BACHELORS_API UMassTriggerBox : public UActorComponent
{
	GENERATED_BODY()
//MEMBERS
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	float TotalMassInKgToTrigger;	//The total mass to trigger the trigger box
	UPROPERTY(BlueprintReadOnly , Category = "Trigger")
	bool IsTriggered;	//Bool reporting if component is triggered or not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	ATriggerVolume* TriggerBox;
	
	//is called when trigger start
	UPROPERTY(BlueprintAssignable)
		FOnTriggerStart OnTriggerStart; //delegate function called on trigger start

	//is called when trigger stop
	UPROPERTY(BlueprintAssignable)
		FOnTriggerStop OnTriggerStop; //delegate function called on trigger stop

//METHODS
public:	
	// Sets default values for this component's properties
	UMassTriggerBox();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Called when trigger box overlap change, broadcast OnTriggerStop and OnTriggerStart functions, manage IsTriggered member.
	UFUNCTION()
	void OnTriggerChange(AActor* owner, AActor* otherActor);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Return the total mass of all overlapping meshes
	UFUNCTION(BlueprintCallable, Category = "MassTriggerBox")
	float GetTotalMassFromOverlappingMeshes();

	//return true if the mass trigger is triggered, meaning that total mass of overlapping actors is greter than TotalMassToTriggerInKg
	UFUNCTION(BlueprintCallable, Category = "MassTriggerBox")
	bool TestIsTriggered();
};
