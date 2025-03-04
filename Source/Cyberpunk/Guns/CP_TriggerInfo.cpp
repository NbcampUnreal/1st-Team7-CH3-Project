#include "CP_TriggerInfo.h"
#include "Engine/Texture2D.h"

ACP_TriggerInfo::ACP_TriggerInfo()
{
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootSceneComponent);

    // 기본값 설정
    IconTexture = nullptr;
    IconTexturePath = TEXT(""); // 기본 경로 초기화
}

void ACP_TriggerInfo::Initialize(const FString& MeshName)
{
    USkeletalMesh* LoadedMesh = nullptr;

    if (MeshName == "SK_TriggerAuto")
    {
        PartName = "SK_TriggerAuto";
        Damage = 10.0f;
        MagazineCapacity = 70;
        GearCost = 2;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerAuto.SK_TriggerAuto")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_TriggerAuto.SK_TriggerAuto");
    }
    else if (MeshName == "SK_TriggerBurst")
    {
        PartName = "SK_TriggerBurst";
        Damage = 20.0f;
        MagazineCapacity = 60;
        GearCost = 3;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerBurst.SK_TriggerBurst")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_TriggerBurst.SK_TriggerBurst");
    }
    else if (MeshName == "SK_StockStandard")
    {
        PartName = "SK_StockStandard";
        Damage = 25.0f;
        MagazineCapacity = 50;
        GearCost = 5;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_StockStandard.SK_StockStandard")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_StockStandard.SK_StockStandard");
    }
    else if (MeshName == "SK_StockHeavy")
    {
        PartName = "SK_StockHeavy";
        Damage = 30.0f;
        MagazineCapacity = 30;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_StockHeavy.SK_StockHeavy")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_StockHeavy.SK_StockHeavy");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Trigger: %s"), *MeshName);
    }

    if (LoadedMesh)
    {
        TriggerMesh->SetSkeletalMesh(LoadedMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
    }

    // 아이콘 로드
    LoadIconTexture();
}

/** 아이콘 로드 함수 */
void ACP_TriggerInfo::LoadIconTexture()
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

USkeletalMeshComponent* ACP_TriggerInfo::GetMesh() const
{
    return TriggerMesh;
}
