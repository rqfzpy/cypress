/*
 *  Cypress -- C++ Spiking Neural Network Simulation Framework
 *  Copyright (C) 2016  Andreas Stöckel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file tuning_curve.hpp
 *
 * Contains code for measuring the tuning curves of the neurons in a network.
 *
 * @author Andreas Stöckel
 */

#ifndef CYPRESS_NEF_TUNING_CURVE_HPP
#define CYPRESS_NEF_TUNING_CURVE_HPP

#include <vector>

#include <cypress/core/types.hpp>
#include <cypress/nef/delta_sigma.hpp>

namespace cypress {
namespace nef {

class TuningCurveEvaluator {
private:
	using Window = DeltaSigma::GaussWindow;

	size_t m_n_samples;
	size_t m_n_repeat;

	DeltaSigma::DiscreteWindow m_wnd;

	Real m_t_wnd;

	std::vector<Real> m_test_values;
	std::vector<Real> m_test_spike_train;

public:
	static constexpr size_t DEFAULT_N_SAMPLES = 100;
	static constexpr size_t DEFAULT_N_REPEAT = 10;

	TuningCurveEvaluator(
	    size_t n_samples = DEFAULT_N_SAMPLES,
	    size_t n_repeat = DEFAULT_N_REPEAT,
	    Real min_spike_interval = DeltaSigma::DEFAULT_MIN_SPIKE_INTERVAL,
	    Real response_time = DeltaSigma::DEFAULT_RESPONSE_TIME,
	    Real step = DeltaSigma::DEFAULT_STEP);

	const std::vector<Real> &input_spike_train() const
	{
		return m_test_spike_train;
	}

	std::vector<std::pair<Real, Real>> evaluate_output_spike_train(
	    std::vector<Real> output_spikes);

	Real input_spike_train_len() const
	{
		return m_t_wnd * m_test_values.size() * 1e3;
	}
};
}
}

#endif /* CYPRESS_NEF_TUNING_CURVE_HPP */

