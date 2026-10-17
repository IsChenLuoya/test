# 单片机学习工程

## 目录结构

- `C51/` —— Keil C51 入门例程（LED、流水灯、按键控制等 8 个工程）
- `STM32/LED/` —— STM32F103C8 的 CubeMX + Keil MDK 工程（LED 点灯）

## 打开工程

- C51：用 Keil uVision 打开各目录下的 `*.uvproj`
- STM32：用 Keil uVision 打开 `STM32/LED/MDK-ARM/LED.uvprojx`

构建输出（`Objects/`、`Listings/`、`MDK-ARM/LED/`）已在 `.gitignore` 中排除，克隆后重新编译即可生成。
