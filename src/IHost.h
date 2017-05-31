//
// Created by Rayer Tung on 31/05/2017.
//

#ifndef OCTO_IHOST_H
#define OCTO_IHOST_H

class IAuth;

class IHost {
    virtual IAuth* get_auth() = 0;
    virtual bool post_message(const std::string& message) = 0;
    virtual ~IHost(){}
};


#endif //OCTO_IHOST_H
