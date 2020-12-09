#include "Stack.h"
#include "../gtest/gtest.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> S_INT(5));
	ASSERT_NO_THROW(TStack<char> S_CHAR(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> S_INT(-5));
	ASSERT_ANY_THROW(TStack<char> S_CHAR(-5));
}

TEST(TStack, can_copy_stack)
{
	TStack<int> S1(2);
	S1.Push(1);

	ASSERT_NO_THROW(TStack<int> S2(S1));
}

TEST(TStack, can_set_elem)
{
	TStack<int> S(5);

	ASSERT_NO_THROW(S.Push(1));
}


TEST(TStack, Is_Full)
{

	TStack<int> S(4);

	S.Push(1);
	S.Push(2);
	S.Push(3);
	S.Push(4);

	ASSERT_NO_THROW();

}

TEST(TStack, IS_Empty)
{
	TStack<int> S(4);

	S.Push(1);
	S.Push(2);
	S.Push(3);
	S.Push(4);

	ASSERT_NO_THROW();
}


TEST(TStack, throws_when_set_stack_with_too_large_index)
{
	TStack<int> S(2);

	S.Push(1);
	S.Push(2);

	ASSERT_ANY_THROW(S.Push(3));

}

