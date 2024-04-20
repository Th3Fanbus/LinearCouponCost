/* SPDX-License-Identifier: MPL-2.0 */

#include "LinearCouponCost.h"
#include "FGResourceSinkSubsystem.h"
#include "LinearCouponCostSubsystem.h"
#include "Patching/NativeHookManager.h"

class FTh3ResourceSinkSubsystem
{
private:
	static inline TWeakObjectPtr<ALinearCouponCostSubsystem> SubsystemPtr;

	static FORCEINLINE ALinearCouponCostSubsystem* GetSubsystem(const UObject* WorldContext)
	{
		if (not IsValid(WorldContext)) {
			return nullptr;
		}
		if (ALinearCouponCostSubsystem* Subsystem = GetValid(SubsystemPtr.Get())) {
			if (not WITH_EDITOR or Subsystem->GetWorld() == WorldContext->GetWorld()) {
				return Subsystem;
			}
		}
		ALinearCouponCostSubsystem* Subsystem = ALinearCouponCostSubsystem::Get(WorldContext);
		if (IsValid(Subsystem)) {
			SubsystemPtr = Subsystem;
			return Subsystem;
		}
		return nullptr;
	}

	static void GetRequiredPointsForLevel(
		TCallScope<int64(__cdecl*)(const AFGResourceSinkSubsystem*, EResourceSinkTrack, int32)>& scope,
		const AFGResourceSinkSubsystem* self,
		EResourceSinkTrack resourceSinkTrack,
		int32 level)
	{
		if (ALinearCouponCostSubsystem* Subsystem = GetSubsystem(self)) {
			const int64 Value = Subsystem->GetCouponCostForSinkTrack(resourceSinkTrack);
			if (Value > 0) {
				scope.Override(Value * FMath::Max<int64>(1, level + 1));
			}
		}
	}

public:
	static void InstallHooks()
	{
		SUBSCRIBE_METHOD(AFGResourceSinkSubsystem::GetRequiredPointsForLevel, &FTh3ResourceSinkSubsystem::GetRequiredPointsForLevel);
	}
};

void FLinearCouponCostModule::StartupModule()
{
	if (not WITH_EDITOR) {
		FTh3ResourceSinkSubsystem::InstallHooks();
	}
}

void FLinearCouponCostModule::ShutdownModule()
{
}

IMPLEMENT_MODULE(FLinearCouponCostModule, LinearCouponCost)