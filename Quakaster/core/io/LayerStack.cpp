#include "LayerStack.h"


namespace qk {

	void LayerStack::insert_layer(std::unique_ptr<ILayer>&& layer) {
		m_Layers.push_back(std::move(layer));
	}

	void LayerStack::attach_queue(EventQueue* queue) {
		m_Queue = queue;
	}



	void LayerStack::propagate_events() {

		if (!m_Queue) return;

		ILayer::EBlock BlockResult = {};


		for (const Event& evt: m_Queue->events())
		{
			for (auto& layerPtr : m_Layers) {
				if (!(layerPtr->filter & evt.m_Category)) continue;
				BlockResult = layerPtr->on_event(evt);       // unique_ptr operator-> gives raw pointer
				if (BlockResult == ILayer::EBlock::Block) break;
			}
		}

		m_Queue->clear();

	}

	void LayerStack::render() {
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it) {
			(*it)->on_render();
		}
	}


}