#include <unity.h>

#include <aoc_lib/math.h>

void setUp() {}
void tearDown() {}

void test_nlogf(void) { TEST_ASSERT_FLOAT_WITHIN(0.01f, 3.0f, nlogf(27.0f, 3.0f)); }

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_nlogf);

    return UNITY_END();
}