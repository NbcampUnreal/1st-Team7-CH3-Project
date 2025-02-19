#include "CP_BarrelInfo.h"

ACP_BarrelInfo::ACP_BarrelInfo()
{
    // 기본 RootComponent로 SceneComponent 설정
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;  // RootComponent 설정

    // BarrelMesh 초기화
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootSceneComponent);  // BarrelMesh는 RootComponent의 자식
}

void ACP_BarrelInfo::InitializeBarrelInfo(const FString& MeshName)
{
    if (MeshName == "SK_BarrelBeam")
    {
        PartName = "SK_BarrelBeam";
        Damage = 100.0f;
        bIsHitscan = false;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeam.SK_BarrelBeam")));
        if (LoadedMesh)
        {
            BarrelMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_BarrelBeamScatter")
    {
        PartName = "SK_BarrelBeamScatter";
        Damage = 120.0f;
        bIsHitscan = true;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeamScatter.SK_BarrelBeamScatter")));
        if (LoadedMesh)
        {
            BarrelMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_BarrelBulletScatter")
    {
        PartName = "SK_BarrelBulletScatter";
        Damage = 150.0f;
        bIsHitscan = false;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
        if (LoadedMesh)
        {
            BarrelMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Barrel: %s"), *MeshName);
    }
}

USkeletalMeshComponent* ACP_BarrelInfo::GetBarrelMesh() const
{
    return BarrelMesh;
}
