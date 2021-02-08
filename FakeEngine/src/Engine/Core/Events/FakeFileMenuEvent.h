/*****************************************************************
 * \file   FakeFileMenuEvent.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
 * 
 * 
 *********************************************************************/

#pragma once

#include "FakeEventsBase.h"

enum class FakeFileMenuType
	{
	FileMenu = 0,
	PopupMenu
	};

 /**
  *
  * The FileMenu Event is being triggered if the User clicks on a File Menu or a Popup Menu Entry.
  *
  */
class FAKE_API FakeFileMenuEvent : public FakeEvent
	{
	private:
		int32 ID;
		FakeFileMenuType Type;

	public:

		/**
		 *
		 * Constructs the FileMenu Event which can be passed as a parameter then.
		 *
		 * @param id The FileMenu ID
		 */
		FakeFileMenuEvent(int id, FakeFileMenuType type);

		/**
		 *
		 * Getter for the FileMenu ID.
		 *
		 * @return Returns the FileMenu ID
		 */
		int32 GetID() const;

		/**
		 * 
		 * Getter for the FileMenuType.
		 * 
		 * @return Returns FileMenu or PopupMenu.
		 */
		FakeFileMenuType GetType() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_TYPE(FileMenu)
		FAKE_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
