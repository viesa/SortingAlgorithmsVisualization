#pragma once

#include <set>
#include <numeric>

#include "Window.h"
#include "Random.h"

// ----- Algorithms -----
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "GnomeSort.h"
#include "RadixSort.h"
// ----------------------

class AlgorithmMgr
{
public:
    AlgorithmMgr();
    ~AlgorithmMgr();
    AlgorithmMgr(const AlgorithmMgr &) = delete;
    const AlgorithmMgr &operator()(const AlgorithmMgr &) = delete;

    void Draw();

    void Add(IAlgorithm *algorithm);

    void Activate(const std::string &name);
    void Deactivate(const std::string &name);

    void ActivateSpectrum() noexcept;
    void DeactivateSpectrum() noexcept;

    void Start();
    void Restart();
    void Pause();
    void Resume();
    void Reset();

    void Resize(size_t size);
    void PopPushUntil(size_t size);
    void Shuffle();

    IAlgorithm::VisType GetVisType() const noexcept { return m_visType; }

    void SetSleepDelay(sf::Time seconds);
    void SetVisType(IAlgorithm::VisType visType);

    const std::vector<IAlgorithm *> &GetAlgorithms() const noexcept { return m_algorithms; }

private:
    void GenerateDrawContainers();
    int GetActiveContainers();

private:
    std::vector<IAlgorithm *> m_algorithms;
    std::vector<sf::FloatRect> m_drawContainers;
    std::vector<Element> m_currentElements;

    // A cache used for getter
    IAlgorithm::VisType m_visType;
};