# DummyDataGenerator

테스트용 Dummy 데이터 생성 Tool

## 구조

```
src/
├── generator/
│   ├── DummyDataGenerator.h
│   └── DummyDataGenerator.cpp
└── main.cpp
include/
└── nlohmann/json.hpp
data/
└── (생성된 JSON 파일 위치)
```

## 생성 데이터

| 파일 | 내용 |
|------|------|
| `samples.json` | 시료 10종 (ID, 이름, 평균생산시간, 수율, 재고) |
| `orders.json` | 주문 10건 (RESERVED / CONFIRMED / PRODUCING / RELEASE / REJECTED 혼합) |
| `production_queue.json` | 생산 큐 3건 |

## 빌드

**Visual Studio 2022**
`DummyDataGenerator.sln` 열기 → 빌드

**커맨드라인 (MSVC)**
```bat
cl /std:c++17 /EHsc /I include src/main.cpp src/generator/DummyDataGenerator.cpp /Fe:DummyDataGenerator.exe
```

## 실행

```
DummyDataGenerator.exe [data_directory] [--reset]
```

| 옵션 | 설명 |
|------|------|
| `data_directory` | 출력 디렉토리 (기본값: `data`) |
| `--reset` | 기존 데이터 초기화 후 재생성 |

```
=== DummyDataGenerator ===
경로  : data
모드  : --reset (기존 데이터 초기화)

[samples.json]          10건 추가 (총 10건)
[orders.json]           10건 추가 (총 10건)
[production_queue.json]  3건 추가 (총  3건)

완료.
```
