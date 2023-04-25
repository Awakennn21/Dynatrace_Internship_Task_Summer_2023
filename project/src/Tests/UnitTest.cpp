#include <gtest/gtest.h>
#include "../Task.h"

TEST(ExampleTest, TaskTest) 
{
    Task Solution("testData.json", 5);
    testing::internal::CaptureStdout();
    Solution.PrintData(5);
    std::string output = testing::internal::GetCapturedStdout();

    // Check that the output is as expected
    std::stringstream expected_output;
    expected_output <<"amazon-linux 2023 5\n"<<"amazon-eks 1.25 4\n"<<"amazon-corretto 20 3\n"<<"alpine 3.17 2\n"<< "almalinux 9 1\n";
    EXPECT_EQ(output, expected_output.str());

}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}