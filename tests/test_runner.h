#ifndef TESTRUNNER_H_
#define TESTRUNNER_H_

#include <cstdio>
#include <cmath>
#include <vector>
#include <stdexcept>

// ---------------------------------------------------------------------------
// Internal counters (shared via inline singletons)
// ---------------------------------------------------------------------------

inline int& _passCount() { static int n = 0; return n; }
inline int& _failCount() { static int n = 0; return n; }

struct _Test { const char* name; void (*fn)(); };

inline std::vector<_Test>& _registry() {
    static std::vector<_Test> r;
    return r;
}

struct _Registrar {
    _Registrar(const char* name, void (*fn)()) { _registry().push_back({name, fn}); }
};

// ---------------------------------------------------------------------------
// Macros
// ---------------------------------------------------------------------------

#define TEST(name) \
    static void _test_##name(); \
    static _Registrar _reg_##name(#name, _test_##name); \
    static void _test_##name()

inline void _check(bool ok, const char* expr, const char* file, int line) {
    if (ok) {
        _passCount()++;
    } else {
        std::printf("    FAIL: %s  (%s:%d)\n", expr, file, line);
        _failCount()++;
    }
}

#define CHECK(expr)             _check(!!(expr), #expr, __FILE__, __LINE__)
#define CHECK_EQ(a, b)          CHECK((a) == (b))
#define CHECK_NEAR(a, b, eps)   CHECK(std::fabs((double)(a) - (double)(b)) < (eps))

// ---------------------------------------------------------------------------
// Runner
// ---------------------------------------------------------------------------

inline int runTests() {
    for (size_t i = 0; i < _registry().size(); i++) {
        _Test& t = _registry()[i];
        std::printf("  %s\n", t.name);
        try {
            t.fn();
        } catch (std::exception& ex) {
            std::printf("    EXCEPTION: %s\n", ex.what());
            _failCount()++;
        } catch (...) {
            std::printf("    UNKNOWN EXCEPTION\n");
            _failCount()++;
        }
    }
    std::printf("\n%d passed, %d failed\n", _passCount(), _failCount());
    return _failCount() ? 1 : 0;
}

#endif /* TESTRUNNER_H_ */
