#include "engine.h"

struct FramebufferSpecification
{
	uint32_t Width, Height;
	// FramebufferFormat Format = 
	uint32_t Samples = 1;

	bool SwapChainTarget = false;
};

class Framebuffer {
public:
	Framebuffer(const FramebufferSpecification& spec);
	~Framebuffer();

	void Invalidate();

	void Bind();
	void Unbind();

	uint32_t GetColorAttachmentRendererID() { return m_ColorAttachment; }

	const FramebufferSpecification& GetSpecification() { return m_Specification; }
private:
	uint32_t m_RendererID;
	uint32_t m_ColorAttachment, m_DepthAttachment;
	FramebufferSpecification m_Specification;
};