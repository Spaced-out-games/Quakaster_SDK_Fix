#pragma once


namespace gui {

	struct Widget {

		Widget() = default;
		
		virtual void draw() = 0;
		
		virtual ~Widget() = default;

	};

}