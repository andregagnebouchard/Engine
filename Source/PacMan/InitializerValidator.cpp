#include "stdafx.h"
#include "InitializerValidator.h"
//=================================================================================================
void InitializerValidator::ValidateIfDiskHaveEnoughSpace(const int64 diskSpaceNeeded)
{
	if (GetDiskSpaceSpace() < diskSpaceNeeded)
		return false;

	return true;
}
//=================================================================================================
const int64 InitializerValidator::GetDiskSpaceSpace() const
{
	// Check for enough free disk space on the current disk.
	const int  drive = _getdrive();
	struct _diskfree_t diskfree;

	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters =
		diskSpaceNeeded / (diskfree.sectors_per_cluster*diskfree.bytes_per_sector);

	if (diskfree.avail_clusters < neededClusters)
	{
		// if you get here you don’t have enough disk space!
		GCC_ERROR("CheckStorage Failure: Not enough physical storage.");
		return false;
	}
	return true;
}
//=================================================================================================
//=================================================================================================
//=================================================================================================
//=================================================================================================
