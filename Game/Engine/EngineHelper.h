#pragma once

template<typename T>
struct delete_pointer_element
{
    void operator()(T element)const
    {
        delete element;
    }
};