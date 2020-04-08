// Fill out your copyright notice in the Description page of Project Settings.
//https://www.youtube.com/watch?v=KsvUYzrTwBw
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Rotator.h"
#include "Containers/UnrealString.h"
#include "Components/TimelineComponent.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_UE4_BACHELORS_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

//MEMBERS
protected:
	FQuat InitialDoorRotation; //used to store initial door rotation
	UTimelineComponent* MyTimeline; //Timeline component
	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;	///Timeline Direction

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpeningDoorSystem")
	UCurveFloat* ApertureCurve; //aperture curve of door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpeningDoorSystem")
	USoundBase* LockSound; //lock sound object reference
	

//METHODS
public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Create and Initialize theTimeline
	void InitTimeline();

	//Timeline On playing Tick
	UFUNCTION()
	void TimelineCallback(float val);

	//Play the Timeline
	void PlayTimeline();

	//reverse the Timeline
	void ReverseTimeline();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//fonction qui enclenche l'ouverture de la porte
	UFUNCTION(BlueprintCallable, Category = "OpenDoor")
	void OpenDoor();
	//fonction qui enclenche la fermeture de la porte
	UFUNCTION(BlueprintCallable, Category = "OpenDoor")
	void CloseDoor();
		
};
