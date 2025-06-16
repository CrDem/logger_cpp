# Metric Logger C++

## Overview

This is a lightweight and thread-safe C++ metrics logging app designed for collecting and logging runtime statistics such as CPU load, requests per second, or any other user-defined data points. It periodically aggregates metrics and writes them to a file with timestamps.

The system is modular and extensible, useful for diagnostics and embedding into larger systems.

## (RU) Обзор классов-компонентов и файлов

IMetric - Абстрактный интерфейс метрик.

Metric<T> - Шаблонная реализация метрик.
  - Используются атомарные переменные (std::atomic) для потокобезопасного накопления.
  - Поддержен подсчет среднего значения для плавающих типов и суммы для целочисленных.

MetricManager - Регистратор и контейнер метрик. Предоставляет доступ к зарегистрированным метрикам с потокобезопасной синхронизацией.

MetricLogger - Фоновый логгер, собирающий метрики с заданным интервалом и записывающий их в текстовый файл.
  - Запускается в отдельном потоке
  - Безопасно завершает логирование при остановке

main.cpp - Пример использования.
