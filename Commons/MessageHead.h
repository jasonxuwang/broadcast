
#include <iostream>
#define BUFSIZE 1024

class MessageHead{
    public:
        MessageHead();
        ~MessageHead();
        // functions to convert a message head to an bytearray
        int32_t toBytes(char* to_buffer, int32_t& outputLength);
        int32_t toClass(char* from_buffer, int32_t outputLength);
        int32_t m_Length;
    private:
        // private fields for a message head
        
        // int32_t m_PlayerId;
        // int32_t m_MessageId;

    public:

        
    private:

};