//------------------------------------------------------------------------------------------------------------
// Confidential and proprietary source code of BEOALEX.
// This source code may not be used, reproduced or disclosed in any manner without permission.
// Copyright (c) 2025, BEOALEX. All rights reserved.
// https://github.com/beoalex
//------------------------------------------------------------------------------------------------------------

#pragma once

#include <string>
#include <chrono>

//------------------------------------------------------------------------------------------------------------

class DiffResults
{
public:
    void addProcessedFile();
    void addChangedFile(const std::wstring& filePath);
    void addAddedFile(const std::wstring& filePath);
    void addRemovedFile(const std::wstring& filePath);
    void fixStartTime();
    void fixEndTime();
    void print() const;

private:
    int m_filesProcessed = 0;
    int m_filesChanged = 0;
    int m_filesAdded = 0;
    int m_filesRemoved = 0;

    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::steady_clock::time_point m_endTime;
};

//------------------------------------------------------------------------------------------------------------