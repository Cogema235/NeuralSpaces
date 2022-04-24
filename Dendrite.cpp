#include "Source.cpp"

class Dendrite : public Source
{
private:
    Source* source = nullptr;
    float weight;

public:
    Dendrite() = default;

    Dendrite(float weights)
    {
        weight = weights;
    }

    void setWeight(float sweight)
    {
        weight = sweight;
    }

    void setSource(Source* sources)
    {
        source = sources;
    }

    float getSignal(void)
    {
        if (source != nullptr)
        {
            //signal = source->getSignal() * weight;
            return source->getSignal() * weight; /////////////////////////////////////////////////////////
        }
        return 0;
    }

    bool isFree(void)
    {
        if (source != nullptr)
        {
            return false;
        }
        return true;
    }

    float getWeight(void)
    {
        return weight;
    }
};