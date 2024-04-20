/* SPDX-License-Identifier: MPL-2.0 */

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "FGResourceSinkSubsystem.h"
#include "LinearCouponCostSubsystem.generated.h"

UCLASS(Abstract)
class LINEARCOUPONCOST_API ALinearCouponCostSubsystem : public AModSubsystem
{
	GENERATED_BODY()
protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
	int64 CouponCost_DefaultTrack;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int64 CouponCost_ExplorationTrack;
public:
	static ALinearCouponCostSubsystem* Get(const UObject* WorldContext);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int64 GetCouponCostForSinkTrack(EResourceSinkTrack SinkTrack) const;
};
