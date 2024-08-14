#ifndef TCPCOM_H
#define TCPCOM_H

#include "comservice.h"

class TCPService : public COMService
{
    void run(void) override;
};

#endif