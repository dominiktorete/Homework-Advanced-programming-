#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};

class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("TestList") {
    SECTION("PushBack") {
        INFO("Test PushBack operation");
        List ls;
        CHECK(ls.Size() == 0);
        ls.PushBack(10);
        CHECK(ls.Size() == 1);
        ls.PushBack(11);
        CHECK(ls.Size() == 2);
        CHECK(ls.PopBack() == 11);
        INFO("This test(PushBack) must fail");
        CHECK(ls.Size() == 0);
    }
    SECTION("PushFront") {
        INFO("Test PushFront operation");
        List ls;
        CHECK(ls.Size() == 0);
        ls.PushFront(10);
        CHECK(ls.Size() == 1);
        ls.PushFront(11);
        CHECK(ls.Size() == 2);
        CHECK(ls.PopFront() == 11);
        INFO("This test(PushFront) must fail");
        CHECK(ls.Size() == 0);
    }
    SECTION("PopBack") {
        INFO("Test PopBack operation");
        List ls;
        CHECK_THROWS_AS(ls.PopBack(), std::runtime_error);

        ls.PushFront(10);
        CHECK(ls.Size() == 1);
        ls.PushFront(11);
        CHECK(ls.Size() == 2);
        CHECK(ls.PopBack() == 10);
        CHECK(ls.Size() == 1);
        INFO("This test(PopBack) must fail");
        CHECK(ls.Size() == 0);
    }
    SECTION("PopFront") {
        INFO("Test PopFront operation");
        List ls;
        CHECK_THROWS_AS(ls.PopFront(), std::runtime_error);
        ls.PushFront(10);
        CHECK(ls.Size() == 1);
        ls.PushFront(11);
        CHECK(ls.Size() == 2);
        CHECK(ls.PopFront() == 11);
        CHECK(ls.Size() == 1);
        INFO("This test(PopFront) must fail");
        CHECK(ls.Size() == 0);

    }
}

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}
