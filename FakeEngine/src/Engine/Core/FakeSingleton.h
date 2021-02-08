/*****************************************************************
 * \file   FakeSingleton.h
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
  * A basic Singleton template class, to avoid retyping the repeating pattern of a singleton.
  *
  */
template<class T>
class FakeSingleton
	{
	private:

		FakeSingleton(FakeSingleton const&)
			{
			}

		FakeSingleton &operator=(FakeSingleton const&)
			{
			return *this;
			}

	protected:

		FakeSingleton()
			{
			}

		~FakeSingleton()
			{
			}

	public:

		/**
		 *
		 * Returns the Instance of the singleton type object.
		 *
		 * @return
		 */
		static T *GetInstance()
			{
			static T instance;
			return &instance;
			}
	};

