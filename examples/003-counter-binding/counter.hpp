#ifndef LUACXX_EXAMPLE_COUNTER_HPP
#define LUACXX_EXAMPLE_COUNTER_HPP

class Counter
{
    int _value;

public:
    explicit Counter(int initial = 0) :
        _value(initial)
    {
    }

    void add(int amount)
    {
        _value += amount;
    }

    int get() const
    {
        return _value;
    }
};

#endif // LUACXX_EXAMPLE_COUNTER_HPP
