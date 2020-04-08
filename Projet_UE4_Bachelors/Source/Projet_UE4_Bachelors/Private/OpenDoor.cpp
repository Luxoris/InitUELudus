// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


/**************************************************************************************
Description: Constructor of class, called before entering editor.

Input: -

Output: -

Note: -

***************************************************************************************/

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize class parameters
	ApertureCurve = NULL;
	LockSound = NULL;
	MyTimeline = NULL;
}

/**************************************************************************************
Description: Function called when game starts, intialize InitialDoorRotation and call initTimeline function.

Input: -

Output: -

Note: -

***************************************************************************************/
// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitialDoorRotation = GetOwner()->GetTransform().GetRotation(); //set the initial door roation on begin play
	
	InitTimeline(); //intialize the timeline
	UE_LOG(LogTemp, Warning, TEXT("Timeline Length: %f"), MyTimeline->GetTimelineLength());
}

/**************************************************************************************
Description: Create and intialize the timeline with functions and values.

Input: -

Output: -

Note: -

***************************************************************************************/
void UOpenDoor::InitTimeline()
{
	FOnTimelineFloat onTimelineCallback;

	if (ApertureCurve != NULL)
	{
		MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		MyTimeline->SetNetAddressable();	// This component has a stable name that can be referenced for replication

		MyTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		MyTimeline->SetFloatCurve(ApertureCurve, FName{ TEXT("ApertureCurve") });

		MyTimeline->SetLooping(false);
		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); //set timeline length mode to Last key frame from Curves
		MyTimeline->SetPlaybackPosition(0.0f, false);
		
		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		MyTimeline->AddInterpFloat(ApertureCurve, onTimelineCallback,NAME_None, FName{ TEXT("ApertureCurve") });

		MyTimeline->RegisterComponent();
	}
}

/**************************************************************************************
Description: Script called when Timeline is playing, Play a sound when door is locked, modify yaw of the door

Input: float val: the value of the interpolate float from curve

Output: -

Note: -

***************************************************************************************/
void UOpenDoor::TimelineCallback(float val)
{
	//Play sound when the door is locked, val == 0.0f
	if (LockSound!=NULL && val==0.0f) {
		UGameplayStatics::PlaySoundAtLocation(this, LockSound,this->GetOwner()->GetTransform().GetLocation());
	}

	//Modify door rotation with curve value
	FRotator ActorRotator;
	FTransform ActorTransform;
	ActorTransform = this->GetOwner()->GetTransform(); //get actor transform
	ActorRotator = ActorTransform.GetRotation().Rotator(); //get rotator from actor transfrom
	ActorRotator.Yaw = this->InitialDoorRotation.Rotator().Yaw + val; //set yaw equal to intialRotation yaw + value form curve
	ActorTransform.SetRotation(ActorRotator.Quaternion()); //set new rotation from rotator
	this->GetOwner()->SetActorTransform(ActorTransform); //set new transform

	//UE_LOG(LogTemp, Warning, TEXT("TimelineValue :  %f, Timeline playbackpos: %f"), val, MyTimeline->GetPlaybackPosition());
}

/**************************************************************************************
Description: Play the timeline if the timeline is not null

Input: 

Output: -

Note: -

***************************************************************************************/
void UOpenDoor::PlayTimeline()
{
	if (MyTimeline != NULL)
	{
		MyTimeline->Play();
		//UE_LOG(LogTemp, Warning, TEXT("Play TimeLine"));
	}
	
}

/**************************************************************************************
Description: Reverse the timeline if the timeline is not null

Input:

Output: -

Note: -

***************************************************************************************/
void UOpenDoor::ReverseTimeline()
{
	if (MyTimeline != NULL)
	{
		MyTimeline->Reverse();
	}
}



/**************************************************************************************
Description: TickComponent

Input:

Output: -

Note: Called every frame

***************************************************************************************/
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...	
}

/**************************************************************************************
Description: Open the door by calling PlayTimeline function.

Input:

Output: -

Note: Accessible by Blueprint

***************************************************************************************/
void UOpenDoor::OpenDoor()
{
	this->PlayTimeline();
}

/**************************************************************************************
Description: Close the door by calling ReverseTimeline function.

Input:

Output: -

Note: Accessible by Blueprint

***************************************************************************************/
void UOpenDoor::CloseDoor()
{
	this->ReverseTimeline();
}

