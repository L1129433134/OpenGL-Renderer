#include <iostream>
#include "glErrors.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <GL/glew.h>

void Renderer::Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader,unsigned int mode) {
	
	//Shader Bind//
	shader.Bind();
	//VAO Bind//
	va.Bind();
	// Index Bind //
	ib.Bind();

	glCall(glDrawElements(mode,ib.GetCount(),GL_UNSIGNED_INT,nullptr));

}
void Renderer::Clear() const{
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}