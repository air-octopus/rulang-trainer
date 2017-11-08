//
// Created by maksko on 14.09.17.
//

#pragma once

#include "Student.h"
#include "Admin.h"

namespace air {

class Trainer {
public:

    // Получить доступ к "учетной записи" администратора
    Admin const *           admin           () const noexcept;
    Admin *                 admin           ()       noexcept;

    // Создать "учетную запись" администратора.
    // Если учетная запись администратора уже была создана, то будет выброшеноо исключене
    Admin *                 createAdmin     ();

    // Получить доступ к массиву учебных проофилей
    const Student::arr &    students        () const noexcept;

    // Добавить учебный профиль
    Student *               addStudent      ();

};

} // air
