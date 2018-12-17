#ifndef VK_BUFFEROBJECT_H
#define VK_BUFFEROBJECT_H

#include "VK_Buffer.h"

class VK_Renderer;

class BufferObject : public Buffer
{
public:
	Cube						cube;
	GameObject					gameObject = GameObject(cube);

	BufferObject				(VK_Renderer& renderer);

	void updateUniformBuffer	(uint32_t currentImage);
	
	void cleanup				();
};

#endif // !VK_BUFFEROBJECT_H
