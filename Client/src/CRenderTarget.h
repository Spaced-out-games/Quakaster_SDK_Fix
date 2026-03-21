#pragma once
#include "gfx/Texture.h"
#include "gfx/CommandBuffer.h"
#include "gfx/FrameBuffer.h"
#include "core/res/Image.h"
#include "spdlog/spdlog.h"
//#include "../core.h"

namespace qk::gfx {
	struct CRenderTarget {
		gfx::CommandBuffer	m_OffscreenCommandBuffer;
		gfx::FrameBuffer	m_OffscreenFramebuffer;
		gfx::Texture		m_OffscreenTarget;
		int					m_Width = 0;
		int					m_Height = 0;

		void init(int width, int height) {
			m_Width = width;
			m_Height = height;
			Image offscreen_image(width, height, 3);
			m_OffscreenTarget.init(offscreen_image, GL_TEXTURE_2D);

			if (!m_OffscreenFramebuffer.attach(m_OffscreenTarget, 0)) {
				spdlog::error("INCOMPLETE FRAMEBUFFER!");
			}

			m_OffscreenCommandBuffer.bindFramebuffer(m_OffscreenFramebuffer);
			m_OffscreenCommandBuffer.setViewport(0, 0, m_Width, m_Height);


		}
	};
}