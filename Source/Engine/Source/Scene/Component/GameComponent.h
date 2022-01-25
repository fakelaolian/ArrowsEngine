/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#pragma once

#include <arrows_core.h>

typedef arrou32 compid_t;

static compid_t ITER_ID = 0;

class GameComponent {
public:
        GameComponent(const char *name) : _name(name)
        { _id = (++ITER_ID); }

        inline const char *GetName()
        { return _name; }

        inline compid_t GetId()
        { return _id; }

private:
        const char *_name;
        compid_t      _id;
};