// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlateDoor.h"

/**************************************************************************************
Description: Constructor of class, called before entering editor.

Input: -

Output: -

Note: -

***************************************************************************************/
APressurePlateDoor::APressurePlateDoor() {
	MassTriggerBox = CreateDefaultSubobject<UMassTriggerBox>(TEXT("MassTriggerBox"));
	OpenDoor = CreateDefaultSubobject<UOpenDoor>(TEXT("OpenDoor"));
}


/**************************************************************************************
Description: Function called when game starts, delegate opening functions to OnTrigger events.

Input: -

Output: -

Note: -

***************************************************************************************/
void APressurePlateDoor::BeginPlay()
{
    // Call the base class  
    Super::BeginPlay();

    if (ensure(OpenDoor)){
        // On Trigger Start Call open door from open door component
        MassTriggerBox->OnTriggerStart.AddDynamic(OpenDoor, &UOpenDoor::OpenDoor);
        //on trigger stop call close door from open doo component
        MassTriggerBox->OnTriggerStop.AddDynamic(OpenDoor, &UOpenDoor::CloseDoor);
    }
}
