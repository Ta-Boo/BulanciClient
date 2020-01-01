//
// Created by tobo on 12/30/19.
//

#ifndef BULANCICLIENT_MESSAGE_H
#define BULANCICLIENT_MESSAGE_H

class Message
{
public:
    int _foo;
    int _bar;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & _foo;
        ar & _bar;
    }


};


#endif //BULANCICLIENT_MESSAGE_H
