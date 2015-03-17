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

    struct Utility {

        template<class T>
        static std::shared_ptr<T> getPointer(T *pointer) {
            return std::shared_ptr<T>(pointer);
        }

        typedef std::shared_ptr<std::vector<std::string> > StringListPointer;

        static StringListPointer split(const std::string &str, const char *delimiter) {
            auto splitted = getPointer(new std::vector<std::string>());
            char *cstr = new char[str.length() + 1];
            strcpy(cstr, str.c_str());
            char *word = strtok(cstr, delimiter);
            while (word) {
                splitted->push_back(std::string(word));
                word = strtok(NULL, delimiter);
            }
            delete[] cstr;
            return splitted;
        }

        template<class T>
        static std::shared_ptr<std::stringstream> toStream(const std::vector<T> &list) {
            auto stream = getPointer(new std::stringstream());
            for (auto const &item : list) {
                *stream << item << " ";
            }
            return stream;
        }

        template<class K, class V>
        static const V &getElementOr(const std::map<K, V> &container, const K &key, const V &defaultValue) {
            return container.find(key) != container.end() ? container.at(key) : defaultValue;
        }

    };

}

#endif /* UTILITY_H_ */
