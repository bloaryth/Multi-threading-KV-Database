//
// Created by wanton-wind on 2018/5/6.
//

#ifndef SYSTEM2018_DATABASE_ERROR_H
#define SYSTEM2018_DATABASE_ERROR_H

#include <bits/exception.h>

namespace Dytz {

    class UnknownCommandType : public std::exception {

    };

    class OpenFileError : public std::exception {

    };


}



#endif //SYSTEM2018_DATABASE_ERROR_H
