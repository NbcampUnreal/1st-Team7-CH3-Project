#include "CP_Guns.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;
    AmmoCount = 30;
    MaxAmmo = 30;
    bIsReloading = false;
    ReloadTime = 2.0f;

    // Root 씬 컴포넌트 생성
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    // 총기 부품들 (스켈레탈 메쉬) 
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    ScopeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ScopeMesh"));

    // 총기 부품들을 Root 씬 컴포넌트에 연결
    BarrelMesh->SetupAttachment(RootScene, TEXT("BarrelSocket"));
    BodyMesh->SetupAttachment(RootScene, TEXT("BodySocket"));
    TriggerMesh->SetupAttachment(RootScene, TEXT("TriggerSocket"));
    ScopeMesh->SetupAttachment(RootScene, TEXT("ScopeSocket"));
}

void ACP_Guns::BeginPlay()
{
    Super::BeginPlay();

    if (BarrelMesh)
    {
        BarrelMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("BarrelSocket"));
    }
    BodyMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("BodySocket"));
    TriggerMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("TriggerSocket"));
    ScopeMesh->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ScopeSocket"));


    if (BarrelMesh)
    {
        SetBarrel(BarrelMesh);
    }
}

void ACP_Guns::SetBarrel(USkeletalMeshComponent* SelectedBarrel)
{
    BarrelMesh = SelectedBarrel;

    if (BarrelMesh)
    {
        // SkeletalMeshAsset 이름을 확인하여 태그 추가
        FString MeshName = BarrelMesh->GetSkeletalMeshAsset()->GetName();
        UE_LOG(LogTemp, Log, TEXT("Selected Barrel: %s"), *MeshName);

        if (MeshName == "SK_BarrelBeam" || MeshName == "SK_BarrelBeamScatter")
        {
            // 히트스캔 방식
            BarrelMesh->ComponentTags.Add(FName("Hitscan"));
            UE_LOG(LogTemp, Log, TEXT("Fire Mode: Hitscan"));
        }
        else if (MeshName == "SK_BarrelBulletScatter" || MeshName == "SK_BarrelBullet")
        {
            // 프로젝타일 방식
            BarrelMesh->ComponentTags.Add(FName("Projectile"));
            UE_LOG(LogTemp, Log, TEXT("Fire Mode: Projectile"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BarrelMesh is null!"));
    }
}


void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 매 틱마다 Fire() 함수 호출 (테스트용)
    if (AmmoCount > 0)
    {
        Fire();
    }
}


void ACP_Guns::Fire()
{
    if (AmmoCount > 0)
    {
        // 발사 효과를 처리 (히트스캔 또는 프로젝타일 처리)
        if (BarrelMesh->ComponentHasTag(FName("Hitscan")))
        {
            UE_LOG(LogTemp, Log, TEXT("Hit scan Fire! Ammo left: %d"), AmmoCount);
            AmmoCount--;
            // 히트스캔 발사 처리 로직
            

        }
        // 프로젝타일 발사 방식
        else if (BarrelMesh->ComponentHasTag(FName("Projectile")))
        {
            UE_LOG(LogTemp, Log, TEXT("Projectile Fire! Ammo left: %d"), AmmoCount);
            AmmoCount--;
            // 프로젝타일 발사 처리 로직
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Out of ammo!"));
        Reload();
    }
}


void ACP_Guns::Reload()
{
    // 기본적인 재장전 기능
}

void ACP_Guns::AttachAttachment(const FString& AttachmentName)
{
    // 기본적인 부착물 장착 기능
}
