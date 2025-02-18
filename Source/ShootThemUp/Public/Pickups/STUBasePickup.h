// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ASTUBasePickup();

    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    virtual void BeginPlay() override;

private:
    float RotationYaw = 0.0f;
    virtual bool GivePickupTo(APawn* PlayerPawn) { return false; };

    void PickupWasTaken();
    void Respawn();

    void GenerateRotationYaw();
};
