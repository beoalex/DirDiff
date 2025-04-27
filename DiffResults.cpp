//------------------------------------------------------------------------------------------------------------
// Confidential and proprietary source code of BEOALEX.
// This source code may not be used, reproduced or disclosed in any manner without permission.
// Copyright (c) 2022, BEOALEX. All rights reserved.
// https://github.com/beoalex
//------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <assert.h>

#include "DiffResults.hpp"

namespace cr = std::chrono;

//------------------------------------------------------------------------------------------------------------

void DiffResults::addProcessedFile()
{
    ++m_filesProcessed;
}

//------------------------------------------------------------------------------------------------------------

void DiffResults::addChangedFile(const std::wstring& filePath)
{
    ++m_filesChanged;
    std::wcout << filePath << L"  CHANGED" << std::endl;
}

//------------------------------------------------------------------------------------------------------------

void DiffResults::addAddedFile(const std::wstring& filePath)
{
    ++m_filesAdded;
    std::wcout << filePath << L"  ADDED" << std::endl;
}

//------------------------------------------------------------------------------------------------------------

void DiffResults::addRemovedFile(const std::wstring& filePath)
{
    ++m_filesRemoved;
    std::wcout << filePath << L"  REMOVED" << std::endl;
}

//------------------------------------------------------------------------------------------------------------

void DiffResults::fixStartTime()
{
    assert(m_startTime == m_endTime);
    m_startTime = cr::steady_clock::now();
}

//------------------------------------------------------------------------------------------------------------

void DiffResults::fixEndTime()
{
    assert(m_startTime > m_endTime);
    m_endTime = cr::steady_clock::now();
}

//------------------------------------------------------------------------------------------------------------

void DiffResults::print() const
{
    assert(m_startTime <= m_endTime);
    const auto processingTime = m_endTime - m_startTime;
    const int minutes = static_cast< int >(cr::duration_cast< cr::minutes >(processingTime).count());
    const int seconds = static_cast< int >(cr::duration_cast< cr::seconds >(processingTime).count());

    wprintf(L"\nComparison finished in %dm %ds. %d files processed, %d changed, %d added, %d removed.\n",
        minutes, seconds, m_filesProcessed, m_filesChanged, m_filesAdded, m_filesRemoved);
}

//------------------------------------------------------------------------------------------------------------
