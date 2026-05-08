#pragma once
#include <string>
#include <nlohmann/json.hpp>

class DummyDataGenerator {
public:
    explicit DummyDataGenerator(const std::string& dataDir);

    void generate(bool reset = false);

private:
    std::string dataDir_;

    nlohmann::json makeSamples() const;
    nlohmann::json makeOrders() const;
    nlohmann::json makeProductionQueue() const;

    nlohmann::json loadOrEmpty(const std::string& filePath) const;
    void writeFile(const std::string& filePath, const nlohmann::json& data) const;
    std::string filePath(const std::string& filename) const;
};
