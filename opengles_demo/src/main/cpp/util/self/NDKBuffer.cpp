//
// Created by baishengye on 2023-11-15.
//


#include "NDKBuffer.h"

NDKBuffer::NDKBuffer(NDKBuffer::Type type, NDKBuffer::UsagePattern usage)
                        :m_bufferType(type),m_usage(usage),m_buffSize(0)
{
    glGenBuffers(1, &m_buffID);
}

NDKBuffer::~NDKBuffer()
{
    glDeleteBuffers(1, &m_buffID);
}

void NDKBuffer::Bind()
{
    glBindBuffer(m_bufferType, m_buffID);
    LOGD("BUFF ID: %d",m_buffID);
}

void NDKBuffer::Release()
{
    glBindBuffer(m_bufferType, 0);
}

void NDKBuffer::SetBufferData(const GLvoid *data, GLsizeiptr size)
{
    if (size > m_buffSize) {
        m_buffSize = size;
        glBufferData(m_bufferType, size, data, m_usage);
    } else {
        glBufferSubData(m_bufferType, 0, size, data);
    }
}