/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#pragma once

#include <arrows_core.h>

typedef arosu32  compid_t;
static  compid_t ITER_ID = 0;

#include <unordered_map>

template <typename T>
class GameComponent {
public:
        GameComponent(const char *name, T* instance) : _name(name), _instance(instance)
        { _id = (++ITER_ID); }

        inline const char *GetName()
        { return _name; }

        inline compid_t GetId()
        { return _id; }

        inline T* GetInstance()
        { return _instance; }

private:
        const char *_name;
        compid_t      _id;

protected:
        T* _instance;
};