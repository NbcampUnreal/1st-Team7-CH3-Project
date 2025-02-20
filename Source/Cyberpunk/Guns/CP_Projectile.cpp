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

    // 2초 후 자동 제거
    SetLifeSpan(2.0f);

    if (ProjectileMesh)
    {
        ProjectileMesh->SetWorldScale3D(FVector(0.04f, 0.04f, 0.04f));
        ProjectileMesh->SetSimulatePhysics(false);
    }

    if (ProjectileMovement)
    {
        ProjectileMovement->InitialSpeed = 3000.f;
        ProjectileMovement->MaxSpeed = 40000.f;
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
