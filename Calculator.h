//------------------------------------------------------------------------------------------------------------
// Confidential and proprietary source code of BEOALEX.
// This source code may not be used, reproduced or disclosed in any manner without permission.
// Copyright (c) 2022, BEOALEX. All rights reserved.
// https://github.com/beoalex
//------------------------------------------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "DiffResults.h"

//------------------------------------------------------------------------------------------------------------

class Calculator
{
public:
    Calculator(const std::wstring& leftDir, const std::wstring& rightDir);

    DiffResults run();

private:
    const std::wstring m_leftDir;
    const std::wstring m_rightDir;

    std::unordered_set< std::wstring > m_leftSubpaths;

    mutable std::vector< std::byte > m_leftBuffer;
    mutable std::vector< std::byte > m_rightBuffer;

    DiffResults m_diffResults;

    static const int ms_pathSeparatorLen = 1;

    void processLeftToRight();
    void processRightToLeft();
    bool areEqualFiles(const std::wstring& leftPath, const std::wstring& rightPath) const;
};

//------------------------------------------------------------------------------------------------------------