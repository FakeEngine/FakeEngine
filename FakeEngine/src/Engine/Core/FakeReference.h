/*****************************************************************
 * \file   FakeReference.h
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

// ONLY NECESSARY IN PRE COMPILED HEADER FILES
#ifndef FAKE_API
	#ifdef FAKE_BUILD_LIBRARY
		#ifdef FAKE_LIBRARY_EXPORT
			#define FAKE_API __declspec(dllexport)
		#else
			#define FAKE_API __declspec(dllimport)
		#endif
	#else
		#define FAKE_API /* nothing */
	#endif
#endif

/**
 *
 * The ReferenceCounting super class.
 *
 * This class must be the super class of any class that should be Reference counted.
 *
 * ### Usage
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * class SomeClass : public FakeRefCounted
 *     {
 *     public:
 *         // Some methods
 *     };
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class FAKE_API FakeRefCounted
	{
	private:
		mutable uint32 RefCount = 0;

	public:

		/**
		 *
		 * Increments the RefCounter of the extending class.
		 *
		 */
		void IncrementRefCount() const
			{
			RefCount++;
			}

		/**
		 *
		 * Decrements the RefCounter of the extending class.
		 *
		 */
		void DecrementRefCount() const
			{
			RefCount--;
			}

		/**
		 *
		 * Getter for the current Reference Counter of the extending class.
		 *
		 * @return Returns the current Reference Counter value.
		 */
		uint32 GetRefCount() const
			{
			return RefCount;
			}
	};

/**
 *
 * The Engine's own Reference Counting System that works like a shared pointer.
 *
 * ### Usage
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * // Instance creation:
 * FakeRef<SomeClass> instanceName = FakeRef::Create<SomeClass>(<Constructor params for SomeClass>);
 *
 * // The Instance is automatically being destroyed if no system holds a reference to this instance anymore.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */
template<typename T>
class FAKE_API FakeRef
	{
	private:
		template<class T2>
		friend class FakeRef;
		T *Instance;

		/**
		 *
		 * This function contains the actual logical code to increment the Reference Counter of the extending class.
		 *
		 */
		void IncReference() const
			{
			if (Instance)
				Instance->IncrementRefCount();
			}

		/**
		 *
		 * This function contains the actual logical code to decrement the Reference Counter of the extending class.
		 *
		 * The Reference is automatically being destroyed if the Reference Counter equals 0.
		 *
		 */
		void DecReference() const
			{
			if (Instance)
				{
				Instance->DecrementRefCount();
				if (Instance->GetRefCount() == 0)
					{
					delete Instance;
					}
				}
			}

	public:

		/**
		 *
		 * Instantiates the Reference Counting system with nullptr.
		 *
		 */
		FakeRef() : Instance(nullptr) {}

		/**
		 *
		 * Instantiates the Reference Counting system with a Ref<> Instance.
		 *
		 * @param instance The instance that should be reference counted.
		 */
		FakeRef(T *instance) : Instance(instance)
			{
			static_assert(std::is_base_of<FakeRefCounted, T>::value, "Class is not Reference Counted!");
			IncReference();
			}

		/**
		 *
		 * Instantiates the Reference Counting system with a Reference of a different type.
		 *
		 * @param other The instance that should be reference counted.
		 */
		template<typename T2>
		FakeRef(const FakeRef<T2> &other)
			{
			Instance = (T*) other.Instance;
			IncReference();
			}

		/**
		 *
		 * Instantiates the Reference Counting system with a Reference of a different type.
		 *
		 * @param other The instance that should be reference counted.
		 */
		template<typename T2>
		FakeRef(FakeRef<T2> &&other) noexcept
			{
			Instance = (T*) other.Instance;
			other.Instance = nullptr;
			}

		/**
		 *
		 * Instantiates the Reference Counting system with a Reference of the same type.
		 *
		 * @param other The instance that should be reference counted.
		 */
		FakeRef(const FakeRef<T> &other)
			: Instance(other.Instance)
			{
			IncReference();
			}

		/**
		 *
		 * Decrements the Reference Counter by one.
		 *
		 */
		~FakeRef()
			{
			DecReference();
			}

		/**
		 *
		 * Overrides the assign operator to be able to assign a Instance to a nullptr.
		 *
		 * @return Returns the Instance with the new value.
		 */
		FakeRef &operator=(std::nullptr_t)
			{
			DecReference();
			Instance = nullptr;
			return *this;
			}

		/**
		 *
		 * Overrides the assign operator to be able to assign a Instance to a different instance.
		 *
		 * @param other The assignment value that the instance should be assigned to.
		 * @return Returns the Instance with the new value.
		 */
		FakeRef &operator=(const FakeRef<T> &other)
			{
			other.IncReference();
			DecReference();

			Instance = other.Instance;
			return *this;
			}

		/**
		 *
		 * Overrides the assign operator to be able to assign a Instance to a different instance of a different type.
		 *
		 * @param other The assignment value that the instance should be assigned to.
		 * @return Returns the Instance with the new value.
		 */
		template<typename T2>
		FakeRef &operator=(FakeRef<T2> &other)
			{
			other.IncReference();
			DecReference();

			Instance = other.Instance;
			return *this;
			}

		/**
		 *
		 * Overrides the assign operator to be able to assign a Instance to a different instance of a different type.
		 *
		 * @param other The assignment value that the instance should be assigned to.
		 * @return Returns the Instance with the new value.
		 */
		template<typename T2>
		FakeRef &operator=(FakeRef<T2> &&other)
			{
			DecReference();

			Instance = other.Instance;
			other.Instance = nullptr;
			return *this;
			}

		/**
		 *
		 * Overrides the bool operator to be able to check if the Instance that should be reference counted is already set or invalid.
		 *
		 * @return Returns true if the Instance is set to a valid value.
		 */
		operator bool() { return Instance != nullptr; }

		/**
		 *
		 * Overrides the bool operator to be able to check if the Instance that should be reference counted is already set or invalid.
		 *
		 * @return Returns true if the Instance is set to a valid value.
		 */
		operator bool() const { return Instance != nullptr; }

		/**
		 *
		 * Overrides the pointer assignment operator to be able to get the pointer value of the instance.
		 *
		 * @return Returns the pointer to the current instance.
		 */
		T *operator->() { return Instance; }

		/**
		 *
		 * Overrides the pointer assignment operator to be able to get the pointer value of the instance.
		 *
		 * @return Returns the pointer to the current instance.
		 */
		const T *operator->() const { return Instance; }

		/**
		 *
		 * Overrides the Dereferencing operator to be able to dereference the instance.
		 *
		 * @return Returns the actual value of the instance.
		 */
		T &operator*() { return *Instance; }

		/**
		 *
		 * Overrides the Dereferencing operator to be able to dereference the instance.
		 *
		 * @return Returns the actual value of the instance.
		 */
		const T &operator*() const { return *Instance; }

		/**
		 *
		 * This function returns the actual instance of the class that should be reference counted where this class is a wrapper around.
		 *
		 * @return Returns the actual value of the extending instance.
		 */
		T *Raw() { return Instance; }

		/**
		 *
		 * This function returns the actual instance of the class that should be reference counted where this class is a wrapper around.
		 *
		 * @return Returns the actual value of the extending instance.
		 */
		const T *Raw() const { return Instance; }

		/**
		 *
		 * Resets the current Instance to a pointer of a different instance or nullptr.
		 * In both scenarios the current Counter will be decremented.
		 *
		 * @param instance The instance that should replace the current instance.
		 */
		void Reset(T *instance = nullptr)
			{
			DecReference();
			Instance = instance;
			}

		/**
		 *
		 * Instantiates the actual Reference of the class that should be reference counted.
		 *
		 * @param args The Arguments which should be forwarded to the constructor of the actual class that should be reference counted.
		 * @return Returns the instance of the class that should be reference counted.
		 */
		template<typename... Args>
		static FakeRef<T> Create(Args&&... args)
			{
			return FakeRef<T>(new T(std::forward<Args>(args)...));
			}
	};

