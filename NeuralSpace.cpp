#include "utils.cpp"
#include "Source.cpp"
#include "Value.cpp"
#include "Neurons.cpp"

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
private:
    int neurons_number;
    int dendrites_per_neuron;
    int input_nodes_number;
    Value* input_nodes = nullptr;

public:
    NeuralNetwork() = default;

    NeuralNetwork(int neurones_number, int dendrites_per_neurons, int input_nodes_numbers)
    {
        neurons_number = neurones_number;
        dendrites_per_neuron = dendrites_per_neurons;

        neurons = new Neuron[neurons_number];

        for (int i = 0; i < neurons_number; i++)
        {
            neurons[i] = Neuron(dendrites_per_neuron);
        }

        input_nodes_number = input_nodes_numbers;
        input_nodes = new Value[input_nodes_number];
        
        for (int i = 0; i < input_nodes_number; i++)
        {
            input_nodes[i] = Value(0);
        }
    }

    void setAnInputNodesSignal(int node_ord, float value)
    {
        input_nodes[node_ord].setSignal(value);
    }

    void connect(int na, int nb)
    {
        if (na == nb) {return;}
        neurons[na].connectTo(&neurons[nb]);
    }

    void connectSource(Source* source, int na) //utilité discutable, debordeliser plus tard.
    {
        neurons[na].connectTo(source);
    }

    int connectNeuronToInputNode(int neuron_ord, int input_node_ord)
    {
        return neurons[neuron_ord].connectTo(&input_nodes[input_node_ord]);
    }

    void mute(float neuron_mutation_probability, float dendrite_mutation_probability, float dendrite_disconnection_probability, float dendrite_new_connection_probability, float weight_mutation_probability, float max_absolute_weight_increment, float increment_probability, float connection_to_input_node_probability)
    {
        for (int i = 0; i < neurons_number; i++) //connections a un neurone aleatoire dans tout l'espace et non de proche en proche (pas efficace, comming soon dans R³)
        {
            if (pileOuFace(neuron_mutation_probability))
            {
                for (int j = 0; j < dendrites_per_neuron; j++)
                {
                    if (pileOuFace(dendrite_mutation_probability))
                    {
                        if (pileOuFace(dendrite_disconnection_probability))
                        {
                            neurons[i].disconnect(j);
                        }
                        if (pileOuFace(dendrite_new_connection_probability))
                        {
                            if (pileOuFace(1.0f - connection_to_input_node_probability))
                            {
                                connect(i, randomInt(0, neurons_number - 1));
                            }
                            else 
                            {
                                neurons[i].connectTo(&input_nodes[randomInt(0, input_nodes_number - 1)]);
                            }
                        }
                        if (pileOuFace(weight_mutation_probability))
                        {
                            if (pileOuFace(increment_probability))
                            {
                                neurons[i].setAWeight(j, neurons[i].getAWeight(j) + randomFloat(0.0f, max_absolute_weight_increment));
                            }
                            else
                            {
                                neurons[i].setAWeight(j, neurons[i].getAWeight(j) - randomFloat(0.0f, max_absolute_weight_increment));
                            }
                        }
                    }
                }
            }
        }
    }
};
