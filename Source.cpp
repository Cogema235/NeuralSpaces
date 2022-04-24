class Source
{
protected:
    float signal = 0;
    
public:
    Source() = default;

    Source(float value)
    {
        signal = value;
    }

    void setSignal(float signals)
    {
        signal = signals;
    }

    virtual float getSignal(void)
    {
        return signal;
    }
};