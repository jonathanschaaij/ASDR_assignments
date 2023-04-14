#include <stdio.h>
#include <cmath>
#include <assert.h>

#include <cmath>

void myReadConvert(const double *src, double *dst)
{
    // [ P1_ENC, P1_IN_1, P1_IN2, P2_ENC, P2_IN_1, P2_IN2, P3_ENC, P3_IN_1, P3_IN2, P4_ENC, P4_IN_1, P4_IN2]
    // Tilt = 2000 per rev  1:1 ratio  index 0
    // Pan = 1250 per rev   4:1 ratio  index 3

    // Convert Tilt encoder to angle, where center is 0.
    if (src[0] > 8191)
    {
        dst[0] = round((2 * M_PI * (src[0] - 16384) / 2000) * 100) / 100;
    }
    else
    {
        dst[0] = round((2 * M_PI * src[0] / 2000) * 100) / 100;
    }

    // Convert Pan encoder to angle, where center is 0.
    if (src[3] > 8191)
    {
        dst[3] = round((2 * M_PI * (src[3] - 16384) / (1250)) * 100) / 100;
    }
    else
    {
        dst[3] = round((2 * M_PI * src[3] / (1250)) * 100) / 100;
    }
}

void myWriteConvert(const double *src, double *dst)
{
    // [P1_PWM, P1_OUT_1, P2_PWM, P2_OUT_1, P3_PWM, P3_OUT_1, P4_PWM, P4_OUT_1]
    // Convert percentile from -1 1 range to -2047 2047 range
    dst[0] = round(src[0] * 2047); // Round to nearest integer
    dst[2] = round(src[2] * 2047); // Round to nearest integer
}

void compare_arrays(const double *expected, const double *result, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (fabs(result[i] - expected[i]) >= 1e-6)
        {
            printf("Assertion failed: expected[%d]=%f, result[%d]=%f\n", i, expected[i], i, result[i]);
            assert(false);
        }
    }
    printf("Passed.\n");
}

void test_myReadConvert()
{
    printf("Testing myReadConvert...\n");
    // 90 degrees tilt and 180 degrees pan
    printf("Readconvert: 90 degrees tilt, 180 degrees pan\n");
    double test_src[12] = {500, 0, 0, 625, 0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst[12] = {1.57, 0, 0, 3.14, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    myReadConvert(test_src, result_dst);
    compare_arrays(expected_dst, result_dst, 12);

    // -90 degrees tilt and -180 degrees pan
    printf("Readconvert: -90 degrees tilt, -180 degrees pan\n");
    double test_src2[12] = {15884, 0, 0, 15759, 0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst2[12] = {-1.57, 0, 0, -3.14, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst2[12];
    myReadConvert(test_src2, result_dst2);
    compare_arrays(expected_dst2, result_dst2, 12);

    // Test 3: Maximum tilt and pan
    printf("Readconvert: Maximum tilt, Maximum pan\n");
    double test_src3[12] = {2000, 0, 0, 1250, 0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst3[12] = {6.28, 0, 0, 6.28, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst3[12];
    myReadConvert(test_src3, result_dst3);
    compare_arrays(expected_dst3, result_dst3, 12);

    // Test 4: Minimum tilt and pan
    printf("Readconvert: Minimum tilt, Minimum pan\n");
    double test_src4[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst4[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst4[12];
    myReadConvert(test_src4, result_dst4);
    compare_arrays(expected_dst4, result_dst4, 12);

    // Test 5: 45 degrees tilt and 90 degrees pan
    printf("Readconvert: 45 degrees tilt, 90 degrees pan\n");
    double test_src5[12] = {250, 0, 0, 312.5, 0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst5[12] = {0.79, 0, 0, 1.57, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst5[12];
    myReadConvert(test_src5, result_dst5);
    compare_arrays(expected_dst5, result_dst5, 12);

    // Test 6: -45 degrees tilt and -90 degrees pan
    printf("Readconvert: -45 degrees tilt, -90 degrees pan\n");
    double test_src6[12] = {16134, 0, 0, 16071.5, 0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst6[12] = {-0.79, 0, 0, -1.57, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst6[12];
    myReadConvert(test_src6, result_dst6);
    compare_arrays(expected_dst6, result_dst6, 12);
}

void test_myWriteConvert()
{
    printf("Testing myWriteConvert...\n");
    // 0.1 tilt and 0.1 pan
    printf("Writeconvert: 0.1 tilt, 0.1 pan\n");
    double test_src[8] = {-0.1, 0, 0.1, 0, 0, 0, 0, 0};
    double expected_dst[8] = {-205, 0, 205, 0, 0, 0, 0, 0};
    double result_dst[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    myWriteConvert(test_src, result_dst);
    compare_arrays(expected_dst, result_dst, 8);

    // -0.1 tilt and -0.1 pan
    printf("Writeconvert: -0.1 tilt, -0.1 pan\n");
    double test_src2[8] = {0.1, 0, -0.1, 0, 0, 0, 0, 0};
    double expected_dst2[8] = {205, 0, -205, 0, 0, 0, 0, 0};
    double result_dst2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    myWriteConvert(test_src2, result_dst2);
    compare_arrays(expected_dst2, result_dst2, 8);

    // Test 3: Maximum tilt and pan
    printf("Writeconvert: Maximum tilt, Maximum pan\n");
    double test_src3[8] = {1, 0, 1, 0, 0, 0, 0, 0};
    double expected_dst3[8] = {2047, 0, 2047, 0, 0, 0, 0, 0};
    double result_dst3[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    myWriteConvert(test_src3, result_dst3);
    compare_arrays(expected_dst3, result_dst3, 8);

    // Test 4: Minimum tilt and pan
    printf("Writeconvert: Maximum negative tilt, maximum negative pan\n");
    double test_src4[8] = {-1, 0, -1, 0, 0, 0, 0, 0};
    double expected_dst4[8] = {-2047, 0, -2047, 0, 0, 0, 0, 0};
    double result_dst4[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    myWriteConvert(test_src4, result_dst4);
    compare_arrays(expected_dst4, result_dst4, 8);

    // Test 5: Tilt and pan at mid-range
    printf("Writeconvert: 0 tilt, 0 pan\n");
    double test_src5[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double expected_dst5[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double result_dst5[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    myWriteConvert(test_src5, result_dst5);
    compare_arrays(expected_dst5, result_dst5, 8);
}

int main()
{
    test_myReadConvert();
    test_myWriteConvert();

    printf("All tests passed.\n");

    return 0;
}
