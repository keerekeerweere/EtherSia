/**
 * Header file for the TFTPServer class
 * @file TFTPServer.h
 */

#ifndef TFTPServer_H
#define TFTPServer_H

#include <stdint.h>
#include "UDPSocket.h"

/**
 * Class for sending and receiving UDP packets on a specified port
 */
class TFTPServer: public UDPSocket {

public:

    /**
     * Construct a UDP socket, with a listening port defined
     *
     * @param ether The Ethernet interface to attach the socket to
     * @param localPort The local UDP port number to listen on
     */
    TFTPServer(EtherSia &ether, uint16_t localPort=69);

    /**
     * Check if a UDP packet is available to be processed on this socket
     * @return true if there is a valid packet has been received for this socket
     */
    boolean handleRequest();


    const uint8_t TFTP_BLOCK_SIZE = 512;

    enum {
        TFTP_OPCODE_READ = 1,
        TFTP_OPCODE_WRITE = 2,
        TFTP_OPCODE_DATA = 3,
        TFTP_OPCODE_ACK = 4,
        TFTP_OPCODE_ERROR = 5
    };

    enum {
        TFTP_UNDEFINED_ERROR = 0,
        TFTP_NOT_FOUND = 1,
        TFTP_ACCESS_VIOLATION = 2,
        TFTP_DISK_FULL = 3,
        TFTP_ILLEGAL_OPERATION = 4,
        TFTP_UNKNOWN_TRANSFER_ID = 5,
        TFTP_FILE_ALREADY_EXISTS = 6,
        TFTP_NO_SUCH_USER = 7,
    };

protected:

    void sendError(uint8_t errorCode);

    void handleWriteRequest(int8_t fileno, IPv6Address& address, uint16_t port);
    void handleReadRequest(int8_t fileno, IPv6Address& address, uint16_t port);

    int8_t openFile(const char* filename);
    void writeBytes(int8_t fileno, uint16_t block, const uint8_t* data, uint16_t len);
    int8_t readBytes(int8_t fileno, uint16_t block, const uint8_t* data, uint16_t len);

};


#endif