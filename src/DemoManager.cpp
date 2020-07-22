#include "DemoManager.h"

DemoManager* DemoManager::pinstance_{ nullptr };
std::mutex DemoManager::mutex_;