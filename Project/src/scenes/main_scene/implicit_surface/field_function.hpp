#pragma once

#include "cgp/cgp.hpp"

// Parametric function defined as a sum of blobs-like primitives
//  f(p) = sa exp(-||p-pa||^2) + sb exp(-||p-pb||^2) + sc exp(-||p-pc||^2) + noise(p)
//   with noise: a Perlin noise
// The operator()(vec3 p) allows to query a value of the function at arbitrary point in space
struct field_function_structure {

	// Query the value of the function at any point p
	float operator()(cgp::vec3 const& p) const;


	// ***************************//
	// Parameters
	// ***************************//

	// The 3 center of the 3 blobs
	cgp::vec3 pa = {  1.0f, 0.0f, 0.0f};
	cgp::vec3 pb = { -1.0f, 0.0f, 0.0f };
	cgp::vec3 pc = {  0.0f, 0.5f, 0.0f };

	// The magnitude associated to each primitive
	float sa = 7.0f;
	float sb = 3.0f;
	float sc = 3.0f;

	// The parameters of the Perlin noise
	float noise_magnitude   = 0.2f; // Magnitude of the noise
	float noise_offset      = 0.0f; // An offset in the parametric domain (get a different value of noise with same parameters)
	float noise_scale       = 1.0f; // Scale in the parametric domain
	int noise_octave        = 5;    // Maximum number of octave
	float noise_persistance = 0.3f; // Persistence of Perlin noise
};

