// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "SDTPathFollowingComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "SoftDesignTrainingPlayerController.generated.h"

class ASDTBridge;
class ASDTBoatOperator;

UCLASS()
class ASoftDesignTrainingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASoftDesignTrainingPlayerController();

    void BeginPlay() override;

protected:

    virtual void SetupInputComponent() override;

    void MoveCameraForward(float axisValue);
    void MoveCameraRight(float axisValue);
    void ZoomCamera(float axisValue);

    void MoveCharacter();

    void DrawPath();

    void Activate();
    void Deactivate();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation, meta = (AllowPrivateAccess = "true"))
    USDTPathFollowingComponent* m_PathFollowingComponent;
    UPROPERTY()
    TObjectPtr<UNavigationPath> m_CurrentPath;

    bool m_CanMoveCharacter;

    ASDTBridge* m_BridgeActivated;
    ASDTBoatOperator* m_BoatOperatorActivated;
};


