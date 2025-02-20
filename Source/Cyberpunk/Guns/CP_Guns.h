#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    ACP_Guns();

protected:
    // virtual void BeginPlay() override;

public:
    // 루트 씬 컴포넌트
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootScene;  // RootComponent

    // 파츠 메쉬 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;  // Barrel Mesh

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;  // Body Mesh

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;  // Trigger Mesh

    // 파츠 정보
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BarrelInfo* BarrelInfo;  // BarrelInfo (배럴 정보)

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_BodyInfo* BodyInfo;  // BodyInfo (몸체 정보)

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    ACP_TriggerInfo* TriggerInfo;  // TriggerInfo (트리거 정보)

    // 발사 타이머 설정
    float FireTimer;

    // 발사 간격 설정
    UPROPERTY(EditAnywhere, Category = "Gun Properties")
    float FireRate;

    // 발사 함수
    void Fire();

    // 발사할 때 사용하는 함수
    void FireProjectile();

    // 기본 파츠 설정 함수
    void SetGunParts(ACP_BarrelInfo* Barrel, ACP_BodyInfo* Body, ACP_TriggerInfo* Trigger);

    // 타이머를 갱신하는 함수 (매 프레임 호출)
    virtual void Tick(float DeltaTime) override;

    // 기본 파츠 로드 함수
    void LoadGunParts();

    // 프로젝타일 클래스는 블루프린트에서 설정할 수 있도록 공개
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
    TSubclassOf<ACP_Projectile> ProjectileClass;  // 프로젝타일 클래스
};
