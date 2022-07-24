//------------------------------------------------------------------------------------------------------------
// Confidential and proprietary source code of BEOALEX.
// This source code may not be used, reproduced or disclosed in any manner without permission.
// Copyright (c) 2022, BEOALEX. All rights reserved.
// https://github.com/beoalex
//------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <assert.h>

#ifdef _DEBUG
    #include <conio.h>
#endif

#include "Calculator.h"

//------------------------------------------------------------------------------------------------------------

int wmain(int argc, wchar_t* argv[])
{
    const int successCode = 0;
    const int errorCode = 1;

    int result = errorCode;

    std::wcout << std::flush;
    assert(_setmode(_fileno(stdout), _O_U16TEXT) != -1);

    try
    {
        if (argc == 3)
        {
            wprintf(L"Comparing directories \"%s\" and \"%s\"...\n\n", argv[1], argv[2]);

            Calculator calc(argv[1], argv[2]);
            const DiffResults diffResults = calc.run();
            diffResults.print();

            result = successCode;
        }
        else
        {
            std::wcout << L"Usage: dir_diff.exe <dir1> <dir2>" << std::endl;
        }
    }
    catch (const std::exception& exc)
    {
        std::wcout << exc.what() << std::endl;
    }

#ifdef _DEBUG
    std::wcout << L"\nPress any key to continue..." << std::endl;
    _getch();
#endif

    return result;
}

//------------------------------------------------------------------------------------------------------------
