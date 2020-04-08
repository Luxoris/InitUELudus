// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MassTriggerBox.h"
#include "OpenDoor.h"
#include "PressurePlateDoor.generated.h"

/**
 * Class managing a prssure plate door, opening on trigger start and closing on trigger stop.
 */
UCLASS()
class PROJET_UE4_BACHELORS_API APressurePlateDoor : public AStaticMeshActor
{
	GENERATED_BODY()

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    //Constructor
    APressurePlateDoor();

    //MassTriggerBox component
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    class UMassTriggerBox *MassTriggerBox;
    
    //OpenDoor component
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    class UOpenDoor *OpenDoor;

};
