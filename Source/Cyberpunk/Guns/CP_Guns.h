#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "CP_TacticalLight.h"  
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"  
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    ACP_Guns();

protected:
    //virtual void BeginPlay() override;

public:
    /** 루트 씬 컴포넌트 */
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootScene;

    /** 파츠 메쉬 컴포넌트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;

    /** 파츠 정보 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BarrelInfo* BarrelInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BodyInfo* BodyInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_TriggerInfo* TriggerInfo;

    /** 부착된 Tactical Light */
    UPROPERTY(VisibleAnywhere, Category = "Gun Parts")
    UChildActorComponent* TacticalLightComponent;

    /** 사운드 컴포넌트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
    UAudioComponent* AudioComponent;

    /** 발사 타이머 설정 */
    float FireTimer;

    /** 발사 간격 설정 */
    UPROPERTY(EditAnywhere, Category = "Gun Properties")
    float FireRate;

    /** 무기 발사 함수 */
    void Fire();

    /** 프로젝타일 발사 함수 */
    void FireProjectile();

    /** 기본 파츠 로드 함수 */
    void LoadGunParts();

    /** 나이아가라 이펙트 비활성화 */
    void DeactivateNiagaraEffect();

    /** 발사할 프로젝타일 클래스 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
    TSubclassOf<ACP_Projectile> ProjectileClass;

    /** 나이아가라 이펙트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Niagara")
    UNiagaraComponent* NiagaraEffect;

    /** 발사 타이머 핸들 */
    FTimerHandle TimerHandle;

    /** 틱 함수 */
    virtual void Tick(float DeltaTime) override;
};
