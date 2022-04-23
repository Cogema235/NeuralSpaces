
class Source
{
protected:
    float signal;

public:
    Source()
    {
    }

    void setSignal(float signals)
    {
        signal = signals;
    }
    float getSignal(void)
    {
        return signal;
    }
};

class Value : public Source
{
public:
    Value() = default;

    Value(float value)
    {
        signal = value;
    }
    ~Value(void)
    {
    }
};

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
            signal = source->getSignal() * weight;
            return signal;
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
};

class Neuron : public Source
{
private:
    int dendrites_number;
    Dendrite* dendrites = nullptr;
    int* connected_dendrites = nullptr;

public:

    Neuron() = default;

    Neuron(int dendrites_numbers)
    {
        dendrites_number = dendrites_numbers;
        dendrites = new Dendrite[dendrites_number];
        connected_dendrites = new int[dendrites_number];

        for(int i = 0; i < dendrites_number; i++)
        {
            dendrites[i] = Dendrite(0);
        }
        signal = 0;
    }

    float getSignal(void)
    {
        float sum = 0;
        for(int i = 0; i < dendrites_number; i++)
        {
            sum += dendrites[i].getSignal();
        }
        signal = sum;
        return signal;
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
                connected_dendrites[i] = 1;
                return i;
            }
        }
        return -1;
    }

    void disconnect(int dendrite_ord)
    {
        if (dendrite_ord <= dendrites_number)
        {
            dendrites[dendrite_ord].setSource(nullptr);
        }

    }
};

class NeuralSpace
{
protected:
    int neurons_number;
    Neuron* neurons = nullptr;

public:
    NeuralSpace() = default;

    NeuralSpace(int neurons_number, int dendrites_per_neuron)
    {
        neurons = new Neuron[neurons_number];
        for (int i = 0; i < neurons_number; i++)
        {
            neurons[i] = Neuron(dendrites_per_neuron);
        }
    }

    void setAWeight(int neurone_ord, int dendrite_ord, float weight)
    {
        neurons[neurone_ord].setAWeight(dendrite_ord, weight);
    }
    
    float openTheBox(int neuron_ord)
    {
        return neurons[neuron_ord].getSignal();
    }
};

class NeuralNetwork : public NeuralSpace
{
public:
    NeuralNetwork(int neurones_number,int dendrites_per_neuron)
    {
        neurons_number = neurones_number;
        neurons = new Neuron[neurons_number];

        for (int i = 0; i < neurons_number; i++)
        {
            neurons[i] = Neuron(dendrites_per_neuron);
        }
    }

    void connect(int na, int nb)
    {
        neurons[na].connectTo(&neurons[nb]);
    }

    void connectSource(Source* source, int na)
    {
        neurons[na].connectTo(source);
    }
};
