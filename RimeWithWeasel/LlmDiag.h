#pragma once
#include <windows.h>
#include <WeaselUtility.h>
#include <atomic>
#include <cstdint>
#include <fstream>
#include <mutex>
#include <string>

inline std::atomic<bool>& LlmDiagEnabled() {
  static std::atomic<bool> enabled{false};
  return enabled;
}

// 只记序号、执行绪、阶段、数量。不得传入任何输入文字或上下文。
inline void LlmDiag(uint64_t seq, const char* stage, size_t n = 0) {
  if (!LlmDiagEnabled().load()) return;
  static std::mutex mtx;
  static std::ofstream out;
  static bool tried = false;
  std::lock_guard<std::mutex> lock(mtx);
  if (!tried) {
    tried = true;
    try {
      auto path = WeaselLogPath() /
          ("weasel-llm-diag." + std::to_string(GetCurrentProcessId()) + ".log");
      out.open(path, std::ios::app);
    } catch (...) {
    }
  }
  if (!out.is_open()) return;
  out << GetTickCount64() << " tid=" << GetCurrentThreadId()
      << " seq=" << seq << ' ' << stage << " n=" << n << '\n';
  out.flush();
}