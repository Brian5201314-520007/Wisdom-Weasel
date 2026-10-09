# Wisdom-Weasel v0.1.0 覆蓋版　安裝教學

> **早期測試版**：作者目前沒有第二台電腦可做乾淨環境實測，本版由早期使用者先行試用。請務必先備份（第 2 步與第 5 步），遇到問題請到 Issues 回報。

## 這是什麼
- 基於上游「小狼毫（Weasel）0.17.4」的修改版，加入以大型語言模型為基礎的候選詞預測。
- **本包不是安裝程式。** 必須先安裝上游小狼毫 0.17.4，再把本包的 13 個檔案複製到它的程式資料夾，覆蓋同名檔案。
- 這是**純 CPU 版**，沒有 GPU 加速。LLM 功能**預設關閉**，需要自行設定。

## 適合誰
已使用過小狼毫、能以系統管理員身分操作檔案總管、會編輯 YAML 設定檔的人。只想雙擊安裝的人，目前不適合。

## 你會用到的檔案（都在 Release 頁面）
1. `weasel-0.17.4.0-installer.exe`：上游原版安裝程式，未經修改。
2. `Wisdom-Weasel-v0.1.0-overlay-cpu-x64.zip`：本覆蓋包。
3. `SHA256SUMS.txt`：以上兩個檔案的雜湊值，用來核對下載是否完整。在 PowerShell 執行 `Get-FileHash 檔名 -Algorithm SHA256`，結果與檔內相同即可。

## 步驟
### 1. 準備
- Windows 8.1 至 Windows 11（上游支援範圍），64 位元。
- 安裝「Microsoft Visual C++ 2015-2022 Redistributable (x64)」，建議使用微軟官方最新版。已安裝可略過。

### 2. 備份（請不要省略）
複製整個 `%AppData%\Rime` 資料夾到安全的地方。在檔案總管網址列輸入 `%AppData%` 即可找到 Rime 資料夾。

### 3. 安裝上游小狼毫 0.17.4
1. 執行 `weasel-0.17.4.0-installer.exe`。
2. 初次安裝會出現「安裝選項」。若使用臺灣鍵盤配置，請在「輸入語言」選擇「中文（臺灣）」，再按「安裝」。
3. 安裝完成後，若輸入法沒有出現在指示器，請登出再登入，或重新開機。

### 4. 先確認上游能正常使用
切換到小狼毫（指示器上的【中】），在記事本打幾個字。上游不能用的話，不要繼續往下做。

### 5. 找到程式資料夾並備份
1. 在工作列右下角的小狼毫圖示按右鍵，選「程序文件夾 (&P)」（簡體介面為「程序文件夹」）。會開啟一個檔案總管視窗，**先不要關閉**。
2. 若該選項沒有反應，改在工作管理員找到 `WeaselServer.exe`，按右鍵選「開啟檔案位置」。
3. 把這個資料夾整個複製一份到別處（例如桌面），作為還原用備份。

### 6. 結束輸入法服務
在小狼毫圖示按右鍵，選「退出 (&Q)」。到工作管理員確認已經沒有 `WeaselServer.exe`。檔案使用中時無法覆蓋。

### 7. 覆蓋檔案
1. 解壓縮本覆蓋包。
2. 把以下 13 個檔案複製到第 5 步開啟的程式資料夾，選擇「取代目的地的檔案」：
   `WeaselServer.exe`、`llama.dll`、`ggml.dll`、`ggml-base.dll`、八個 `ggml-cpu-*.dll`（alderlake、haswell、icelake、ivybridge、sandybridge、skylakex、sse42、x64）、`libomp140.x86_64.dll`。
3. 若程式資料夾位於 Program Files 底下，複製時需要系統管理員權限，出現提示請按「繼續」。
4. 不要刪除資料夾裡的其他檔案。

### 8. 啟動並重新部署
1. 在程式資料夾按兩下 `WeaselServer.exe`。
2. 在圖示按右鍵，選「重新部署 (&R)」，等待完成。
3. 在記事本測試能否正常打字。能的話就完成了。上游安裝程式會設定開機自動啟動 WeaselServer，之後不需要手動啟動。

### 9. 啟用 LLM（選做，預設關閉）
1. 在圖示按右鍵，選「用戶文件夾 (&C)」，開啟 `%AppData%\Rime`。
2. 新增或編輯 `weasel.custom.yaml`（純文字，UTF-8）。以 OpenAI 相容 API 為例：

```
patch:
  llm/enabled: true
  llm/provider_type: openai
  llm/openai/api_url: "https://api.openai.com/v1/chat/completions"
  llm/openai/api_key: "你的金鑰"
  llm/openai/model: "gpt-3.5-turbo"
  llm/openai/max_tokens: 20
  llm/openai/temperature: "0.6"
```

3. 存檔後，在圖示按右鍵選「重新部署 (&R)」。

補充：
- 本地模型（llama.cpp）：把 `provider_type` 改為 `llamacpp`，並設定 `llm/llamacpp/model_path`（例如 `"D:/models/your_model.gguf"`，路徑用正斜線）。其他欄位與 hf_constraint 後端，請見專案 README 的「LLM 配置說明」。
- 專案 README 寫設定放在 `weasel.yaml`；本教學改用 `weasel.custom.yaml`（Rime 慣用的 patch 方式）。若設定沒有生效，請回報。
- **API 金鑰以純文字存在設定檔，請勿把這個檔案貼到網路上。**

### 10. 開發者主控台（除錯用，預設關閉）
在 `weasel.custom.yaml` 的 `patch:` 之下加入 `dev_console/enabled: true`，重新部署。啟用後主控台會顯示編輯中的拼音與 HTTP 內容，處理敏感內容時請勿啟用。

## 還原
1. 在圖示按右鍵，選「退出 (&Q)」。
2. 把第 5 步備份的程式資料夾內容複製回原位，取代同名檔案。
3. 需要的話，把第 2 步備份的 Rime 資料夾還原。
4. 按兩下 `WeaselServer.exe` 重新啟動。

## 已知限制與未驗證項目
- 本版尚未在乾淨環境完整實測，覆蓋後的相容性依靜態檢查推論。
- 內建更新檢查（WinSparkle）啟動時是否連網、是否寫入 `HKCU\Software\Rime\Weasel\Updates`，未做執行期驗證。
- 純 CPU 版，無 GPU 加速。
- 啟用 DevConsole 時會輸出編輯中拼音、HTTP 請求與回應，並顯示 API key 前 8 個字元（金鑰 8 字元以下時完整顯示）。
- exe 版本資源內嵌的提交雜湊（64ba2fd）早於本版提交（ea52d4e）；原始碼內容與二進位一致。
- 版本字串沿用上游 0.17.4，與 tag v0.1.0 不同源。
- DevConsole.cpp 中部分註解仍描述舊的「預設啟用」行為，將於下一版修正。

## 回報問題
請到 https://github.com/Brian5201314-520007/Wisdom-Weasel/issues 開新的 Issue，並附上：
- Windows 版本，以及是否已安裝 VC++ 執行庫。
- 做到第幾步出問題，以及畫面或錯誤訊息的截圖。
- 圖示右鍵「日誌文件夾 (&L)」中最新的日誌檔。**貼出前請檢查內容沒有 API 金鑰或私人資料。**

## 授權與來源
- 本專案採 GPLv3。原始碼：https://github.com/Brian5201314-520007/Wisdom-Weasel （tag v0.1.0）。
- 基於 scukeqi/Wisdom-Weasel（LLM 預測功能原作者）與上游 rime/weasel 0.17.4（原始碼 https://github.com/rime/weasel/tree/0.17.4 ）。
- 第三方元件見 `THIRD-PARTY-NOTICES.txt`（llama.cpp，MIT 授權）。