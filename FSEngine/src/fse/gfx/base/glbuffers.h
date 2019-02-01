#pragma once 

namespace FSEngine {

class FSDLL DynamicBuffer {
public:
	DynamicBuffer(GLuint size);
	virtual ~DynamicBuffer();

	void lock();
	void wait();

	inline operator GLuint() const { return m_id; }
protected:
	GLuint m_id;
	void *_data;
private:
	GLsync m_syncObj = nullptr;
};


class FSDLL VertexBuffer : public DynamicBuffer {
public:
	VertexBuffer(GLuint size);
	inline ~VertexBuffer() {}

	void storeData(const float *data, GLuint offset, GLuint length);
private:
	float *m_data;
};


class FSDLL IndexBuffer : public DynamicBuffer {
public:
	IndexBuffer(GLuint size);
	inline ~IndexBuffer() {}

	void storeData(const short *data, GLuint offset, GLuint length);

	inline GLuint getIndexCount() const { return m_indexCount; }
private:
	short *m_data;
	GLuint m_indexCount;
};


class FSDLL UniformBuffer {
public:
	UniformBuffer(GLuint size, GLuint shaderProgram, GLuint bindingPoint, const std::string &blockName);
	~UniformBuffer();

	void storeData(const void *data, GLuint offset, GLuint length);

	inline void bind() { glBindBuffer(GL_UNIFORM_BUFFER, m_id); }
private:
	GLuint m_id, m_shaderProgram;
};


class FSDLL VertexArray {
public:
	inline VertexArray() { glCreateVertexArrays(1, &m_id); }
	inline ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

	void setIndexBuffer(const IndexBuffer &ib);
	inline void formatVertexAttrib(GLuint formatIndex, GLuint size, GLuint rOffset) const { glVertexArrayAttribFormat(m_id, formatIndex, size, GL_FLOAT, false, rOffset); }
	inline void addVertexBuffer(GLuint bufferIndex, GLintptr offset, GLsizei stride, const VertexBuffer &vb) const { glVertexArrayVertexBuffer(m_id, bufferIndex, vb, offset, stride); }
	inline void linkAttribs(GLuint formatIndex, GLuint bufferIndex) const { glVertexArrayAttribBinding(m_id, formatIndex, bufferIndex); }

	inline void enableAttrib(GLuint formatIndex) { glEnableVertexArrayAttrib(m_id, formatIndex); }
	inline void disableAttrib(GLuint formatIndex) { glDisableVertexArrayAttrib(m_id, formatIndex); }

	inline GLuint getID() const { return m_id; }
	inline operator GLuint() const { return m_id; }
	inline GLuint getIndexCount() const { return m_indexCount; }
private:
	GLuint m_id;
	GLuint m_indexCount;
};

}