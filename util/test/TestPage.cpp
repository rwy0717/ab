#include <Ab/Config.hpp>
#include <Ab/Page.hpp>
#include <gtest/gtest.h>

using namespace Ab;

TEST(TestPage, pageSize) {
	Process::init();
	EXPECT_NE(Page::size(), std::size_t{0});
	Process::kill();
}

TEST(TestPage, mapOnePage) {
	Process::init();
	auto size = Page::size();
	auto addr = Page::map(size);
	Page::unmap(addr, size);
	Process::kill();
}
