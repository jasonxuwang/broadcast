#include "Serializer.h"


Serializer::Serializer(){
    reset();
}


Serializer::~Serializer(){
}


//  Message m_Message;
//         char m_uffer[BUFSIZ];
int32_t Serializer::read(char* iBuffer, int32_t iSize){
      // empty buffer first 
    reset();
    memcpy(m_buffer, iBuffer, iSize);    // copy to self buffer
   
    return 0;
}


void Serializer::reset(){
    memset(m_buffer, '\0', BUFSIZE);     // empty buffer first 
    m_MessageLength = 0;
    m_offset = 0;
}

/**
 * 把输入的iMessage对象，按 长度(4Bytes) | Message Body 格式复制到给定字符数组中
*/
int32_t Serializer::serialize(Message iMessage, char* iBuffer){
    // 先计算长度
    int32_t tMessageLength = iMessage.ByteSizeLong();

    //长度复制到buffer首部
    encode_int32(iBuffer,tMessageLength );

    // serailize message对象
    iMessage.SerializeToArray(iBuffer+sizeof(int32_t), tMessageLength); // 长度放到buffer中
						   
} // convert message to char
        

/**
 * 在read()调用后执行。
 * 从存储的字符数组中，解析出一个Message对象存储到成员变量中。
*/   
int32_t Serializer::deserialize(){
    // 先读长度.
    m_MessageLength = decode_int32(m_buffer+m_offset);
    if (m_MessageLength <0) {
        //如果没有东西可读
        reset();
        return 0;
    }

    m_offset += sizeof(int32_t);
    if (!m_Message.ParseFromArray(m_buffer+m_offset, m_MessageLength) ){
        //如果读取出错，重置所有Buffer
        reset();
        return -1;
    }
    m_offset += sizeof(m_MessageLength);
    return 1;
   

}// parse a message from the current buffer, set the message member;



