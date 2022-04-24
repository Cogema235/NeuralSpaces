#include "Source.cpp"

class Value : public Source
{
public:
    Value() = default;

    Value(float value)
    {
        signal = value;
    }
};