#pragma once

#include <string>

static class CommonData {
public:
	enum class InitializationMethod {
		GRID,
		RANDOM
	};

	enum class AlgorithmMethod {
		BRUTE_FORCE,
		OCTREE
	};

	static float FrameRate;
	static int CubeNumber;
	static InitializationMethod InitMethod;
	static AlgorithmMethod AlgoMethod;

	static std::string InitMethodToString() {
		switch (InitMethod)
		{
		case CommonData::InitializationMethod::GRID:
			return "GRID";
			break;
		case CommonData::InitializationMethod::RANDOM:
			return "RANDOM";
			break;
		default:
			break;
		}
	}

	static std::string AlgorithmMethodToString() {
		switch (AlgoMethod)
		{
		case CommonData::AlgorithmMethod::BRUTE_FORCE:
			return "BRUTE_FORCE";
			break;
		case CommonData::AlgorithmMethod::OCTREE:
			return "OCTREE";
			break;
		default:
			break;
		}
	}

};