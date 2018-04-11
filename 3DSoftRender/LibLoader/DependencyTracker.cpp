#include "loaderPCH.h"

DependencyTracker::DependencyTracker()
{
}

DependencyTracker::DependencyTracker(const std::wstring & baseFile)
{
}

DependencyTracker::~DependencyTracker()
{
}

const DependencyTracker & DependencyTracker::operator=(const DependencyTracker & other)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

void DependencyTracker::SetBaseFile(const std::wstring & baseFile)
{
}

void DependencyTracker::AddDependency(const std::wstring & dependencyFile)
{
}

bool DependencyTracker::IsStale()
{
	return false;
}

void DependencyTracker::SetLastLoadTime(time_t lastLoadTime)
{
}

time_t DependencyTracker::GetLastLoadTime() const
{
	return time_t();
}

bool DependencyTracker::Save()
{
	return false;
}

bool DependencyTracker::Load()
{
	return false;
}
