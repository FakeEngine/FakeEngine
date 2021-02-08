/*****************************************************************
 * \file   FakeStringHelperUtils.h
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

 /**
  *
  * This Helper function converts any lowercase character to a uppercase character.
  *
  * @param letter The letter that should be converted to a uppercase character.
  * @return Returns the uppercase version of the provided character or the character itself if it is already a uppercase character.
  */
static char fake_string_helper_to_upper_case(char letter)
	{
	if (letter >= 'a' && letter <= 'z')
		{
		return letter + ('A' - 'a');
		}

	return letter;
	}

/**
 *
 * This Helper function converts any uppercase character to a lowerchase character.
 *
 * @param letter The letter that should be converted to a lowercase character.
 * @return Returns the lowercase version of the provided character or the character itself if it is already a lowercase character.
 */
static char fake_string_helper_to_lower_case(char letter)
	{
	if (letter >= 'A' && letter <= 'Z')
		{
		return letter - ('A' - 'a');
		}

	return letter;
	}
