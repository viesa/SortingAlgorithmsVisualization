#pragma once

#include <SFML/Graphics.hpp>

#include <Saffron.h>

#include "Element.h"

namespace Se
{
struct ContainerRefGroup;

class Algorithm
{
public:
	enum class VisType
	{
		Bars,
		NumberLine,
		Circles,
		Hoops,
		Line,
		ScatterPlot,
		Image
	};

	enum class State
	{
		Sorting,
		WaitingForStart,
		Paused,
		Finished,
		BeingCollected
	};

	enum class Palette
	{
		Rainbow,
		Fiery,
		UV
	};

	enum class NumberGeneratorType
	{
		Linear,
		Quadratic,
		Random
	};

private:
	struct TransitionColor
	{
		float r;
		float g;
		float b;
		float a;
	};

public:
	explicit Algorithm(String name);

	virtual ~Algorithm() = default;

	void OnUpdate();

	void Draw(Scene& scene, const sf::FloatRect& rect);
	void DrawName(Scene& scene, const sf::FloatRect& rect);

	void Activate();
	void Deactivate();
	auto Active() const -> bool;

	void Start();
	void Restart();
	void Pause();
	void Resume();
	void Reset();

	void Resize(size_t size);
	void SoftResize(size_t size);

	void SetImage(const String& filepath);

	void Shuffle(Random::Engine generator);

	auto Name() const -> const String&;

	void SetSleepDelay(sf::Time delay);
	void SetVisType(VisType visType);
	void SetNumberGeneratorType(NumberGeneratorType numberGeneratorType);

	void UsePalette(bool use);
	void SetPalette(Palette palette);
	auto PaletteImage() -> const sf::Image&;

	auto Elements() -> List<Element>&;
	auto RestartElements() -> List<Element>&;
	auto ResetElements() -> List<Element>&;

protected:
	virtual void Sort() = 0;

	auto ElementByIndex(size_t index) -> Element&;
	auto ValueByIndex(size_t index) -> long;

	void SetValue(Element& element, long value);
	void SetValue(size_t index, long value);
	void SetColor(Element& element, const sf::Color& color);
	void SetColor(size_t index, const sf::Color& color);

	void SwapElements(Element& first, Element& second);
	void SwapElements(size_t iFirst, size_t iSecond);

	void PauseCheck();
	void SleepDelay();

private:
	auto Generator() -> Function<long(size_t)>;
	auto HighestElementValue() -> long;

	auto PixelCoord(size_t index) const -> sf::Vector2u;
	auto ScaledPixel(size_t index, size_t max) const -> sf::FloatRect;
	auto ClosestPixelCoord(size_t index, size_t max) const -> sf::Vector2u;

	// Calls overridden Sort() and later OnFinish() upon finish
	void SortThreadFn();
	void OnFinish();
	void CollectSorter();

	void DrawBars(Scene& scene, const sf::FloatRect& rect);
	void DrawNumberLine(Scene& scene, const sf::FloatRect& rect);
	void DrawCircles(Scene& scene, const sf::FloatRect& rect);
	void DrawHoops(Scene& scene, const sf::FloatRect& rect);
	void DrawLine(Scene& scene, const sf::FloatRect& rect);
	void DrawScatterPlot(Scene& scene, const sf::FloatRect& rect);
	void DrawImage(Scene& scene, const sf::FloatRect& rect);

	// Used as a wrapper to check if drawing in spectrum mode or not
	auto ElementColorByIndex(size_t index) -> sf::Color;

	auto VerifyElements() -> bool;

protected:
	String _name;

	Thread _sorter;

	Shared<sf::Image> _image;
	sf::RenderTexture _imageRenderTexture;

	sf::Time _sleepDelay;
	bool _minorDelay;
	sf::Int64 _minorDelayTimer;

	State _state;
	bool _isActive;

	Shared<sf::Font> _nameTextFont;
	sf::Text _nameText;
	VisType _visType;

private:
	static constexpr int MaxElements = 10000;
	static constexpr int PaletteWidth = 2048;

	List<Element> _elements;
	List<Element> _elementsRestart;
	List<Element> _elementsReset;

	NumberGeneratorType _numberGeneratorType = NumberGeneratorType::Linear;

	// Shapes cache
	sf::VertexArray _barsVA;
	List<sf::CircleShape> _hoopsShapes;
	sf::VertexArray _numberLineVA;
	List<sf::Text> _numberLineTextList;

	// Palette
	sf::Texture _paletteTexture;
	Palette _desiredPalette = Palette::Rainbow;
	sf::Image _currentPalette;
	Array<TransitionColor, PaletteWidth> _colorsStart;
	Array<TransitionColor, PaletteWidth> _colorsCurrent;
	float _colorTransitionTimer;
	float _colorTransitionDuration;
	List<Shared<sf::Image>> _palettes;
	bool _usePalette = false;
};
}
