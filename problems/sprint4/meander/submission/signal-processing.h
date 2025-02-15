#pragma once
#include <QtCore/qlogging.h>
#include <cassert>
#include <cstdint>
#include <numbers>
#include <vector>

enum class SignalType {
    kSin,
    kCos,
    kMeander
};

struct SignalData {
    SignalType signal_type; // Тип сигнала.
    int samples;            // Длина сигнала.
    int wave_length;        // Длина волны.
    int16_t amplitude;      // Максимальное значение.
    double cycle;           // Скважность меандра.
};

inline void ReplicateSignal(std::vector<int16_t>& signal, size_t desired_length) {
    assert(signal.size() > 0);

    signal.reserve(desired_length);

    size_t wave_length = signal.size();
    while (signal.size() < desired_length) {
        size_t max_insert = desired_length - signal.size();
        size_t to_insert = std::min(wave_length, max_insert);

        std::copy_n(signal.begin(), to_insert, std::back_inserter(signal));
    }
}

inline std::vector<int16_t> GenerateSignal(SignalData data) {
    std::vector<int16_t> signal(data.wave_length);

    switch (data.signal_type) {
    case SignalType::kSin:
        std::generate_n(signal.begin(), data.wave_length, [&, i = 0]() mutable {
            return data.amplitude * std::sin(i++ * 2 * std::numbers::pi / data.wave_length);
        });
        break;
    case SignalType::kCos:
        std::generate_n(signal.begin(), data.wave_length, [&, i = 0]() mutable {
            return data.amplitude * std::cos(i++ * 2 * std::numbers::pi / data.wave_length);
        });
        break;
    case SignalType::kMeander: {
        int positive_samples = static_cast<int>(data.cycle * data.wave_length);
        std::fill_n(signal.begin(), positive_samples, data.amplitude);
        std::fill_n(signal.begin() + positive_samples, data.wave_length - positive_samples, -data.amplitude);
        break;
    }
    }
    ReplicateSignal(signal, data.samples);
    return signal;
}

inline void applyAttacka(std::vector<int16_t>& signal, size_t max_length) {
    const size_t attack_length = std::min(signal.size(), max_length);

    for(size_t i = 0; i < attack_length; ++i) {
        int16_t& sample = signal[i];
        const double factor = static_cast<double>(i) / static_cast<double>(attack_length);
        sample = static_cast<int16_t>(sample * factor);
    }
}

inline void ApplyDecayAndAttack(std::vector<int16_t>& signal, size_t max_length) {
    const size_t decay_length = std::min(signal.size(), max_length);

    auto decay_transformer = [=, i = decay_length](int16_t source) mutable {
        double factor = double(i--) / decay_length;
        return static_cast<int16_t>(source * factor);
    };

    auto start_pos = signal.end() - decay_length;
    std::transform(start_pos, signal.end(), start_pos, decay_transformer);

    const size_t attack_length = std::min(signal.size(), max_length);

    auto attack_transformer = [=, i = 0](int16_t source) mutable {
        double factor = double(i++) / attack_length;
        return static_cast<int16_t>(source * factor);
    };

    std::transform(signal.begin(), signal.begin() + attack_length, signal.begin(), attack_transformer);
}
