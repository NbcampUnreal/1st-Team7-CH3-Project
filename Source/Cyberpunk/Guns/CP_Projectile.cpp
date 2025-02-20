#include "CP_Projectile.h"
#include "UObject/ConstructorHelpers.h"  // StaticLoadObject 사용을 위한 헤더 추가

ACP_Projectile::ACP_Projectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root Scene Component 추가
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    // Projectile Mesh 설정
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(RootComponent);

    // Projectile Movement 설정
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->bAutoActivate = false;  // 초기에는 비활성화

    // 총알 메쉬 경로로 로드
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMesh(TEXT("/Game/Gun_BluePrint/Bullet/9mm.9mm"));
    if (BulletMesh.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(BulletMesh.Object);  // 로드한 메쉬를 설정
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Bullet Mesh"));
    }
}

void ACP_Projectile::BeginPlay()
{
    Super::BeginPlay();

    // 총알 메쉬 스케일 설정
    if (ProjectileMesh)
    {
        ProjectileMesh->SetWorldScale3D(FVector(0.025f, 0.025f, 0.025f));
        ProjectileMesh->SetSimulatePhysics(false);  // 물리 시뮬레이션 비활성화
    }

    // ProjectileMovement 설정
    if (ProjectileMovement)
    {
        ProjectileMovement->InitialSpeed = 30000.f;
        ProjectileMovement->MaxSpeed = 30000.f;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->bShouldBounce = true;
    }
}

// 발사 함수 추가
void ACP_Projectile::LaunchProjectile(const FVector& LaunchDirection)
{
    if (ProjectileMovement)
    {
        // 발사 방향 설정
        FVector LaunchVelocity = LaunchDirection * ProjectileMovement->InitialSpeed;
        ProjectileMovement->Velocity = LaunchVelocity;

        // ProjectileMovement 활성화
        ProjectileMovement->Activate();
    }
}
