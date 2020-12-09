#include "../gtest/gtest.h"
#include "MultiStack.h"


TEST(TMultiStack, can_create_MultiStack_with_positive_length)
{
	ASSERT_NO_THROW(TMultiStack<int> M(9, 3));
}

TEST(TMultiStack, throws_when_create_MultiStack_with_negative_length)
{
	ASSERT_ANY_THROW(TMultiStack<int> M(-5));
}

TEST(TMultiStack, can_copy_MultiStack)
{
	TMultiStack<int> M1(9, 3);
	M1.Push(10, 2);

	ASSERT_NO_THROW(TMultiStack<int> M2(M1));
}

TEST(TMultiStack, is_empty)
{
	TMultiStack<int> M(9, 3);

	EXPECT_EQ(true, M.IsEmpty(2));
}

TEST(TMultiStack, check_empty_MultiStack_with_negative_index)
{
	TMultiStack<int> M(9, 3);

	ASSERT_ANY_THROW(M.IsEmpty(-2));
}

TEST(TMultiStack, is_full)
{
	TMultiStack<int> M(9, 3);

	EXPECT_EQ(false, M.IsFull(2));
}

TEST(TMultiStack, check_full_MultiStack_with_negative_index)
{
	TMultiStack<int> M(9, 3);

	ASSERT_ANY_THROW(M.IsFull(-2));
}

TEST(TMultiStack, can_set_elem)
{
	TMultiStack<int> M(9, 3);

	ASSERT_NO_THROW(M.Push(10, 1));
}

TEST(TMultiStack, can_get)
{
	TMultiStack<int> M(9, 3);
	M.Push(10, 1);

	ASSERT_NO_THROW(M.Get(1));
}

TEST(TMultiStack, cant_get_negative)
{
	TMultiStack<int> M(9, 3);
	M.Push(10, 1);

	ASSERT_ANY_THROW(M.Get(-4));
}

TEST(TMultiStack, cant_get_nonexistent)
{
	TMultiStack<int> M(9, 3);
	M.Push(10, 1);

	ASSERT_ANY_THROW(M.Get(4));
}

TEST(TMultiStack, can_get_size)
{
	TMultiStack<int> M(9, 3);

	ASSERT_NO_THROW(M.GetSize());
}

TEST(TMultiStack, can_resize)
{
	TMultiStack<int> M(9, 3);

	ASSERT_NO_THROW(M.Resize(5, 0));
}

TEST(TMultiStack, can_StackRelocation)
{
	TMultiStack<int> M(9, 3);
	M.Push(11, 0);
	M.Push(12, 1);
	M.Push(12, 1);

	ASSERT_NO_THROW(M.Push(15, 1));
}