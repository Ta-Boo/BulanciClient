//
// Created by tobo on 1/1/20.
//

#ifndef BULANCICLIENT_MESSAGEFACTORY_H
#define BULANCICLIENT_MESSAGEFACTORY_H


#include "Message.h"
#include <boost/algorithm/string.hpp>


class MessageFactory {
public:
    MessageFactory();
    ~MessageFactory();
    Message createMessage(char* input);

};


#endif //BULANCICLIENT_MESSAGEFACTORY_H
