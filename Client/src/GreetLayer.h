#pragma once
#include "core/ILayer.h"
#include "core/IEvent.h"
#include <iostream>

struct GreetLayer : qk::ILayer {

	EBlock on_event(const qk::IEvent& evt) override {

		std::cout << "hi!";

		return EBlock::Pass;

	}

	void on_render() override {

	}

	GreetLayer() {
		subscribe(qk::EEventCategory::cat_all);
	}
};