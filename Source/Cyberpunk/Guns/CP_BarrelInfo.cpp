#include "CP_BarrelInfo.h"
#include "Engine/Texture2D.h"

ACP_BarrelInfo::ACP_BarrelInfo()
{
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootSceneComponent);

    // 기본값 설정
    IconTexture = nullptr;
    IconTexturePath = TEXT(""); // 기본 경로는 빈 값
}

void ACP_BarrelInfo::Initialize(const FString& MeshName)
{
    USkeletalMesh* LoadedMesh = nullptr;

    if (MeshName == "SK_BarrelBeam")
    {
        PartName = "SK_BarrelBeam";
        Damage = 100.0f;
        GearCost = 3;
        bIsHitscan = true;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeam.SK_BarrelBeam")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BarrelBeam.SK_BarrelBeam");
    }
    else if (MeshName == "SK_BarrelBeamScatter")
    {
        PartName = "SK_BarrelBeamScatter";
        Damage = 120.0f;
        GearCost = 5;
        bIsHitscan = true;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeamScatter.SK_BarrelBeamScatter")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BarrelBeamScatter.SK_BarrelBeamScatter");
    }
    else if (MeshName == "SK_BarrelBulletScatter")
    {
        PartName = "SK_BarrelBulletScatter";
        Damage = 150.0f;
        GearCost = 6;
        bIsHitscan = false;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BarrelBulletScatter.SK_BarrelBulletScatter");
    }

    if (LoadedMesh)
    {
        BarrelMesh->SetSkeletalMesh(LoadedMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
    }

    // 아이콘 로드
    LoadIconTexture();
}

/** 아이콘 로드 함수 */
void ACP_BarrelInfo::LoadIconTexture()
{
    if (!IconTexturePath.IsEmpty())
    {
        IconTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *IconTexturePath));
        if (!IconTexture)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load IconTexture: %s"), *IconTexturePath);
        }
    }
}

USkeletalMeshComponent* ACP_BarrelInfo::GetMesh() const
{
    return BarrelMesh;
}
