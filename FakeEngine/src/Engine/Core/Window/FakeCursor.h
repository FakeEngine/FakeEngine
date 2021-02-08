/*****************************************************************
 * \file   FakeCursor.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

#include "Engine/Core/FakeCore.h"

enum class FakeCursorType
    {
    None = 0,
    AppStarting,
    Arrow, Cross, Hand, UpArrow,
    SizeAll, SizeNESW, SizeNS, SizeNWE, SizeWE,
    Help, IBeam, No, Wait
    };

/**
 *
 * This class represents a Cursor. It can be set by the client and changed in the Window class.
 *
 */
class FAKE_API FakeCursor
    {
    public:

        /**
         *
         * Activates and sets a specific cursor type.
         *
         * @param type The Cursor type.
         */
        static void ActivateCursor(FakeCursorType type);

        /**
         *
         * Sets a specific cursor type.
         *
         * @param type The cursor type.
         */
        static void SetCursor(FakeCursorType type);

        /**
         *
         * Returns the current cursor type.
         *
         * @return Returns the current cursor type.
         */
        static FakeCursorType GetActiveCursor();
    };
