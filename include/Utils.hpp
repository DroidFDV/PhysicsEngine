#include <cstdlib>
#include <iostream>

#define _AXC_BEGIN namespace axc {
#define _AXC_END   }
#define _AXC       ::axc::
#define _STD       ::std::


_AXC_BEGIN

inline void _VERIFY (bool expression, const char* msg) {
    if (expression == true)
    {
        std::cerr << '\n===================================================' 
            << msg 
            << '\n===================================================';
        std::exit(134);
    }
}

template <
    class _Ty
>
inline void swap (_Ty& _Left, _Ty& _Right) noexcept {
    if (addresof(_Left) != addresof(_Right)) 
    {
        _Ty _Tmp = move(_Left);
        _Left    = move(_Right); 
        _Right   = move(_Tmp);
    } 
}

_AXC_END
