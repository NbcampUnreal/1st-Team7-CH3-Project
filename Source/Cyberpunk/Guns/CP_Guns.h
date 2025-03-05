#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Projectile.h"
#include "CP_TacticalLight.h"
#include "CP_GunTypes.h"
#include "Inventory/CP_Inventory.h"
#include "Character/CP_Enemy.h"
#include "NiagaraFunctionLibrary.h"
#include "CP_Guns.generated.h"

class ACP_Player;

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    ACP_Guns();
   
    void EquipPart(const FString& PartName, EGunPartType PartType);
    void Reload();
    void ApplyDamage(AActor* HitActor);
    float CalculateTotalDamage();
    void Fire();
    void Fire(FVector FireDirection);
    virtual void Tick(float DeltaTime) override;
    void LoadGunParts();
    void DeactivateNiagaraEffect();
    void ToggleLight();

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootScene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BarrelInfo* BarrelInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BodyInfo* BodyInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_TriggerInfo* TriggerInfo;

    UPROPERTY(VisibleAnywhere, Category = "Gun Parts")
    UChildActorComponent* TacticalLightComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
    UAudioComponent* AudioComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
    TSubclassOf<ACP_Projectile> ProjectileClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Niagara")
    UNiagaraComponent* NiagaraEffect;

    UPROPERTY(EditAnywhere, Category = "Hit Effect")
    TSubclassOf<AActor> HitEffectBPClass;

    FTimerHandle TimerHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
    int32 AmmoCount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
    int32 MaxAmmo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    UCP_Inventory* InventoryRef;

    void SetInventory(UCP_Inventory* Inventory);

    UPROPERTY()
    ACP_TacticalLight* TacticalLight;
};
