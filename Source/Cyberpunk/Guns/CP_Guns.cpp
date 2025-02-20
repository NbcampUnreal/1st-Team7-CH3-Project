#include "CP_Guns.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "Kismet/GameplayStatics.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootScene);

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootScene);

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootScene);

    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    FireTimer = 0.0f;

    // 기본 파츠 로드 (배럴, 바디, 트리거)
    LoadGunParts();
}

void ACP_Guns::LoadGunParts()
{
    // 총기 기본 파츠들 생성

    USkeletalMesh* BarrelSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
    if (BarrelSkeletalMesh)
    {
        BarrelMesh->SetSkeletalMesh(BarrelSkeletalMesh);

        // BarrelInfo 초기화
        if (BarrelInfo)
        {
            BarrelInfo->Initialize("SK_BarrelBulletScatter");  
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("BarrelInfo is null"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Barrel Mesh"));
    }

    USkeletalMesh* BodySkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
    if (BodySkeletalMesh)
    {
        BodyMesh->SetSkeletalMesh(BodySkeletalMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Body Mesh"));
    }

    USkeletalMesh* TriggerSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerSingle.SK_TriggerSingle")));
    if (TriggerSkeletalMesh)
    {
        TriggerMesh->SetSkeletalMesh(TriggerSkeletalMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Trigger Mesh"));
    }
}

void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 발사 간격 설정 (초당 1회 발사) 이거 테스트용입니다.
    FireTimer += DeltaTime;
    if (FireTimer >= 1.0f)  // 1초마다 발사
    {
        Fire();
        FireTimer = 0.0f;  // 타이머 리셋
    }
}

void ACP_Guns::Fire()
{
    if (BarrelInfo)
    {
        if (BarrelInfo->bIsHitscan)
        {
            // FireHitscan(); 
        }
        else
        {
            FireProjectile();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ACP_Guns::Fire - BarrelInfo not found!"));
    }
}

void ACP_Guns::FireProjectile()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));
    FRotator MuzzleRotation = BarrelMesh->GetSocketRotation(FName("Muzzle"));

    // MuzzleRotation의 Pitch를 0으로 설정하여 수평으로 향하게 함
    MuzzleRotation.Pitch = 0.0f;

    // 발사 방향 계산 (수평 방향으로 나오도록)
    FVector LaunchDirection = MuzzleRotation.Vector();  // 발사 방향
    FVector Velocity = LaunchDirection * 8000.f;  // 발사 속도 설정

    UE_LOG(LogTemp, Log, TEXT("MuzzleLocation: %s, MuzzleRotation: %s, LaunchDirection: %s"), *MuzzleLocation.ToString(), *MuzzleRotation.ToString(), *LaunchDirection.ToString());

    if (ProjectileClass)
    {
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
        if (Projectile)
        {
            // 발사한 총기의 정보를 Projectile에 설정
            Projectile->SetOwner(this);

            // 물리 시뮬레이션을 비활성화 // 이거 체크 
            if (Projectile->ProjectileMesh)
            {
                Projectile->ProjectileMesh->SetSimulatePhysics(false);
            }

            // 수동으로 초기 속도 설정 (Velocity에 초기 속도 지정)
            if (Projectile->ProjectileMovement)
            {
                Projectile->ProjectileMovement->Velocity = Velocity;  // 수동으로 속도 설정
                Projectile->ProjectileMovement->Activate();  // Activate 호출
            }

            UE_LOG(LogTemp, Log, TEXT("Projectile fired successfully!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Projectile"));
        }
    }
}




