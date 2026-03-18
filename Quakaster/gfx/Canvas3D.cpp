#include "Canvas3D.h"
#include "GL/glew.h"

namespace qk::gfx {

	Canvas3D::~Canvas3D() {

	}

	qk::io::Layer::EBlock Canvas3D::on_event(const qk::io::Event& evt) {
		// don't worry about it yet
		return EBlock::Pass;
	}
	void Canvas3D::on_render() {

		if (m_CommandBuffer) call(*m_CommandBuffer);

	}
	void Canvas3D::on_attach() {}
	void Canvas3D::on_detach() {}



}