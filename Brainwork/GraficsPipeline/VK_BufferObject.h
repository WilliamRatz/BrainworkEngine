#ifndef VK_BUFFEROBJECT_H
#define VK_BUFFEROBJECT_H

#include "VK_Buffer.h"

class VK_Renderer;


class VK_BufferObject : public VK_Buffer
{
public:
	Texture						texture;
	Cube						cube;
	GameObject					gameObject = GameObject(cube);

	VK_BufferObject				(VK_Renderer& renderer);
	~VK_BufferObject			();

	void updateUniformBuffer	(uint32_t currentImage);
	
	void cleanup				();
};

#endif // !VK_BUFFEROBJECT_H
