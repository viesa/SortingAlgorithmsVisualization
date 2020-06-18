#include "RadixSort.h"

void RadixSort::Sort()
{
    long h = HighestValue();
    for (size_t exp = 1; (size_t)(h / exp) > 0 && m_state != State::BeingCollected; exp *= 10)
        CountSort(exp);
}

void RadixSort::CountSort(size_t exponent)
{
    std::vector<Element> outBucket(GetContainer().size());
    std::array<size_t, 10> count = {0};

    // Store count of occurrences in count[]
    for (size_t i = 0; i < GetContainer().size() && m_state != State::BeingCollected; i++)
    {
        PauseCheck();
        count[(GetValue(i) / exponent) % 10]++;
    }

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (size_t i = 1; i < 10 && m_state != State::BeingCollected; i++)
    {
        PauseCheck();
        count[i] += count[i - 1];
    }

    // Build the output array
    for (long i = static_cast<long>(GetContainer().size() - 1); i >= 0 && m_state != State::BeingCollected; i--)
    {
        PauseCheck();
        outBucket[count[(GetValue(i) / exponent) % 10] - 1] = GetElement(i);
        count[(GetValue(i) / exponent) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (size_t i = 0; i < GetContainer().size() && m_state != State::BeingCollected; i++)
    {
        SetColor(i, sf::Color::Red);
        SleepDelay();
        SleepDelay();
        SleepDelay();
        PauseCheck();
        SetValue(i, outBucket[i].value);
        SetColor(i, sf::Color::White);
    }

    if (m_state != State::BeingCollected)
        GetContainer() = outBucket;
}

long RadixSort::HighestValue()
{
    return std::max_element(GetContainer().begin(), GetContainer().end(), [](const Element &first, const Element &second) {
               return first.value < second.value;
           })
        ->value;
}