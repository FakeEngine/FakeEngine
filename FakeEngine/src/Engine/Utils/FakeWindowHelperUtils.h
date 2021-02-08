/*****************************************************************
 * \file   FakeWindowHelperUtils.h
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

#include "Engine/Core/Defines/FakeKeyCodes.h"

 /**
  *
  * Helper function to convert Windows KeyCodes to the FakeEngine specific keyCodes.
  *
  * @param keyCode The keyCode that should be converted.
  * @return Returns the equivalent FakeEngine specific KeyCode.
  */
static int32 fake_window_helper_windows_to_fake(int32 keyCode)
	{
	switch (keyCode)
		{
		case 0x41: // A
			return static_cast<int32>(FAKE_KEY_A);

		case 0x42: // B
			return static_cast<int32>(FAKE_KEY_B);

		case 0x43: // C
			return static_cast<int32>(FAKE_KEY_C);

		case 0x44: // D
			return static_cast<int32>(FAKE_KEY_D);

		case 0x45: // E
			return static_cast<int32>(FAKE_KEY_E);

		case 0x46: // F
			return static_cast<int32>(FAKE_KEY_F);

		case 0x47: // G
			return static_cast<int32>(FAKE_KEY_G);

		case 0x48: // H
			return static_cast<int32>(FAKE_KEY_H);

		case 0x49: // I
			return static_cast<int32>(FAKE_KEY_I);

		case 0x4A: // J
			return static_cast<int32>(FAKE_KEY_J);

		case 0x4B: // K
			return static_cast<int32>(FAKE_KEY_K);

		case 0x4C: // L
			return static_cast<int32>(FAKE_KEY_L);

		case 0x4D: // M
			return static_cast<int32>(FAKE_KEY_M);

		case 0x4E: // N
			return static_cast<int32>(FAKE_KEY_N);

		case 0x4F: // O
			return static_cast<int32>(FAKE_KEY_O);

		case 0x50: // P
			return static_cast<int32>(FAKE_KEY_P);

		case 0x51: // Q
			return static_cast<int32>(FAKE_KEY_Q);

		case 0x52: // R
			return static_cast<int32>(FAKE_KEY_R);

		case 0x53: // S
			return static_cast<int32>(FAKE_KEY_S);

		case 0x54: // T
			return static_cast<int32>(FAKE_KEY_T);

		case 0x55: // U
			return static_cast<int32>(FAKE_KEY_U);

		case 0x56: // V
			return static_cast<int32>(FAKE_KEY_V);

		case 0x57: // W
			return static_cast<int32>(FAKE_KEY_W);

		case 0x58: // X
			return static_cast<int32>(FAKE_KEY_X);

		case 0x59: // Y
			return static_cast<int32>(FAKE_KEY_Y);

		case 0x5A: // Z
			return static_cast<int32>(FAKE_KEY_Z);

		case 0x1B: // Escape
			return static_cast<int32>(FAKE_KEY_ESCAPE);

		case 0x09: // Tab
			return static_cast<int32>(FAKE_KEY_TAB);

		case 0x0D: // Enter
			return static_cast<int32>(FAKE_KEY_ENTER);

		case 0x10: // Shift
			return static_cast<int32>(FAKE_KEY_LEFT_SHIFT);

		case 0x11: // Control
			return static_cast<int32>(FAKE_KEY_LEFT_CONTROL);

		case 0x14: // Caps Lock
			return static_cast<int32>(FAKE_KEY_CAPS_LOCK);

		case 0x90: // Numpad Lock
			return static_cast<int32>(FAKE_KEY_NUM_LOCK);

		case 0x20: // Space
			return static_cast<int32>(FAKE_KEY_SPACE);

		case 0x08: // Backspace
			return static_cast<int32>(FAKE_KEY_BACKSPACE);

		case 0x21: // Page up
			return static_cast<int32>(FAKE_KEY_PAGE_UP);

		case 0x22: // Page down
			return static_cast<int32>(FAKE_KEY_PAGE_DOWN);

		case 0x2C: // Print Screen (Screenshot) KEy
			return static_cast<int32>(FAKE_KEY_PRINT_SCREEN);

		case 0x13: // Pause Key
			return static_cast<int32>(FAKE_KEY_PAUSE);

		case 0x23: // End Key
			return static_cast<int32>(FAKE_KEY_END);

		case 0x24: // Home Key
			return static_cast<int32>(FAKE_KEY_HOME);

		case 0x2D: // Insert Key
			return static_cast<int32>(FAKE_KEY_INSERT);

		case 0x2E: // Delete Key
			return static_cast<int32>(FAKE_KEY_DELETE);

		case 0x5B: // Left Windows Key
			return static_cast<int32>(FAKE_KEY_LEFT_SUPER);

		case 0x5C: // Right Windows Key
			return static_cast<int32>(FAKE_KEY_RIGHT_SUPER);

		case 0x25: // Left
			return static_cast<int32>(FAKE_KEY_LEFT);

		case 0x26: // Up
			return static_cast<int32>(FAKE_KEY_UP);

		case 0x27: // Right
			return static_cast<int32>(FAKE_KEY_RIGHT);

		case 0x28: // Down
			return static_cast<int32>(FAKE_KEY_DOWN);

		case 0xBC: // , Key
			return static_cast<int32>(FAKE_KEY_COMMA);

		case 0xBD: // - Key
			return static_cast<int32>(FAKE_KEY_MINUS);

		case 0xBE: // . Key
			return static_cast<int32>(FAKE_KEY_PERIOD);

		case 0x30: // 0
			return static_cast<int32>(FAKE_KEY_0);

		case 0x31: // 1
			return static_cast<int32>(FAKE_KEY_1);

		case 0x32: // 2
			return static_cast<int32>(FAKE_KEY_2);

		case 0x33: // 3
			return static_cast<int32>(FAKE_KEY_3);

		case 0x34: // 4
			return static_cast<int32>(FAKE_KEY_4);

		case 0x35: // 5
			return static_cast<int32>(FAKE_KEY_5);

		case 0x36: // 6
			return static_cast<int32>(FAKE_KEY_6);

		case 0x37: // 7
			return static_cast<int32>(FAKE_KEY_7);

		case 0x38: // 8
			return static_cast<int32>(FAKE_KEY_8);

		case 0x39: // 9
			return static_cast<int32>(FAKE_KEY_9);

		case 0x60: // Numpad 0
			return static_cast<int32>(FAKE_KEY_KP_0);

		case 0x61: // Numpad 1
			return static_cast<int32>(FAKE_KEY_KP_1);

		case 0x62: // Numpad 2
			return static_cast<int32>(FAKE_KEY_KP_2);

		case 0x63: // Numpad 3
			return static_cast<int32>(FAKE_KEY_KP_3);

		case 0x64: // Numpad 4
			return static_cast<int32>(FAKE_KEY_KP_4);

		case 0x65: // Numpad 5
			return static_cast<int32>(FAKE_KEY_KP_5);

		case 0x66: // Numpad 6
			return static_cast<int32>(FAKE_KEY_KP_6);

		case 0x67: // Numpad 7
			return static_cast<int32>(FAKE_KEY_KP_7);

		case 0x68: // Numpad 8
			return static_cast<int32>(FAKE_KEY_KP_8);

		case 0x69: // Numpad 9
			return static_cast<int32>(FAKE_KEY_KP_9);

		case 0x6A: // Numpad Multiply
			return static_cast<int32>(FAKE_KEY_KP_MULTIPLY);

		case 0x6B: // Numpad Add
			return static_cast<int32>(FAKE_KEY_KP_ADD);

		case 0x6D: // Numpad Subtract
			return static_cast<int32>(FAKE_KEY_KP_SUBTRACT);

		case 0x6E: // Numpad Decimal
			return static_cast<int32>(FAKE_KEY_KP_DECIMAL);

		case 0x6F: // Numpad Divide
			return static_cast<int32>(FAKE_KEY_KP_DIVIDE);

		case 0x70: // F1
			return static_cast<int32>(FAKE_KEY_F1);

		case 0x71: // F2
			return static_cast<int32>(FAKE_KEY_F2);

		case 0x72: // F3
			return static_cast<int32>(FAKE_KEY_F3);

		case 0x73: // F4
			return static_cast<int32>(FAKE_KEY_F4);

		case 0x74: // F5
			return static_cast<int32>(FAKE_KEY_F5);

		case 0x75: // F6
			return static_cast<int32>(FAKE_KEY_F6);

		case 0x76: // F7
			return static_cast<int32>(FAKE_KEY_F7);

		case 0x77: // F8
			return static_cast<int32>(FAKE_KEY_F8);

		case 0x78: // F9
			return static_cast<int32>(FAKE_KEY_F9);

		case 0x79: // F10
			return static_cast<int32>(FAKE_KEY_F10);

		case 0x7A: // F11
			return static_cast<int32>(FAKE_KEY_F11);

		case 0x7B: // F12
			return static_cast<int32>(FAKE_KEY_F12);

		case 0x7C: // F13
			return static_cast<int32>(FAKE_KEY_F13);

		case 0x7D: // F14
			return static_cast<int32>(FAKE_KEY_F14);

		case 0x7E: // F15
			return static_cast<int32>(FAKE_KEY_F15);

		case 0x7F: // F16
			return static_cast<int32>(FAKE_KEY_F16);

		case 0x80: // F17
			return static_cast<int32>(FAKE_KEY_F17);

		case 0x81: // F18
			return static_cast<int32>(FAKE_KEY_F18);

		case 0x82: // F19
			return static_cast<int32>(FAKE_KEY_F19);

		case 0x83: // F20
			return static_cast<int32>(FAKE_KEY_F20);

		case 0x84: // F21
			return static_cast<int32>(FAKE_KEY_F21);

		case 0x85: // F22
			return static_cast<int32>(FAKE_KEY_F22);

		case 0x86: // F23
			return static_cast<int32>(FAKE_KEY_F23);

		case 0x87: // F24
			return static_cast<int32>(FAKE_KEY_F24);
		}

	return -1;
	}

/**
 *
 * Helper function to convert FakeEngine KeyCodes to Windows specific keyCodes.
 *
 * @param keyCode The keyCode that should be converted.
 * @return Returns the equivalent Windows specific KeyCode.
 */
static int32 fake_window_helper_fake_to_windows(FakeKey keyCode)
	{
	switch (keyCode)
		{
		case FAKE_KEY_A: // A
			return 0x41;

		case FAKE_KEY_B: // B
			return 0x42;

		case FAKE_KEY_C: // C
			return 0x43;

		case FAKE_KEY_D: // D
			return 0x44;

		case FAKE_KEY_E: // E
			return 0x45;

		case FAKE_KEY_F: // F
			return 0x46;

		case FAKE_KEY_G: // G
			return 0x47;

		case FAKE_KEY_H: // H
			return 0x48;

		case FAKE_KEY_I: // I
			return 0x49;

		case FAKE_KEY_J: // J
			return 0x4A;

		case FAKE_KEY_K: // K
			return 0x4B;

		case FAKE_KEY_L: // L
			return 0x4C;

		case FAKE_KEY_M: // M
			return 0x4D;

		case FAKE_KEY_N: // N
			return 0x4E;

		case FAKE_KEY_O: // O
			return 0x4F;

		case FAKE_KEY_P: // P
			return 0x50;

		case FAKE_KEY_Q: // Q
			return 0x51;

		case FAKE_KEY_R: // R
			return 0x52;

		case FAKE_KEY_S: // S
			return 0x53;

		case FAKE_KEY_T: // T
			return 0x54;

		case FAKE_KEY_U: // U
			return 0x55;

		case FAKE_KEY_V: // V
			return 0x56;

		case FAKE_KEY_W: // W
			return 0x57;

		case FAKE_KEY_X: // X
			return 0x58;

		case FAKE_KEY_Y: // Y
			return 0x59;

		case FAKE_KEY_Z: // Z
			return 0x5A;

		case FAKE_KEY_ESCAPE: // Escape
			return 0x1B;

		case FAKE_KEY_TAB: // Tab
			return 0x09;

		case FAKE_KEY_ENTER: // Enter
			return 0x0D;

		case FAKE_KEY_LEFT_SHIFT: // Shift
		case FAKE_KEY_RIGHT_SHIFT:
			return 0x10;

		case FAKE_KEY_LEFT_CONTROL: // Control
		case FAKE_KEY_RIGHT_CONTROL:
			return 0x11;

		case FAKE_KEY_CAPS_LOCK: // Caps Lock
			return 0x14;

		case FAKE_KEY_NUM_LOCK: // Numpad Lock
			return 0x90;

		case FAKE_KEY_SPACE: // Space
			return 0x20;

		case FAKE_KEY_BACKSPACE: // Backspace
			return 0x08;

		case FAKE_KEY_PAGE_UP: // Page up
			return 0x21;

		case FAKE_KEY_PAGE_DOWN: // Page down
			return 0x22;

		case FAKE_KEY_PRINT_SCREEN: // Print Screen (Screenshot) KEy
			return 0x2C;

		case FAKE_KEY_PAUSE: // Pause Key
			return 0x13;

		case FAKE_KEY_END: // End Key
			return 0x23;

		case FAKE_KEY_HOME: // Home Key
			return 0x24;

		case FAKE_KEY_INSERT: // Insert Key
			return 0x2D;

		case FAKE_KEY_DELETE: // Delete Key
			return 0x2E;

		case FAKE_KEY_LEFT_SUPER: // Left Windows Key
			return 0x5B;

		case FAKE_KEY_RIGHT_SUPER: // Right Windows Key
			return 0x5C;

		case FAKE_KEY_LEFT: // Left
			return 0x25;

		case FAKE_KEY_UP: // Up
			return 0x26;

		case FAKE_KEY_RIGHT: // Right
			return 0x27;

		case FAKE_KEY_DOWN: // Down
			return 0x28;

		case FAKE_KEY_COMMA: // , Key
			return 0xBC;

		case FAKE_KEY_MINUS: // - Key
			return 0xBD;

		case FAKE_KEY_PERIOD: // . Key
			return 0xBE;

		case FAKE_KEY_0: // 0
			return 0x30;

		case FAKE_KEY_1: // 1
			return 0x31;

		case FAKE_KEY_2: // 2
			return 0x32;

		case FAKE_KEY_3: // 3
			return 0x33;

		case FAKE_KEY_4: // 4
			return 0x34;

		case FAKE_KEY_5: // 5
			return 0x35;

		case FAKE_KEY_6: // 6
			return 0x36;

		case FAKE_KEY_7: // 7
			return 0x37;

		case FAKE_KEY_8: // 8
			return 0x38;

		case FAKE_KEY_9: // 9
			return 0x39;

		case FAKE_KEY_KP_0: // Numpad 0
			return 0x60;

		case FAKE_KEY_KP_1: // Numpad 1
			return 0x61;

		case FAKE_KEY_KP_2: // Numpad 2
			return 0x62;

		case FAKE_KEY_KP_3: // Numpad 3
			return 0x63;

		case FAKE_KEY_KP_4: // Numpad 4
			return 0x64;

		case FAKE_KEY_KP_5: // Numpad 5
			return 0x65;

		case FAKE_KEY_KP_6: // Numpad 6
			return 0x66;

		case FAKE_KEY_KP_7: // Numpad 7
			return 0x67;

		case FAKE_KEY_KP_8: // Numpad 8
			return 0x68;

		case FAKE_KEY_KP_9: // Numpad 9
			return 0x69;

		case FAKE_KEY_KP_MULTIPLY: // Numpad Multiply
			return 0x6A;

		case FAKE_KEY_KP_ADD: // Numpad Add
			return 0x6B;

		case FAKE_KEY_KP_SUBTRACT: // Numpad Subtract
			return 0x6D;

		case FAKE_KEY_KP_DECIMAL: // Numpad Decimal
			return 0x6E;

		case FAKE_KEY_KP_DIVIDE: // Numpad Divide
			return 0x6F;

		case FAKE_KEY_F1: // F1
			return 0x70;

		case FAKE_KEY_F2: // F2
			return 0x71;

		case FAKE_KEY_F3: // F3
			return 0x72;

		case FAKE_KEY_F4: // F4
			return 0x73;

		case FAKE_KEY_F5: // F5
			return 0x74;

		case FAKE_KEY_F6: // F6
			return 0x75;

		case FAKE_KEY_F7: // F7
			return 0x76;

		case FAKE_KEY_F8: // F8
			return 0x77;

		case FAKE_KEY_F9: // F9
			return 0x78;

		case FAKE_KEY_F10: // F10
			return 0x79;

		case FAKE_KEY_F11: // F11
			return 0x7A;

		case FAKE_KEY_F12: // F12
			return 0x7B;

		case FAKE_KEY_F13: // F13
			return 0x7C;

		case FAKE_KEY_F14: // F14
			return 0x7D;

		case FAKE_KEY_F15: // F15
			return 0x7E;

		case FAKE_KEY_F16: // F16
			return 0x7F;

		case FAKE_KEY_F17: // F17
			return 0x80;

		case FAKE_KEY_F18: // F18
			return 0x81;

		case FAKE_KEY_F19: // F19
			return 0x82;

		case FAKE_KEY_F20: // F20
			return 0x83;

		case FAKE_KEY_F21: // F21
			return 0x84;

		case FAKE_KEY_F22: // F22
			return 0x85;

		case FAKE_KEY_F23: // F23
			return 0x86;

		case FAKE_KEY_F24: // F24
			return 0x87;
		}

	return -1;
	}
