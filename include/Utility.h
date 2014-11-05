/*
 * utility.h
 *
 *  Created on: Oct 26, 2014
 *      Author: yuczhou
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "Global.h"

namespace BioChip {
namespace Utility {

template<class T>
std::shared_ptr<T> getPointer(T *pointer) {
    return std::shared_ptr<T>(pointer);
}

}
}

#endif /* UTILITY_H_ */
