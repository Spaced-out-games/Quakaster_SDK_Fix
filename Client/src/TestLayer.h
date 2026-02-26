#pragma once
#include "core/ILayer.h"
#include "core/IEvent.h"


struct TestLayer : qk::ILayer {

	EBlock on_event(const qk::IEvent& evt) override {

		if (evt.m_Type == qk::EEventType::KeyPress_evt) return EBlock::Block;

		return EBlock::Pass;

	}

	void on_render() override {

	}

	TestLayer() {
		subscribe(qk::EEventCategory::cat_kbmouse);
	}
};