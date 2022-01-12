/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>
#include <utility>

typedef void (*RESIZE_CALLBACK)(anciu32 x, anciu32 y);

enum AnciKeyCodeBits {
};

class AnciWindow {
public:
        AnciWindow(String title, ancivec2 dimension)          : _title(std::move(title)), _dimension(dimension) {};
        virtual ~AnciWindow()                                 {};
        virtual ANCI_WINDOW_HANDLE      GetHandle   ()        = 0;
        virtual bool                    ShouldClose ()        = 0;
        virtual void                    PollEvents  ()        = 0;
        String&                         GetTitle    ()        { return _title;     }
        ancivec2                        GetDimension()        { return _dimension; };
        virtual void                    SetResizeCallback(RESIZE_CALLBACK callback) = 0;

protected:
        String                          _title;
        ancivec2                        _dimension;

};