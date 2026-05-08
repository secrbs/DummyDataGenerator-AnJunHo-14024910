#include "DummyDataGenerator.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

DummyDataGenerator::DummyDataGenerator(const std::string& dataDir)
    : dataDir_(dataDir) {}

void DummyDataGenerator::generate(bool reset) {
    fs::create_directories(dataDir_);

    auto samplesPath = filePath("samples.json");
    auto ordersPath  = filePath("orders.json");
    auto queuePath   = filePath("production_queue.json");

    nlohmann::json samples = reset ? nlohmann::json::array() : loadOrEmpty(samplesPath);
    nlohmann::json orders  = reset ? nlohmann::json::array() : loadOrEmpty(ordersPath);
    nlohmann::json queue   = reset ? nlohmann::json::array() : loadOrEmpty(queuePath);

    auto newSamples = makeSamples();
    auto newOrders  = makeOrders();
    auto newQueue   = makeProductionQueue();

    for (auto& s : newSamples) samples.push_back(s);
    for (auto& o : newOrders)  orders.push_back(o);
    for (auto& q : newQueue)   queue.push_back(q);

    writeFile(samplesPath, samples);
    writeFile(ordersPath,  orders);
    writeFile(queuePath,   queue);

    std::cout << "[samples.json]          " << newSamples.size() << "건 추가 (총 " << samples.size() << "건)\n";
    std::cout << "[orders.json]           " << newOrders.size()  << "건 추가 (총 " << orders.size()  << "건)\n";
    std::cout << "[production_queue.json] " << newQueue.size()   << "건 추가 (총 " << queue.size()   << "건)\n";
}

nlohmann::json DummyDataGenerator::makeSamples() const {
    return nlohmann::json::array({
        {{"id","S-001"},{"name","실리콘 웨이퍼-8인치"},  {"avgProductionTime",0.5},{"yield",0.92},{"stock",480}},
        {{"id","S-002"},{"name","GaN 에피택셜-4인치"},    {"avgProductionTime",0.3},{"yield",0.78},{"stock",220}},
        {{"id","S-003"},{"name","SiC 파워기판-6인치"},    {"avgProductionTime",0.8},{"yield",0.92},{"stock", 30}},
        {{"id","S-004"},{"name","포토레지스트-PR7"},       {"avgProductionTime",0.2},{"yield",0.95},{"stock",910}},
        {{"id","S-005"},{"name","산화막 웨이퍼-SiO2"},    {"avgProductionTime",0.6},{"yield",0.88},{"stock",  0}},
        {{"id","S-006"},{"name","질화막 기판-Si3N4"},     {"avgProductionTime",0.7},{"yield",0.85},{"stock",150}},
        {{"id","S-007"},{"name","게르마늄 웨이퍼-4인치"}, {"avgProductionTime",1.2},{"yield",0.70},{"stock", 60}},
        {{"id","S-008"},{"name","InP 에피택셜-2인치"},    {"avgProductionTime",1.5},{"yield",0.65},{"stock", 20}},
        {{"id","S-009"},{"name","다이아몬드 기판"},        {"avgProductionTime",2.0},{"yield",0.60},{"stock",  5}},
        {{"id","S-010"},{"name","사파이어 기판-2인치"},    {"avgProductionTime",0.9},{"yield",0.90},{"stock",300}},
    });
}

nlohmann::json DummyDataGenerator::makeOrders() const {
    return nlohmann::json::array({
        {{"orderId","ORD-20260501-0001"},{"sampleId","S-001"},{"customerName","삼성전자 파운드리"},{"quantity",200},{"status","RESERVED"},  {"createdAt","2026-05-01T09:00:00"}},
        {{"orderId","ORD-20260501-0002"},{"sampleId","S-002"},{"customerName","SK하이닉스"},      {"quantity",150},{"status","RESERVED"},  {"createdAt","2026-05-01T10:00:00"}},
        {{"orderId","ORD-20260502-0001"},{"sampleId","S-003"},{"customerName","LG이노텍"},        {"quantity",300},{"status","PRODUCING"}, {"createdAt","2026-05-02T09:00:00"}},
        {{"orderId","ORD-20260502-0002"},{"sampleId","S-004"},{"customerName","DB하이텍"},        {"quantity",400},{"status","CONFIRMED"}, {"createdAt","2026-05-02T11:00:00"}},
        {{"orderId","ORD-20260503-0001"},{"sampleId","S-001"},{"customerName","마이크론 코리아"}, {"quantity",100},{"status","CONFIRMED"}, {"createdAt","2026-05-03T08:00:00"}},
        {{"orderId","ORD-20260503-0002"},{"sampleId","S-005"},{"customerName","인텔 코리아"},     {"quantity",500},{"status","PRODUCING"}, {"createdAt","2026-05-03T14:00:00"}},
        {{"orderId","ORD-20260504-0001"},{"sampleId","S-002"},{"customerName","TSMC 코리아"},     {"quantity", 80},{"status","RELEASE"},   {"createdAt","2026-05-04T09:00:00"}},
        {{"orderId","ORD-20260504-0002"},{"sampleId","S-006"},{"customerName","르네사스"},        {"quantity",250},{"status","RELEASE"},   {"createdAt","2026-05-04T10:00:00"}},
        {{"orderId","ORD-20260505-0001"},{"sampleId","S-007"},{"customerName","TI 코리아"},       {"quantity", 50},{"status","REJECTED"},  {"createdAt","2026-05-05T09:00:00"}},
        {{"orderId","ORD-20260505-0002"},{"sampleId","S-003"},{"customerName","NXP 코리아"},      {"quantity",170},{"status","PRODUCING"}, {"createdAt","2026-05-05T11:00:00"}},
    });
}

nlohmann::json DummyDataGenerator::makeProductionQueue() const {
    return nlohmann::json::array({
        {{"orderId","ORD-20260502-0001"},{"sampleId","S-003"},{"shortage",270},{"actualProduction",326},{"totalTime",260.8},{"enqueuedAt","2026-05-02T09:30:00"}},
        {{"orderId","ORD-20260503-0002"},{"sampleId","S-005"},{"shortage",500},{"actualProduction",631},{"totalTime",378.6},{"enqueuedAt","2026-05-03T14:30:00"}},
        {{"orderId","ORD-20260505-0002"},{"sampleId","S-003"},{"shortage",140},{"actualProduction",169},{"totalTime",135.2},{"enqueuedAt","2026-05-05T11:30:00"}},
    });
}

nlohmann::json DummyDataGenerator::loadOrEmpty(const std::string& path) const {
    std::ifstream f(path);
    if (!f.is_open()) return nlohmann::json::array();
    try {
        nlohmann::json j;
        f >> j;
        return j;
    } catch (...) {
        return nlohmann::json::array();
    }
}

void DummyDataGenerator::writeFile(const std::string& path, const nlohmann::json& data) const {
    std::ofstream f(path);
    if (!f.is_open()) throw std::runtime_error("Cannot write: " + path);
    f << data.dump(2);
}

std::string DummyDataGenerator::filePath(const std::string& filename) const {
    return dataDir_ + "/" + filename;
}
