/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>
#include <utility>

class AnciWindow {
public:
        AnciWindow(String title, ancivec2 dimension)          : _title(std::move(title)), _dimension(dimension) {};
        virtual ~AnciWindow()                                 {};
        virtual ANCI_WINDOW_HANDLE      GetHandle   ()        = 0;
        virtual bool                    ShouldClose ()        = 0;
        virtual void                    PollEvents  ()        = 0;
        String&                         GetTitle    ()        { return _title;     }
        glm::vec2                       GetDimension()        { return _dimension; };

private:
        String                          _title;
        ancivec2                        _dimension;

};