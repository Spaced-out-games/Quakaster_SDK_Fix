/// **************************************** QUAKASTER ENGINE **************************************** 
/// gui/Widget.h
/// Purpose: Defines an interface for defining ImGui prefabs.
/// **************************************************************************************************

#pragma once


namespace qk::gui {

	struct Widget {

		Widget() = default;
		
		virtual void draw() = 0;
		
		virtual ~Widget() = default;

	};

}