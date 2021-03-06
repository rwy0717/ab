#include <Ab/Config.hpp>
#include <Ab/Span.hpp>
#include <gtest/gtest.h>

using namespace Ab;

int string[] = {1, 2, 3, 4};

TEST(TestSpan, defaultConstructor) {
	Span<int> s;
	EXPECT_EQ(s.value(), nullptr);
	EXPECT_EQ(s.length(), 0u);
	EXPECT_EQ(s.size(), 0u);
}

TEST(TestSpan, valueConstructor) {
	Span<int> s{string};
	EXPECT_EQ(s.value(), string);
	EXPECT_EQ(s.length(), 0u);
	EXPECT_EQ(s.size(), 0u);
}

TEST(TestSpan, lengthConstructor) {
	Span<int> s{string, sizeof(string)};
	EXPECT_EQ(s.value(), string);
	EXPECT_EQ(s.length(), sizeof(string));
	EXPECT_EQ(s.size(), sizeof(string) * sizeof(int));
}

TEST(TestSpan, fullConstructor) {
	Span<int> s{string, sizeof(string)};
	EXPECT_EQ(s.value(), string);
	EXPECT_EQ(s.length(), sizeof(string));
	EXPECT_EQ(s.size(), sizeof(string) * sizeof(int));
}

TEST(TestSpan, assignAndCompare) {
	Span<int> a{nullptr, 1};
	Span<int> b{string, sizeof(string)};
	EXPECT_NE(a, b);
	a = b;
	EXPECT_EQ(a, b);
}

TEST(TestSpan, compare) {
}
