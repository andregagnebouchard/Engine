#pragma once
//=================================================================================================
class AppUtil
{
public:
	const int64 GetDiskSpaceByte() const;
	const bool IsProcessUniqueInstance(const std::wstring &processName) const;
	const int64 GetPhysicalRAMByte() const;
	const int64 GetVirtualRAMByte() const;
	const MegaHertz GetCpuSpeed() const;
};
//=================================================================================================