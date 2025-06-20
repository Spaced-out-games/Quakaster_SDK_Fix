#include "Layer.h"
#include <SDL.h>

namespace qk
{

	// does nothing by default
	Layer::Layer() {}
	// does nothing by default
	Layer::~Layer() {}


	// default implementation is passthrough
	void Layer::on_attach() {}

	void Layer::render() {}

	// default implementation is passthrough
	void Layer::on_detach() {}




	[[nodiscard]] uint8_t LayerStack::insert(Layer* layer)
	{
		if (!m_EmptyCount)
		{
			uint8_t handle = m_Layers.size();
			m_Layers.push_back(layer);
			layer->on_attach();
			return handle;
		}

		// otherwise, we gotta look for the first empty space
		for (uint8_t i = 0; i < m_Layers.size(); i++)
		{
			// found an empty slot
			if (m_Layers[i] == nullptr)
			{
				m_Layers[i] = layer;
				m_EmptyCount--;
				layer->on_attach();
				return i;
			}
		}
		return UINT8_MAX;

	}
	bool LayerStack::remove(uint8_t handle)
	{
		// make sure it's in range, exit if not
		if (handle >= m_Layers.size()) return false;
		if (m_Layers[handle] == nullptr) return false;

		// call on_detach()

		m_Layers[handle]->on_detach();

		// call the virtual destructor
		delete m_Layers[handle];

		// mark empty
		m_Layers[handle] = nullptr;

		// also, keep track of how many empty slots we have
		m_EmptyCount++;

		return true;

	}
	
	void LayerStack::render() {
		// Render from back to front, including index 0
		for (size_t i = m_Layers.size(); i-- > 0;) {
			if (m_Layers.at(i)) m_Layers.at(i)->render();
		}
	}

	void LayerStack::propagate_events()
	{
		// poll SDL events
		while (SDL_PollEvent(&m_Event))
		{
			for (size_t i = 0; i < m_Layers.size(); i++)
			{
				// If the layer consumes the event, the later layers don't get it. 
				if (m_Layers.at(i))
				{
					// if the layer consumes the event, don't bother propagating the event further.
					if (m_Layers.at(i)->on_event(m_Event)) return;
				}
				
				
			}
		}
		return;
	}

	LayerStack::~LayerStack()
	{
		for (size_t i = 0; i < m_Layers.size(); i++)
		{
			// Detach, then delete each layer
			if (m_Layers.at(i))
			{
				// detach first, delete layer second
				m_Layers.at(i)->on_detach();
				delete m_Layers.at(i);
			}


		}
	}

}