#include "utils.cpp"
#include "Dendrite.cpp"

class Neuron : public Source
{
private:
    int dendrites_number;
    Dendrite* dendrites = nullptr;

public:

    Neuron() = default;

    Neuron(int dendrites_numbers)
    {
        dendrites_number = dendrites_numbers;
        dendrites = new Dendrite[dendrites_number];
    
        for(int i = 0; i < dendrites_number; i++)
        {
            dendrites[i] = Dendrite(0);
        }
    }

    float getSignal(void)
    {
        float sum = 0;
        for(int i = 0; i < dendrites_number; i++)
        {
            sum += dendrites[i].getSignal();
        }
        return sum;
    }

    void setAWeight(int dendrite_ord, float weight)
    {
        dendrites[dendrite_ord].setWeight(weight);
    }

    int connectTo(Source* source)
    {
        for (int i = 0; i < dendrites_number; i++)
        {
            if (dendrites[i].isFree())
            {
                dendrites[i].setSource(source);
                return i;
            }
        }
        return -1;
    }

    float getAWeight(int dendrite_ord)
    {
        return dendrites[dendrite_ord].getWeight();
    }

    void disconnect(int dendrite_ord)
    {
        if (dendrite_ord <= dendrites_number)
        {
            dendrites[dendrite_ord].setSource(nullptr);
        }

    }
};