#ifndef _SPOS_LAB1_DEMOFUNCS
#define _SPOS_LAB1_DEMOFUNCS

#include <chrono>
#include <thread>
#include <optional>
#include <condition_variable>

# ifdef __GNUG__
# define INLINE_CONST	constexpr
# else
# define INLINE_CONST	inline const
# endif

namespace spos::lab1::demo {
    using namespace std::chrono_literals;
    using duration = std::chrono::seconds;
    using std::pair;
    using std::optional;

    template<typename T> optional<T> gen_func(optional<pair<duration, T>> attribs) {
	if (attribs) {
	    std::this_thread::sleep_for(std::get<duration>(attribs.value()));
	    return std::get<T>(attribs.value());
	}
	else {
	    std::condition_variable cv;
	    std::mutex m;
	    std::unique_lock<std::mutex> lock(m);
	    cv.wait(lock, []{return false;});
	    return {};
	}
    }

    enum op_group { AND, OR, INT, DOUBLE };

    template<op_group O>
    struct op_group_traits;

    template<typename T> 
    struct op_group_type_traits {
	typedef T value_type;
	typedef pair<duration, value_type> attr_type;
	typedef struct { optional<attr_type> f_attrs, g_attrs; } case_type;
    };

    template<> 
    struct op_group_traits<INT> : op_group_type_traits<int> {
    	INLINE_CONST static case_type cases[] = {
	    { .f_attrs = pair(1s, 3), .g_attrs = pair(3s, 5) }, // pair<duration, int>
	    { .f_attrs = pair(3s, 3), .g_attrs = pair(1s, 5) },
	    { .f_attrs = pair(3s, 0), .g_attrs = {} },
	    { .f_attrs =          {}, .g_attrs = pair(3s, 0) },
	    { .f_attrs = pair(3s, 1), .g_attrs = {} },
	    { .f_attrs =          {}, .g_attrs = pair(5s, 1) }
	};
    };

    template<> 
    struct op_group_traits<DOUBLE> : op_group_type_traits<double> {
    	INLINE_CONST static case_type cases[] = {
	    { .f_attrs = pair(1s, 3.), .g_attrs = pair(3s, 5.) },
	    { .f_attrs = pair(3s, 3.), .g_attrs = pair(1s, 5.) },
	    { .f_attrs = pair(3s, 0.), .g_attrs = {} },
	    { .f_attrs =           {}, .g_attrs = pair(3s, 0.) },
	    { .f_attrs = pair(3s, 1.), .g_attrs = {} },
	    { .f_attrs =           {}, .g_attrs = pair(5s, 1.) }
	};
    };

    template<> 
    struct op_group_traits<AND> : op_group_type_traits<bool> {
    	INLINE_CONST static case_type cases[] = {
	    { .f_attrs =  pair(1s, true), .g_attrs = pair(3s, true) },
	    { .f_attrs =  pair(3s, true), .g_attrs = pair(1s, true) },
	    { .f_attrs = pair(3s, false), .g_attrs = {} },
	    { .f_attrs =              {}, .g_attrs = pair(3s, false) },
	    { .f_attrs =  pair(3s, true), .g_attrs = {} },
	    { .f_attrs =              {}, .g_attrs = pair(5s, true) }
	};
    };

    template<> 
    struct op_group_traits<OR> : op_group_type_traits<bool> {
    	INLINE_CONST static case_type cases[] = {
	    { .f_attrs = pair(1s, false), .g_attrs = pair(3s, false) },
	    { .f_attrs = pair(3s, false), .g_attrs = pair(1s, false) },
	    { .f_attrs =  pair(3s, true), .g_attrs = {} },
	    { .f_attrs =              {}, .g_attrs = pair(3s, true) },
	    { .f_attrs = pair(3s, false), .g_attrs = {} },
	    { .f_attrs =              {}, .g_attrs = pair(5s, false) }
	};
    };

	
    template<op_group O> typename op_group_traits<O>::value_type f_func(int case_nr) {
	return gen_func<typename op_group_traits<O>::value_type>(op_group_traits<O>::cases[case_nr].f_attrs).value();
    }

    template<op_group O> typename op_group_traits<O>::value_type g_func(int case_nr) {
	return gen_func<typename op_group_traits<O>::value_type>(op_group_traits<O>::cases[case_nr].g_attrs).value();
    }
}
#endif
