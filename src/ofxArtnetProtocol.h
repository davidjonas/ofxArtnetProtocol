/*The MIT License (MIT)

 Copyright (c) 2014 Nathanaël Lécaudé
 https://github.com/natcl/Artnet, http://forum.pjrc.com/threads/24688-Artnet-to-OctoWS2811

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef ARTNET_H
#define ARTNET_H

#include "ofMain.h"
#include "ofxNetwork.h"

// UDP specific
#define ART_NET_PORT 6454
// Opcodes
#define ART_POLL 0x2000
#define ART_DMX 0x5000
// Buffers
#define MAX_BUFFER_ARTNET 530
// Packet
#define ART_NET_ID "Art-Net\0"
#define ART_DMX_START 18

typedef struct {
    char id[8];
    char opcode[2];
    char sequence;
    char universe[2];
    char length[2];
    char data[MAX_BUFFER_ARTNET];
}_artnet_packet;

class ofxArtnetProtocol// : public ofThread
{
public:
    ofxArtnetProtocol();

    void begin();
    void begin(const char* ip);
    uint16_t read();
    void setDmxData(uint8_t* data, uint16_t size);
    void setDmxData(uint16_t index, uint8_t data);
    void send(uint8_t* data, uint16_t universe = 0, uint16_t size = 512);
    void printPacketHeader();
    void printPacketContent();

    // Return a pointer to the start of the DMX data
    inline uint8_t* getDmxFrame(void)
    {
        return artnetPacket + ART_DMX_START;
    }

    inline uint16_t getOpcode(void)
    {
        return opcode;
    }

    inline uint8_t getSequence(void)
    {
        return sequence;
    }

    inline uint16_t getUniverse(void)
    {
        return incomingUniverse;
    }

    inline uint16_t getLength(void)
    {
        return dmxDataLength;
    }

    inline void setArtDmxCallback(void (*fptr)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data))
    {
        artDmxCallback = fptr;
    }

private:

    ofxUDPManager udpConnection;
    _artnet_packet packet;

    uint8_t artnetPacket[MAX_BUFFER_ARTNET];
    uint16_t packetSize;
    uint16_t opcode;
    uint8_t sequence;
    uint16_t incomingUniverse;
    uint16_t dmxDataLength;
    void (*artDmxCallback)(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);

    char artnet_send_packet[MAX_BUFFER_ARTNET];

    bool bConnected;
};

#endif
