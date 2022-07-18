#include "framebuffer.h"

#include "gl_utils.h"
//#include <glad/glad.h>

Framebuffer::Framebuffer(const FramebufferSpecification& spec): m_Specification(spec) {
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
}

void Framebuffer::Invalidate() {
	GL(glGenFramebuffers(1, &m_RendererID));
	GL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

	GL(glGenTextures(1, &m_ColorAttachment));
	GL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment));
	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0));

	GL(glGenTextures(1, &m_DepthAttachment));
	GL(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
	GL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height));
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0,
	// 	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0));

	//HZ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

	GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Framebuffer::Bind() {
	GL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void Framebuffer::Unbind() {
	GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
