/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/
#include "precomp.h"
#include "WexTestClass.h"

#include "CommonState.hpp"

#include "globals.h"
#include "textBuffer.hpp"

#include "input.h"

using namespace WEX::Logging;
using namespace WEX::TestExecution;

class Ucs2CharRowTests
{
    TEST_CLASS(Ucs2CharRowTests);

    Ucs2CharRow* pSingleByte;
    Ucs2CharRow* pDoubleByte;

    size_t _sRowWidth = 80;

    TEST_METHOD_SETUP(MethodSetup)
    {
        pSingleByte = new Ucs2CharRow(static_cast<short>(_sRowWidth));
        pSingleByte->SetWrapForced(true);
        pSingleByte->SetDoubleBytePadded(true);

        pDoubleByte = new Ucs2CharRow(static_cast<short>(_sRowWidth));
        pDoubleByte->SetWrapForced(true);
        pDoubleByte->SetDoubleBytePadded(true);

        return true;
    }

    TEST_METHOD_CLEANUP(MethodCleanup)
    {
        delete pDoubleByte;
        delete pSingleByte;
        return true;
    }

    TEST_METHOD(TestInitialize)
    {
        // Cases to test
        Ucs2CharRow* pTestItems[] { pSingleByte, pDoubleByte };

        // Loop cases
        for (UINT iIndex = 0; iIndex < ARRAYSIZE(pTestItems); iIndex++)
        {
            Ucs2CharRow* pUnderTest = pTestItems[iIndex];

            pUnderTest->Reset();

            VERIFY_IS_FALSE(pUnderTest->WasWrapForced());
            VERIFY_IS_FALSE(pUnderTest->WasDoubleBytePadded());

            for (UINT iStrLength = 0; iStrLength < _sRowWidth; iStrLength++)
            {
                VERIFY_ARE_EQUAL(pUnderTest->GetGlyphAt(iStrLength), UNICODE_SPACE);
                VERIFY_IS_TRUE(pUnderTest->GetAttribute(iStrLength).IsSingle());
            }
        }
    }

    TEST_METHOD(TestContainsText)
    {
        // After init, should have no text
        pSingleByte->Reset();
        VERIFY_IS_FALSE(pSingleByte->ContainsText());

        // add some text
        pSingleByte->GetGlyphAt(10) = L'a';

        // should have text
        VERIFY_IS_TRUE(pSingleByte->ContainsText());
    }
};
