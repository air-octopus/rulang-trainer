//
// Created by maksko on 03.11.17.
//

#pragma once

#include <bits/shared_ptr.h>
#include <vector>

namespace air {

class Student {
public:

    using ptr = std::shared_ptr<Student>;
    using arr = std::vector<Student*>;


};

} // air
