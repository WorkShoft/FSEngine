#include "pch.h"
#include "glbuffers.h"

namespace FSEngine {

/*******************************
*         DynamicBuffer        *
*******************************/

DynamicBuffer::DynamicBuffer(GLuint size)
{
	GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
	glCreateBuffers(1, &m_id);
	glNamedBufferStorage(m_id, size, nullptr, flags);
	_data = glMapNamedBufferRange(m_id, 0, size, flags);
}

DynamicBuffer::~DynamicBuffer()
{
	glUnmapNamedBuffer(m_id);
	glDeleteBuffers(1, &m_id);
}

void DynamicBuffer::wait()
{
	GLenum waitReturn = GL_UNSIGNALED;
	while (waitReturn != GL_ALREADY_SIGNALED && waitReturn != GL_CONDITION_SATISFIED) {
		waitReturn = glClientWaitSync(m_syncObj, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
	}
}

void DynamicBuffer::lock()
{
	if(m_syncObj != nullptr) glDeleteSync(m_syncObj);
	m_syncObj = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

/*******************************
*         VertexBuffer         *
*******************************/

VertexBuffer::VertexBuffer(GLuint size) : DynamicBuffer(size * sizeof(float))
{
	m_data = (float*)_data;
}

void VertexBuffer::storeData(const float *data, GLuint offset, GLuint length)
{
	int j = 0;
	for(int i = offset; i < length + offset; i++) {
		m_data[i] = data[j];
		j++;
	}
}

/*******************************
*          IndexBuffer         *
*******************************/

IndexBuffer::IndexBuffer(GLuint size) : DynamicBuffer(size * sizeof(short))
{
	m_data = (short*)_data;
	m_indexCount = size;
}

void IndexBuffer::storeData(const short *data, GLuint offset, GLuint length)
{
	int j = 0;
	for(int i = offset; i < length + offset; i++) {
		m_data[i] = data[j];
		j++;
	}
}

/*******************************
*          UniformBuffer       *
*******************************/

UniformBuffer::UniformBuffer(GLuint size, GLuint shaderProgram, GLuint bindingPoint, const std::string &blockName) : m_shaderProgram(shaderProgram)
{
	GLuint blockIndex = glGetUniformBlockIndex(shaderProgram, blockName.c_str());
	glUniformBlockBinding(shaderProgram, blockIndex, bindingPoint);
	
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_UNIFORM_BUFFER, m_id); //Doing it the old way because I think that's the only way to do it.
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_id);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void UniformBuffer::storeData(const void *data, GLuint offset, GLuint length)
{
	glBufferSubData(GL_UNIFORM_BUFFER, offset, length, data);
}

/*******************************
*          VertexArray         *
*******************************/

void VertexArray::setIndexBuffer(const IndexBuffer &ib) 
{
	m_indexCount = ib.getIndexCount();
	glVertexArrayElementBuffer(m_id, ib);
}

}