//------------------------------------------------------------------------------------------------------------
// Confidential and proprietary source code of BEOALEX.
// This source code may not be used, reproduced or disclosed in any manner without permission.
// Copyright (c) 2025, BEOALEX. All rights reserved.
// https://github.com/beoalex
//------------------------------------------------------------------------------------------------------------

#include <filesystem>
#include <assert.h>

#include "Calculator.hpp"

namespace fs = std::filesystem;

//------------------------------------------------------------------------------------------------------------

Calculator::Calculator(const std::wstring& leftDir, const std::wstring& rightDir) : m_leftDir(leftDir), m_rightDir(rightDir)
{
    m_leftBuffer.resize(0x1'0000); // 64 kB
    m_rightBuffer.resize(m_leftBuffer.size());
}

//------------------------------------------------------------------------------------------------------------

DiffResults Calculator::run()
{
    m_diffResults.fixStartTime();
    processLeftToRight();
    processRightToLeft();
    m_diffResults.fixEndTime();
    return m_diffResults;
}

//------------------------------------------------------------------------------------------------------------

void Calculator::processLeftToRight()
{
    const std::size_t leftPrefixLen = m_leftDir.size() + ms_pathSeparatorLen;

    for (const auto& it : fs::recursive_directory_iterator(m_leftDir, fs::directory_options::skip_permission_denied))
    {
        const fs::directory_entry leftEntry(it.path());

        if (leftEntry.is_directory())
        {
            continue;
        }

        m_diffResults.addProcessedFile();
        const std::wstring leftSubpath = it.path().wstring().substr(leftPrefixLen);
        m_leftSubpaths.insert(leftSubpath);
        const fs::directory_entry rightEntry(fs::path(m_rightDir) / leftSubpath);

        if (   rightEntry.exists()
            && !rightEntry.is_directory())
        {
            if (   leftEntry.file_size() == 0
                && rightEntry.file_size() == 0)
            {
                continue;
            }

            if (   leftEntry.file_size() != rightEntry.file_size()
                || !areEqualFiles(leftEntry.path().wstring(), rightEntry.path().wstring()))
            {
                m_diffResults.addChangedFile(leftSubpath);
            }
        }
        else
        {
            m_diffResults.addRemovedFile(leftSubpath);
        }
    }
}

//------------------------------------------------------------------------------------------------------------

void Calculator::processRightToLeft()
{
    const std::size_t rightPrefixLen = m_rightDir.size() + ms_pathSeparatorLen;

    for (const auto& it : fs::recursive_directory_iterator(m_rightDir, fs::directory_options::skip_permission_denied))
    {
        if (fs::directory_entry(it.path()).is_directory())
        {
            continue;
        }

        const std::wstring rightSubpath = it.path().wstring().substr(rightPrefixLen);

        if (m_leftSubpaths.find(rightSubpath) == m_leftSubpaths.cend())
        {
            m_diffResults.addProcessedFile();
            m_diffResults.addAddedFile(rightSubpath);
        }
    }
}

//------------------------------------------------------------------------------------------------------------

bool Calculator::areEqualFiles(const std::wstring& leftPath, const std::wstring& rightPath) const
{
    bool result = false;

    static_assert(sizeof(decltype(m_leftBuffer)::value_type) == sizeof(decltype(m_rightBuffer)::value_type));
    assert(m_leftBuffer.size() == m_rightBuffer.size());
    const std::size_t itemSize = sizeof(decltype(m_leftBuffer)::value_type);

    const wchar_t* const fileMode = L"rb";
    FILE* leftFile = _wfsopen(leftPath.c_str(), fileMode, _SH_DENYWR);
    FILE* rightFile = _wfsopen(rightPath.c_str(), fileMode, _SH_DENYWR);

    if (   leftFile != nullptr
        && rightFile != nullptr)
    {
        while (true)
        {
            const std::size_t leftRead = fread(m_leftBuffer.data(), itemSize, m_leftBuffer.size(), leftFile);
            const std::size_t rightRead = fread(m_rightBuffer.data(), itemSize, m_rightBuffer.size(), rightFile);

            if (   leftRead != rightRead
                || ferror(leftFile) != 0
                || ferror(rightFile) != 0)
            {
                break;
            }

            if (   leftRead == 0
                && rightRead == 0)
            {
                assert(feof(leftFile) != 0);
                assert(feof(rightFile) != 0);
                result = true;
                break;
            }

            if (std::memcmp(m_leftBuffer.data(), m_rightBuffer.data(), leftRead * itemSize) != 0)
            {
                break;
            }
        }
    }

    if (leftFile != nullptr)
    {
        fclose(leftFile);
    }

    if (rightFile != nullptr)
    {
        fclose(rightFile);
    }

    return result;
}

//------------------------------------------------------------------------------------------------------------
